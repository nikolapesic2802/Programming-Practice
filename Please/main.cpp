/*
    - Decompose the tree using centroid decomposition.
    - Do something super similar to the example problem in this post: https://www.geeksforgeeks.org/centroid-decomposition-of-tree/
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;

const int N=3e5+5;
vector<vector<int> > graph(N),centroid_graph(N);
vector<int> visited(N),siz(N),local(N),what(N);
void dfs(int tr,int par)
{
    siz[tr]=1;
    for(auto p:graph[tr])
    {
        if(visited[p]||p==par)
            continue;
        dfs(p,tr);
        siz[tr]+=siz[p];
    }
}
int find_centroid(int tr,int n,int par)
{
    for(auto p:graph[tr])
    {
        if(p==par||visited[p])
            continue;
        if(siz[p]>n/2)
            return find_centroid(p,n,tr);
    }
    return tr;
}
int decompose(int tr)
{
    dfs(tr,-1);
    tr=find_centroid(tr,siz[tr],-1);
    visited[tr]=1;
    for(auto p:graph[tr])
    {
        if(visited[p])
            continue;
        int t=decompose(p);
        centroid_graph[t].pb(tr);
        centroid_graph[tr].pb(t);
    }
    return tr;
}
ll cnt=0;
vector<int> allowed(N),str,fin,start(N),finish(N);
void calculate(int tr,int par,int offset,int maxx,int minn)
{
    if(what[tr]==0){
        offset++;
        maxx=max(maxx,offset);
        if(offset==maxx)
        {
            str.pb(offset);
        }
    }
    else{
        offset--;
        minn=min(minn,offset);
        if(offset==minn)
        {
            fin.pb(-1*offset);
        }
    }
    for(auto p:graph[tr])
    {
        if(allowed[p]==0||p==par)
            continue;
        calculate(p,tr,offset,maxx,minn);
    }
}
void solve(int tr,int par)
{
    for(auto p:centroid_graph[tr])
    {
        if(p==par)
            continue;
        solve(p,tr);
    }
    int off;
    if(what[tr]==0)
        off=1;
    else
        off=-1;
    vector<int> s,f;
    for(auto p:graph[tr])
    {
        if(allowed[p]){
            calculate(p,tr,0,0,0);
            for(auto d:str)
            {
                if(off+d>=0)
                    cnt+=finish[d+off];
                s.pb(d);
            }
            for(auto d:fin)
            {
                if(d-off>=0)
                    cnt+=start[d-off];
                finish[d]++;
                f.pb(d);
            }
            for(auto d:str)
                start[d]++;
            str.clear();
            fin.clear();
        }
    }
    allowed[tr]=1;
    if(what[tr]==0)
        cnt+=finish[1];
    else
        cnt+=start[1];
    for(auto p:s)
        start[p]=0;
    for(auto p:f)
        finish[p]=0;
}
int main()
{
	int n;
	scanf("%i",&n);
	string s;
	cin >> s;
	for(int i=0;i<n;i++)
        what[i+1]=s[i]==')';
	for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        graph[a].pb(b);
        graph[b].pb(a);
    }
    int root=decompose(1);
    solve(root,-1);
    printf("%lld\n",cnt);
    return 0;
}
