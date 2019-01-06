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
const int N=1e5+5;
vector<vector<int> > graf(N);
vector<int> sol(N,-1);
int dfs(int tr)
{
    if(sol[tr]!=-1)
        return sol[tr];
    sol[tr]=0;
    for(auto p:graf[tr])
    {
        sol[tr]=max(sol[tr],1+dfs(p));
    }
    return sol[tr];
}
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    vector<int> indegree(n);
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        indegree[b]++;
    }
    int maxx=0;
    for(int i=0;i<n;i++)
    {
        maxx=max(maxx,dfs(i));
    }
    printf("%i\n",maxx);
    return 0;
}
