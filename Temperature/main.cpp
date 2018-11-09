#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
int ma;
const int N=2*1e6+5;
int m[N];
int n;
int i,k,l0,l,r,r0,nn;
int maxx=INT_MIN;
int res=0;
int hi,lo,mid,d,a;
struct SegmentTree{
    void set()
    {
        a+=n;
        m[a]=k;
        a>>=1;
        for(;a;a>>=1)
            m[a]=max(m[2*a],m[2*a+1]);
    }
    int get()
    {
        ma=INT_MIN;
        for(l0+=n,r0+=n;l0<=r0;l0>>=1,r0>>=1)
        {
            if(l0%2==1)
            {
                ma=max(ma,m[l0]);
                l0++;
            }
            if(r0%2==0)
            {
                ma=max(ma,m[r0]);
                r0--;
            }
        }
        return ma;
    }
};
void fastscan(int &number)
{
    bool negative = false;
    register int c;
    number = 0;
    c = getchar();
    if (c=='-')
    {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}
int main()
{
    SegmentTree m;
    fastscan(n);
    assert(n<N);
    for(i=0;i<n;i++)
    {
        fastscan(lo);
        fastscan(hi);
        a=i;
        k=lo;
        m.set();
        if(hi<maxx)
        {
            l++;
            r=i;
            while(l<r)
            {
                mid=(l+r)/2;
                l0=mid;
                r0=i;
                d=m.get();
                //printf("%i-%i   [%i][%i]=%i\n",l,r,mid,i,d);
                if(hi<d)
                {
                    l=mid+1;
                }
                else
                {
                    r=mid;
                }
            }
            l0=l;
            r0=i;
            maxx=m.get();
        }
        maxx=max(maxx,lo);
        res=max(res,i-l+1);
    }
    //printf("%i\n",res);
    cout << res;
    return 0;
}
