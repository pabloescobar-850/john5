//5. Deadlock avoidance (CO4)
//Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

#include <stdio.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

int main(void)
{
    int allocation[P][R];  // Resources allocated to each process
    int max[P][R];         // Maximum resources required
    int need[P][R];        // Remaining resources needed
    int available[R];      // Currently available resources
    int work[R];           // Resources available during safety check
    int finish[P] = {0};   // 0 = Not finished, 1 = Finished
    int safeSeq[P];        // Stores safe sequence
    int completed = 0;     // Counts completed processes

    // Step 1: Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", P, R);

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (scanf("%d", &allocation[i][j]) != 1 ||
                allocation[i][j] < 0)
            {
                printf("Invalid Allocation Matrix.\n");
                return 1;
            }
        }
    }

    // Step 2: Input Max Matrix
    printf("Enter Max Matrix (%d x %d):\n", P, R);

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (scanf("%d", &max[i][j]) != 1 ||
                max[i][j] < allocation[i][j])
            {
                printf("Invalid input: Max must be >= Allocation.\n");
                return 1;
            }

            // Calculate remaining need
            // Need = Max - Allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Step 3: Input Available Resources
    printf("Enter Available Resources (%d values):\n", R);

    for (int j = 0; j < R; j++)
    {
        if (scanf("%d", &available[j]) != 1 ||
            available[j] < 0)
        {
            printf("Invalid Available Resources.\n");
            return 1;
        }

        // Copy available resources into work
        work[j] = available[j];
    }

    // Step 4: Display Available Resources
    printf("\nInitial Available Resources: ");

    for (int j = 0; j < R; j++)
    {
        printf("%d ", available[j]);
    }

    printf("\n");

    // Step 5: Display Initial Work
    printf("Initial Work: ");

    for (int j = 0; j < R; j++)
    {
        printf("%d ", work[j]);
    }

    printf("\n");

    // Step 6: Display Need Matrix
    printf("\nNeed Matrix:\n");

    for (int i = 0; i < P; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < R; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // Step 7: Banker's Safety Algorithm
    printf("\n--- Safety Algorithm Execution ---\n");

    // Continue until all processes finish
    while (completed < P)
    {
        int found = 0;  // Checks if any process can execute

        for (int i = 0; i < P; i++)
        {
            // Check only unfinished processes
            if (finish[i] == 0)
            {
                int canExecute = 1;

                // Check if Need <= Work
                for (int j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        // Not enough resources
                        canExecute = 0;
                        break;
                    }
                }

                // Execute process if resources are sufficient
                if (canExecute)
                {
                    printf("\nP%d can execute.\n", i);

                    // Display work before execution
                    printf("Work before P%d: ", i);

                    for (int j = 0; j < R; j++)
                    {
                        printf("%d ", work[j]);
                    }

                    printf("\n");

                    // Display resources released by process
                    printf("P%d releases Allocation: ", i);

                    for (int j = 0; j < R; j++)
                    {
                        printf("%d ", allocation[i][j]);
                    }

                    printf("\n");

                    // Process finishes and releases resources
                    // Work = Work + Allocation
                    for (int j = 0; j < R; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    // Display updated work
                    printf("Work after P%d: ", i);

                    for (int j = 0; j < R; j++)
                    {
                        printf("%d ", work[j]);
                    }

                    printf("\n");

                    // Mark process as completed
                    finish[i] = 1;

                    // Add process to safe sequence
                    safeSeq[completed] = i;

                    // Increase completed process count
                    completed++;

                    // At least one process executed
                    found = 1;

                    // Display Finish array
                    printf("Finish array: ");

                    for (int k = 0; k < P; k++)
                    {
                        printf("%d ", finish[k]);
                    }

                    printf("\n");
                }
            }
        }

        // Stop if no process can execute
        if (found == 0)
        {
            break;
        }
    }

    // Step 8: Display Final Result
    printf("\n--- Final Result ---\n");

    // If all processes finish, system is safe
    if (completed == P)
    {
        printf("System is in SAFE STATE.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < P; i++)
        {
            printf("P%d", safeSeq[i]);

            // Print arrow between processes
            if (i < P - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        // If some processes cannot finish, system is unsafe
        printf("System is in an UNSAFE STATE.\n");
        printf("No safe sequence exists for the given state.\n");
    }

    return 0;
}