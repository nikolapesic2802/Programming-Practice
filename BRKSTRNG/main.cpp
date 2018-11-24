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
const ll inf=LLONG_MAX/2;
const int Ma=1005;
int poz[Ma];
ll dp[Ma][Ma];
int mid[Ma][Ma];
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int m;
        scanf("%i",&m);
        poz[0]=0;
        for(int i=1;i<=m;i++)
            scanf("%i",&poz[i]);
        m++;
        poz[m]=n;
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++)
                dp[i][j]=inf;
        for(int s=0;s<=m;s++)
        {
            for(int L=0;L+s<=m;L++)
            {
                int R=L+s;
                if(s<2)
                {
                    dp[L][R]=0;
                    mid[L][R]=L;
                    continue;
                }
                if(s==2)
                {
                    dp[L][R]=poz[R]-poz[L];
                    mid[L][R]=L+1;
                    continue;
                }
                int mleft=mid[L][R-1];
                int mright=mid[L+1][R];
                pair<ll,int> sol=mp(inf,0);
                for(int M=mleft;M<=mright;M++)
                {
                    sol=min(sol,mp(dp[L][M]+dp[M][R]+(ll)(poz[R]-poz[L]),M));
                    //printf("%i-%i  %i   %lld  %lld\n",L,R,M,dp[L][M]+dp[M][R]+(poz[R]-poz[L]));
                }
                dp[L][R]=sol.first;
                mid[L][R]=sol.second;
            }
        }
        printf("%lld\n",dp[0][m]);
    }
    return 0;
}
