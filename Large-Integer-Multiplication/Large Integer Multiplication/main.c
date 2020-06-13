//
//  main.c
//  Large Integer Multiplication
//
//  Created by 徐天洋 on 3/13/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Multiply(void);

int NumberLength(long number);

int SIGN(long A);

long Calculate(long X, long Y, int xn, int yn);

int main()
{
    Multiply();
    return (0);
}

int SIGN(long A)
{
    return A > 0 ? 1 : -1;
}

void Multiply()
{
    long X=0,Y = 0;
    int xn=0,yn=0;
    printf("请输入两个大整数：\nX = ");
    scanf("%ld",&X);
    printf("Y = ");
    scanf("%ld",&Y);
    
    xn = NumberLength(X);
    yn = NumberLength(Y);
    
    long sum = Calculate(X, Y, xn,yn);
    
    printf("X * Y = %ld * %ld = %ld \n",X,Y,sum);
}

int NumberLength(long number){//获得数字长度
    int i=0;
    do{
        number=number/10;
        i++;
    }while(number!=0);
    return i;
}


long Calculate(long X, long Y, int xn, int yn)
{
    if (X == 0 || Y == 0)
        return 0;
    else if ((xn == 1 && yn == 1) || xn == 1 || yn == 1)
        return X * Y;
    else
    {
        int xn0 = xn / 2, yn0 = yn / 2;
        int xn1 = xn - xn0, yn1 = yn - yn0;
        
        long A = (long)(X / pow(10, xn0));
        long B = (long)(X % (long)pow(10, xn0));
        long C = (long)(Y / pow(10, yn0));
        long D = (long)(Y % (long)pow(10, yn0));
        
        long AC = Calculate(A, C, xn1, yn1);
        long BD = Calculate(B, D, xn0, yn0);
        long ABCD = Calculate((long)(A * pow(10, xn0) - B), (long)(D - C * pow(10, yn0)), xn1, yn1);
        
        return (long)(2 * AC * pow(10, (xn0 + yn0)) + ABCD + 2 * BD);
    }
}
