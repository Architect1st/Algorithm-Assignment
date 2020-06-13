//
//  main.c
//  IntegerPartition
//
//  Created by 徐天洋 on 3/6/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include <stdio.h>
//int main()
//{
//    int equation(int n,int m);
//    int n,m;
//    printf("请输入正整数之和 n (0<n<100):");
//    scanf("%d",&n);
//    printf("请输入划分数最大值 m (0<m≤n):");
//    scanf("%d",&m);
//    printf("正整数 %d 有 %d 种划分。\n", n , equation(n,m));
//    return 0;
//}
//
//int equation(int n,int m)
//{
//    if ((n<1)||(m==1))
//        return 0;
//    if(n==1||m==1)
//        return 1;
//    if(n<m)
//        return equation(n,n);
//    if(n==m)
//        return equation(n,n-1)+1;
//    else
//        return equation(n-m,m)+equation(n,m-1);
//}
int a[100]={-1};

int main()
{
    int x;
    for(x = 0 ; x < 100 ; x++)
    {
        a[x] = -1;
    }//输出「+」用的
    
    void split(int n,int k);
    int n;
    printf("请输入一个正整数 n (0<n<100)：");
    scanf("%d",&n);
    printf("正整数 %d 的分解结果为:\n", n);
    split(n,0);
}

void split(int n,int k)//k是数组中的位置，亦是递归层数
{
    void display(int k);
    int i;
    if(n==0)//分解完成，输出结果
        display(k);
    else
        for(i=n;i>0;i--)
            if(k==0||i<=a[k-1])
            {
                a[k]=i;//写入数组
                split(n-i,k+1);
            }
}

//输出数组前k项
void display(int k)
{
    int i;
    for(i=0;i<k;i++)
    {
        printf("%d ",a[i]);
        if (a[i+1] != -1)
            printf("+ ");//输出「+」号
    }
    printf("\n");
}
