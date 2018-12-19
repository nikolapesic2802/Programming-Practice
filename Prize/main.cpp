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

static const int max_q = 10000;
static int n;
static int query_count = 0;
static vector<int> g;
static vector<vector<int> > rank_count;

vector<int> ask(int i) {
	query_count++;
	if(query_count > max_q) {
		cerr << "Query limit exceeded" << endl;
		exit(0);
	}

	if(i < 0 || i >= n) {
		cerr << "Bad index: " << i << endl;
		exit(0);
	}

	vector<int> res(2);
	res[0] = rank_count[g[i] - 1][i + 1];
	res[1] = rank_count[g[i] - 1][n] - res[0];
	return res;
}
/*
#include <bits/stdc++.h>
#include "prize.h"
using namespace std;
*/
const int N=2e5+5;
map<int,vector<int> > mapa[N];
int sol=-1;
void solve(int l,int r)
{
    if(sol!=-1||l>r)
        return;
    int m=(l+r)>>1;
    vector<int> cur=ask(m);
    int sum=cur[0]+cur[1];
    if(sum==0)
    {
        sol=m;
        return;
    }
    int left=1,right=1;

    auto it=mapa[sum].upper_bound(m);
    if(it!=mapa[sum].begin()&&mapa[sum].size())
    {
        it--;
        if((*it).second[1]==cur[1])
            left=0;
        it++;
    }
    if(it!=mapa[sum].end())
    {
        if((*it).second[0]==cur[0])
            right=0;
    }
    /*if(it!=mapa[sum].end())
    {
        if((*it).second[0]==cur[0])
            right=0;
    }
    if(it!=mapa[sum].begin())
        it--;
    if(it!=mapa[sum].begin())
    {
        if((*it).second[1]==cur[1])
            left=0;
    }*/
    mapa[sum][m]=cur;
    if(left)
        solve(l,m-1);
    if(right)
        solve(m+1,r);
}
int find_best(int n) {
    solve(0,n-1);
    return sol;
}

int main() {
	cin >> n;

	g.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> g[i];
		if(g[i] < 1) {
			cerr << "Invalid rank " << g[i] << " at index " << i << endl;
			exit(0);
		}
	}

	int max_rank = *max_element(g.begin(), g.end());

	rank_count.resize(max_rank + 1, vector<int>(n + 1, 0));
	for(int r = 0; r <= max_rank; r++) {
		for(int i = 1; i <= n; i++) {
			rank_count[r][i] = rank_count[r][i - 1];
			if(g[i - 1] == r)
			  rank_count[r][i]++;
		}
	}

	for(int i = 0; i <= n; i++)
		for(int r = 1; r <= max_rank; r++)
			rank_count[r][i] += rank_count[r - 1][i];

	int res = find_best(n);
	cout << res << endl << "Query count: " << query_count << endl;

	return 0;
}
