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

const int N=501;
int n,k,c;
gp_hash_table<ll,bool> visited;
struct o;
set<o> ok;
vector<vector<int> > values(N,vector<int>(6));
struct o{
    set<int> s;
    int score;
    ll get_hash()
    {
        ll h=0;
        for(auto p:s)
            h=h*N+p;
        return h;
    }
    void calcScore()
    {
        vector<int> best(k);
        for(auto p:s)
            for(int i=0;i<k;i++)
                best[i]=max(best[i],values[p][i]);
        score=0;
        for(auto p:best)
            score+=p;
    }
    void add_values()
    {
        vector<int> imam(n);
        for(auto p:s)
            imam[p]=1;
        set<int> novi=s;
        for(int i=0;i<k;i++)
        {
            int b=*s.begin();
            s.erase(s.begin());
            novi.erase(b);
            for(int j=0;j<n;j++)
                if(!imam[j])
                {
                    novi.insert(j);
                    o a;
                    a.s=novi;
                    novi.erase(j);
                    if(visited[a.get_hash()])
                        continue;
                    visited[a.get_hash()]=true;
                    a.calcScore();
                    //assert(a.score<=score);
                    ok.insert(a);
                }
            novi.insert(b);
        }
    }
};
bool operator<(o a,o b)
{
    return a.score>b.score;
}
ostream& operator<<(ostream& out,o a){out << "[" << a.score << ":" << a.s << "]";return out;}
int main()
{
    freopen("input1.txt","r",stdin);
	scanf("%i %i %i",&n,&k,&c);
	for(int i=0;i<n;i++)
        for(int j=0;j<k;j++)
            scanf("%i",&values[i][j]);
    o start,best;
    for(int i=0;i<k;i++)
    {
        start.s.clear();
        int maxx=-1,gde;
        for(int j=0;j<n;j++)
            if(maxx<values[j][i])
                maxx=values[j][i],gde=j;
        start.s.insert(gde);
        best.s.insert(gde);
        for(int j=0;j<n&&(int)start.s.size()<k;j++)
            start.s.insert(j);
        if(visited[start.get_hash()]==0)
        {
            visited[start.get_hash()]=1;
            start.calcScore();
            ok.insert(start);
            start.add_values();
        }
    }
    for(int j=0;j<n&&(int)best.s.size()<k;j++)
        best.s.insert(j);
    if(visited[best.get_hash()]==0)
    {
        visited[best.get_hash()]=1;
        best.calcScore();
        ok.insert(best);
    }
    for(int i=1;i<c;i++)
    {
        o tr=(*ok.begin());
        ok.erase(ok.begin());
        tr.add_values();
    }
    printf("%i\n",(*ok.begin()).score);
    return 0;
}
