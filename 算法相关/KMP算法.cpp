#include<iostream>
#include<string.h>
using namespace std;
void pret(char p[],int pre[],int n)
{
    int len=0;int i;
    pre[0]=0;
   for(i=1;i<n;i++)
    {
        if(p[i]==p[len])
        {
            len++;pre[i]=len;
        }
        else
        {
            len=0;
            pre[i]=len;
        }
    }
    for(i=n-1;i>0;i--)
    {
        pre[i]=pre[i-1];
    }
    pre[0]=-1;
}
void KMP(char text[],char a[])
{
    int n=strlen(a);
    int m=strlen(text);
    int *pre=new int[n];
    pret(a,pre,n);
    int i=0,j=0;
    while(i<m)
    {
        if(text[i]==a[j])
        {
            i++;j++;
        }
        else
        {
            j=pre[j];
            if(j==-1)
            {
                i++;j++;
            }

        }
        if(j==n-1&&text[i]==a[j])
            {
                cout<<"Yes,it start at"<<i-j+1;
                break;
            }

    }
    if(i==m)
      cout<<"No,it isn't in it";
    delete(pre);
}
int main()
{
    int m;int i;
    cin>>m;
    char *a=new char[m];
    for(i=0;i<m;i++)
        cin>>a[i];
    char text[]="abababcabaabababab";
    int pre[9];
    int n=9;
    KMP(text,a);
    return 0;
}
