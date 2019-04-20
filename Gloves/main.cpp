/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2008_solutions/gloves-sol-en.pdf
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

int main()
{
	int n;
	scanf("%i",&n);
	vector<int> a(n),b(n);
	for(int i=0;i<n;i++)
        scanf("%i",&a[i]);
    for(int i=0;i<n;i++)
        scanf("%i",&b[i]);
    vector<pair<int,int> > pairs,cords;
    for(int i=0;i<1<<n;i++)
    {
        ll l=0,r=0;
        for(int j=0;j<n;j++)
            if(i&(1<<j))
                l+=a[j];
            else
                r+=b[j];
        pairs.pb({l,r});
    }
    sort(all(pairs));
    for(auto p:pairs)
    {
        while(cords.size()&&cords.back().s<=p.s)
            cords.pop_back();
        cords.pb(p);
    }
    ll lsol=INT_MAX,rsol=INT_MAX;
    for(int i=1;i<cords.size();i++)
        if(cords[i-1].f+cords[i].s+2<lsol+rsol)
            lsol=cords[i-1].f+1,rsol=cords[i].s+1;
    printf("%lld\n%lld\n",lsol,rsol);
    return 0;
}
