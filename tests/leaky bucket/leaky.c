#include <stdio.h>
#include <stdlib.h>
int main()
{
    int occuppied = 0, bucket_size, n,output_rate;
    printf("Enter the bucket size: \n");
    scanf("%d", &bucket_size);
    printf("Enter the number of inputs: \n");
    scanf("%d", &n);
    printf("Enter the output rate: \n");
    scanf("%d",&output_rate);
    while (n != 0)
    {
        printf("Enter the size: \n");
        int in;
        scanf("%d", &in);
        if (in <= (bucket_size - occuppied))
        {
            occuppied += in;
            printf("Status: \noccupied: %d\t total: %d\n", occuppied, bucket_size);
        }
        else
        {
            printf("discarding: %d\n", (in - (bucket_size - occuppied)));
            occuppied = bucket_size;
            printf("Status: \noccupied: %d\t total: %d\n", occuppied, bucket_size);
        }
        occuppied-=output_rate;
        printf("status after discarding..\n occupied: %d\t total: %d\n",occuppied,bucket_size);
        n--;
    }
}