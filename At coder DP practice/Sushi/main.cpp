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
int n;
const int N=301;
double dp[N][N][N];
double val(int pr)
{
    return (double)n/pr;
}
double calc(int a,int b,int c)
{
    //printf("%i %i %i\n",a,b,c);
    int s=a+b+c;
    if(s==0)
        return 0;
    if(dp[a][b][c]!=-1)
        return dp[a][b][c];
    dp[a][b][c]=val(s);
    //printf("%f\n",dp[a][b][c]);
    if(a>0)
        dp[a][b][c]+=(double)a/s*calc(a-1,b,c);
    if(b>0)
        dp[a][b][c]+=(double)b/s*calc(a+1,b-1,c);
    if(c>0)
        dp[a][b][c]+=(double)c/s*calc(a,b+1,c-1);
    return dp[a][b][c];
}
int main()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            for(int k=0;k<N;k++)
            {
                dp[i][j][k]=-1;
            }
        }
    }
    scanf("%i",&n);
    int a=0,b=0,c=0;
    for(int i=0;i<n;i++)
    {
        int d;
        scanf("%i",&d);
        if(d==1)
            a++;
        if(d==2)
            b++;
        if(d==3)
            c++;
    }
    printf("%.10f\n",calc(a,b,c));
    return 0;
}
