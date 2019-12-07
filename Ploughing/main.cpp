/*
    -dp[l][r]-we still haven't plowed horizontally in rows [l-r].
    -We need make as many vertical plows from the left and right on these rows, if we can do all of them, the answer is m+n-(r-l+1), if not, do as many as we can and then we need to make a horizontal plow if possible and transition to a new state.
    -To not calculate how many vertical plows we can do for a state from the start all the time (that would be n^3) we will start from the positions we could plow for states [l-1][r] and [l][r+1],
     since we will for sure be able to plow them.
    -Memory is really tight for this approach, i had to use short and a constant optimization that r>=l so we can use only half the matrix.
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

const int N=2000;
int n,m,k,mat[N][N];
int get(int i,int j,int l,int r){
    int ans=mat[j][r];
    if(l)
        ans-=mat[j][l-1];
    if(i)
        ans-=mat[i-1][r];
    if(i&&l)
        ans+=mat[i-1][l-1];
    return ans;
}
void cons(){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(i)
                mat[i][j]+=mat[i-1][j];
            if(j)
                mat[i][j]+=mat[i][j-1];
            if(i&&j)
                mat[i][j]-=mat[i-1][j-1];
        }
}
void decons(){
    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            if(i)
                mat[i][j]-=mat[i-1][j];
            if(j)
                mat[i][j]-=mat[i][j-1];
            if(i&&j)
                mat[i][j]+=mat[i-1][j-1];
        }
    }
}
vector<bool> dp[N];
vector<short> posL[N],posR[N];
int calc(){
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
            dp[i][j-i]=0,posL[i][j-i]=0,posR[i][j-i]=m-1;
    vector<pair<int,pair<int,int> > > order;
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
            order.pb({j-i+1,{i,j}});
    sort(order.rbegin(),order.rend());
    dp[0][n-1]=1;
    for(auto p:order){
        int l=p.s.f,r=p.s.s;
        if(!dp[l][r-l])
            continue;
        while(posL[l][r-l]<=posR[l][r-l]){
            if(get(l,r,posL[l][r-l],posL[l][r-l])<=k)
                posL[l][r-l]++;
            else
                if(get(l,r,posR[l][r-l],posR[l][r-l])<=k)
                    posR[l][r-l]--;
                else
                    break;
        }
        if(posL[l][r-l]>posR[l][r-l])
            return m+n-p.f;
        if(get(l,l,posL[l][r-l],posR[l][r-l])<=k)
            dp[l+1][r-l-1]=1,posL[l+1][r-l-1]=max(posL[l+1][r-l-1],posL[l][r-l]),posR[l+1][r-l-1]=min(posR[l+1][r-l-1],posR[l][r-l]);
        if(get(r,r,posL[l][r-l],posR[l][r-l])<=k)
            dp[l][r-1-l]=1,posL[l][r-1-l]=max(posL[l][r-1-l],posL[l][r-l]),posR[l][r-1-l]=min(posR[l][r-1-l],posR[l][r-l]);
    }
    return n+m-1;
    assert(0);
}
int main()
{
    for(int i=0;i<N;i++)
        dp[i].resize(N-i),posL[i].resize(N-i),posR[i].resize(N-i);
	scanf("%i %i %i",&k,&m,&n);
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%i",&mat[i][j]);
    cons();
    int sol=calc();
    decons();
    for(int i=0;i<max(n,m);i++)
        for(int j=i+1;j<max(n,m);j++)
            swap(mat[i][j],mat[j][i]);
    swap(n,m);
    cons();
    printf("%i\n",min(calc(),sol));
    return 0;
}
