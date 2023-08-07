#include<stdio.h>
#include<stdlib.h>
int main(){
    int bucket_size,occupied=0,rate,n;
    printf("Enter the number of inputs: \n");
    scanf("%d",&n);
    printf("Enter the bucket size: \n");
    scanf("%d",&bucket_size);
    printf("Enter the rate: \n");
    scanf("%d",&rate);
    while(n!=0){
        printf("Enter the input size: \n");
        int in;
        scanf("%d",&in);
        if(in<=(bucket_size-occupied)){
            occupied+=in;
            printf("Status:\noccupied: %d\t total size: %d\n",occupied,bucket_size);
        }
        else{
            printf("Removing %d\n",in-(bucket_size-occupied));
            occupied=bucket_size;
            printf("Status:\noccupied: %d\t total size: %d\n",occupied,bucket_size);
        }
        occupied-=in;
        printf("Status after removal:\noccupied: %d\t total size: %d\n",occupied,bucket_size);
        n--;
    }
}