//
//  main.c
//  Linear Time Select
//
//  Created by 徐天洋 on 5/29/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include <ctime>
#include <iostream>
using namespace std;

template <class Type>
void Swap(Type &x,Type &y);

inline int Random(int x, int y);

template <class Type>
void BubbleSort(Type a[],int p,int r);

template <class Type>
int Partition(Type a[],int p,int r,Type x);

template <class Type>
Type Select(Type a[],int p,int r,int k);

int main()
{
    //初始化数组
    int a[100];
    
    //必须放在循环体外面
    srand((unsigned)time(0));
    
    for(int i=0; i<100; i++)
    {
        a[i] = Random(0,500);
        cout<<"a["<<i<<"]:"<<a[i]<<" ";
    }
    cout<<endl;
    
    cout<<"第小元素是"<<Select(a,0,99,83)<<endl;
    
    //重新排序，对比结果
    BubbleSort(a,0,99);
    
    for(int i=0; i<100; i++)
    {
        cout<<"a["<<i<<"]:"<<a[i]<<" ";
    }
    cout<<endl;
}

template <class Type>
void Swap(Type &x,Type &y)
{
    Type temp = x;
    x = y;
    y = temp;
}

inline int Random(int x, int y)
{
    int ran_num = rand() % (y - x) + x;
    return ran_num;
}

//冒泡排序
template <class Type>
void BubbleSort(Type a[],int p,int r)
{
    //记录一次遍历中是否有元素的交换
    bool exchange;
    for(int i=p; i<=r-1;i++)
    {
        exchange = false ;
        for(int j=i+1; j<=r; j++)
        {
            if(a[j]<a[j-1])
            {
                Swap(a[j],a[j-1]);
                exchange = true;
            }
        }
        //如果这次遍历没有元素的交换,那么排序结束
        if(false == exchange)
        {
            break ;
        }
    }
}

template <class Type>
int Partition(Type a[],int p,int r,Type x)
{
    int i = p-1,j = r + 1;
    
    while(true)
    {
        while(a[++i]<x && i<r);
        while(a[--j]>x);
        if(i>=j)
        {
            break;
        }
        Swap(a[i],a[j]);
    }
    return j;
}


template <class Type>
Type Select(Type a[],int p,int r,int k)
{
    if(r-p<75)
    {
        BubbleSort(a,p,r);
        return a[p+k-1];
    }
    //(r-p-4)/5相当于n-5
    for(int i=0; i<=(r-p-4)/5; i++)
    {
        //将元素每个分成一组，分别排序，并将该组中位数与a[p+i]交换位置
        //使所有中位数都排列在数组最左侧，以便进一步查找中位数的中位数
        BubbleSort(a,p+5*i,p+5*i+4);
        Swap(a[p+5*i+2],a[p+i]);
    }
    //找中位数的中位数
    Type x = Select(a,p,p+(r-p-4)/5,(r-p-4)/10);
    int i = Partition(a,p,r,x);
    int j = i-p+1;
    if(k<=j)
    {
        return Select(a,p,i,k);
    }
    else
    {
        return Select(a,i+1,r,k-j);
    }
}
