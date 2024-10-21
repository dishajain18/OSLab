#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority; // 0: RR, 1: SJF, 2: FCFS
    struct Process* next;
} Process;

typedef struct Queue {
    Process* front;
    Process* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Process* process) {
    if (!queue->rear) {
        queue->front = queue->rear = process;
    } else {
        queue->rear->next = process;
        queue->rear = process;
    }
    queue->rear->next = NULL;
}

Process* dequeue(Queue* queue) {
    if (!queue->front) return NULL;
    Process* temp = queue->front;
    queue->front = queue->front->next;
    if (!queue->front) queue->rear = NULL;
    return temp;
}

// Scheduling policies
void roundRobin(Queue* queue, int quantum, Queue* sjfQueue) {
    Process* current;
    while (queue->front) {
        current = dequeue(queue);
        if (current->remaining_time > quantum) {
            printf("Processing P%d in RR for %d seconds. Remaining time: %d\n", 
                   current->id, quantum, current->remaining_time - quantum);
            current->remaining_time -= quantum;
            current->priority = 1; // Update priority to 1 for SJF
            enqueue(sjfQueue, current); // Enqueue in SJF queue
        } else {
            printf("Processing P%d in RR for %d seconds (completed).\n", 
                   current->id, current->remaining_time);
            current->remaining_time = 0; // Process completed
            free(current); // Free completed process
            continue; // Skip to next iteration
        }

        // If not completed, shift to SJF queue and change priority
        
    }
}

void sjf(Queue* queue, int quantum, Queue* fcfsQueue) {
    // Sort processes based on remaining time
    Process* sorted = NULL;
    Process* current = queue->front;

    while (current) {
        Process* next = current->next;
        if (!sorted || sorted->remaining_time > current->remaining_time) {
            current->next = sorted;
            sorted = current;
        } else {
            Process* temp = sorted;
            while (temp->next && temp->next->remaining_time <= current->remaining_time) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    
    queue->front = sorted;
    queue->rear = NULL;

    // Now process the sorted queue
    Process* sjfCurrent;
    while (queue->front) {
        sjfCurrent = dequeue(queue);
        if (sjfCurrent->remaining_time > quantum) {
            printf("Processing P%d in SJF for %d seconds. Remaining time: %d\n", 
                   sjfCurrent->id, quantum, sjfCurrent->remaining_time - quantum);
            sjfCurrent->remaining_time -= quantum;
            sjfCurrent->priority = 2; // Update priority to 2 for FCFS
            enqueue(fcfsQueue, sjfCurrent); // Enqueue in FCFS queue
        } else {
            printf("Processing P%d in SJF for %d seconds (completed).\n", 
                   sjfCurrent->id, sjfCurrent->remaining_time);
            sjfCurrent->remaining_time = 0; // Process completed
            free(sjfCurrent); // Free completed process
            continue; // Skip to next iteration
        }

        // If not completed, shift to FCFS queue and change priority
        
    }
}

void fcfs(Queue* queue) {
    Process* current;
    while (queue->front) {
        current = dequeue(queue);
        printf("Processing P%d in FCFS for %d seconds (completed).\n", 
               current->id, current->remaining_time);
        current->remaining_time = 0; // Process completed
        free(current); // Free completed process
    }
}

// Main function
int main() {
    Queue* rrQueue = createQueue();
    Queue* sjfQueue = createQueue();
    Queue* fcfsQueue = createQueue();

    // Sample processes
    Process* p1 = (Process*)malloc(sizeof(Process));
    p1->id = 1; p1->arrival_time = 0; p1->burst_time = 10; p1->remaining_time = 10; p1->priority = 0; // RR
    Process* p2 = (Process*)malloc(sizeof(Process));
    p2->id = 2; p2->arrival_time = 2; p2->burst_time = 5; p2->remaining_time = 5; p2->priority = 0; // RR
    Process* p3 = (Process*)malloc(sizeof(Process));
    p3->id = 3; p3->arrival_time = 4; p3->burst_time = 8; p3->remaining_time = 8; p3->priority = 0; // RR

    // Enqueue processes to the RR queue
    enqueue(rrQueue, p1);
    enqueue(rrQueue, p2);
    enqueue(rrQueue, p3);
    
    printf("Round Robin Scheduling:\n");
    roundRobin(rrQueue, 2, sjfQueue); // Quantum = 2s for RR
    
    printf("\nSJF Scheduling:\n");
    sjf(sjfQueue, 4, fcfsQueue); // Quantum = 4s for SJF
    
    printf("\nFCFS Scheduling:\n");
    fcfs(fcfsQueue); // FCFS processing with no quantum
    
    // Free memory
    free(rrQueue);
    free(sjfQueue);
    free(fcfsQueue);
    
    return 0;
}
