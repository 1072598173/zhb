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
    BTnode *st[maxsize],*p; //st[]���ڹ���һ��ջ�����ڶ������Ľ���
    int top=-1,k,j=0; //top����ջ��k���ж����ҽڵ㣬j���ڱ���str����
    char ch;//ch�ж����ű�ʾ����λ��
    b=NULL;ch=str[j]; //b���ڴ����ڵ�
    while(ch!='\0')
    {
        switch(ch)
        {
            case '(':top++;st[top]=p;k=1;break; //����������ʱ����p��ջ��topָ��ǰ��,k��Ϊ1��ָ������
            case ')':top--;break;//")"���֣���ʾ���������˸��ڵ�
            case ',':k=2;break;//��ʾ����������Ԫ��Ϊ�Һ���
            default:
                p=new BTnode;
                p->data=ch;
                p->left=p->right=NULL;
                if(b==NULL)//pΪ�������ĸ���㡢
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
