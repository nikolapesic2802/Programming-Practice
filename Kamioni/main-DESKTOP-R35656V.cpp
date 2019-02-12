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

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

vector<set<int> > graf;
const int N=1e5+5;
vector<int> sol(N);
map<int,int> mapa[N];
vector<vector<int> > route;
bool test(int l1,int r1,int l2,int r2)
{
    printf("Test %i %i  %i %i\n",l1,r1,l2,r2);
    if((l1>r1&&l2>r2)||(l1<r1&&l2<r2))
        return false;
    if(l1>r1)
        return test(l2,r2,l1,r1);
    int d1=r1-l1,d2=l2-r2;
    int d=d1-d2;
    if(d>0)
    {
        r1-=d;
    }
    if(d<0)
    {
        r2-=d;
    }
    if(l1>r2||l2>r1)
        return false;
    return true;
}
void doit(int tr)
{
    printf("Doit %i\n",tr);
    vector<pair<pair<int,int>,pair<int,int> > > events;
    int time=0;
    for(int i=0;i<route[tr].size()-1;i++)
        events.pb({{time,-1},{route[tr][i],route[tr][i+1]}}),time+=abs(route[tr][i]-route[tr][i+1]),events.pb({{time,-2},{route[tr][i],route[tr][i+1]}});
    for(auto p:graf[tr]){
        time=0;
        for(int i=0;i<route[p].size()-1;i++)
            events.pb({{time,1},{route[p][i],route[p][i+1]}}),time+=abs(route[p][i]-route[p][i+1]),events.pb({{route[p][i+1],2},{time,route[p][i+1]}});
    }
    sort(all(events));

}
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	route.resize(n);
	for(int i=0;i<n;i++)
    {
        int k;
        scanf("%i",&k);
        for(int j=0;j<k;j++)
        {
            int a;
            scanf("%i",&a);
            route[i].pb(a);
        }
    }
    graf.resize(n);
    vector<int> degree(n);
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].insert(b);
        graf[b].insert(a);
        mapa[a][b]=i;
        mapa[b][a]=i;
        degree[a]++;
        degree[b]++;
    }
    set<pair<int,int>,greater<pair<int,int> > > d;
    for(int i=0;i<n;i++)
        if(degree[i])
            d.insert({degree[i],i});
    while(d.size())
    {
        auto it=*d.begin();
        d.erase(d.begin());
        doit(it.s);
        for(auto p:graf[it.s])
        {
            d.erase({degree[p],p});
            degree[p]--;
            if(degree[p])
                d.insert({degree[p],p});
            graf[p].erase(it.s);
        }
        graf[it.s].clear();
    }
    for(int i=0;i<m;i++)
        printf("%i\n",sol[i]);
    return 0;
}
