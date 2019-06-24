/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2001/sol.pdf
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

vector<vector<pair<int,pair<int,int> > > > undo;
vector<pair<int,pair<int,int> > > y;
vector<vector<int> > order;
vector<int> values,off;
int n,N;
bool del(int row,int val)
{
    if(row==-1)
    {
        off.pb(val);
        return true;
    }
    int pos=lower_bound(all(order[row]),val)-order[row].begin();
    if(pos==0)
        return false;
    pos--;
    int sta=order[row][pos];
    undo.back().pb({order[row][pos],{row,pos}});
    order[row][pos]=val;
    return del(row-1,sta);
}
void genAnswers()
{
    if(order[0].empty())
    {
        for(int i=off.size()-1;i>=0;i--)
            printf("%i ",values[off[i]]);
        printf("\n");
        return;
    }
    for(int i=0;i<n;i++)
    {
        if(i!=n-1&&order[i].size()==order[i+1].size())
            continue;
        undo.pb(y);
        if(!del(i-1,order[i].back())){
            undo.pop_back();
            continue;
        }
        undo.back().pb({-1,{i,order[i].back()}});
        order[i].pop_back();
        genAnswers();
        for(auto p:undo.back())
            if(p.f==-1)
                order[p.s.f].pb(p.s.s);
            else
                order[p.s.f][p.s.s]=p.f;
        undo.pop_back();
        off.pop_back();
    }
}
int main()
{
	scanf("%i",&n);
	order.resize(n);
	for(int i=0;i<n;i++)
    {
        int k;
        scanf("%i",&k);
        N+=k;
        order[i].resize(k);
        for(int j=0;j<k;j++){
            scanf("%i",&order[i][j]);
            values.pb(order[i][j]);
        }
    }
    sort(all(values));
    gp_hash_table<int,int> mapa;
    for(int i=0;i<N;i++)
        mapa[values[i]]=i;
    for(auto &p:order)
        for(auto &d:p)
            d=mapa[d];
    for(int i=0;i<(int)order.size();i++)
        for(int j=1;j<(int)order[i].size();j++)
            if(order[i][j]<order[i][j-1])
                return 0;
    for(int i=1;i<(int)order.size();i++)
        if(order[i].size()>order[i-1].size())
            return 0;
    order.pb({});
    genAnswers();
    return 0;
}
