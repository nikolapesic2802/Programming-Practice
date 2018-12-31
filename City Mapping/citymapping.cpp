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
    assert(d>=0);
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
    assert(dist[l][r]>=d);
    //printf("Dodajem izmedju %i %i  %i  %lld\n",l,r,n,d);
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
    //printf("Pitam %i %i\n",x,y);
    if(x>=offset)
        x=mapa[x];
    if(y>=offset)
        y=mapa[y];
    //printf("%i %i\n",x,y);
    return get_distance(x+1,y+1);
}
void printGraf(int tr,int par)
{
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        printf("%i %i\n",tr+1,p+1);
        printGraf(p,tr);
    }
}
vector<int> vertex;
int maxx,koji;
void dfs(int tr,pair<int,int> blocked,int d,int par)
{
    if(maxx<d)
    {
        koji=tr;
        maxx=d;
    }
    for(auto p:graf[tr])
    {
        if(p==blocked.first||p==par||p==blocked.second||blocke[p])
            continue;
        dfs(p,blocked,d+1,tr);
    }
}
vector<int> stk;
void dfs2(int tr,pair<int,int> blocked,int d,int par)
{
    stk.pb(tr);
    if(maxx==d)
    {
        vertex=stk;
        maxx++;
    }
    for(auto p:graf[tr])
    {
        if(p==blocked.first||p==par||p==blocked.second||blocke[p])
            continue;
        dfs2(p,blocked,d+1,tr);
    }
    stk.pop_back();
}
int find_vertex(int tr,int par)
{
    //printf("Trazim %i %i\n",tr,par);
    if(tr<offset||mapa[tr]!=-1)
        return tr;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        int t=find_vertex(p,tr);
        if(t!=-1)
            return t;
    }
    return -1;
}
void solve(int tr,pair<int,int> block,int dodati,ll di)
{
    printf("Solvujem %i  %i %i  %i\n",dodati+1,block.first,block.second,tr);
    maxx=0;
    dfs(tr,block,1,-1);
    maxx=0;
    dfs(koji,block,1,-1);
    stk.clear();
    dfs2(koji,block,1,-1);
    //cout << "Diameter: " << vertex << endl;
    if(vertex.back()>=offset&&mapa[vertex.back()]==-1)
    {
        if(vertex.size()==2)
        {
            add_between(vertex[0],vertex[1],dodati,di);
            return;
        }
        reverse(vertex.begin(),vertex.end());

        assert(vertex.back()<offset||mapa[vertex.back()]!=-1);
    }
    if(vertex[0]>=offset&&mapa[vertex[0]]==-1)
        assert(tr==vertex[0]);
    ll d=dist[vertex.front()][vertex.back()];
    ll d1;
    if(vertex[0]>=offset&&mapa[vertex[0]]==-1)
    {
        //printf("DA!\n");
        int ver=find_vertex(block.first,vertex[0]);
        if(ver==-1)
            ver=find_vertex(block.second,vertex[0]);
        //printf("VER! %i %i\n",ver,tr);
        assert(ver!=-1);
        d1=ask(ver,dodati);
        d1-=dist[ver][tr];
    }
    else
        d1=ask(vertex[0],dodati);
    if(vertex.size()==1){
        add_new(dodati,vertex[0],d1);
        return;
    }
    ll d2=ask(vertex.back(),dodati);
    //printf("%lld %lld  %lld\n",d1,d2,dist[vertex.front()][vertex.back()]);
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
    assert(s%2==0);
    s/=2;
    d1-=s;
    d2-=s;
    //printf("%lld %lld %lld %lld\n",d1,d2,s,dist[vertex.front()][vertex.back()]);
    int l=0,r=vertex.size()-1;
    //cout << "Diam2: " << vertex << endl;
    //printf("%lld %lld\n",d1,d2);
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        //printf("Mid; %i  %i-%i  %lld  %lld\n",vertex[mid]+1,vertex[l],vertex[mid],dist[vertex[l]][vertex[mid]],d1);
        if(dist[vertex[l]][vertex[mid]]>=d1){
            //printf("Idem of %i do %i: %lld\n",vertex[r]+1,vertex[mid]+1,dist[vertex[r]][vertex[mid]]);
            d2-=dist[vertex[r]][vertex[mid]];
            r=mid;
        }
        else{
            //printf("Idem2 of %i do %i: %lld\n",vertex[l]+1,vertex[mid]+1,dist[vertex[l]][vertex[mid]]);
            d1-=dist[vertex[l]][vertex[mid]];
            l=mid;
        }
    }
    //printf("%i %i  %i  %i  %lld  %lld\n",l,r,vertex[l]+1,vertex[r]+1,d1,d2);
    assert(r-l==1);
    if(d1==0)
    {
        if(s==0)
        {
            assert(vertex[l]>=offset);
            mapa[vertex[l]]=dodati;
            return;
        }
        assert(l>0&&l<vertex.size()-1);
        blocke[vertex[l-1]]=1;
        blocke[vertex[l+1]]=1;
        solve(vertex[l],{vertex[l-1],vertex[l+1]},dodati,s);
        return;
    }
    if(d2==0)
    {
        if(s==0)
        {
            assert(vertex[r]>=offset);
            mapa[vertex[r]]=dodati;
            return;
        }
        assert(r<vertex.size()-1&&r>0);
        blocke[vertex[r-1]]=1;
        blocke[vertex[r+1]]=1;
        solve(vertex[r],{vertex[r-1],vertex[r+1]},dodati,s);
        return;
    }
    //assert(d1+d2==dist[vertex[l]][vertex[r]]);
    if(s==0)
    {
        add_between(vertex[l],vertex[r],dodati,d1);
        return;
    }
    int tt=offset+cnt;
    cnt++;
    //printf("Dosao! %i-%i  %i   %lld\n",vertex[l],vertex[r],tt,d1-s);
    //assert(d1>0);
    add_between(vertex[l],vertex[r],tt,d1);
    add_new(dodati,tt,s);
}
void find_roads(int n, int Q, int A[], int B[], int W[]) {
    memset(dist,-1,sizeof(dist));
	ll a=get_distance(1,2);
	add_new(1,0,a);
	//printGraf(0,-1);
    for(int i=2;i<n;i++)
    {
        fill(blocke.begin(),blocke.end(),0);
        solve(0,{-1,-1},i,-1);
        printGraf(0,-1);
        /*for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(dist[i][j]!=-1)
                {
                    printf("Udaljenost izmedju %i i %i: %lld\n",i+1,j+1,dist[i][j]);
                }
            }
        }*/
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
            //printf("%i %i  %lld\n",tr+1,p+1,dist[tr][p]);
            num++;
            visited[p]=1;
            q.push(p);
        }
    }
	return;
}
