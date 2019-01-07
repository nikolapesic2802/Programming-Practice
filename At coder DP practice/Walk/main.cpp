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

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
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
    return ((ll)a*b)%mod;
}
struct Matrix{
    int n;
    vector<vector<int> > mat;
    Matrix(int nn)
    {
        n=nn;
        mat.resize(n,vector<int>(n));
    }
    void make_one()
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mat[i][j]=(i==j);
    }
};
Matrix mul(Matrix a,Matrix b)
{
    int n=a.n;
    Matrix sol(n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int ans=0;
            for(int k=0;k<n;k++)
            {
                ans=add(ans,mul(a.mat[i][k],b.mat[k][j]));
            }
            sol.mat[i][j]=ans;
        }
    }
    return sol;
}
Matrix pwrmod(Matrix x,ll k)
{
    Matrix ans(x.n);
    ans.make_one();
    for(;k;k>>=1,x=mul(x,x))
        if(k&1)
            ans=mul(ans,x);
    return ans;
}
int main()
{
    int n;
    ll k;
    scanf("%i %lld",&n,&k);
    Matrix m(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%i",&m.mat[i][j]);
    m=pwrmod(m,k);
    int ans=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            ans=add(ans,m.mat[i][j]);
    printf("%i\n",ans);
    return 0;
}
