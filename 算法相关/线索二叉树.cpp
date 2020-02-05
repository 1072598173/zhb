#include<iostream>
#include<stdlib.h>
using namespace std;

#define ERROR  0
#define OK  1

typedef enum{Link, Thread} PointerTag;

typedef struct BitNode
{
    char data;
    struct BitNode *lchild;
    struct BitNode *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BitNode, *BiTree;

BiTree pre;


void CreateTree(BiTree *t)
{
    char ch;
   cin>>ch;

    if(ch == '#')
    {
        *t = NULL;
    }
    else
    {
        (*t) = (BiTree)malloc(sizeof(BitNode));
        if((*t) == NULL)
        {
            return;
        }
        (*t)->data = ch;
        CreateTree(&((*t)->lchild));
        CreateTree(&((*t)->rchild));
    }
}

int InOrderThraverse_Thr(BiTree t)
{
    BiTree p;
    p = t->lchild;
    while(p != t)
    {
        while(p->ltag == Link)
        {
            p = p->lchild;
        }
        cout<<"%c ", p->data;
        while(p->rtag == Thread && p->rchild != t)
        {
            p = p->rchild;
           cout<<p->data;
        }

        p = p->rchild;
    }

    return OK;
}


void InThreading(BiTree p)
{
    if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->ltag = Thread;
            p->lchild = pre;
        }
        if(!pre->rchild)
        {
            pre->rtag = Thread;
            pre->rchild = p;
        }
        pre = p;

        InThreading(p->rchild);
    }
}

int InOrderThread_Head(BiTree *h, BiTree t)
{
    (*h) = (BiTree)malloc(sizeof(BitNode));
    if((*h) == NULL)
    {
        return ERROR;
    }

    (*h)->rchild = *h;
    (*h)->rtag = Link;

    if(!t)
    {
        (*h)->lchild = *h;
        (*h)->ltag = Link;
    }
    else
    {
        pre = *h;
        (*h)->lchild = t;
        (*h)->ltag = Link;
        InThreading(t);
        pre->rchild = *h;
        pre->rtag = Thread;
        (*h)->rchild = pre;
    }
}

int main()
{
    BiTree t;
    BiTree temp;

   cout<<"请输入前序二叉树的内容:\n";
    CreateTree(&t);
    InOrderThread_Head(&temp, t);
    cout<<"输出中序二叉树的内容:\n";
    InOrderThraverse_Thr(temp);

    return 0;
}
