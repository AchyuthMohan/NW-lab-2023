#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Link
{
    int hop, wt, dest;
};
struct Network
{
    int h, l;
    struct Link *link;
};
int main()
{
    int h, l, s;
    printf("Enter the number of hopes: \n");
    scanf("%d", &h);
    printf("Enter the number of links: \n");
    scanf("%d", &l);
    printf("Enter the start: \n");
    scanf("%d", &s);
    struct Network *n = (struct Network *)malloc(sizeof(struct Network));
    n->h = h;
    n->l = l;
    n->link = (struct Link *)malloc(l * sizeof(struct Link));
    int dist[h];
    for (int i = 0; i < h; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;
    for (int i = 0; i < l; i++)
    {
        printf("Enter the source, dest and wt: \n");
        scanf("%d", &n->link[i].hop);
        scanf("%d", &n->link[i].dest);
        scanf("%d", &n->link[i].wt);
    }
    for (int i = 1; i < h; i++)
    {
        for (int j = 0; j < l; j++)
        {
            int u = n->link[j].hop;
            int v = n->link[j].dest;
            int wt = n->link[j].wt;
            if (u >= 0 && u < h && v >= 0 && v < h && dist[u] != INT_MAX)
            {
                if (dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    for (int i = 0; i < l; i++)
    {
        int u = n->link[i].hop;
        int v = n->link[i].dest;
        int wt = n->link[i].wt;
        if (u >= 0 && u < h && v >= 0 && v < h && dist[u] != INT_MAX && dist[u] + wt < dist[v])
        {
            printf("Negative weighted cycles exists..\n");
        }
    }
    printf("Source\tdistsnce\n");
    for (int i = 0; i < h; i++)
    {
        printf("%d\t%d\n", i, dist[i]);
    }
    free(n->link);
    free(n);
    return 0;
}