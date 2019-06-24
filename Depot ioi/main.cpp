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
vector<pair<int,pair<int,int> > > ins;
vector<vector<pair<int,pair<int,int> > > > undo;
vector<vector<int> > order;
vector<int> roww(16),fieldrow(16);
vector<bool> napred(16);
int n,N;
bool insert(int row,int tr)
{
    if(roww[tr]<row)
        return false;
    if(row==0)
        undo.pb(ins);
    if((int)field.size()==row)
    {
        if((int)order.size()<=row)
            return false;
        if(order[row][0]>tr)
            return false;
        if(roww[tr]==row&&order[row][0]!=tr)
            return false;
        field.pb({tr});
        undo.back().pb({-1,{-1,-1}});
        undo.back().pb({-2,{tr,fieldrow[tr]}});
        fieldrow[tr]=row;
        return true;
    }
    int i=lower_bound(all(field[row]),tr)-field[row].begin();
    if(i==(int)field[row].size())
    {
        if((int)order[row].size()<=(int)field[row].size())
            return false;
        if(order[row][i]>tr)
            return false;
        if(roww[tr]==row&&order[row][i]!=tr)
            return false;
        field[row].pb(tr);
        undo.back().pb({-1,{row,row}});
        undo.back().pb({-2,{tr,fieldrow[tr]}});
        fieldrow[tr]=row;
        return true;
    }
    bool test=insert(row+1,field[row][i]);
    if(!test)
        return test;
    if(order[row][i]>tr)
        return false;
    if(roww[tr]==row&&order[row][i]!=tr)
            return false;
    undo.back().pb({row,{i,field[row][i]}});
    field[row][i]=tr;
    undo.back().pb({-2,{tr,fieldrow[tr]}});
    fieldrow[tr]=row;
    return true;
}
void undoo()
{
    for(auto p:undo.back())
    {
        if(p.f==-2)
        {
            fieldrow[p.s.f]=p.s.s;
            continue;
        }
        if(p.f==-1)
        {
            if(p.s.f==-1)
                field.pop_back();
            else
                field[p.s.f].pop_back();
        }
        else
            field[p.f][p.s.f]=p.s.s;
    }
    undo.pop_back();
}
vector<int> values;
bool taken[15];
vector<int> orderr;
int cnt=0;
void genAnswers()
{
    if(cnt==N)
    {
        for(auto p:orderr)
            printf("%i ",values[p]);
        printf("\n");
        return;
    }
    int manjih=0;
    for(int i=0;i<N;i++)
    {
        if(!taken[i])
        {
            if(roww[i]>manjih)
                return;
            manjih++;
        }
        else
        {
            if(roww[i]-fieldrow[i]>manjih)
                return;
        }
    }
    for(int i=0;i<N;i++)
    {
        if(cnt==0&&!napred[i]){
            if(!taken[i])
                manjih++;
            continue;
        }
        if(!taken[i])
        {
            bool tr=insert(0,i);
            if(tr)
            {
                orderr.pb(i);
                taken[i]=1;
                cnt++;
                genAnswers();
                cnt--;
                taken[i]=0;
                orderr.pop_back();
            }
            undoo();
            manjih++;
        }
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
        for(auto p:order[i])
            roww[p]=i;
    for(int i=0;i<(int)order.size();i++)
        for(int j=1;j<(int)order[i].size();j++)
            if(order[i][j]<order[i][j-1])
                return 0;
    for(int i=1;i<(int)order.size();i++)
        if(order[i].size()>order[i-1].size())
            return 0;
    //napred[11]=1;
    for(int i=0;i<(int)order.size();i++)
        napred[order[i][0]]=1;
    genAnswers();
    return 0;
}
