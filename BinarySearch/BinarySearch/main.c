//
//  main.c
//  BinarySearch
//
//  Created by 徐天洋 on 3/6/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include <stdio.h>
int main()
{
    int n;
    int i;
    int c=0;
    int key;
    printf("请输入数组长度（ 0～999 ）：");
    scanf("%d",&n);
    int a[999];
    printf("\n请按升序输入数组元素：\n");
    for(i=1;i<=n;i++)
    {
        printf("第 %d 个：",i);
        scanf("%d",&a[i]);
//        printf("\n");
    }
    printf("\n请输入待查找的数字：");
    scanf("%d",&key);
    while(c<=n)
    {
        int middle=(c+n)/2;
        if (key==a[middle])
            printf("\n数字 %d 是第 %d 项。\n",key ,middle);
        if (key>a[middle])
            c=middle+1;
        else
            n=middle-1;
    }
}
