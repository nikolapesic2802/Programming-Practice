/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/olympiad_solutions/solutions.pdf
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
int k,n,m;
vector<pair<int,int> > songs;
int dp[300001][2];
pair<int,int> sta[300001][2];
set<pair<int,int> > nxt;
int calc(int a,int top) ///1-napred 0-nazad
{
    if(dp[a][top]!=-1)
        return dp[a][top];
    int gde=songs[a].f+top*(k-1);
    auto it=nxt.upper_bound({gde,INT_MAX});
    if(it==nxt.end()){
        sta[a][top]={m,0};
        return dp[a][top]=0;
    }
    int sl=(*it).f;
    int sol1=min(sl-gde,k)+calc((*it).s,0);
    int sol2=k+calc((*it).s,1);
    if(sol1<=sol2)
    {
        sta[a][top]={(*it).s,0};
        dp[a][top]=sol1;
    }
    else
    {
        sta[a][top]={(*it).s,1};
        dp[a][top]=sol2;
    }
    return dp[a][top];
}
int main()
{
    for(int i=0;i<300001;i++)
        for(int j=0;j<2;j++)
            sta[i][j]={m,-1};
    memset(dp,-1,sizeof(dp));
	scanf("%i %i %i",&n,&k,&m);
	songs.resize(m);
	for(int i=0;i<m;i++)
        scanf("%i",&songs[i].f),songs[i].s=i;
    sort(all(songs));
    for(int i=0;i<(int)songs.size();i++)
        nxt.insert({songs[i].f,i});
    int soll=k+calc(0,1);
    vector<pair<int,int> > sol(m);
    pair<int,int> tr={0,1};
    while(true){
        pair<int,int> interval={songs[tr.f].f,songs[tr.f].f+k-1};
        if(tr.s==0)
            interval.s-=2*k-2,swap(interval.f,interval.s);
        if(interval.s>n)
            interval.f-=interval.s-n,interval.s=n;
        pair<int,int> nxt=sta[tr.f][tr.s];
        while(tr.f<nxt.f)
        {
            sol[songs[tr.f].s]=interval;
            tr.f++;
        }
        if(tr.f==m)
            break;
        tr.s=nxt.s;
    }
    printf("%i\n",soll);
    for(int i=0;i<m;i++)
        printf("%i %i\n",sol[i].f,sol[i].s);
    return 0;
}