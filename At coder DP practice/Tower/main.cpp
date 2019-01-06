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
const int N=1e3+5;
const int S=1e4+5;
ll dp[N][S];
int w[N],s[N],v[N];
ll calc(int tr,int sss)
{
    if(tr==-1)
        return 0;
    if(dp[tr][sss]!=-1)
        return dp[tr][sss];
    dp[tr][sss]=calc(tr-1,sss);
    int ss=sss;
    if(ss==S-1)
        ss=s[tr];
    else
        ss=min(ss-w[tr],s[tr]);
    if(ss>=0)
        dp[tr][sss]=max(dp[tr][sss],v[tr]+calc(tr-1,ss));
    return dp[tr][sss];
}

int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    scanf("%i",&n);
    vector<pair<pair<int,int>,pair<int,int> > > lol(n);
    for(int i=0;i<n;i++)
        scanf("%i %i %i",&lol[i].s.f,&lol[i].f.s,&lol[i].s.s),lol[i].f.f=lol[i].f.s+lol[i].s.f;
    sort(all(lol));
    for(int i=0;i<n;i++)
    {
        w[i]=lol[i].s.f;
        s[i]=lol[i].f.s;
        v[i]=lol[i].s.s;
    }
    printf("%lld\n",calc(n-1,S-1));
    return 0;
}
