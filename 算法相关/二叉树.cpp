#include<iostream>
using namespace std;
#define maxsize 100
typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
}BTnode;

void CreatBTnode(BTnode *&b,char *str)
{
    BTnode *st[maxsize],*p; //st[]用于构造一个栈，便于二叉树的建立
    int top=-1,k,j=0; //top用于栈，k是判断左右节点，j用于遍历str数组
    char ch;//ch判断括号表示法的位置
    b=NULL;ch=str[j]; //b用于创建节点
    while(ch!='\0')
    {
        switch(ch)
        {
            case '(':top++;st[top]=p;k=1;break; //“（”出现时，将p入栈，top指针前进,k置为1，指向左孩子
            case ')':top--;break;//")"出现，表示树结束，退父节点
            case ',':k=2;break;//表示“，”后面元素为右孩子
            default:
                p=new BTnode;
                p->data=ch;
                p->left=p->right=NULL;
                if(b==NULL)//p为二叉树的根结点、
                    b=p;
                else
                {
                    switch(k)
                    {
                        case 1:st[top]->left=p;break;
                        case 2:st[top]->right=p;break;
                    }
                }
        }
        j++;ch=str[j];
    }
}
void disp(BTnode *b)
{
    if(b)
    {
        cout<<b->data<<" ";
        if(b->left!=NULL||b->right!=NULL)
        {
            disp(b->left);
            disp(b->right);
        }
    }

}
void pre(BTnode *b)
{
    if(b)
    {

    pre(b->left);

    pre(b->right);

    cout<<b->data;
    }

    }
void level(BTnode *b)
{
    BTnode *p;
    BTnode *qu[maxsize];
    int front,rear;
    front=rear=0;
    rear++;
    qu[rear]=b;
    while(front!=rear)
    {
        front=(front+1)%maxsize;
        p=qu[front];
        cout<<p->data<<" ";
        if(p->left!=NULL)
        {
            rear=(rear+1)%maxsize;
            qu[rear]=p->left;
        }
        if(p->right!=NULL)
        {
            rear=(rear+1)%maxsize;
            qu[rear]=p->right;
        }
    }
}
int main()
{
    char str[maxsize];
    BTnode *b=NULL;int i=0;
        cin>>str;
   CreatBTnode(b,str);
   disp(b);
   cout<<endl;
    pre(b);
   level(b);
    return 0;

}
