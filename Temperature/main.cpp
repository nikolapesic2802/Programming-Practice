/*
    - The basic idea is just to do a 2 pointer.
    - When the upper value for some position is smaller than the maximum lower value in the interval, we need to move the left pointer.
    - Unfortunately, we need to make a more advanced program to make it pass in time.
    - We use segment tree + binary search to look where to move the left pointer to instead of iterating over the position.
    - There is also the problem of memory usage being to high when using just regular scanf and printf
    - We need to use either cin/cout + optimization or a custom fast scan function like i did.
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

const int N=1e6+5;
vector<int> lo(N),hi(N);
struct SegmentTree{
    vector<int> m;
    int n;
    void init(int nn)
    {
        n=nn;
        m.resize(2*n);
        for(int i=n;i<2*n;i++)
            m[i]=lo[i-n];
        for(int j=n-1;j>0;j--)
            m[j]=max(m[2*j],m[2*j+1]);
    }
    void set(int i,int k)
    {
        i+=n;
        m[i]=k;
        i>>=1;
        for(;i;i>>=1)
            m[i]=max(m[2*i],m[2*i+1]);
    }
    int get(int l,int r)
    {
        int ma=INT_MIN;
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1)
        {
            if(l%2==1)
            {
                ma=max(ma,m[l]);
                l++;
            }
            if(r%2==0)
            {
                ma=max(ma,m[r]);
                r--;
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
    int n;
    fastscan(n);
    for(int i=0;i<n;i++)
        fastscan(lo[i]),fastscan(hi[i]);
    m.init(n);
    int l=0;
    int maxx=INT_MIN;
    int res=0;
    for(int i=0;i<n;i++)
    {
        if(hi[i]<maxx)
        {
            l++;
            int r=i;
            while(l<r)
            {
                int mid=(l+r)/2;
                int d=m.get(mid,i);
                //printf("%i-%i   [%i][%i]=%i\n",l,r,mid,i,d);
                if(hi[i]<d)
                {
                    l=mid+1;
                }
                else
                {
                    r=mid;
                }
            }
            maxx=m.get(l,i);
        }
        maxx=max(maxx,lo[i]);
        res=max(res,i-l+1);
        //printf("%i-%i %i  %i\n",l,i,maxx,res);
    }
    cout << res;
    return 0;
}
