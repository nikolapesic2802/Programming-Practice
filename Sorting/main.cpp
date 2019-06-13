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

int mod=1234567;
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
int n,x;
const int N=32,L=N*(N+1)/2;
int d[N][N][L];
int dp[N][L][L];
int cmax(int nn)
{
    return nn*(nn+1)/2;
}
int main()
{
    d[0][0][0]=1;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k=0;k<L;k++)
            {
                if(i-1>=0&&k-j>=0)
                    d[i][j][k]=add(d[i][j][k],d[i-1][j][k-j]);
                if(j-1>=0)
                    d[i][j][k]=add(d[i][j][k],d[i][j-1][k]);
            }
	dp[0][0][0]=1;
	for(int N=0;N<=31;N++)
    {
        for(int L1=0;L1<N;L1++)
        {
            int L2=N-1-L1;
            for(int Q1=0;Q1<=cmax(L1);Q1++)
            {
                for(int Q2=0;Q2<=cmax(L2);Q2++)
                {
                    vector<int> S(cmax(L1)+cmax(L2)+1);
                    vector<int> I2Options;
                    for(int I2=0;I2<=cmax(L2);I2++)
                        if(dp[L2][Q2][I2]!=0)
                            I2Options.pb(I2);
                    for(int I1=0;I1<=cmax(L1);I1++){
                        if(dp[L1][Q1][I1]==0)
                            continue;
                        for(auto I2:I2Options)
                            S[I1+I2]=add(S[I1+I2],mul(dp[L1][Q1][I1],dp[L2][Q2][I2]));
                    }
                    vector<int> IcOptions;
                    for(int Ic=0;Ic<=L1*L2;Ic++)
                        if(d[L1][L2][Ic]!=0)
                            IcOptions.pb(Ic);
                    int Q=Q1+Q2+N-1;
                    for(int SI=0;SI<=cmax(L1)+cmax(L2);SI++){
                        if(S[SI]==0)
                            continue;
                        for(auto Ic:IcOptions)
                        {
                            int I=SI+Ic+L1;
                            dp[N][Q][I]=add(dp[N][Q][I],mul(S[SI],d[L1][L2][Ic]));
                        }
                    }
                }
            }
        }
    }
    vector<pair<int,int> > a={{5, 1}, {12, 2}, {18, 3}, {20, 1}, {22, 5}, {23, 3}, {24, 4}, {29, 2}, {30, 5}, {31, 1}};
    for(int i=0;i<10;i++)
    {
        int n=a[i].f,x=a[i].s;
        int sol=0;
        for(int Q=0;Q<=cmax(n);Q++)
            for(int I=min(cmax(n),Q*x);I>=n-1;I--)
                sol=add(sol,dp[n][Q][I-n+1]);
        printf("%i: %i\n",i,sol);
    }
    return 0;
}
