/*
    -
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
int mul(int a,int b)
{
    return (ll)a*b%mod;
}
struct matrix{
    int n,m,p,q;
    vector<vector<vector<vector<int> > > > mat;
    matrix(int nn,int mm,int pp,int qq)
    {
        n=nn;m=mm;p=pp;q=qq;
        mat.resize(n,vector<vector<vector<int> > >(m,vector<vector<int> >(p,vector<int>(q))));
    }
};
matrix operator*(matrix a,matrix b)
{
    matrix sol(a.n,a.m,b.p,b.q);
    assert(a.p==b.n&&a.q==b.m);
    for(int i=0;i<a.n;i++)
        for(int j=0;j<a.m;j++)
            for(int o=0;o<b.p;o++)
                for(int l=0;l<b.q;l++)
                {
                    int ans=0;
                    for(int k=0;k<a.p;k++)
                        for(int u=0;u<a.q;u++)
                            ans=add(ans,mul(a.mat[i][j][k][u],b.mat[k][u][o][l]));
                    sol.mat[i][j][o][l]=ans;
                }
    return sol;
}
const int L=26,M=5;
matrix start(M,L+1,M,L+1);
matrix powr(int k)
{
    matrix ans=start,x=start;
    for(;k;k>>=1,x=x*x)
        if(k&1)
            ans=ans*x;
    return ans;
}
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    vector<vector<int> > dist(L,vector<int>(L,1));
    for(int i=0;i<m;i++)
    {
        char a,b;
        int c;
        scanf(" %c %c %i",&a,&b,&c);
        dist[a-'a'][b-'a']=dist[b-'a'][a-'a']=c;
    }
    matrix sol(1,1,M,L+1);
    for(int i=0;i<L;i++)
        sol.mat[0][0][0][i]=1;
    start.mat[0][L][0][L]++;
    for(int i=0;i<L;i++)
        start.mat[0][i][0][L]++;
    for(int i=1;i<M;i++)
        for(int j=0;j<L;j++)
            start.mat[i][j][i-1][j]++;
    for(int i=0;i<L;i++)
        for(int j=0;j<L;j++)
            start.mat[0][i][dist[i][j]-1][j]++;
    matrix multi=powr(n);
    sol=sol*multi;
    printf("%i\n",sol.mat[0][0][0][L]);
    return 0;
}
