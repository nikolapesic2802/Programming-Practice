#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

struct func{
    int h;
    ll w;
    func()
    {
        h=-1;
        w=0;
    }
};
ll f(func x,int poz)
{
    ll o=(ll)(x.h-poz)*(x.h-poz)+x.w;
    return o;
}
int N;
struct LiChao{
    vector<func> tr;
    vector<bool> iszero;
    vector<ll> inc;
    void init(func start)
    {
        tr.resize(4*N);
        inc.resize(8*N);
        fill(tr.begin(),tr.end(),start);
    }
    void increase(ll x)
    {
        inc[1]+=x;
    }
    void set(func x, int i=1,int l=0,int r=N)
    {
        int mid=(l+r)>>1;
        func nw=tr[i];
        nw.w+=inc[i];
        tr[i]=nw;
        inc[2*i]+=inc[i];
        inc[2*i+1]+=inc[i];
        inc[i]=0;
        bool lef=f(x,l)<f(tr[i],l);
        bool m=f(x,mid)<f(tr[i],mid);
        if(m)
        {
            swap(tr[i],x);
            inc[i]=0;
        }
        if(r-l==1)
            return;
        if(lef!=m)
            set(x,2*i,l,mid);
        else
            set(x,2*i+1,mid,r);
    }
    ll get(int x,int i=1,int l=0,int r=N)
    {
        int mid=(l+r)>>1;
        func nw=tr[i];
        nw.w+=inc[i];
        tr[i]=nw;
        inc[2*i]+=inc[i];
        inc[2*i+1]+=inc[i];
        inc[i]=0;
        if(r-l==1)
            return f(tr[i],x);
        if(x<mid)
            return min(f(tr[i],x),get(x,2*i,l,mid));
        else
            return min(f(tr[i],x),get(x,2*i+1,mid,r));
    }
} ST;
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> h(n),w(n);
    for(int i=0;i<n;i++){
        scanf("%i",&h[i]);
        N=max(N,h[i]);
    }
    N++;
    for(int i=0;i<n;i++)
        scanf("%i",&w[i]);
    func start;
    start.h=h[0];
    start.w=0;
    ST.init(start);
    for(int i=1;i<n-1;i++)
    {
        //printf("Usao za %i\n",i);
        ll res=ST.get(h[i]);
        //printf("Resenje za %i: %lld\n",i,res);
        ST.increase(w[i]);
        func nxt;
        nxt.h=h[i];
        nxt.w=res;
        ST.set(nxt);
    }
    ll res=ST.get(h[n-1]);
    printf("%lld\n",res);
    return 0;
}
