/*
    -This brute force with O(n^4 log n) (1e9 operations) passes, but you of course asked for a n^2 log n, so i will try to figure that out.
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
const int K=9;
const int N=512;
int dist[N][N];
vector<vector<vector<int> > > d(2*N);
void solve(int p,int l,int r)
{
    int n=r-l+1;
    d[p].resize(n);
    for(int i=0;i<n;i++)
        d[p][i].resize(n,INT_MAX);
    if(r-l==1)
    {
        d[p][0][1]=dist[r][l];
        d[p][1][0]=dist[r][l];
        return;
    }
    int m=(l+r)>>1;
    solve(2*p,l,m);
    solve(2*p+1,m+1,r);
    int m1=(l+m)>>1,m2=(r+m+1)>>1;
    for(int i=l;i<=m1;i++)
    {
        for(int j=m1+1;j<=m;j++)
        {
            for(int a=m+1;a<=m2;a++)
            {
                for(int b=m2+1;b<=r;b++)
                {
                    int di=d[2*p][i-l][j-l]+d[2*p+1][a-m-1][b-m-1];
                    if(d[p][i-l][b-l]>di+dist[j][a])
                        d[p][i-l][b-l]=di+dist[j][a];
                    if(d[p][i-l][a-l]>di+dist[j][b])
                        d[p][i-l][a-l]=di+dist[j][b];
                    if(d[p][j-l][b-l]>di+dist[i][a])
                        d[p][j-l][b-l]=di+dist[i][a];
                    if(d[p][j-l][a-l]>di+dist[i][b])
                        d[p][j-l][a-l]=di+dist[i][b];
                }
            }
        }
    }
}
int main()
{
    int k;
    scanf("%i",&k);
    int n=(int)pow(2,k);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%i",&dist[i][j]);
    solve(1,0,n-1);
    int sol=INT_MAX;
    int mid=n/2;
    for(int i=0;i<mid;i++)
    {
        for(int j=mid;j<n;j++)
        {
            if(sol>d[1][i][j])
                sol=d[1][i][j];
        }
    }
    printf("%i\n",sol);
    return 0;
}
