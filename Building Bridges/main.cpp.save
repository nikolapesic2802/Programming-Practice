/*
    - Save in a segment tree for every future height, the heights at which we would benefit from taking the current pillar
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
int N;
pair<int,ll> nul=make_pair(-1,-1);
vector<int> convert;
map<int,int> mapa;

struct segmentTreee{
    vector<pair<int,ll> > lazy;
    vector<bool> iszero;
    vector<ll> inc;
    void init()
    {
        lazy.resize(8*N);
        inc.resize(8*N);
        iszero.resize(8*N);
        //fill(lazy.begin(),lazy.end(),nul);
    }
    void increase(int qs,int qe,ll x,int i=1,int l=0,int r=N-1)
    {
        if(qe<l||qs>r){
            return;
        }
        if(iszero[i])
        {
            iszero[2*i]=true;
            inc[2*i]=0;
            iszero[2*i+1]=true;
            inc[2*i+1]=0;
            iszero[i]=false;
        }
        if(qs<=l&&r<=qe)
        {
            inc[i]+=x;
            return;
        }
        int m=(l+r)>>1;
        increase(qs,qe,x,2*i,l,m);
        increase(qs,qe,x,2*i+1,m+1,r);
    }
    void set(int qs,int qe,pair<int,ll> x,int i=1,int l=0,int r=N-1)
    {
        //printf("Usao za %i %i %i %i %i %i\n",qs,qe,x.first,i,l,r);
        if(qe<l||qs>r)
            return;
        if(qs<=l&&r<=qe)
        {
            lazy[i]=x;
            iszero[i]=true;
            inc[i]=0;
            return;
        }
        if(iszero[i]){
            iszero[2*i]=true;
            inc[2*i]=0;
            iszero[2*i+1]=true;
            inc[2*i+1]=0;
            iszero[i]=false;
        }
        else
        {
            if(inc[i]!=0)
            {
                //printf("%i\n",inc[i]);
                if(iszero[2*i])
                {
                    inc[2*i]=0;
                    iszero[4*i]=true;
                    iszero[4*i+1]=true;
                }
                iszero[2*i]=false;
                if(iszero[2*i+1])
                {
                    inc[2*i+1]=0;
                    iszero[4*i+2]=true;
                    iszero[4*i+3]=true;
                }
                iszero[2*i+1]=false;
                inc[2*i+1]+=inc[i];
                inc[2*i]+=inc[i];
                inc[i]=0;
            }
        }
        int m=(l+r)>>1;
        set(qs,qe,x,2*i,l,m);
        set(qs,qe,x,2*i+1,m+1,r);
    }
    pair<int,ll> get(int p,int i=1,int l=0,int r=N-1)
    {
        if(p<l||p>r)
            return nul;
        if(p<=l&&r<=p)
        {
            return mp(lazy[i].first,lazy[i].second+inc[i]);
        }
        if(lazy[i]!=nul){
            lazy[2*i]=lazy[i];
            lazy[2*i+1]=lazy[i];
            lazy[i]=nul;
        }
        int m=(l+r)>>1;
        if(iszero[i]){
            iszero[2*i]=true;
            inc[2*i]=0;
            iszero[2*i+1]=true;
            inc[2*i+1]=0;
            iszero[i]=false;
        }
        else
        {
            if(inc[i]!=0)
            {
                //printf("%i\n",inc[i]);
                if(iszero[2*i])
                {
                    inc[2*i]=0;
                    iszero[4*i]=true;
                    iszero[4*i+1]=true;
                }
                iszero[2*i]=false;
                if(iszero[2*i+1])
                {
                    inc[2*i+1]=0;
                    iszero[4*i+2]=true;
                    iszero[4*i+3]=true;
                }
                iszero[2*i+1]=false;
                inc[2*i+1]+=inc[i];
                inc[2*i]+=inc[i];
                inc[i]=0;
            }
        }
        pair<int,ll> pp=get(p,2*i,l,m);
        if(pp!=nul){
            //get(p,2*i+1,m+1,r);
            return pp;
        }
        return get(p,2*i+1,m+1,r);
    }
} ST;
int hi,y,we;
ll W;
ll calc(int mid)
{
    int i=mid;
    mid=convert[i];
    ll o1=(ll)(mid-hi)*(ll)(mid-hi)+(ll)(hi-y)*(hi-y)+W;
    pair<int,ll> lol=ST.get(i);
    int y2=convert[lol.first];
    ll W2=lol.second;
    ll o2=(ll)(mid-y2)*(mid-y2)+we+W2;
    return o1-o2;
}
int offset=10000;
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> h(n),w(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&h[i]);
        convert.pb(h[i]);
    }
    sort(convert.begin(),convert.end());
    convert.erase(unique(convert.begin(),convert.end()),convert.end());
    for(int i=0;i<convert.size();i++)
        mapa[convert[i]]=i;
    N=convert.size();
    ST.init();
    for(int i=0;i<n;i++)
    {
        scanf("%i",&w[i]);
    }
    //ll res1=calc(n-2,h[n-1]);
    //printf("%lld\n",calc(n-2,h[n-1]));
    ST.set(0,N-1,mp(mapa[h[0]],0));
    //ST1.set(0,N-1,mp(mapa[h[0]],0));
    //printf("Stavio od 0 do %i na %i %i\n",N,h[0],0);
    for(int i=1;i<n-1;i++)
    {
        /*if(i>50000)
            assert(0);*/
        /*for(int j=0;j<N;j++)
        {
            pair<int,ll> lol=ST.get(j);
            pair<int,ll> lol2=ST1.get(j);
            if(lol!=lol2)
            {
                printf("%i: %i %lld   %i %lld\n",j,lol.first,lol.second,lol2.first,lol2.second);
                exit(0);
            }
        }*/
        //printf("Usao za %i  %i %i\n",i,h[i],w[i]);
        pair<int,ll> lol=ST.get(mapa[h[i]]);
        /*pair<int,ll> lol2=ST1.get(mapa[h[i]]);
        if(lol!=lol2)
        {
            printf("%i\n",i);
        }*/
        y=convert[lol.first];
        W=lol.second;
        hi=h[i];
        we=w[i];
        int l=0,r=N-1;
        ll cl=calc(l);
        ll calcr=calc(r);
        bool tru=false;
        if(calcr>=0)
        {
            /*if(calc(r-1)>=calcr){
                ST.increase(0,N-1,w[i]);
                //ST1.increase(0,N-1,w[i]);
                //printf("Dodajem %i na sve!\n",w[i]);
                continue;
            }*/
        }
        else
        {
            tru=true;
        }
        if(cl>=0)
        {
            /*if(calc(l+1)>cl)
            {
                ST.increase(0,N-1,w[i]);
                //ST1.increase(0,N-1,w[i]);
                //printf("Dodajem %i na sve!\n",w[i]);
                continue;
            }*/
            l++;
            while(l<r)
            {
                int mid=(l+r)>>1;
                ll t=calc(mid);
                if(t<0)
                {
                    r=mid;
                }
                else{
                if(t>=cl)
                {
                    r=mid-1;
                }
                else{
                if(t>=calcr)
                {
                    l=mid+1;
                }
                else{
                ll t2=calc(mid+1);
                if(t2<=t)
                {
                    l=mid+1;
                }
                else
                {
                    r=mid-1;
                }
                }}}
            }
        }
        if(calc(l)>=0)
        {
            ST.increase(0,N-1,w[i]);
            //ST1.increase(0,N-1,w[i]);
            //printf("Dodajem %i na sve!\n",w[i]);
        }
        else{
        if(tru)
        {
            if(l>0){
            ST.increase(0,l-1,w[i]);
            //ST1.increase(0,l-1,w[i]);
            //printf("Dodajem %i od %i do %i!\n",w[i],0,l-1);
            }
            ST.set(l,N-1,mp(mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W));
            //ST1.set(l,N-1,mp(mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W));
            //printf("Stavljam1 od %i do %i na %i %lld\n",l,N-1,mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W);
        }
        else{
        int left=l,right=N-2;
        if(N-2-l>offset)
        {
            if(calc(l+offset)>=0)
                right=l+offset-1;
            else
                left+=offset;
        }
        if(right-left>offset)
        {
            if(calc(right-offset)<=0)
                left=right-offset;
            else
                right-=offset;
        }
        while(left<right)
        {
            int mid=(left+right)>>1;
            ll t=calc(mid);
            if(t<0)
            {
                if(calc(mid+1)>=0)
                {
                    left=mid;
                    right=mid;
                }
                else
                {
                    left=mid+1;
                }
            }
            else
            {
            if(t>=cl)
            {
                right=mid-1;
            }
            else{
            if(t>=calcr)
            {
                left=mid+1;
            }
            else{
            ll t2=calc(mid+1);
            if(t2<=t)
            {
                left=mid+1;
            }
            else
            {
                right=mid-1;
            }
            }}}
        }
        ST.set(l,left,mp(mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W));
        //ST1.set(l,left,mp(mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W));
        //printf("Stavljam2 od %i do %i na %i %lld\n",l,left,mapa[h[i]],(ll)(h[i]-y)*(h[i]-y)+W);
        if(l>0){
            ST.increase(0,l-1,w[i]);
            //ST1.increase(0,l-1,w[i]);
            //printf("Dodajem %i od %i do %i!\n",w[i],0,l-1);
        }
        if(left<N-1){
            ST.increase(left+1,N-1,w[i]);
            //ST1.increase(left+1,N-1,w[i]);
            //printf("Dodajem %i od %i do %i!\n",w[i],left+1,N-1);
        }
        }}
    }
    int i=n-1;
    pair<int,ll> lol=ST.get(mapa[h[i]]);
    /*pair<int,ll> lol2=ST1.get(mapa[h[i]]);
    if(lol!=lol2)
    {
        printf("END!\n");
    }*/
    int y=convert[lol.first];
    ll W=lol.second;
    //printf("%i %lld %i\n",y,W,h[i]);
    ll res=(ll)(h[i]-y)*(h[i]-y)+W;
    printf("%lld\n",res);
    return 0;
}

