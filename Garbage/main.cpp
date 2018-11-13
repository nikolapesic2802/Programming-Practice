/*
    - Its enough to just travel using streets that either have garbage on them and need to be clean or the opposite
    - Also its only possible to complete the task if the graph consisting only of the above mentioned edges has an euler cycle
    - The algorithm for finding the cycles to go on is something similar to the algorithm for finding biconneced components (algo with the stack)
    - Its quite a challenge to make the solution run in time, you need to do the following things:
      * Mark an edge as visited in O(1) (not using a map)
      * Save up to which edge you came to for each vertex (so you dont check for the same edges if they are not visited a lot of times i guess. It took me a long time to figure this out)
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
const int N=1e5+5;
vector<int> degree(N);
vector<vector<pair<int,int> > > graf(N);
vector<int> visited(10*N);
vector<vector<int> > sol;
stack<int> stk;
vector<int> vis(N);
vector<int> indx(N);
void solve(int tr)
{
    vis[tr]++;
    stk.push(tr);
    if(vis[tr]==2)
    {
        vector<int> t;
        t.pb(tr);
        vis[tr]--;
        stk.pop();
        while(stk.top()!=tr)
        {
            t.pb(stk.top());
            vis[stk.top()]--;
            stk.pop();
        }
        t.pb(stk.top());
        sol.pb(t);
    }
    for(int i=indx[tr];i<graf[tr].size();i++)
    {
        indx[tr]++;
        if(!visited[graf[tr][i].second])
        {
            int p=graf[tr][i].first;
            visited[graf[tr][i].second]=1;
            degree[tr]--;
            degree[p]--;
            solve(p);
            return;
        }
    }
}
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,s,t;
        scanf("%i %i %i %i",&a,&b,&s,&t);
        if(s!=t)
        {
            graf[a].pb({b,i});
            graf[b].pb({a,i});
            degree[a]++;
            degree[b]++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(degree[i]%2==1)
        {
            printf("NIE\n");
            return 0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        while(degree[i]!=0)
        {
            while(stk.size())
                stk.pop();
            solve(i);
            vis[i]--;
        }
    }
    printf("%d\n",sol.size());
    for(auto p:sol)
    {
        printf("%d ",p.size()-1);
        for(auto d:p)
        {
            printf("%d ",d);
        }
        printf("\n");
    }
    return 0;
}
