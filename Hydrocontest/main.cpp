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
const int N=1e3+5;
vector<vector<int> > graf(N);
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    for(int i=0;i<n;i++)
    {
        vector<vector<int> > visited(n,vector<int>(2));
        queue<pair<int,int> > q;
        vector<int> depend[n][2];
        q.push({i,0});
        vector<pair<int,int> > order;
        while(q.size())
        {
            pair<int,int> tr=q.front();
            order.pb(tr);
            q.pop();
            int nxt=(tr.s+1)%2;
            for(auto p:graf[tr.f])
            {
                if(visited[p][nxt])
                    continue;
                visited[p][nxt]=1;
                depend[tr.f][tr.s].pb(p);
            }
        }
        vector<vector<int> > solution(n,vector<int>(2));
        reverse(all(order));
        for(auto p:order)
        {
            bool win=false;
            int nxt=(p.s+1)%2;
            for(auto d:depend[p.f][p.s])
            {
                if(solution[d][nxt]==p.s)
                {
                    win=true;
                    break;
                }
            }
            if(win)
                solution[p.f][p.s]=p.s;
            else
                solution[p.f][p.s]=nxt;
        }
        printf("%i\n",solution[i][0]+1);
    }
    return 0;
}