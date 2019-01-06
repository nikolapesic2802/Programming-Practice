#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=100;
const int K=1e5+5;
int dp[K][2];
vector<int> rem;
int calc(int k,int p)
{
    if(dp[k][p]!=-1)
        return dp[k][p];
    if(p==0)
    {
        dp[k][p]=1;
        for(auto d:rem)
        {
            if(d<=k)
            {
                int a=calc(k-d,1);
                if(a==0)
                    dp[k][p]=0;
            }
        }
    }
    else
    {
        dp[k][p]=0;
        for(auto d:rem)
        {
            if(d<=k)
            {
                int a=calc(k-d,0);
                if(a==1)
                    dp[k][p]=1;
            }
        }
    }
    return dp[k][p];
}
int main()
{
    memset(dp,-1,sizeof(dp));
    int n,k;
    scanf("%i %i",&n,&k);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        rem.pb(a);
    }
    if(calc(k,0)==0)
        printf("First\n");
    else
        printf("Second\n");
    return 0;
}
