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
const int mod=1e9+7;
const int N=1e3+5;
int grid[N][N];
int what[N][N];
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    for(int i=0;i<n;i++)
    {
        string s;
        cin >> s;
        for(int j=0;j<m;j++)
        {
            if(s[j]=='.')
                what[i][j]=0;
            else
                what[i][j]=1;
        }
    }
    for(int i=n-1;i>=0;i--)
    {
        for(int j=m-1;j>=0;j--)
        {
            if(i==n-1&&j==m-1)
            {
                grid[i][j]=1;
                continue;
            }
            if(what[i][j]==0)
            {
                grid[i][j]=add(grid[i+1][j],grid[i][j+1]);
            }
        }
    }
    printf("%i\n",grid[0][0]);
    return 0;
}
