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

const int N=15,oo=INT_MIN/2;
struct fair{
    int t,l,m;
};
bool operator<(fair a,fair b){
    if(a.t!=b.t)
        return a.t<b.t;
    if(a.l!=b.l)
        return a.l<b.l;
    return a.m<b.m;
}
vector<fair> f;
vector<int> r(N);
int n,u,d,s;
int dp[N][1<<N];
int getDist(int a,int b){
    if(a<b)
        return b*d-a*d;
    return a*u-b*u;
}
int calc(int tr,int msk){
    if(dp[tr][msk]!=oo)
        return dp[tr][msk];
    dp[tr][msk]=f[tr].m-getDist(f[tr].l,s);
    for(int i=0;i<n;i++)
        if((msk&(1<<i))==0&&f[i].t>=f[tr].t)
            dp[tr][msk]=max(dp[tr][msk],f[tr].m+calc(i,msk^(1<<i))-getDist(f[tr].l,f[i].l));
    return dp[tr][msk];
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	for(int i=0;i<N;i++)
        for(int j=0;j<(1<<N);j++)
            dp[i][j]=oo;
	scanf("%i %i %i %i",&n,&u,&d,&s);
	f.resize(n);
	for(int i=0;i<n;i++)
        scanf("%i %i %i",&f[i].t,&f[i].l,&f[i].m);
    int sol=0;
    for(int i=0;i<n;i++)
        sol=max(sol,calc(i,1<<i)-getDist(s,f[i].l));
    printf("%i\n",sol);
    return 0;
}
