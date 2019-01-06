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
const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int mul(int a,int b)
{
    return ((ll)a*b)%mod;
}
vector<vector<int> > graf(N);
map<int,int> mapa[N][2];
int calc(int tr,int par,int color)
{
    if(mapa[tr][color][par]!=0)
        return mapa[tr][color][par];
    int sol=1;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        if(color==0)
        {
            sol=mul(sol,add(calc(p,tr,0),calc(p,tr,1)));
        }
        else
        {
            sol=mul(sol,calc(p,tr,0));
        }
    }
    mapa[tr][color][par]=sol;
    return sol;
}
int main()
{
    int n;
    scanf("%i",&n);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    printf("%i\n",add(calc(0,-1,0),calc(0,-1,1)));
    return 0;
}
