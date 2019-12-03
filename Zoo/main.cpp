/*
    -dp[tr][m]-> maximum number of children whose vision ends after tr and the last 4 enclosures are represented by bitmask m
    -Try all 2^4 possible starting positions for the first 4 enclosures: Time: O(2^8*(N+C)), Memory: O(2^4*(N+C))
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=1e4+5,L=5,M=1<<L,M2=M/2,dodaj=M2/2;
vector<vector<int> > points(N,vector<int>(M));
vector<int> maska(L);
int dp[N][M2],n,c;
int calc(int tr,int m){
    if(tr<=3){
        if(tr==3)
            return points[tr][m+M2*maska[tr]];
        return points[tr][m+M2*maska[tr]]+calc(tr+1,(m>>1)+dodaj*maska[tr]);
    }
    if(dp[tr][m]!=-1)
        return dp[tr][m];
    return dp[tr][m]=max(points[tr][m]+calc((tr+1)%n,m>>1),points[tr][m+M2]+calc((tr+1)%n,(m>>1)+dodaj));
}
int main()
{
	scanf("%i %i",&n,&c);
	while(c--)
    {
        int e;
        scanf("%i",&e);
        e--;
        int f,l,fe=0,lo=0,o;
        scanf("%i %i",&f,&l);
        for(int i=0;i<f;i++){
            scanf("%i",&o);
            if(o<=e)
                o+=n;
            o-=e+1;
            fe^=1<<o;
        }
        for(int i=0;i<l;i++){
            scanf("%i",&o);
            if(o<=e)
                o+=n;
            o-=e+1;
            lo^=1<<o;
        }
        for(int i=0;i<M;i++)
            points[(e+4)%n][i]+=(i&fe)!=fe||(i&lo)!=0;
    }
    int sol=0;
    for(int i=0;i<M2;i++){
        for(int j=0;j<4;j++)
            maska[j]=(i&(1<<j))!=0;
        memset(dp,-1,sizeof(dp));
        sol=max(sol,calc(4,i));
    }
    printf("%i\n",sol);
    return 0;
}
