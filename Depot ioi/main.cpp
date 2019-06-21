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

vector<vector<int> > field;
void insert(int row,int tr)
{
    if((int)field.size()==row)
    {
        field.pb({tr});
        return;
    }
    for(auto &p:field[row])
        if(p>tr)
        {
            insert(row+1,p);
            p=tr;
            return;
        }
    field[row].pb(tr);
}
int main()
{
	int n;
	scanf("%i",&n);
	vector<vector<int> > order(n);
	vector<int> values;
	for(int i=0;i<n;i++)
    {
        int k;
        scanf("%i",&k);
        order[i].resize(k);
        for(int j=0;j<k;j++)
            scanf("%i",&order[i][j]),values.pb(order[i][j]);
    }
    sort(all(values));
    /*gp_hash_table<int,int> mapa;
    for(int i=0;i<(int)values.size();i++)
        mapa[values[i]]=i;
    for(auto &p:order)
        for(auto &d:p)
            d=mapa[d];*/
    int m=values.size();
    vector<int> perm=values;
    /*for(int i=0;i<m;i++)
        perm.pb(i);*/
    do{
        field.clear();
        for(auto p:perm)
            insert(0,p);
        if(field==order)
            cout << perm << endl;
    }while(next_permutation(all(perm)));
    return 0;
}