/*
    -Use dsu (query 2 is the merge operation).
    -In each node keep a hash of what numbers i have and what numbers i need (The hash is the difference between the elements of p and the elements of q).
    -In order for the cloud to be good when merging two sets, the has of the first has to be equal to -1*hash of the second.
    -We can count this using a map (gp_hash_table to make it faster)
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define ll long long
#define pb push_back

using namespace std;

__gnu_pbds::gp_hash_table<ll,int> cnt;

const int N=1e6+1;
const ll mod=8473968574039; //just a random large number
vector<int> par(N),siz(N,1),p,q;
vector<ll> pwr(1,1),hsh(N);
int n,qq;
ll ans4;
int ans3;
ll mul(ll a,ll b)
{
    return a*b%mod;
}
ll add(ll a,ll b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
ll sub(ll a,ll b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
int find(int tr)
{
    if(par[tr]==tr)
        return tr;
    return par[tr]=find(par[tr]);
}
void query(int a,int b,int t)
{
    int pa=p[a],pb=p[b];
    if(t==1)
        swap(p[a],p[b]);
    a=find(a);
    b=find(b);
    if(a==b)
        return;
    cnt[hsh[a]]-=siz[a];
    if(hsh[a]!=0)
        ans4-=(ll)siz[a]*cnt[sub(0,hsh[a])],ans3--;
    if(hsh[b]!=0)
        ans4-=(ll)siz[b]*cnt[sub(0,hsh[b])],ans3--;
    cnt[hsh[b]]-=siz[b];
    if(t==1)
    {
        hsh[a]=sub(hsh[a],pwr[pa]);
        hsh[a]=add(hsh[a],pwr[pb]);
        hsh[b]=sub(hsh[b],pwr[pb]);
        hsh[b]=add(hsh[b],pwr[pa]);
        if(hsh[b]!=0)
            cnt[hsh[b]]+=siz[b],ans4+=(ll)siz[b]*cnt[sub(0,hsh[b])],ans3++;
    }
    else
    {
        hsh[a]=add(hsh[a],hsh[b]);
        siz[a]+=siz[b];
        par[b]=a;
    }
    if(hsh[a]!=0)
        cnt[hsh[a]]+=siz[a],ans4+=(ll)siz[a]*cnt[sub(0,hsh[a])],ans3++;
}
int main()
{
	for(int i=0;i<N;i++)
        par[i]=i,pwr.pb(mul(pwr.back(),N));
    scanf("%i %i",&n,&qq);
    p.resize(n);
    for(int i=0;i<n;i++)
        scanf("%i",&p[i]);
    q=p;
    sort(q.begin(),q.end());
    for(int i=0;i<n;i++){
        hsh[i]=add(hsh[i],pwr[p[i]]),hsh[i]=sub(hsh[i],pwr[q[i]]),cnt[hsh[i]]++;
        if(hsh[i]!=0)
            ans4+=cnt[sub(0,hsh[i])],ans3++;
    }
    while(qq--)
    {
        int t,a,b;
        scanf("%i",&t);
        if(t==1||t==2)
            scanf("%i %i",&a,&b),query(a-1,b-1,t);
        if(t==3)
            printf(ans3==0?"DA\n":"NE\n");
        if(t==4)
            printf("%lld\n",ans4);
    }
    return 0;
}
