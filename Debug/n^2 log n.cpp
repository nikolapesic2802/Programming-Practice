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
const int N=305;
vector<vector<int> > mat(N,vector<int>(N)),obican(N,vector<int>(N)),inv(N,vector<int>(N));
vector<int> pwr;
int getobican(int i,int l,int r)
{
    return obican[i][r]-obican[i][l-1]*pwr[r-l+1];
}
int getinv(int i,int l,int r)
{
    return inv[i][l]-inv[i][r+1]*pwr[r-l+1];
}
bool check(int tr)
{
    for(int i=1;i<c-tr+1;i++)
    {
        int j=i+tr-1;
        vector<int> ob(N),in(N);
        for(int k=1;k<=r;k++)
            ob[k]=ob[k-1]*pwr[j-i+1]+getobican(k,i,j);
        for(int k=r;k>=1;k--)
            in[k]=in[k+1]*pwr[j-i+1]+getinv(k,i,j);
        auto getob=[&](int l,int r)
        {
            int tr=ob[r]-ob[l-1]*pwr[(r-l+1)*(j-i+1)];
            return tr;
        };
        auto getin=[&](int l,int r)
        {
            int tr=in[l]-in[r+1]*pwr[(r-l+1)*(j-i+1)];
            return tr;
        };
        int d=(j-i+1)%2,siz=(j-i+2)/2;
        for(int k=1;k<=r-j+i;k++)
            if(getob(k,k+siz-1)==getin(k+siz-d,k+siz-d+siz-1))
                return true;
    }
    return false;
}
int main()
{
    pwr.pb(1);
    for(int i=0;i<N*N;i++)
        pwr.pb(pwr[i]*3);
	scanf("%i %i",&r,&c);
	char input[r][c];
	for(int i=0;i<r;i++)
        scanf("%s",input[i]);
	for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            mat[i][j]=input[i-1][j-1]=='1';
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
            obican[i][j]=obican[i][j-1]*3+mat[i][j]+1;
        for(int j=c;j>=1;j--)
            inv[i][j]=inv[i][j+1]*3+mat[i][j]+1;
    }
    int sol=-1;
    int le=1,ri=c/2+1;
    while(le<=ri)
    {
        int mi=(le+ri)>>1;
        int tr=mi*2;
        bool moze=check(tr);
        if(moze)
            sol=max(sol,tr),le=mi+1;
        else
            ri=mi-1;
    }
    le=max(1,sol/2),ri=c/2+1;
    while(le<=ri)
    {
        int mi=(le+ri)>>1;
        int tr=mi*2+1;
        bool moze=check(tr);
        if(moze)
            sol=max(sol,tr),le=mi+1;
        else
            ri=mi-1;
    }
    printf("%i\n",sol);
    return 0;
}
