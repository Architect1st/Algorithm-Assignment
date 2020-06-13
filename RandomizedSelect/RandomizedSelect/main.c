//
//  main.c
//  RandomizedSelect
//
//  Created by 徐天洋 on 4/3/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int randomized_select(int *, int, int, int);
static int randomized_partition(int *, int, int);
static int partition(int *, int, int);
static int randomd(int, int);
static void swap(int *, int *);


int main(int argc, char *argv[])
{
    
    int mid;
    int array[9] = {1,2,4,7,3,5,6,8,12};
    　　　　　/*返回第５小的元素．*/
    mid = randomized_select(array, 0, 8, 5);
    printf("%d\n", mid);
    return 0;
}


static int randomized_select(int *A, int p, int r, int i)
{
    int q, k;
    
    if (p == r)
        return A[p];
    
    q = randomized_partition(A, p, r);
    k = q - p + 1;
    
    if (i == k)
        return A[q];
    else if (i < k)
        return randomized_select(A, p, q - 1, i);
    else
        return randomized_select(A, q + 1, r, i - k);
}

static int randomized_partition(int *A, int p, int r)
{
    int i, temp;
    i = randomd(p, r);
    swap(A + r, A + i);
    /*
     temp = A[r];
     A[r] = A[i];
     A[i] = temp;
     */
    return partition(A, p, r);
}
/*划分，跟快速排序一样．*/
static int partition(int *A, int p, int r)
{
    int a, i, j, temp;
    a = A[r];
    i = p - 1;
    
    for (j = p; j < r; ++j)
    {
        if (A[j] <= a)
        {
            ++i;
            swap(A + j, A + i);
            /*
             temp = A[j];
             A[j] = A[i];
             A[i] = temp;
             */
        }
        
    }
    
    swap(A + r, A + i + 1);
    /*
     temp = A[r];
     A[r] = A[i + 1];
     A[i + 1] = temp;
     */
    return i + 1;
}

/*返回特定范围［a, b］内的一个随机数．*/
static int randomd(int a, int b)
{
    int q;
    
    srand((unsigned int)time(NULL));
    q = rand()%(b - a + 1) + a;
    
    return q;
}

/*交换值．*/
static void swap(int *num1, int *num2)
{
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
