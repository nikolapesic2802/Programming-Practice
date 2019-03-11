#include <iostream>
#include <bits/stdc++.h>
#define For(a,b,c) for(int a=b;a<=c;a++)
#define Ford(a,b,c) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define ll long long
#define db double
const int MAX=5005,INF=1e9+1;
using namespace std;

int main()
{
   int n,a[MAX],q,k[MAX],je[MAX],dv[MAX],l[MAX],r[MAX],t=0,rez=0;
   cin>>n>>q;
   For(i,1,q)
   {
       scanf("%i%i",&l[i],&r[i]);
       For(j,l[i],r[i])
            k[j]++;
   }
   For(i,1,n)
   je[i]=dv[i]=0;
   je[0]=0;
   dv[0]=0;
   For(i,1,n)
   if (k[i]==1)
    je[i]=je[i-1]+1;
    else je[i]=je[i-1];
   For(i,1,n)
   if (k[i]==2)
    dv[i]=dv[i-1]+1;
   else dv[i]=dv[i-1];

   For(i,1,n)
   if (k[i]>0)
    t++;

    int curr;
   For(i,1,q)
   For(j,1+1,q)
   {
     curr=je[r[i]]-je[l[i]-1]+  je[r[j]]-je[l[j]-1];
     if (max(l[i],l[j])<=min(r[i],r[j]))
        curr+=dv[min(r[i],r[j])]-dv[max(l[i],l[j])-1];
    rez=max(rez,t-curr);

   }
   cout<<rez;

    return 0;
}
