#include <bits/stdc++.h>

using namespace std;


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
            s.erase(s.begin());
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
    for(int i=1;i<children.size();i++)
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
        //scanf("%i %i %i",&b,&C[i],&L[i]);
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
    {
        sol=max(sol,(ll)num[i]*L[i]);
    }
    printf("%lld\n",sol);
    return 0;
}
