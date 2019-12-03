#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=1e5+5;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,x,y;
	scanf("%i",&n);
	vector<pair<pair<int,int>,pair<int,int> > > e;
	for(int i=0;i<n;i++)
        scanf("%i %i",&x,&y),e.pb({{x,N-y},{i,1}});
    for(int i=0;i<n;i++)
        scanf("%i %i",&x,&y),e.pb({{x,N-y},{i,2}});
    vector<pair<int,int> > sol;
    set<pair<int,int> > tr;
    ll ans=0;
    sort(all(e));
    int last=0;
    for(auto p:e){
        p.f.s=N-p.f.s;
        ans+=(ll)(p.f.f-last)*tr.size();
        last=p.f.f;
        if(p.s.s==1)
            tr.insert({p.f.s,p.s.f});
        else{
            auto it=*tr.lower_bound({p.f.s,0});
            tr.erase(it);
            ans+=it.f-p.f.s;
            sol.pb({it.s,p.s.f});
        }
    }
    printf("%lld\n",ans);
    for(auto p:sol)
        printf("%i %i\n",p.f+1,p.s+1);
    return 0;
}
