/*
    -My idea is to go from vertex 1 to N and insert them in the right place in the graph.
    -Sometimes this requires us to add some temporary vertexes, in my case i added them as vertexes with values greater than N. Later when i find out what vertex that is i put a map value to tell me what the real value of that vertex is
    -I figured out the right place for every vertex by taking the diameter of the current tree, and figuring out where on the diameter the vertex is, and calling recursively for that subtree or adding it to the ends. We need to make sure not the explore the same vertexes 2 times too.
    -Taking the diameter insures that the size of the next diameter is at most half of the current one so we get log n recursive calls.
*/
#include "citymapping.h"
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
using namespace std;
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a))
			os << ", ";
		os << a[i]+1;
	}
	os << '}';
    return os;
}
const int N=2e3+5;
const int offset=1e3+5;
vector<vector<int> > graf(N);
vector<int> blocke(N);
vector<int> mapa(N,-1);
ll dist[N][N];
int cnt=0;
void add_new(int n,int old,ll d)
{
    graf[n].pb(old);
    graf[old].pb(n);
    for(int i=0;i<N;i++)
        if(dist[old][i]!=-1)
            dist[n][i]=dist[old][i]+d,dist[i][n]=dist[old][i]+d;
    dist[n][old]=d;
    dist[old][n]=d;
}
vector<int> v;
void dfs3(int tr,int par)
{
    v.pb(tr);
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        dfs3(p,tr);
    }
}
void add_between(int l,int r,int n,ll d)
{
    v.clear();
    dfs3(l,r);
    for(auto p:v)
        dist[n][p]=dist[l][p]+d,dist[p][n]=dist[l][p]+d;
    v.clear();
    dfs3(r,l);
    for(auto p:v)
        dist[n][p]=dist[r][p]+dist[l][r]-d,dist[p][n]=dist[r][p]+dist[l][r]-d;
    for(int i=0;i<(int)graf[l].size();i++)
    {
        if(graf[l][i]==r)
        {
            graf[l].erase(graf[l].begin()+i);
            break;
        }
    }
    for(int i=0;i<(int)graf[r].size();i++)
    {
        if(graf[r][i]==l)
        {
            graf[r].erase(graf[r].begin()+i);
            break;
        }
    }
    graf[l].pb(n);
    graf[n].pb(l);
    graf[r].pb(n);
    graf[n].pb(r);
    dist[l][n]=d;
    dist[n][l]=d;
    dist[r][n]=dist[l][r]-d;
    dist[n][r]=dist[l][r]-d;
}
ll ask(int x,int y)
{
    if(dist[x][y]!=-1)
        return dist[x][y];
    if(x>=offset)
        x=mapa[x];
    if(y>=offset)
        y=mapa[y];
    return get_distance(x+1,y+1);
}
vector<int> vertex;
int maxx,koji;
void dfs(int tr,int d,int par)
{
    if(maxx<d)
    {
        koji=tr;
        maxx=d;
    }
    for(auto p:graf[tr])
    {
        if(p==par||blocke[p])
            continue;
        dfs(p,d+1,tr);
    }
}
vector<int> stk;
void dfs2(int tr,int d,int par)
{
    stk.pb(tr);
    if(maxx==d)
    {
        vertex=stk;
        maxx++;
    }
    for(auto p:graf[tr])
    {
        if(p==par||blocke[p])
            continue;
        dfs2(p,d+1,tr);
    }
    stk.pop_back();
}
void solve(int tr,int dodati)
{
    maxx=0;
    dfs(tr,1,-1);
    maxx=0;
    dfs(koji,1,-1);
    stk.clear();
    dfs2(koji,1,-1);
    ll d1=ask(vertex.front(),dodati);
    ll d2=ask(vertex.back(),dodati);
    ll d=dist[vertex.front()][vertex.back()];
    if(abs(d1-d2)==d)
    {
        if(d2>d1)
        {
            add_new(dodati,vertex.front(),d1);
        }
        else
        {
            add_new(dodati,vertex.back(),d2);
        }
        return;
    }
    ll s=d1+d2;
    s-=dist[vertex.front()][vertex.back()];
    s/=2;
    d1-=s;
    d2-=s;
    int l=0,r=vertex.size()-1;
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        if(dist[vertex[l]][vertex[mid]]>=d1)
        {
            d2-=dist[vertex[r]][vertex[mid]];
            r=mid;
        }
        else
        {
            d1-=dist[vertex[l]][vertex[mid]];
            l=mid;
        }
    }
    if(d1==0)
    {
        if(s==0)
        {
            mapa[vertex[l]]=dodati;
            return;
        }
        if(graf[vertex[l]].size()<3)
        {
            add_new(dodati,vertex[l],s);
            return;
        }
        blocke[vertex[l-1]]=1;
        blocke[vertex[l+1]]=1;
        dist[vertex[l]][dodati]=s;
        dist[dodati][vertex[l]]=s;
        solve(vertex[l],dodati);
        return;
    }
    if(d2==0)
    {
        if(s==0)
        {
            mapa[vertex[r]]=dodati;
            return;
        }
        if(graf[vertex[r]].size()<3)
        {
            add_new(dodati,vertex[r],s);
            return;
        }
        blocke[vertex[r-1]]=1;
        blocke[vertex[r+1]]=1;
        dist[vertex[r]][dodati]=s;
        dist[dodati][vertex[r]]=s;
        solve(vertex[r],dodati);
        return;
    }
    if(s==0)
    {
        add_between(vertex[l],vertex[r],dodati,d1);
        return;
    }
    int tt=offset+cnt;
    cnt++;
    add_between(vertex[l],vertex[r],tt,d1);
    add_new(dodati,tt,s);
}
void find_roads(int n, int Q, int A[], int B[], int W[]) {
    memset(dist,-1,sizeof(dist));
	ll a=get_distance(1,2);
	add_new(1,0,a);
    for(int i=2;i<n;i++)
    {
        fill(blocke.begin(),blocke.end(),0);
        solve(0,i);
    }
    int num=0;
    vector<int> visited(N);
    queue<int> q;
    q.push(0);
    visited[0]=1;
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        for(auto p:graf[tr])
        {
            if(visited[p])
                continue;
            if(tr>=offset)
                A[num]=mapa[tr]+1;
            else
                A[num]=tr+1;
            if(p>=offset)
                B[num]=mapa[p]+1;
            else
                B[num]=p+1;
            W[num]=dist[tr][p];
            num++;
            visited[p]=1;
            q.push(p);
        }
    }
	return;
}
