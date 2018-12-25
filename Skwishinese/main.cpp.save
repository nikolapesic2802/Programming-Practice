/*
    -https://www.hackerrank.com/contests/ioi-2014-practice-contest-1/challenges/skwishinese-ioi14/editorial
*/
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
		if(i>0&&i<sz(a))
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=401;
int dp[N][N][N];
string s;
int n;
int calc(int i,int j,int k)
{
    if(j>k)
        return 0;
    if(i>=n)
        return INT_MAX/2;
    if(dp[i][j][k]!=-1)
        return dp[i][j][k];
    int sol1=calc(i+1,j,k);
    int sol2;
    if(s[j]==s[i])
    {
        if(s[k]==s[i])
            sol2=calc(i+1,j+1,k-1);
        else
            sol2=calc(i+1,j+1,k);
    }
    else
    {
        if(s[k]==s[i])
            sol2=calc(i+1,j,k-1);
        else
            sol2=calc(i+1,j,k);
    }
    dp[i][j][k]=min(sol1,sol2+1);
    return dp[i][j][k];
}
int main()
{
	memset(dp,-1,sizeof(dp));
	scanf("%i",&n);
	cin >> s;
	printf("%i\n",calc(0,0,n-1));
    return 0;
}
