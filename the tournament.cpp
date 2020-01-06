/*
    -Overcomplicated solution:
    -First merge all the vertices that are not connected by an edge with a DSU (This can be done in m log m).
    -Interesting fact: there are at most sqrt(m) different connected components.
    -Now find strongly connected components in this compressed graph.
    -At most one SCC will contain all the people that can win. That SCC will be the one with indegree 0. Find it (if it exists) and print all the vertices that it contains.
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
#define ld long double

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=1e5+5,M=5000;
vector<vector<int> > graf(N),svi(N);
vector<vector<int> > rev(M);
vector<int> par(N),mapa(N),other;
int n;
set<int> inds;
int find(int tr){return tr==par[tr]?tr:par[tr]=find(par[tr]);}
void merge(int a,int b){
    a=find(a);
    b=find(b);
    if(a==b)
        return;
    if(svi[a].size()>svi[b].size())
        swap(a,b);
    for(auto p:svi[a])
        svi[b].pb(p);
    svi[a].clear();
    par[a]=b;
    inds.erase(a);
}
int component[M],in[M];
vector<int> order;
bool done[M];
void dfs(int tr){
    done[tr]=1;
    for(auto p:graf[tr])
        if(!done[p])
            dfs(p);
    order.pb(tr);
}
void dfs2(int tr,int c){
    component[tr]=c;
    for(auto p:rev[tr])
        if(!component[p])
            dfs2(p,c);
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    scanf("%i",&n);
    iota(all(par),0);
    vector<pair<int,int> > grane;
    for(int i=0;i<n;i++){
        inds.insert(i);
        svi[i].pb(i);
        int k,a;
        scanf("%i",&k);
        for(int j=0;j<k;j++)
            scanf("%i",&a),graf[i].pb(a-1),grane.pb({i,a-1});
    }
    for(int i=0;i<n;i++){
        int moj=find(i);
        for(auto it=inds.begin();it!=inds.end();){
            if((*it)==moj){
                it++;
                continue;
            }
            bool nasao=0;
            for(auto p:svi[(*it)]){
                auto prvi=lower_bound(all(graf[i]),p),drugi=lower_bound(all(graf[p]),i);
                if((prvi==graf[i].end()||(*prvi)!=p)&&(drugi==graf[p].end()||(*drugi)!=i)){
                    if(svi[(*it)].size()<=svi[moj].size()){
                        int gde=*it;
                        it++;
                        merge(gde,moj);
                        nasao=1;
                        break;
                    }else{
                        merge(moj,*it);
                        moj=*it;
                        it++;
                        nasao=1;
                        break;
                    }
                }
            }
            if(!nasao)
                it++;
        }
    }
    inds.clear();
    for(int i=0;i<n;i++)
        inds.insert(find(i));
    for(int i=0;i<n;i++)
        graf[i].clear();
    n=inds.size();
    bool visited[n],graf2[n][n];
    memset(graf2,0,sizeof(graf2));
    auto it=inds.begin();
    for(int i=0;i<n;i++,it++)
        mapa[*it]=i,other.pb(*it);
    for(auto p:grane)
        if(mapa[find(p.f)]!=mapa[find(p.s)]&&!graf2[mapa[find(p.f)]][mapa[find(p.s)]])
            graf2[mapa[find(p.f)]][mapa[find(p.s)]]=1,graf[mapa[find(p.f)]].pb(mapa[find(p.s)]),rev[mapa[find(p.s)]].pb(mapa[find(p.f)]);
    for(int i=0;i<n;i++)
        if(!done[i])
            dfs(i);
    int trc=1;
    while(order.size()){
        if(!component[order.back()])
            dfs2(order.back(),trc),trc++;
        order.pop_back();
    }
    for(auto p:grane)
        if(component[mapa[find(p.f)]]!=component[mapa[find(p.s)]])
            in[component[mapa[find(p.s)]]]++;
    vector<int> ans;
    for(int i=0;i<n;i++)
        if(!in[component[i]])
            for(auto p:svi[other[i]])
                ans.pb(p);
    sort(all(ans));
    printf("%i ",ans.size());
    for(auto p:ans)
        printf("%i ",p+1);
    return 0;
}
