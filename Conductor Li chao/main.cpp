#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
struct func{
    int poz;
    int h;
};
double f(func x,int i,int p)
{
    if(p==0)
    {
        if(i>x.poz)
            return -1;
    }
    else
        if(i<x.poz)
            return -1;
    double sol=(double)x.h+(double)sqrt(abs(i-x.poz));
    return sol;
}
int N;
struct liChao{
    vector<func> tr;
    void init(func start)
    {
        tr.resize(4*N);
        fill(tr.begin(),tr.end(),start);
    }
    void set(func x,int p,int i=1,int l=0,int r=N)
    {
        int m=(l+r)>>1;
        if(m>p)
        {
            set(x,p,2*i,l,m);
            return;
        }
        bool lft=f(x,l,0)>f(tr[i],l,0);
        bool mid=f(x,m,0)>f(tr[i],m,0);
        if(mid){
            swap(tr[i],x);
        }
        if(r-l==1)
            return;
        if(lft!=mid)
        {
            set(x,p,2*i,l,m);
        }
        else
        {
            set(x,p,2*i+1,m,r);
        }
    }
    double get(int poz,int i=1,int l=0,int r=N)
    {
        int m=(l+r)>>1;
        if(r-l==1)
            return f(tr[i],poz,0);
        if(poz<m)
            return max(f(tr[i],poz,0),get(poz,2*i,l,m));
        else
            return max(f(tr[i],poz,0),get(poz,2*i+1,m,r));
    }
} ST;
struct liChao2{
    vector<func> tr;
    void init(func start)
    {
        tr.resize(4*N);
        fill(tr.begin(),tr.end(),start);
    }
    void set(func x,int p,int i=1,int l=0,int r=N)
    {
        int m=(l+r)>>1;
        if(m<p)
        {
            if(r-l==1)
                return;
            set(x,p,2*i+1,m,r);
            return;
        }
        bool lft=f(x,l,1)>f(tr[i],l,1);
        bool mid=f(x,m,1)>f(tr[i],m,1);
        if(mid){
            swap(tr[i],x);
        }
        if(r-l==1)
            return;
        if(lft!=mid)
        {
            set(x,p,2*i,l,m);
        }
        else
        {
            set(x,p,2*i+1,m,r);
        }
    }
    double get(int poz,int i=1,int l=0,int r=N)
    {
        int m=(l+r)>>1;
        if(r-l==1)
            return f(tr[i],poz,1);
        if(poz<m)
            return max(f(tr[i],poz,1),get(poz,2*i,l,m));
        else
            return max(f(tr[i],poz,1),get(poz,2*i+1,m,r));
    }
} ST2;
int main()
{
    int n;
    scanf("%i",&n);
    N=n;
    vector<int> h(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&h[i]);
        func tr;
        tr.h=h[i];
        tr.poz=i;
        if(i==0)
            ST2.init(tr);
        else
            ST2.set(tr,i);
    }
    for(int i=n-1;i>=0;i--)
    {
        func tr;
        tr.h=h[i];
        tr.poz=i;
        if(i==n-1)
            ST.init(tr);
        else
            ST.set(tr,i);
    }
    for(int i=0;i<n;i++)
    {
        double d=max(ST.get(i),ST2.get(i));
        //printf("%i: %f\n",i,d);
        int a=d;
        //printf("%i\n",a);
        if(d>a)
            a++;
        printf("%i\n",a-h[i]);
    }
    return 0;
}
