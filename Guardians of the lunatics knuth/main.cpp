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
const int L=8005,G=805;
ll inf=LLONG_MAX/2;
ll dp[G][L];
int mid[G][L];
ll sum[L];
ll get(int l,int r)
{
    return (sum[r]-sum[l-1])*(ll)(r-l+1);
}
int main()
{
    int l,g;
    scanf("%i %i",&l,&g);
    for(int i=1;i<=l;i++)
        scanf("%lld",&sum[i]),sum[i]+=sum[i-1];
    if(g>=l)
    {
        printf("%lld\n",sum[l]);
        return 0;
    }
    for(int i=1;i<=l;i++)
    {
        dp[0][i]=inf;
        dp[1][i]=sum[i]*i;
        mid[1][i]=i;
        mid[g+1][i]=i;
    }
    for(int i=2;i<=g;i++)
<<<<<<< HEAD
        for(int w=1;w<=l;w++)
            dp[i][w]=inf;
=======
    {
        for(int w=1;w<=l;w++)
            dp[i][w]=inf;
    }
>>>>>>> 3db3e0bfa5fb7865875aa6cd7501066a97af70d5
    for(int d=0;d<=l;d++){
        for(int h=1;h+d<=l&&h<=g;h++)
        {
           if(d==0)
           {
<<<<<<< HEAD
               mid[h][h]=h;
=======
               mid[h][h]=1;
>>>>>>> 3db3e0bfa5fb7865875aa6cd7501066a97af70d5
               dp[h][h]=sum[h];
               continue;
           }
           int le=mid[h][h+d-1],ri=mid[h+1][h+d];
           pair<ll,int> sol=mp(inf,0);
           for(int k=le;k<=ri;k++)
           {
               sol=min(sol,mp((ll)dp[h-1][k-1]+get(k,h+d),k));
           }
           dp[h][h+d]=sol.first;
           mid[h][h+d]=sol.second;
        }
    }
    printf("%lld\n",dp[g][l]);
    return 0;
}
