#include <stdio.h>

// Define the segment table structure
#define NUM_SEGMENTS 5

// Structure to represent a segment
struct Segment {
    int base;   // Base address of the segment
    int limit;  // Limit (size) of the segment
};

// Segment table storing base and limit for each segment
struct Segment segment_table[NUM_SEGMENTS] = {
    {1400, 1000},  
    {6300, 400},  
    {4300, 400},  
    {3200, 1100},  
    {4700, 1000}  
};

// Function to convert logical address to physical address
int logical_to_physical(int segment, int offset) {
    // Check if the segment number is valid
    if (segment < 0 || segment >= NUM_SEGMENTS) {
        printf("Error: Invalid segment number %d\n", segment);
        return -1;
    }

    // Check if the offset is within the segment's limit
    if (offset >= segment_table[segment].limit) {
        printf("Error: Offset %d is beyond the limit of segment %d\n", offset, segment);
        return -1;
    }

    // Convert logical address to physical address
    int physical_address = segment_table[segment].base + offset;
    return physical_address;
}

int main() {
    // Test cases provided in the problem

    // (i) 53 byte of segment 2
    int segment = 2;
    int offset = 53;
    int physical_address = logical_to_physical(segment, offset);
    if (physical_address != -1) {
        printf("Physical address of 53 byte in segment 2: %d\n", physical_address);
    }

    // (ii) 852 byte of segment 3
    segment = 3;
    offset = 852;
    physical_address = logical_to_physical(segment, offset);
    if (physical_address != -1) {
        printf("Physical address of 852 byte in segment 3: %d\n", physical_address);
    }

    // (iii) 1222 byte of segment 0
    segment = 0;
    offset = 1222;
    physical_address = logical_to_physical(segment, offset);
    if (physical_address != -1) {
        printf("Physical address of 1222 byte in segment 0: %d\n", physical_address);
    }

    return 0;
}