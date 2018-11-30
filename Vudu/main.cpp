/*
    - Subtract p from every element, and calculate prefix sums.
    - We need to map every prefix sum value to a new value in range [1,n] and use fenwick tree to calculate the number of left borders that are good for every right border
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back

using namespace std;

const int N=1e6+5;
vector<ll> pre(N);
vector<int> fen(N),mapa(N);
void update(int i){
    for(;i<N;i+=i&(-i))
        fen[i]++;
}
int get(int i){
    int sum=0;
    for(;i;i-=i&(-i))
        sum+=fen[i];
    return sum;
}
int main()
{
    int n,p;
    scanf("%i",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&pre[i]);
    scanf("%i",&p);
    vector<pair<ll,int> > poz;
    for(int i=1;i<=n;i++)
    {
        pre[i]+=pre[i-1]-p;
        poz.pb({pre[i],i});
    }
    poz.pb({0,0});
    sort(poz.begin(),poz.end());
    for(int i=0;i<=n;i++)
        mapa[poz[i].second]=i+1;
    ll ans=0;
    update(mapa[0]);
    for(int i=1;i<=n;i++)
    {
        ans+=get(mapa[i]);
        update(mapa[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
