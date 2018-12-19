/*
<<<<<<< HEAD
    -Just write a dp[l][r][move] l and r being the borders of the taken interval and move being whose move is it(this move dimension is not required since r-l+1 will be odd for the first player and even for the second one, but it was easier to write this way.
=======
    -Just write a dp[l][r][move] l and r being the borders of the taken interval and move being whose move is it(this move dimension is not required since r-l+1 will be odd for the first player and even for the second one, but it was easier to write this way).
>>>>>>> 9474051d178f5be8b497f4ee169757a088fe6e70
    -Really simple to figure out the transitions.
    -Just try taking every cake as the first cake and take the maximum of those.
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
const int N=2005;
vector<int> cakes(N);
ll dp[N][N][2];
int n;
int prev(int tr)
{
    if(tr==0)
        return n-1;
    return tr-1;
}
int nxt(int tr)
{
    if(tr==n-1)
        return 0;
    return tr+1;
}
<<<<<<< HEAD
ll calc(int l,int r,int potez)
{
    if(dp[l][r][potez]!=-1)
        return dp[l][r][potez];
    if(potez==0)
    {
        if(l==r)
            return dp[l][r][potez]=0;
        if(cakes[l]>cakes[r])
            return dp[l][r][potez]=calc(prev(l),r,1);
        else
            return dp[l][r][potez]=calc(l,nxt(r),1);
=======
ll calc(int l,int r,int move)
{
    if(dp[l][r][move]!=-1)
        return dp[l][r][move];
    if(move==0)
    {
        if(l==r)
            return dp[l][r][move]=0;
        if(cakes[l]>cakes[r])
            return dp[l][r][move]=calc(prev(l),r,1);
        else
            return dp[l][r][move]=calc(l,nxt(r),1);
>>>>>>> 9474051d178f5be8b497f4ee169757a088fe6e70
    }
    else
    {
        if(l==r)
<<<<<<< HEAD
            return dp[l][r][potez]=cakes[l];
        return dp[l][r][potez]=max((ll)calc(prev(l),r,0)+cakes[l],(ll)calc(l,nxt(r),0)+cakes[r]);
=======
            return dp[l][r][move]=cakes[l];
        return dp[l][r][move]=max((ll)calc(prev(l),r,0)+cakes[l],(ll)calc(l,nxt(r),0)+cakes[r]);
>>>>>>> 9474051d178f5be8b497f4ee169757a088fe6e70
    }
}
int main()
{
    memset(dp,-1,sizeof(dp));
    scanf("%i",&n);
    vector<int> niz(n);
    for(int i=0;i<n;i++)
        scanf("%i",&cakes[i]);
    ll best=0;
    for(int i=0;i<n;i++)
        best=max(best,(ll)cakes[i]+calc(prev(i),nxt(i),0));
    printf("%lld\n",best);
    return 0;
}
