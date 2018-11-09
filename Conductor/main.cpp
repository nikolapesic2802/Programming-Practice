/*
    - If some radio tower j is higher than radio tower i and j>i, it will overtake the value for some index>=j.
    - So find that value with binary search +segment tree to memorize the maximums. We do this in both direction and get the answer for every element based on the values in the seg tree.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
int n;
struct segmentTree{

    vector<pair<int,int> > lazy;
    void init()
    {
        lazy.resize(4*n);
    }
    void prop(int i)
    {
        if(lazy[i]==make_pair(0,0))
            return;
        lazy[2*i]=lazy[i];
        lazy[2*i+1]=lazy[i];
        lazy[i]=make_pair(0,0);
    }
    void set(int l,int r,pair<int,int> x,int i=1,int lo=0,int hi=n-1)
    {
        //printf("Usao za %i-%i   %i  %i-%i\n",l,r,i,lo,hi);
        if(hi<l||lo>r)
            return;
        if(l<=lo&&hi<=r)
        {
            lazy[i]=x;
            return;
        }
        prop(i);
        int mid=(lo+hi)/2;
        set(l,r,x,2*i,lo,mid);
        set(l,r,x,2*i+1,mid+1,hi);
    }
    pair<int,int> get(int p,int i=1,int lo=0,int hi=n-1)
    {
        if(lo>p||hi<p)
            return make_pair(0,0);
        if(lo==hi&&lo==p)
            return lazy[i];
        prop(i);
        int mid=(lo+hi)/2;
        pair<int,int> p1=get(p,2*i,lo,mid),p2=get(p,2*i+1,mid+1,hi);
        return make_pair(p1.first+p2.first,p1.second+p2.second);
    }
} ST,ST2;
/// pair<int,int> f1 - first:height, second: start position
bool test(pair<int,int> f1,pair<int,int> f2,int poz)
{
    double h1=f1.first+(double)sqrt(abs(f1.second-poz));
    double h2=f2.first+(double)sqrt(abs(f2.second-poz));
    return h1>h2;
}
int calc(pair<int,int> f,int poz)
{
    int dist=abs(f.second-poz);
    //printf("Dist: %i\n",dist);
    double r = f.first+(double)sqrt(dist);
    int res=r;
    if(r>res)
        res++;
    //printf("Vracam %i:\n",res);
    return res;
}
int main()
{
    scanf("%i",&n);
    ST.init();
    ST2.init();
    /*ST.set(0,5,make_pair(1,1));
    ST.set(3,4,make_pair(2,2));
    ST.set(1,3,make_pair(3,3));
    ST.set(2,2,make_pair(8,8));
    for(int i=0;i<n;i++)
    {
        auto p=ST.get(i);
        printf("%i %i\n",p.first,p.second);
    }*/
    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&arr[i]);
    }
    int maxx=-1;
    for(int i=0;i<n;i++)
    {
        if(arr[i]>maxx)
        {
            //printf("Usao za %i\n",i);
            maxx=arr[i];
            pair<int,int> tr=make_pair(arr[i],i);
            int l=i,r=n-1;
            while(l<r)
            {
                int mid=(l+r)/2;
                pair<int,int> f=ST.get(mid);
                if(test(f,tr,mid))
                {
                    l=mid+1;
                }
                else
                {
                    r=mid;
                }
            }
            if(l==n-1)
            {
                pair<int,int> f=ST.get(l);
                if(test(f,tr,l))
                {
                    continue;
                }
            }
            //printf("Postavljam od %i do %i na %i-%i\n",l,n-1,tr.first,tr.second);
            ST.set(l,n-1,tr);
        }
    }
    //printf("Zavrxio\n");
    maxx=-1;
    for(int i=n-1;i>=0;i--)
    {
        if(arr[i]>maxx)
        {
            //printf("Usao za %i\n",i);
            maxx=arr[i];
            pair<int,int> tr=make_pair(arr[i],i);
            int l=0,r=i;
            while(l<r)
            {
                int mid=(l+r)/2;
                pair<int,int> f=ST2.get(mid);
                if(test(f,tr,mid))
                {
                    r=mid;
                }
                else
                {
                    l=mid+1;
                }
            }
            if(l==0)
            {
                pair<int,int> f=ST2.get(l);
                //printf("%i %i\n",f.first,f.second);
                if(test(f,tr,l))
                {
                    continue;
                }
            }
            //printf("Postavljam %i-%i na %i %i\n",0,l,tr.first,tr.second);
            ST2.set(0,l,tr);
        }
    }
    for(int i=0;i<n;i++)
    {
        pair<int,int> f1=ST.get(i);
        pair<int,int> f2=ST2.get(i);
        //printf("F1: %i %i, F2: %i %i\n",f1.first,f1.second,f2.first,f2.second);
        int m=max(calc(f1,i),calc(f2,i));
        printf("%i\n",m-arr[i]);
    }
    return 0;
}
