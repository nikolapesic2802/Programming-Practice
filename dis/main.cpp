/*
    -When we connect the ninjas to their boss, they form a tree, we root this tree at the master.
    -Each manager can dispatch only ninjas that are in his subtree.
    -For every subtree we need to take as many ninjas as possible to get the most satisfaction.
    -This can be done with subtree set merging by keeping a multiset of ninjas salaries and when its sum gets to over m, we take out the ninja with the highest salary.
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
int n,m,root;
const int N=1e5+5;
vector<vector<int> > graf(N);
vector<int> C(N),L(N),subtree(N),num(N);
struct myset{
    multiset<int,greater<int> > s;
    int sum;
    void insert(int i)
    {
        s.insert(i);
        sum+=i;
        if(sum>m)
            sum-=*s.begin(),s.erase(s.begin());
    }
    int size()
    {
        return s.size();
    }
};
vector<myset> leaves;
void dfs(int tr,int par)
{
    subtree[tr]=1;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        dfs(p,tr);
        subtree[tr]+=subtree[p];
    }
}
int solve(int tr,int par)
{
    if(graf[tr].size()==1&&tr!=root)
    {
        myset s;
        s.sum=0;
        s.insert(C[tr]);
        leaves.pb(s);
        num[tr]=1;
        return leaves.size()-1;
    }
    vector<pair<int,int> > children;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        children.pb({subtree[p],solve(p,tr)});
    }
    sort(all(children));
    reverse(all(children));
    int moj=children[0].second;
    leaves[moj].insert(C[tr]);
    for(int i=1;i<(int)children.size();i++)
        for(auto p:leaves[children[i].second].s)
            leaves[moj].insert(p);
    num[tr]=leaves[moj].size();
    return moj;
}
int main()
{
	scanf("%i %i",&n,&m);
	for(int i=1;i<=n;i++)
    {
        int b;
        scanf("%i %i %i",&b,&C[i],&L[i]);
        if(b!=0)
        {
            graf[b].pb(i);
            graf[i].pb(b);
        }
        else
            root=i;
    }
    dfs(root,-1);
    solve(root,-1);
    ll sol=0;
    for(int i=1;i<=n;i++)
        sol=max(sol,(ll)num[i]*L[i]);
    printf("%lld\n",sol);
    return 0;
}
