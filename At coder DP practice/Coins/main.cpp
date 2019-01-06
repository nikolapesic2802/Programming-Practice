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
const int N=3e3+5;
double p[N][N];
int main()
{
    int n;
    scanf("%i",&n);
    p[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        double h;
        cin >> h;
        double t=(double)1-h;
        for(int j=0;j<=i;j++)
        {
            p[i][j]=(double)p[i-1][j]*t;
            if(j>0)
                p[i][j]+=(double)p[i-1][j-1]*h;
        }
    }
    double pp=0;
    for(int i=n;i>n/2;i--)
        pp+=p[n][i];
    printf("%.10f\n",pp);
    return 0;
}
