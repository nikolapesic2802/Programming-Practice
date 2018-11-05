#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
const int N=1e5+5,M=5*1e4+5;
vector<vector<int> > contains(N);
vector<vector<int> > graph(N);
vector<int> number(M);
vector<pair<int,int> > branches;
vector<set<pair<int,int> > > leaves;
int k;
int solve(int tr,int par)
{
    int all[graph[tr].size()-1];
    int poz=0;
    for(auto p:graph[tr])
    {
        if(p==par)
            continue;
        all[poz]=solve(p,tr);
        poz++;
    }
    if(par==-1)
        return 0;
    int maxx=0;
    int where=-1;
    for(int i=0;i<graph[tr].size()-1;i++)
    {
        if(leaves[all[i]].size()>maxx)
        {
            maxx=leaves[all[i]].size();
            where=i;
        }
    }
    if(where!=-1)
    {
        int sol=all[where];
        for(int i=0;i<graph[tr].size()-1;i++)
        {
            if(i==where)
                continue;
            for(auto p:leaves[all[i]])
            {
                pair<int,int> minn=*leaves[sol].lower_bound({p.first,0});
                if(minn.first==p.first)
                {
                    leaves[sol].erase(minn);
                    int t=minn.second+p.second;
                    if(t!=number[p.first])
                    {
                        leaves[sol].insert({p.first,t});
                    }
                }
                else
                {
                    leaves[sol].insert(p);
                }
            }
        }
        for(auto p:contains[tr])
        {
            pair<int,int> minn=*leaves[sol].lower_bound({p,0});
            if(minn.first==p)
            {
                leaves[sol].erase(minn);
                int t=minn.second+1;
                if(t!=number[p])
                {
                    leaves[sol].insert({p,t});
                }
            }
            else
            {
                leaves[sol].insert({p,1});
            }
        }
        if(leaves[sol].size()>=k)
        {
            branches.pb({tr,par});
        }
        return sol;
    }
    else
    {
        set<pair<int,int> > sol;
        for(auto p:contains[tr])
        {
            sol.insert({p,1});
            if(number[p]==1)
            {
                sol.erase({p,1});
            }
        }
        if(sol.size()>=k)
        {
            branches.pb({tr,par});
        }
        leaves.pb(sol);
        return leaves.size()-1;
    }
}

int main()
{
    int n,m;
    scanf("%i %i %i",&n,&m,&k);
    map<pair<int,int>,int> mapp;
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        mapp[{a,b}]=i;
        mapp[{b,a}]=i;
        graph[a].pb(b);
        graph[b].pb(a);
    }
    for(int i=0;i<m;i++)
    {
        scanf("%i",&number[i]);
        for(int j=0;j<number[i];j++)
        {
            int a;
            scanf("%i",&a);
            a--;
            contains[a].pb(i);
        }
    }
    solve(0,-1);
    vector<int> sol;
    for(auto p:branches)
    {
        int x=p.first;
        int y=p.second;
        sol.pb(mapp[{x,y}]);
    }
    sort(sol.begin(),sol.end());
    printf("%i\n",sol.size());
    for(auto p:sol)
    {
        printf("%i ",p);
    }
    return 0;
}
