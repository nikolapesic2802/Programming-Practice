/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/COCI/official/2017/contest1_solutions
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
const int N=26;
vector<vector<int> > graf(N);
int mat[N][N];
vector<int> visited(N);
void dfs(int tr)
{
    if(visited[tr])
    {
        printf("NE\n");
        exit(0);
    }
    visited[tr]=1;
    for(auto p:graf[tr])
        dfs(p);
    visited[tr]=0;
}
vector<int> top;
void topo(int tr)
{
    if(visited[tr])
        return;
    visited[tr]=1;
    for(auto p:graf[tr])
        topo(p);
    top.pb(tr);
}
int main()
{
	int n;
	scanf("%i",&n);
	vector<string> niz(n);
	vector<string> input(n);
    for(int i=0;i<n;i++)
        cin >> input[i];
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%i",&x);
        x--;
        niz[i]=input[x];
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            int si=niz[i].size();
            int sj=niz[j].size();
            if(si<sj)
            {
                if(niz[j].substr(0,si)==niz[i])
                {
                    printf("NE\n");
                    return 0;
                }
            }
        }
    }
    vector<int> degree(N);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<min((int)niz[i].size(),(int)niz[i-1].size());j++)
        {
            if(niz[i][j]!=niz[i-1][j])
            {
                if(mat[niz[i][j]-'a'][niz[i-1][j]-'a']==0)
                {
                    mat[niz[i][j]-'a'][niz[i-1][j]-'a']=1;
                    graf[niz[i][j]-'a'].pb(niz[i-1][j]-'a');
                    degree[niz[i-1][j]-'a']++;
                }
                break;
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        fill(all(visited),0);
        dfs(i);
    }
    fill(all(visited),0);
    for(int i=0;i<N;i++)
        if(degree[i]==0)
            topo(i);
    vector<int> sol(N);
    for(int i=0;i<top.size();i++)
        sol[top[i]]=i;
    printf("DA\n");
    for(int i=0;i<N;i++)
    {
        printf("%c",sol[i]+'a');
    }
    printf("\n");
    return 0;
}
