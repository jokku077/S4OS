#include <stdio.h>

#define MAX_PARTITIONS 10

struct Partition {
    int id;
    int size;
    int allocated;
};

struct Partition partitions[MAX_PARTITIONS];
int numPartitions = 0;

void initializePartitions();
void displayPartitions();
void firstFit(int processId, int processSize);
void worstFit(int processId, int processSize);
void bestFit(int processId, int processSize);

int main() {
    int choice;
    int processId, processSize;

    initializePartitions();

    do {
        printf("\n--- Memory Allocation Methods ---\n");
        printf("1. Display Partitions\n");
        printf("2. First Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Best Fit\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayPartitions();
                break;
            case 2:
                printf("Enter the process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                firstFit(processId, processSize);
                break;
            case 3:
                printf("Enter the process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                worstFit(processId, processSize);
                break;
            case 4:
                printf("Enter the process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                bestFit(processId, processSize);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void initializePartitions() {
    int i, partitionSize;
    printf("Enter the number of partitions: ");
    scanf("%d", &numPartitions);

    printf("Enter the size of each partition: \n");
    for (i = 0; i < numPartitions; i++) {
        printf("Partition %d: ", i + 1);
        scanf("%d", &partitionSize);
        partitions[i].id = i + 1;
        partitions[i].size = partitionSize;
        partitions[i].allocated = 0;
    }
}

void displayPartitions() {
    int i;
    printf("\n--- Partitions ---\n");
    printf("Partition\tSize\tAllocated\n");
    for (i = 0; i < numPartitions; i++) {
        printf("%d\t\t%d\t%s\n", partitions[i].id, partitions[i].size,
               partitions[i].allocated ? "Yes" : "No");
    }
}

void firstFit(int processId, int processSize) {
    int i;
    for (i = 0; i < numPartitions; i++) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            partitions[i].allocated = 1;
            printf("Process %d allocated to Partition %d\n", processId, partitions[i].id);
            return;
        }
    }
    printf("Process %d cannot be allocated. No suitable partition found.\n", processId);
}

void worstFit(int processId, int processSize) {
    int i, maxPartitionIndex = -1;
    int maxPartitionSize = -1;

    for (i = 0; i < numPartitions; i++) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            if (partitions[i].size > maxPartitionSize) {
                maxPartitionSize = partitions[i].size;
                maxPartitionIndex = i;
            }
        }
    }

    if (maxPartitionIndex != -1) {
        partitions[maxPartitionIndex].allocated = 1;
        printf("Process %d allocated to Partition %d\n", processId, partitions[maxPartitionIndex].id);
    } else {
        printf("Process %d cannot be allocated. No suitable partition found.\n", processId);
    }
}

void bestFit(int processId, int processSize) {
    int i, bestPartitionIndex = -1;
    int minPartitionSize = -1;

    for (i = 0; i < numPartitions; i++) {
        if (!partitions[i].allocated && partitions[i].size >= processSize) {
            if (partitions[i].size < minPartitionSize || minPartitionSize == -1) {
                minPartitionSize = partitions[i].size;
                bestPartitionIndex = i;
            }
        }
    }

    if (bestPartitionIndex != -1) {
        partitions[bestPartitionIndex].allocated = 1;
        printf("Process %d allocated to Partition %d\n", processId, partitions[bestPartitionIndex].id);
    } else {
        printf("Process %d cannot be allocated. No suitable partition found.\n", processId);
    }
}

