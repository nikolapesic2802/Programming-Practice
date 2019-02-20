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
set<vector<vector<int> > > s;
void gen(vector<int> orr,int ostalo,vector<vector<int> > dosada)
{
    if(orr.empty())
    {
        for(auto &p:dosada)
            sort(all(p));
        sort(all(dosada));
        s.insert(dosada);
        return;
    }
    for(int i=0;i<=ostalo;i++){
        dosada[orr.back()].pb(i);
        dosada[i].pb(orr.back());
        int undo=orr.back();
        orr.pop_back();
        gen(orr,ostalo+1,dosada);
        orr.pb(undo);
        dosada[orr.back()].pop_back();
        dosada[i].pop_back();
    }
}
int main()
{
	int lim=5;
	for(int m=1;m<lim;m++)
    {
        int n=lim-m;
        s.clear();
        vector<vector<int> > graf(n+m);
        for(int i=0;i<m-1;i++)
        {
            graf[i].pb(i+1);
            graf[i+1].pb(i);
        }
        vector<int> add;
        for(int i=m;i<m+n;i++)
            add.pb(i);
        do{
        gen(add,m-1,graf);
        }while(next_permutation(all(add)));
        printf("%i: %i\n",m,s.size());
        //cout << s << endl;
    }
    return 0;
}
