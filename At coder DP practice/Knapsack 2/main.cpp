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
const int N=101;
const int W=1e5+1;
ll dp[N][W];
int main()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<W;j++)
            dp[i][j]=LLONG_MAX;
    }
    int n,w;
    scanf("%i %i",&n,&w);
    vector<pair<int,int> > items(n);
    for(int i=0;i<n;i++)
        scanf("%i %i",&items[i].f,&items[i].s);
    dp[0][0]=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<W;j++)
        {
            if(dp[i][j]!=LLONG_MAX)
            {
                dp[i+1][j+items[i].s]=min(dp[i+1][j+items[i].s],dp[i][j]+items[i].f);
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
            }
        }
    }
    for(int i=W-1;i>=0;i--)
    {
        if(dp[n][i]<=w)
        {
            printf("%i\n",i);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}
