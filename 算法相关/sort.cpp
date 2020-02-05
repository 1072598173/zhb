#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
int main()
{
   int n,sum=0;
   cin>>n;
   while(1)
   {
	   int m=(int)sqrt(n);
	   sum+=m;
	   n=n-2*m;
	   if(n<=3)
	   {break;}
   }
   cout<<sum;
    return 0;
}
