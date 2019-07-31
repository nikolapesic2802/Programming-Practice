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
const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
int mul(int a,int b)
{
    return (ll)a*b%mod;
}
int n,m,M,a,b;
vector<vector<int> > graf;
vector<int> mask;
vector<int>
vector<int> solve(int tr,int par)
{
    printf("%i %i\n",tr,par);
    vector<int> sol(M),novi(M);
    sol[mask[tr]]++;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        auto aa=solve(p,tr);
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++)
                if((i&j)==i)
                    sol[j]*=aa[i];
        for(int i=0;i<M;i++)
            sol[i]+=aa[i];
    }
    return sol;
}
void test()
{
    graf.clear();
    scanf("%i %i",&n,&m);
    graf.resize(n);
    mask.resize(n);
    M=1<<m;
    for(int i=1;i<n;i++)
        scanf("%i %i",&a,&b),graf[a-1].pb(b-1),graf[b-1].pb(a-1);
    for(int i=0;i<n;i++)
    {
        int nxt=0;
        for(int j=0;j<m;j++)
            scanf("%i",&a),nxt=nxt*2+a;
        mask[i]=nxt;
    }
    auto tr=solve(0,0);
    vector<int> sol(m+1);
    for(int i=0;i<M;i++)
        sol[__builtin_popcount(i)]=add(sol[__builtin_popcount(i)],tr[i]);
    for(int i=0;i<=m;i++)
        printf("%i ",sol[i]);
    printf("\n");
}
int main()
{
	int t;
	scanf("%i",&t);
	while(t--)
        test();
    return 0;
}
