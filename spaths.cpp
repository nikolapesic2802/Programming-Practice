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
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=2e3+5,M=1e5+1;
vector<vector<pair<int,int> > > graf(N);
int n,m,a,b,k;
map<pair<int,int>,int> ind;
vector<vector<int> > dist(N,vector<int>(N,INT_MAX));
vector<int> in(N);
vector<pair<int,int> > q[M];
vector<int> st(M);
vector<vector<int> > ev(N);
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	n=2000;
	m=100000;
	a=1;
	b=2000;
	//scanf("%i %i %i %i",&n,&m,&a,&b);
	a--;b--;
	vector<pair<pair<int,int>,int> > edges;
	for(int i=0;i<n-1;i++)
        edges.pb({{i,i+1},1});
    for(int i=n-1;i<m;i++){
        int x=rng()%n;
        int y=rng()%n;
        while(x==y)
            y=rng()%n;
        int z=rng()%m+1;
        edges.pb({{x,y},z});
    }
	/*for(int i=0;i<m;i++){
        int x,y,z;
        scanf("%i %i %i",&x,&y,&z);
        x--;y--;
        edges.pb({{x,y},z});
	}*/
	k=n;
	for(int i=0;i<k;i++)
        in[i]=i;
	/*scanf("%i",&k);
	for(int i=0;i<k;i++)
        scanf("%i",&in[i]),in[i]--;*/
    vector<int> napred(k),nazad(k);
	for(int i=1;i<k;i++)
        ind[{in[i],in[i-1]}]=ind[{in[i-1],in[i]}]=i;
    for(auto p:edges)
        if(!ind[p.f])
            graf[p.f.f].pb({p.f.s,p.s}),graf[p.f.s].pb({p.f.f,p.s});
        else
            napred[ind[p.f]]=nazad[ind[p.f]-1]=p.s;
    for(int i=1;i<k;i++)
        napred[i]+=napred[i-1];
    for(int i=k-2;i>=0;i--)
        nazad[i]+=nazad[i-1];
    for(int i=0;i<k;i++){
        dist[i][in[i]]=0;
        q[0].pb({i,in[i]});
    }
    int kk=0;
    for(int t=0;t<10*M;t++){
        while(st[kk]!=q[kk].size()){
            int d=q[kk][st[kk]].f,i=q[kk][st[kk]++].s;
            if(t!=dist[d][i])
                continue;
            for(auto p:graf[i]){
                if(dist[d][p.f]>t+p.s){
                    dist[d][p.f]=t+p.s;
                    int o=kk+p.s;
                    if(o>=M)
                        o-=M;
                    q[o].pb({d,p.f});
                }
            }
        }
        kk++;
        if(kk>=M)
            kk-=M;
    }
    for(int i=0;i<k;i++){
        for(int j=i+1;j<k;j++){
            int d=dist[i][in[j]];
            if(d!=INT_MAX)
                ev[i].pb(d+napred[i]+nazad[j]),ev[j].pb(-d-napred[i]-nazad[j]);
        }
    }
    return 0;
    multiset<int> s;
    for(int i=0;i<k-1;i++){
        for(auto p:ev[i])
            if(p<0)
                s.erase(s.find(-p));
            else
                s.insert(p);
        if(s.size())
            printf("%i\n",*s.begin());
        else
            printf("-1\n");
    }
    return 0;
}
