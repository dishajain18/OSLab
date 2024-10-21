#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct mab {
    int offset;
    int size;
    int allocated; // 1 if allocated, 0 if free
    struct mab *next;
    struct mab *prev;
};

typedef struct mab Mab;
typedef Mab* MabPtr;
MabPtr lastAllocated = NULL; //for next fit

// Function prototypes
MabPtr createBlock(int offset, int size, int allocated);
MabPtr createMemoryBlocks(int totalSize, int blockCount);
void displayMemory(MabPtr head);
MabPtr memChkFirstFit(MabPtr m, int size);
MabPtr memAllocFirstFit(MabPtr m, int size);
MabPtr memChkBestFit(MabPtr m, int size);
MabPtr memAllocBestFit(MabPtr m, int size);
MabPtr memChkWorstFit(MabPtr m, int size);
MabPtr memAllocWorstFit(MabPtr m, int size);
MabPtr memChkNextFit(MabPtr m, int size);
MabPtr memAllocNextFit(MabPtr m, int size);
MabPtr memFree(MabPtr m);
MabPtr memMerge(MabPtr m);
MabPtr memSplit(MabPtr m, int size);

int main() {
    srand(time(NULL)); // Seed for random number generation
    int totalMemorySize = 100; // Total size of memory
    int blockCount = 10; // Number of memory blocks

    // Create memory blocks
    MabPtr memory = createMemoryBlocks(totalMemorySize, blockCount);
    
    // Display the current status of memory
    displayMemory(memory);

    // Example of allocating memory using different strategies
    printf("\nFirst Fit for size:12\n");
    MabPtr allocatedFirst = memAllocFirstFit(memory, 12);
    if(allocatedFirst)
    printf("Allocated block: offset=%d, size=%d\n", allocatedFirst->offset, allocatedFirst->size);
    else
    printf("No such block\n");
    displayMemory(memory);

    printf("\nBest Fit for size:8\n");
    MabPtr allocatedBest = memAllocBestFit(memory, 8);
    if(allocatedBest)
    printf("Allocated block: offset=%d, size=%d\n", allocatedBest->offset, allocatedBest->size);
    else
    printf("No such block\n");
    displayMemory(memory);

    printf("\nWorst Fit for size:2\n");
    MabPtr allocatedWorst = memAllocWorstFit(memory, 2);
    if(allocatedWorst)
    printf("Allocated block: offset=%d, size=%d\n", allocatedWorst->offset, allocatedWorst->size);
    else
    printf("No such block\n");
    displayMemory(memory);

    lastAllocated=allocatedWorst;
    printf("\nNext Fit for size:5\n");
    MabPtr allocatedNext = memAllocNextFit(memory, 5);
    if(allocatedNext)
    printf("Allocated block: offset=%d, size=%d\n", allocatedNext->offset, allocatedNext->size);
    else
    printf("No such block\n");
    displayMemory(memory);

    // Free a block
    printf("Freed block at offset=%d\n", allocatedFirst->offset);
    memFree(allocatedFirst);
    displayMemory(memory);

    // Free allocated memory
    MabPtr current = memory;
    while (current != NULL) {
        MabPtr next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

// Function to create a new memory block
MabPtr createBlock(int offset, int size, int allocated) {
    MabPtr block = (MabPtr)malloc(sizeof(Mab));
    block->offset = offset;
    block->size = size;
    block->allocated = allocated;
    block->next = NULL;
    block->prev = NULL;
    return block;
}

// Function to create memory blocks with random sizes
MabPtr createMemoryBlocks(int totalSize, int blockCount) {
    MabPtr head = NULL;
    MabPtr current = NULL;
    int remainingSize = totalSize;

    for (int i = 0; i < blockCount; i++) {
        int size;
        if(i==(blockCount-1)) 
            size = remainingSize;
        else
            size = rand() % (remainingSize / (blockCount - i)) + 1; // Ensure enough size left
        int allocated = rand() % 2; // Randomly assign allocated (0 or 1)
        
        MabPtr block = createBlock((current ? current->offset + current->size : 0), size, allocated);
        
        if (head == NULL) {
            head = block; // Set head for the first block
        } else {
            current->next = block; // Link the previous block to the new one
            block->prev = current; // Link back to the previous block
            block->next = NULL;
        }
        
        current = block; // Move to the new block
        remainingSize -= size; // Decrease remaining size
    }

    return head; // Return the head of the linked list
}

// Function to display the current status of memory
void displayMemory(MabPtr head) {
    printf("Memory Status:\n");
    printf("Offset\tSize\tAllocated\n");
    printf("---------------------------\n");
    
    MabPtr current = head;
    while (current != NULL) {
        printf("%d\t%d\t%d\n", current->offset, current->size, current->allocated);
        current = current->next;
    }
}

// Function to check if memory is available (First Fit)
MabPtr memChkFirstFit(MabPtr head, int size) {
    MabPtr m = head;
    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            return m; // Found a suitable block
        }
        m = m->next;
    }
    return NULL; // No suitable block found
}

// Allocate a memory block (First Fit)
MabPtr memAllocFirstFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr block = memChkFirstFit(m, size);
    if (block) {
        if (block->size > size) {
            memSplit(block, size);
        }
        block->allocated = 1; // Mark as allocated
    }
    return block; // Return the allocated block or NULL
}

// Check for Best Fit
MabPtr memChkBestFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr bestFit = NULL;
    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            if (bestFit == NULL || m->size < bestFit->size) {
                bestFit = m; // Update best fit
            }
        }
        m = m->next;
    }
    return bestFit;
}

// Allocate a memory block (Best Fit)
MabPtr memAllocBestFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr block = memChkBestFit(m, size);
    if (block) {
        if (block->size > size) {
            memSplit(block, size);
        }
        block->allocated = 1; // Mark as allocated
    }
    return block; // Return the allocated block or NULL
}

// Check for Worst Fit
MabPtr memChkWorstFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr worstFit = NULL;
    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            if (worstFit == NULL || m->size > worstFit->size) {
                worstFit = m; // Update worst fit
            }
        }
        m = m->next;
    }
    return worstFit;
}

// Allocate a memory block (Worst Fit)
MabPtr memAllocWorstFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr block = memChkWorstFit(m, size);
    if (block) {
        if (block->size > size) {
            memSplit(block, size);
        }
        block->allocated = 1; // Mark as allocated
    }
    return block; // Return the allocated block or NULL
}


// Check for Next Fit
MabPtr memChkNextFit(MabPtr head, int size) {
    MabPtr m = head;
    if (!lastAllocated) lastAllocated = m; // Start from the beginning if no last allocated

    MabPtr start = lastAllocated;
    do {
        if (!lastAllocated->allocated && lastAllocated->size >= size) {
            return lastAllocated; // Found a suitable block
        }
        lastAllocated = lastAllocated->next ? lastAllocated->next : m; // Wrap around
    } while (lastAllocated != start);

    return NULL; // No suitable block found
}

// Allocate a memory block (Next Fit)
MabPtr memAllocNextFit(MabPtr head, int size) {
    MabPtr m = head;
    MabPtr block = memChkNextFit(m, size);
    if (block) {
        if (block->size > size) {
            memSplit(block, size);
        }
        block->allocated = 1; // Mark as allocated
    }
    return block; // Return the allocated block or NULL
}

// Free a memory block
MabPtr memFree(MabPtr m) {
    if (m) {
        m->allocated = 0; // Mark as free
        memMerge(m); // Try to merge with adjacent free blocks
    }
    return m;
}

// Merge two memory blocks
MabPtr memMerge(MabPtr m) {
    if (!m) return NULL;

    if (m->prev && !m->prev->allocated) {
        // Merge with previous block
        m->prev->size += m->size;
        m->prev->next = m->next;
        if (m->next) m->next->prev = m->prev;
        MabPtr temp = m->prev;
        free(m);
        m = temp; // Update m to the new merged block
    }

    if (m->next && !m->next->allocated) {
        // Merge with next block
        m->size += m->next->size;
        MabPtr temp = m->next;
        m->next = temp->next;
        if (temp->next) temp->next->prev = m;
        free(temp);
    }

    return m;
}

// Split a memory block
MabPtr memSplit(MabPtr m, int size) {
    if (!m || m->size <= size) return NULL;

    MabPtr newBlock = createBlock(m->offset + size, m->size - size, 0);
    newBlock->next = m->next;
    newBlock->prev = m;

    if (m->next) {
        m->next->prev = newBlock;
    }

    m->next = newBlock;
    m->size = size; // Resize the current block
    return newBlock;
}
