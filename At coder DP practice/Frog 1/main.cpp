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
    vector<int> h(n+3,INT_MAX);
    for(int i=0;i<n;i++)
        cin >> h[i];
    vector<int> cost(n+3,INT_MAX);
    cost[0]=0;
    for(int i=0;i<n;i++)
    {
        cost[i+1]=min(cost[i+1],cost[i]+abs(h[i]-h[i+1]));
        cost[i+2]=min(cost[i+2],cost[i]+abs(h[i]-h[i+2]));
    }
    printf("%i\n",cost[n-1]);
    return 0;
}
