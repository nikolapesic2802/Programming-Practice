#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
const int mod=1e9+7;
ll calc(ll l,ll r)
{
    r%=mod;
    l%=mod;
    ll sol=(r*(r+1)/2)%mod-(l*(l+1)/2)%mod;
    if(sol<0)
        sol+=mod;
    return sol;
}
int main()
{
    ll n;
    scanf("%lld",&n);
    int ans=0;
    for(ll i=1;;)
    {
        ll hi=n/i,lo=n/(i+1);
        ans=(ans+(ll)i*calc(lo,hi))%mod;
        if(lo==0) break;
        i=n/lo;
    }
    printf("%i\n",ans);
    return 0;
}
