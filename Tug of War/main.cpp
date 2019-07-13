/*
    -Make a graph where the nodes are the spots and edges connect the two spots someone is willing to take and have a weight equal to the strength of that person.
    -While there are nodes that have degrees less than 2, either print NO (if the degree is 0) or assign the person to that node.
    -Now we are left with a graph containing only cycles. For each cycle there are two options for the difference between teams.
    -Do knapsack with dp on these values to get AC.
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

const int N=6e4+1,M=3e5+1;
vector<int> degree(N),visited(N);
vector<multiset<pair<int,int> > > graf(N);
int dif,n,k,a,b,c;
void dfs(int tr)
{
    if(graf[tr].size()==0)
        return;
    int sl=(*graf[tr].begin()).f;
    int t=(*graf[tr].begin()).s;
    graf[tr].erase(graf[tr].begin());
    graf[sl].erase(graf[sl].find({tr,t}));
    if(tr<n)
        dif+=t;
    else
        dif-=t;
    dfs(sl);
}
bitset<3*M/2> moze;
int main()
{
	scanf("%i %i",&n,&k);
	for(int i=0;i<2*n;i++)
        scanf("%i %i %i",&a,&b,&c),a--,b+=n-1,graf[a].insert({b,c}),graf[b].insert({a,c}),degree[a]++,degree[b]++;
    queue<int> q;
    for(int i=0;i<2*n;i++)
        if(degree[i]==1)
            q.push(i);
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        visited[tr]=1;
        if(graf[tr].size()==0)
            continue;
        int sl=(*graf[tr].begin()).f;
        int t=(*graf[tr].begin()).s;
        graf[tr].erase(graf[tr].begin());
        degree[tr]--;
        degree[sl]--;
        graf[sl].erase(graf[sl].find({tr,t}));
        if(degree[sl]==1)
            q.push(sl);
        if(tr<n)
            dif+=t;
        else
            dif-=t;
    }
    vector<int> dp={abs(dif)};
    dif=0;
    for(int i=0;i<2*n;i++)
    {
        if(!visited[i])
        {
            if(degree[i]!=2)
            {
                printf("NO\n");
                return 0;
            }
            dfs(i);
            dp.pb(abs(dif));
            dif=0;
        }
    }
    sort(dp.rbegin(),dp.rend());
    while(dp.size()&&dp.back()==0)
        dp.pop_back();
    if(dp.empty())
    {
        printf("YES\n");
        return 0;
    }
    moze[M/2]=1;
    for(auto p:dp)
        moze=(moze<<p)|(moze>>p);
    bool ima=false;
    for(int i=M/2;i<=M/2+k;i++)
        if(moze[i])
            ima=true;
    if(ima)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
