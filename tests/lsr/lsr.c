#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main()
{
    int n;
    printf("Enter the number of hops: \n");
    scanf("%d", &n);
    int adj[n][n], distance[n], visited[n];
    printf("Enter the number adjacency matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }
    distance[0] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min = INT_MAX, min_index;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && min > distance[j])
            {
                min = distance[j];
                min_index = j;
            }
        }
        visited[min_index] = 1;
        for (int d = 0; d < n; d++)
        {
            if (!visited[d] &&
                adj[min_index][d] &&
                distance[min_index] != INT_MAX &&
                distance[min_index] + adj[d][min_index] < distance[d])
            {
                distance[d] = distance[min_index] + adj[d][min_index];
            }
        }
    }
    printf("Result: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Node: %d\tdistance: %d\n", i, distance[i]);
    }
}