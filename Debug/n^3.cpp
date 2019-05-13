/*
    -In order for a square to be a killer, the "inverted" bottom side of it has to be the same as the top side.
    -We can check for this with hashing.
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
int r,c;
const int N=305,mod=1e9+7;
vector<vector<int> > mat(N,vector<int>(N));
vector<vector<int> > obican(N,vector<int>(N));
vector<vector<int> > inv(N,vector<int>(N));
vector<int> pwr;
int getobican(int i,int l,int r)
{
    return (obican[i][r]-(ll)obican[i][l-1]*pwr[r-l+1]%mod+mod)%mod;
}
int getinv(int i,int l,int r)
{
    return (inv[i][l]-(ll)inv[i][r+1]*pwr[r-l+1]%mod+mod)%mod;
}
int main()
{
    pwr.pb(1);
    for(int i=0;i<N*N;i++)
        pwr.pb((ll)pwr[i]*3%mod);
	scanf("%i %i",&r,&c);
	vector<string> input(r);
	for(int i=0;i<r;i++)
        cin >> input[i];
	for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            mat[i][j]=input[i-1][j-1]=='1';
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
            obican[i][j]=((ll)obican[i][j-1]*3+mat[i][j]+1)%mod;
        for(int j=c;j>=1;j--)
            inv[i][j]=((ll)inv[i][j+1]*3+mat[i][j]+1)%mod;
    }
    int sol=-1;
    for(int i=1;i<c;i++)
    {
        for(int j=i+1;j<=c;j++)
        {
            vector<int> ob(N),in(N);
            for(int k=1;k<=r;k++)
                ob[k]=((ll)ob[k-1]*pwr[j-i+1]%mod+getobican(k,i,j))%mod;
            for(int k=r;k>=1;k--)
                in[k]=((ll)in[k+1]*pwr[j-i+1]%mod+getinv(k,i,j))%mod;
            auto getob=[&](int l,int r)
            {
                return (ob[r]-(ll)ob[l-1]*pwr[(r-l+1)*(j-i+1)]%mod+mod)%mod;
            };
            auto getin=[&](int l,int r)
            {
                return (in[l]-(ll)in[r+1]*pwr[(r-l+1)*(j-i+1)]%mod+mod)%mod;
            };
            int d=(j-i+1)%2,siz=(j-i+2)/2;
            for(int k=1;k<=r-j+i;k++)
            {
                int jedan=getob(k,k+siz-1);
                int dva=getin(k+siz-d,k+siz-d+siz-1);
                if(jedan==dva)
                {
                    sol=max(sol,j-i+1);
                }
            }
        }
    }
    printf("%i\n",sol);
    return 0;
}
