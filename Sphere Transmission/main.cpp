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

int main()
{
	int n;
	scanf("%i",&n);
	vector<ll> pos;
	for(int i=1;i<=(int)sqrt(n);i++)
    {
        if(n%i==0)
        {
            int br=n/i;
            ll a=(ll)(br)*(br-1)/2;
            a=(ll)a*i;
            a+=(ll)br;
            pos.pb(a);

            br=i;
            a=(ll)(br)*(br-1)/2;
            a=(ll)a*(n/i);
            a+=(ll)br;
            pos.pb(a);
        }
    }
    sort(all(pos));
    pos.erase(unique(all(pos)),pos.end());
    for(auto p:pos)
    {
        printf("%lld ",p);
    }
    return 0;
}
