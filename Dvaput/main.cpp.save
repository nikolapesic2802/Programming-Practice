/*
    -Make a function to get a hash value on range [l,r] in O(1).
    -Binary search for the length and check all the ranges to see if there are two with the same hash.
    -Double hash is needed not to get WA
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
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int mod=1e9+9,mul=28;
const int mod2=1e9+7;
int main()
{
	int n;
	scanf("%i",&n);
	string s;
	cin >> s;
	vector<int> h(n),h2(n),pwr(n),pwr2(n);
	pwr[0]=pwr2[0]=1;
	for(int i=1;i<n;i++)
        pwr[i]=(ll)pwr[i-1]*mul%mod;
    for(int i=1;i<n;i++)
        pwr2[i]=(ll)pwr2[i-1]*mul%mod2;
	h[0]=h2[0]=s[0]-'a'+1;
	for(int i=1;i<n;i++)
        h[i]=((ll)h[i-1]*mul+s[i]-'a'+1)%mod;
    for(int i=1;i<n;i++)
        h2[i]=((ll)h2[i-1]*mul+s[i]-'a'+1)%mod2;
    auto get=[&](int l,int r){
        if(l>r)
            return make_pair(0,0);
        int tr=h[r];
        int d=r-l+1;
        if(l)
            tr-=(ll)h[l-1]*pwr[d]%mod;
        if(tr<0)
            tr+=mod;
        int tr2=h2[r];
        if(l)
            tr2-=(ll)h2[l-1]*pwr2[d]%mod2;
        if(tr2<0)
            tr2+=mod2;
        return make_pair(tr,tr2);
    };
    int l=0,r=n-1;
    while(l<r)
    {
        int m=(l+r+1)>>1;
        vector<pair<int,int> > hh;
        for(int i=0;i<n-m+1;i++)
            hh.pb(get(i,i+m-1));
        sort(all(hh));
        bool ima=false;
        for(int i=1;i<(int)hh.size();i++)
            if(hh[i]==hh[i-1])
                ima=true;
        if(ima)
            l=m;
        else
            r=m-1;
    }
    printf("%i\n",l);
    return 0;
}
