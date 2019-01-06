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

int main()
{
    int n;
    scanf("%i",&n);
    int val[n][3];
    for(int i=0;i<n;i++)
        cin >> val[i][0] >> val[i][1] >> val[i][2];
    int dp[n+1][3];
    memset(dp,INT_MIN,sizeof(dp));
    for(int i=0;i<3;i++)
        dp[0][i]=val[0][i];
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                if(j==k)
                    continue;
                dp[i][j]=max(dp[i][j],dp[i-1][k]+val[i][j]);
            }
        }
    }
    printf("%i\n",max(dp[n-1][0],max(dp[n-1][1],dp[n-1][2])));
    return 0;
}
