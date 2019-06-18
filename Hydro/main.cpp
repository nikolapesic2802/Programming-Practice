/*
    -We can transform each cycle into a vertex and connect it to all vertexes of the cycle.
    -This gives us a tree that we can do DP on.
    -Because of the shape of the graph, we will always end up where we started.
    -We need to calculate can we reach that spot without having any more available paths and its our opponents turn.
    -For each cycle and each point in the cycle we will calculate if we enter that cycle from that point, can we force us to end up at the end of the cycle and it be out turn/out opponents turn (2 values)
    -If we have a cycle thats connected to the current vertex where we have both choices available, the answer for that vertex is always yes(we can end up going in a circle and end up with it being our opponents turn).
    -Otherwise, the answer is the xor of all the values for all the cycles we can reach.
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
const int N=5e5+5;
struct node{
    vector<int> nxt,flip,jedan;
    vector<vector<int> > dp,pref,suf,revpref,revsuf;
    void construct(int tr)
    {
        for(int i=1,n=flip.size();i<n;i++)
            flip[i]^=flip[i-1];
        for(int i=1,n=jedan.size();i<n;i++)
            jedan[i]+=jedan[i-1];
        pref=suf=revpref=revsuf=dp;
        for(int i=1,n=dp.size();i<n;i++)
            for(int j=0;j<4;j++)
                pref[i][j]=dp[i][pref[i-1][j]];
        for(int i=1,n=dp.size();i<n;i++)
            for(int j=0;j<4;j++)
                revpref[i][j]=revpref[i-1][dp[i][j]];
        for(int n=dp.size(),i=n-2;i>=0;i--)
            for(int j=0;j<4;j++)
                suf[i][j]=suf[i+1][dp[i][j]];
        for(int n=dp.size(),i=n-2;i>=0;i--)
            for(int j=0;j<4;j++)
                revsuf[i][j]=dp[i][revsuf[i+1][j]];
    }
    int getAns()
    {
        int a=flip.back();
        if(jedan.back()&&a==0)
            a=1;
        return a;
    }
    int getFlipWithout(int i)
    {
        int ans=0;
        if(i)
            ans^=flip[i-1];
        if(i<(int)flip.size()-1)
            ans^=flip[flip.size()-1]^flip[i];
        int p=0;
        if(i)
            p+=jedan[i-1];
        if(i<(int)jedan.size()-1)
            p+=jedan[jedan.size()-1]-jedan[i];
        if(ans==0&&p)
            ans=1;
        return ans;
    }
    int getWithout(int i)
    {
        int ans1=2;
        if(i<(int)suf.size()-1)
            ans1=suf[i+1][ans1];
        if(i)
            ans1=pref[i-1][ans1];
        int ans2=2;
        if(i)
            ans2=revpref[i-1][ans2];
        if(i<(int)suf.size()-1)
            ans2=revsuf[i+1][ans2];
        return ans1|ans2;
    }
};
vector<node> graf(3*N/2);
void addEdge(int a,int b)
{
    graf[a].nxt.pb(b);
    graf[a].flip.pb(-1);
    graf[a].jedan.pb(0);
    graf[b].nxt.pb(a);
    graf[b].flip.pb(-1);
    graf[b].dp.pb({0,0,0,0});
}
vector<vector<int> > initialGraf(N);
vector<int> in(N),low(N),st,ans(N);
int t=1,cnt;
void build(int tr=0,int par=-1)
{
    in[tr]=low[tr]=t++;
    st.pb(tr);
    for(auto p:initialGraf[tr])
    {
        if(p==par)
            continue;
        if(!in[p])
        {
            build(p,tr);
            if(low[p]>=in[tr])
            {
                while(st.back()!=p)
                    addEdge(st.back(),N+cnt),st.pop_back();
                addEdge(st.back(),N+cnt);st.pop_back();
                addEdge(tr,N+cnt++);
            }
            low[tr]=min(low[tr],low[p]);
        }
        else
            low[tr]=min(low[tr],in[p]);
    }
}
int init(int tr=0,int par=-1)
{
    if(tr<N)
    {
        int f=0;
        bool ima=false;
        for(int i=0,n=graf[tr].nxt.size();i<n;i++)
        {
            int p=graf[tr].nxt[i];
            if(p==par)
                continue;
            int val=init(p,tr);
            graf[tr].flip[i]=(val&2)==2;
            if(val==3)
                graf[tr].jedan[i]=1;
            if(val==3)
                ima=true;
            f^=graf[tr].flip[i];
        }
        if(f==0&&ima)
            f=1;
        return f;
    }
    for(int i=0,n=graf[tr].nxt.size();i<n-1;i++)
    {
        int p=graf[tr].nxt[i];
        graf[tr].flip[i]=init(p,tr);
        for(int j=0;j<4;j++)
            graf[tr].dp[i][j]=(((j&2)==2&&!graf[tr].flip[i])||((j&1)&&graf[tr].flip[i]))+((j&1)<<1);
    }
    int dp=2;
    for(int i=0,n=graf[tr].nxt.size();i<n-1;i++)
        dp=graf[tr].dp[i][dp];
    int prvi=dp;
    dp=2;
    for(int n=graf[tr].nxt.size(),i=n-2;i>=0;i--)
        dp=graf[tr].dp[i][dp];
    prvi|=dp;
    return prvi;
}
void calc(int tr=0,int par=-1)
{
    graf[tr].construct(tr);
    if(tr<N)
        ans[tr]=graf[tr].getAns();
    for(int i=0,n=graf[tr].nxt.size();i<n;i++)
    {
        int p=graf[tr].nxt[i];
        if(p==par)
            continue;
        for(int j=0,m=graf[p].nxt.size();j<m;j++)
            if(graf[p].flip[j]==-1)
            {
                if(tr<N)
                {
                    int f=graf[tr].getFlipWithout(i);
                    for(int k=0;k<4;k++)
                        graf[p].dp[j][k]=(((k&2)==2&&!f)||((k&1)&&f))+((k&1)<<1);
                }
                else
                {
                    int val=graf[tr].getWithout(i);
                    graf[p].flip[j]=(val&2)==2;
                    if(val==3)
                        graf[p].jedan[j]=1;
                }
            }
        calc(p,tr);
    }
}
int main()
{
	int n,m,a,b;
	scanf("%i %i",&n,&m);
	for(int i=0;i<m;i++)
        scanf("%i %i",&a,&b),a--,b--,initialGraf[a].pb(b),initialGraf[b].pb(a);
    build();
    init();
    calc();
    for(int i=0;i<n;i++)
        printf("%i\n",(ans[i]^1)+1);
    return 0;
}
