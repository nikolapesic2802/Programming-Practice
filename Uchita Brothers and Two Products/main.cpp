/*
    -First for every value in [0,2^m) find what is the sum of the products of all subsets with the AND value&current value=current value.
    -Then use inclusion-exclusion to calculate the answer.
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
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	int M=1<<m;
    vector<int> pr(M,1);
    for(int i=0;i<n;i++)
    {
        int p;
        char c[M];
        scanf("%i %s",&p,c);
        int val=0;
        for(int i=0;i<m;i++)
            val=val*2+(c[i]=='1');
        pr[val]=mul(pr[val],p+1);
    }
    for(int j=0;j<m;j++)
        for(int i=0;i<M;i++)
            if((i&(1<<j))==0)
                pr[i]=mul(pr[i],pr[i^(1<<j)]);
    for(int i=0;i<M;i++)
        pr[i]--;
    for(int i=0;i<m;i++)
        for(int j=0;j<M;j++)
            if((j&(1<<i))==0)
                pr[j]=sub(pr[j],pr[j^(1<<i)]);
    vector<int> sol(m+1);
    for(int i=0;i<M;i++)
        sol[__builtin_popcount(i)]=add(sol[__builtin_popcount(i)],pr[i]);
    for(int i=0;i<=m;i++)
        printf("%i ",sol[i]);
    return 0;
}
