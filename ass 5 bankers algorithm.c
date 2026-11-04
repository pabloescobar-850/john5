//5. Deadlock avoidance (CO4)
//Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

#include <stdio.h>

int main()
{
    // Initialization for Banker's Algorithm
    int i, j, k;
    int n, m;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int count = 0;
    int found;
    int finish[10] = {0};
    int safe[10];

    // Input
    printf("Enter the number of processes:- \n");
    scanf("%d", &n);

    printf("Enter the number of resources:- \n");
    scanf("%d", &m);

    printf("Enter the allocation matrix:- \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the max matrix:- \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:- \n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Display need matrix
    printf("Need matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Find safe sequence
    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                // Check if process can execute
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        break;
                    }
                }

                if (j == m)
                {
                    // Process can finish
                    for (k = 0; k < m; k++)
                    {
                        avail[k] += alloc[i][k];
                    }

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("Safe sequence cannot be made, deadlock is possible.\n");
            return 0;
        }
    }

    // Display safe sequence
    printf("Safe sequence:\n");
    for (k = 0; k < n; k++)
    {
        printf("P%d\n", safe[k]);
    }

    return 0;
}


// terminal 
// gcc bankers.c -o bankers
// ./bankers

// inputs
5
3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
    
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
    
3 3 2
// now 3 3 2 is our that a b c wala shit ok \
    // create table and in remaingin (4th collumn) do cal of max - Allocation \
    // 3 3 2  zhalya war te p2 madhe 2 0 0 add kar if max need satisfies or not means \
    // jar ka p2 cha satisfy zhala (max need) the add the availabale madhe p2 cha allcated ok?
