/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/NOI/official
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
	priority_queue<ll> lefts;
	priority_queue<ll,vector<ll>,greater<ll> > rights;
	int n,h;
	scanf("%i %i",&n,&h);
	int x;
	scanf("%i",&x);
	lefts.push(x);
	rights.push(x);
	ll sol=0;
	for(int i=1;i<n;i++)
    {
        int x;
        scanf("%i",&x);
        ll shift=(ll)i*h;
        ll left_border=lefts.top()-shift;
        ll right_border=rights.top()+shift;
        if(x<left_border)
        {
            lefts.push(x+shift);
            lefts.push(x+shift);
            lefts.pop();
            rights.push(left_border-shift);
            sol+=left_border-x;
            continue;
        }
        if(x>right_border)
        {
            rights.push(x-shift);
            rights.push(x-shift);
            rights.pop();
            lefts.push(right_border+shift);
            sol+=x-right_border;
            continue;
        }
        lefts.push(x+shift);
        rights.push(x-shift);
    }
    printf("%lld\n",sol);
    return 0;
}
