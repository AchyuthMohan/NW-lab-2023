#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
struct Link
{
    int s, d, w;
};
struct Network
{
    int h, l;
    struct Link *link;
};
int main()
{
    int h, l;
    printf("Enter the number of hops and links: \n");
    scanf("%d%d", &h, &l);
    int dist[h];
    for (int i = 0; i < h; i++)
    {
        dist[i] = INT_MAX;
    }
    struct Network *n = (struct Network *)malloc(sizeof(struct Network));
    n->h = h;
    n->l = l;
    n->link = (struct Link *)malloc(l * sizeof(struct Link));
    for (int i = 0; i < l; i++)
    {
        printf("Enter the src,dest and wt of link: \n");
        scanf("%d", &n->link[i].s);
        scanf("%d", &n->link[i].d);
        scanf("%d", &n->link[i].w);
    }
    int s;
    printf("Enter the start node : \n");
    scanf("%d", &s);
    dist[s] = 0;
    for (int i = 1; i < h; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int u = n->link[j].s;
            int v = n->link[j].d;
            int wt = n->link[j].w;
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
        int u = n->link[i].s;
        int v = n->link[i].d;
        int w = n->link[i].w;
        if (u >= 0 && u < h && v >= 0 && v < h && dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            printf("negative cycle exits..\n");
        }
    }
    for (int i = 0; i < h; i++)
    {
        printf("Node: %d\tdistance: %d\n", i, dist[i]);
    }
}