//
//  main.c
//  Knapsack Problem
//
//  Created by 徐天洋 on 5/22/19.
//  Copyright © 2019 徐天洋. All rights reserved.
//

#include <iostream>
using namespace std;
#define e 0.0001
struct NODE{        //结点数据结构
    NODE *Parent;    //指向父结点指针
    NODE *next;    //后继结点指针
    int   Level;    //结点的所在的层数
    int   Tag;        //左右孩子的标志，1为左孩子，0为右孩子
    int   CW;        //目前背包剩余空间
    int   CV;        //目前已装入物品有效益值
    int   LB;        //结点的下界值
    float UB;        //结点的上界值
};
NODE *head;            //活动结点队列队头
NODE *RESULT,*E;    //解结点、根结点
int *v,*w;            //指向物品的价值、重量数组指针
int W,lb,cw,cv;        //背包最大容量、下限、目前剩余容量、目前物品价值之和
int N;                //背包中物品数量
float ub;            //背包的价值上限

void INIT(int *vv,int *ww,int WW,int NN,int& value);    //初始化队列
void LUBOUND(int rw,int cp,int k,int &LBB,float &UBB);    //计算上下界限
NODE* INSERTNODE(NODE *parent,int level,int t,int cw,int cv,int lb,float ub);    //生成一个新结点
void ENQUEUE(NODE *node);    //将结点i加入优先队列
void DEQUEUE(NODE *node);    //将结点i从优先队列中删除(杀死结点)
NODE* NEXLIVENODE();        //下一扩展结点(取下限lb最大结点)
void PRINT(NODE* result,int n,int value);    //打印结果
void LCBB(NODE* reusult,int n,int W,int lb,float ub,int cv,int cw,int& value);    //求解最优解

int main()
{
    int VALUE;            //目前装入物品价值
    int value[]={20,20,24,36};
    int weight[]={10,20,30,45};
    int BW;
    cout<<"各个物品的价值和重量为："<<endl;
    cout<<"name\tvalue\tweight"<<endl;
    for(int i=0;i<sizeof(value)/sizeof(int);i++)
        cout<<"x"<<i+1<<"\t"<<value[i]<<"\t"<<weight[i]<<endl;
    cout << "请输入背包的重量:";
    cin >> BW;
    cout << endl;
    INIT(value,weight,BW,sizeof(value)/sizeof(int),VALUE);
    LCBB(RESULT,N,W,lb,ub,cv,cw,VALUE);
    return 0;
}

void INIT(int *vv,int *ww,int WW,int NN,int& value)    //初始化队列
{
    N=NN;
    W=WW;
    v=new int[N];
    w=new int[N];
    for(int i=0;i<N;i++)
    {
        v[i]=vv[i];
        w[i]=ww[i];
    }
    head=new(NODE);
    head->next=NULL;
    value=0;
    RESULT=new(NODE);
}

void LUBOUND(int rw,int cp,int k,int &LBB,float &UBB)    //计算上下界限
{
    int i,j,c;
    LBB=cp;
    c=rw;
    for(i=k;i<N;i++)
    {
        if(c<w[i])
        {
            UBB=(float)(LBB+c*v[i]/w[i]);
            for(j=i+1;j<N;j++)
                if(c>=w[j])
                {
                    c=c-w[j];
                    LBB+=v[j];
                }
            return;
        }
        c=c-w[i];
        LBB+=v[i];
    }
    UBB=(float)LBB;
}
NODE* INSERTNODE(NODE *parent,int level,int t,int cw,int cv,int lb,float ub)    //生成一个新结点
{
    NODE* node=new(NODE);
    node->Parent=parent;
    node->next=NULL;
    node->Level=level;
    node->Tag=t;
    node->CW=cw;
    node->CV=cv;
    node->UB=ub;
    node->LB=lb;
    return(node);
}
void ENQUEUE(NODE* node)    //将结点i加入优先队列
{
    
    node->next=head->next;
    head->next=node;
}
void DEQUEUE(NODE* node)    //将结点i从优先队列中删除
{
    NODE *pre=head,*p=head->next;
    while(p!=node)
    {
        pre=p;
        p=p->next;
    }
    pre->next=p->next;
}
NODE* NEXLIVENODE()    //下一扩展结点(取下限lb最大结点)
{
    NODE *p=head->next,*choice=p;
    int lb=p->LB;
    while(p)
    {
        if(p->LB>lb)
            choice=p;
        p=p->next;
    }
    return(choice);
}
void PRINT(NODE* result,int n,int value)    //打印结果
{
    cout<<"背包装入的最大价值为:"<<value<<endl;
    cout<<"装入包中的物品有:";
    for(int i=n;i>=1;i--)
    {
        if(RESULT->Tag==1)
            cout<<'x'<<i<<' ';
        RESULT=RESULT->Parent;
    }
    cout<<endl;
}
void LCBB(NODE* reusult,int n,int W,int lb,float ub,int cv,int cw,int& value)    //求解最优解
{
    int i;
    NODE* node=new(NODE);    //根结点
    node->Parent=NULL;
    node->next=NULL;
    node->Level=0;
    node->CW=W;
    node->CV=0;
    node->Tag=0;
    LUBOUND(W,0,0,lb,ub);    //计算根结点上下界限
    value=lb-e;
    node->LB=lb;
    node->UB=ub;
    while(node->UB>value)    //当前扩展结点上界<当前解时结束
    {
        i=node->Level;
        cw=node->CW;
        cv=node->CV;
        if(i==N)
        {
            if(cv>value)
            {
                value=cv;
                RESULT=node;
            }
        }
        else                            //node有两个儿子
        {
            if(cw>=w[i])                //左孩子结点可行
                ENQUEUE(INSERTNODE(node,i+1,1,cw-w[i],cv+v[i],node->LB,node->UB));
            LUBOUND(cw,cv,i+1,lb,ub);    //重新计算上下界
            if(ub>value)                //右孩子结点可行
            {
                ENQUEUE(INSERTNODE(node,i+1,0,cw,cv,lb,ub));
                if(value<lb-e)
                    value=lb-e;
            }
        }
        if(head->next==NULL)        //队列空或ub>VALUE结束
            break;
        else
        {
            node=NEXLIVENODE();        //下一扩展结点
            DEQUEUE(node);            //将结点从队列中删除
        }
        
    }
    PRINT(RESULT,n,value);
}
