/*
    -Just a lot of prefix and suffix sums
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

int main()
{
	int n;
	scanf("%i",&n);
	string s;
	cin >> s;
	s=' '+s;
	vector<int> prefixI(n+2),prefixJ(n+2),prefixO(n+2);
	vector<ll> vrednost(n+2),vr(n+2);
	for(int i=1;i<=n;i++)
    {
        if(s[i]=='J')
            prefixJ[i]++;
        if(s[i]=='O')
            prefixO[i]++;
        if(s[i]=='I')
            prefixI[i]++;
    }
    for(int i=1;i<=n+1;i++)
    {
        prefixJ[i]+=prefixJ[i-1];
        prefixI[i]+=prefixI[i-1];
        prefixO[i]+=prefixO[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='O')
            vrednost[i]=prefixJ[i],vr[i]=prefixI[n+1]-prefixI[i];
    }
    for(int i=1;i<=n+1;i++)
        vrednost[i]+=vrednost[i-1];
    for(int i=n;i>=0;i--)
        vr[i]+=vr[i+1];
    ll best=0;
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='I')
            best+=vrednost[i];
    }
    ll maxx=0;
    for(int i=0;i<=n;i++)
    {
        ll add=(ll)prefixJ[i]*(prefixI[n+1]-prefixI[i]);
        add=max(add,vrednost[i]);
        add=max(add,vr[i]);
        maxx=max(maxx,add);z
    }
    printf("%lld\n",best+maxx);
    return 0;
}