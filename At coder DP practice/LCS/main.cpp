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
const int N=3e3+1;
int dp[N][N];
int best[N][N];
string s,t;
int calc(int i,int j)
{
    if(i==0||j==0){
        best[i][j]=-2;
        return dp[i][j]=0;
    }
    if(dp[i][j]!=-1)
        return dp[i][j];
    if(s[i]==t[j])
    {
        best[i][j]=-1;
        return dp[i][j]=1+calc(i-1,j-1);
    }
    int a=calc(i-1,j);
    int b=calc(i,j-1);
    if(a>=b)
    {
        best[i][j]=1;
        return dp[i][j]=a;
    }
    best[i][j]=2;
    return dp[i][j]=b;
}
int main()
{
    memset(dp,-1,sizeof(dp));
    cin >> s;
    cin >> t;
    s='0'+s;
    t='0'+t;
    calc(s.size()-1,t.size()-1);
    int i=s.size()-1,j=t.size()-1;
    string sol;
    while(best[i][j]!=-2)
    {
        if(best[i][j]==-1)
        {
            sol+=s[i];
            i--;
            j--;
            continue;
        }
        if(best[i][j]==1)
        {
            i--;
            continue;
        }
        j--;
        continue;
    }
    reverse(all(sol));
    cout << sol << endl;
    return 0;
}
