#include<iostream>
#include<math.h>
using namespace std;
int main()
{
long long a[20190324];
a[0]=a[1]=a[2]=1;
for(long i=3;i<20190324;i++)
{
	a[i]=(a[i-1]+a[i-2]+a[i-3])%10000;
}
cout<<a[20190323];
	return 0;
}