/*
    - Do a dp in O(n^2) where dp[x][y] is the number of ways  to choose x numbers such that the maximum element we have chosen so far is y.
    - Its would be easy if not for the memory limit, because of it you need to save memory
      by memorizing only the current and last dp row and saving values that we need in a map.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()

const int N=1e4;
const int mod=1e6+7;
int dp[2][N];
int pref[N];
int add(int a,int b){
    a+=b;
    if(a>mod)
        a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
map<pair<int,int>,int> resenja;
set<pair<int,int> > trazi;
int main()
{
    int n;
    scanf("%i",&n);
    int res=0;
    int tr=0;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        scanf("%i",&arr[i]);
    for(int i=0;i<n;i++){
        int a=arr[i];
        trazi.insert({n-i-1,tr-2});
        tr=max(tr,a+1);
    }
    trazi.insert({N,N});
    set<pair<int,int> >::iterator it=trazi.begin();
    for(int i=0;i<N;i++){
        dp[0][i]=1;
    }
    while((*it).first<=0)
    {
        resenja[{(*it).first,(*it).second}]=dp[(*it).first][(*it).second];
        it++;
    }
    for(int n=1;n<N;n++)
    {
        pref[0]=dp[(n-1)%2][0];
        for(int i=1;i<N;i++)
        {
            pref[i]=add(pref[i-1],dp[(n-1)%2][i]);
        }
        for(int i=0;i<N-1;i++)
        {
            dp[n%2][i]=add(((ll)dp[(n-1)%2][i]*(i+1))%mod,dp[(n-1)%2][i+1]);
        }
        while((*it).first<=n)
        {
            resenja[{(*it).first,(*it).second}]=dp[((*it).first)%2][(*it).second];
            it++;
        }
    }
    tr=0;
    for(int i=0;i<n;i++){
        int a=arr[i];
        res=add(res,((ll)(a-1)*resenja[{n-i-1,tr-2}])%mod);
        tr=max(tr,a+1);
    }
    res++;
    printf("%i\n",res);
    return 0;
}
