#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int safe_sequence[MAX_PROCESSES];
int num_processes;
int num_resources;

bool is_safe_state()
{
    int work[MAX_RESOURCES];
    bool finish[num_processes];
    int i, j;

    // Initialize work and finish arrays
    for (i = 0; i < num_resources; i++)
        work[i] = available[i];

    for (i = 0; i < num_processes; i++)
        finish[i] = false;

    int count = 0;
    while (count < num_processes)
    {
        bool found = false;

        for (i = 0; i < num_processes; i++)
        {
            if (!finish[i])
            {
                bool can_allocate = true;
                for (j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate)
                {
                    for (j = 0; j < num_resources; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    safe_sequence[count] = i;
                    count++;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    return (count == num_processes);
}

int main()
{
    int i, j;

    // Input the number of processes and resources
    printf("No of processes: ");
    scanf("%d", &num_processes);

    printf("No of resources: ");
    scanf("%d", &num_resources);

    // Input the available resources
    printf("\nEnter the available resources:");
    for (i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    // Input the maximum claim for each process
    printf("\nEnter the maximum claim for each process:");
    for (i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++)
            scanf("%d", &maximum[i][j]);
    }

    // Input the allocation for each process
    printf("Enter allocation for each process:\n");
    for (i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);
    }

    // Calculate the need for each process
    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_resources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            if (need[i][j] < 0)
                need[i][j] = 0;
        }
    }

    // Check if the initial state is safe
    if (is_safe_state())
    {
        printf("The initial state is safe. Safe sequence: ");
        for (i = 0; i < num_processes; i++)
        {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("The initial state is unsafe. Program will exit.\n");
        return 0;
    }

    return 0;
}

