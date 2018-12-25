/*
    -idea for dp taken from: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2009_solutions/monument-sol.pdf
    -I used a trick with a stack to calculate the first element smaller than the current one before it and after it in an array in O(n) (not directly told on how to do the traversal in the pdf, so this is how).
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
		if(i>0&&i<sz(a))
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=150;
vector<vector<vector<int> > > matrix(N,vector<vector<int> > (N,vector<int> (N))),matrix2(N,vector<vector<int> > (N,vector<int> (N)));
int check(int p,int q,int h)
{
    vector<vector<vector<int> > > dp(N,vector<vector<int> > (N,vector<int> (N)));
    for(int k=0;k<h;k++)
    {
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<q;j++)
            {
                if(i==0||j==0)
                {
                    if(matrix[i][j][k]==1)
                        dp[i][j][k]=1;
                }
                else
                {
                    if(matrix[i][j][k]==1)
                    {
                        dp[i][j][k]=min(dp[i-1][j][k],min(dp[i][j-1][k],dp[i-1][j-1][k]))+1;
                    }
                }
            }
        }
    }
    int sol=0;
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            vector<pair<int,int> > siz;
            int last=-1;
            vector<int> napred(h);
            for(int k=0;k<h;k++)
            {
                if(dp[i][j][k]>last)
                {
                    siz.pb({last,k-1});
                }
                if(dp[i][j][k]<last)
                {
                    while(siz.back().first>=dp[i][j][k])
                        siz.pop_back();
                }
                last=dp[i][j][k];
                napred[k]=siz.back().second;
            }
            siz.clear();
            last=-1;
            for(int k=h-1;k>=0;k--)
            {
                if(dp[i][j][k]>last)
                {
                    siz.pb({last,k+1});
                }
                if(dp[i][j][k]<last)
                {
                    while(siz.back().first>dp[i][j][k])
                        siz.pop_back();
                }
                last=dp[i][j][k];
                int mesto=siz.back().second-napred[k]-1;
                sol=max(sol,dp[i][j][k]*4*mesto);
            }
        }
    }
    return sol;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int p,q,h;
	cin >> p >> q >> h;
	swap(p,q);
	for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            string s;
            cin >> s;
            for(int k=0;k<h;k++)
            {
                if(s[k]=='N')
                    matrix[i][j][k]=1;
            }
        }
    }
    int sol=check(p,q,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix2[k][j][i]=matrix[i][j][k];
            }
        }
    }
    swap(p,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix[i][j][k]=matrix2[i][j][k];
            }
        }
    }
    sol=max(sol,check(p,q,h));
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix2[i][k][j]=matrix[i][j][k];
            }
        }
    }
    swap(q,h);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<q;j++)
        {
            for(int k=0;k<h;k++)
            {
                matrix[i][j][k]=matrix2[i][j][k];
            }
        }
    }
    sol=max(sol,check(p,q,h));
    printf("%i\n",sol);
    return 0;
}
