/*
    -Calculate for every position and a direction of push, where the robot will end up
    -Use something like bfs to figure out what is the lowest number of pushes required to merge all the robots from interval [l,r]
*/
#include <bits/stdc++.h>

#define pb push_back
#define f first
#define s second

using namespace std;

const int N=9,H=500,maxDist=H*H; ///By trial and error(submitting a bunch), i found out that the max Distance will be at most 500*500 and not 500*500*9 which let my program run in time
int n,h,w;
vector<int> dx={-1,0,1,0},dy={0,1,0,-1};
pair<int,int> dest[H][H][4],null={-1,-1};
vector<string> board;
void add(int &a,int b)
{
    a+=b;
    if(a>=4)
        a-=4;
    if(a<0)
        a+=4;
}
pair<int,int> dfs(int i,int j,int p)
{
    if(dest[i][j][p]!=null)
        return dest[i][j][p];
    int np=p;
    if(board[i][j]=='A')
        add(np,-1);
    if(board[i][j]=='C')
        add(np,1);
    int ni=i+dx[np];
    int nj=j+dy[np];
    if(ni<0||ni>=h||nj<0||nj>=w||board[ni][nj]=='x')
        return dest[i][j][p]=make_pair(i,j);
    return dest[i][j][p]=dfs(ni,nj,np);
}
vector<vector<vector<int> > > dp;
vector<vector<int> > initial_dp(H,vector<int>(H,(int)1e9));
int mask[H][H];
vector<pair<int,int> > q[maxDist];
void update(int k,int x,int y,int d)
{
    if(d<dp[k][x][y])
    {
        dp[k][x][y]=d;
        q[d].pb({x,y});
    }
}
void bfs(int k)
{
    for(int i=0;i<maxDist;i++)
        for(auto p:q[i])
            if(dp[k][p.f][p.s]>=i)
                for(int l=0;l<4;l++)
                    update(k,dest[p.f][p.s][l].f,dest[p.f][p.s][l].s,i+1);
}
int main()
{
    for(int i=0;i<H;i++)
        for(int j=0;j<H;j++)
            for(int k=0;k<4;k++)
                dest[i][j][k]=null;
	scanf("%i %i %i",&n,&h,&w);
	swap(h,w);
	board.resize(h);
	for(int i=0;i<h;i++)
        cin >> board[i];
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            for(int k=0;k<4;k++)
                dfs(i,j,k);
    vector<pair<int,int> > pos(n);
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
        {
            int t=board[i][j]-'0';
            if(t>0&&t<10)
                pos[t-1]=make_pair(i,j);
        }
    for(int i=0,k=0;i<n;i++)
    {
        for(int j=i;j>=0;j--,k++)
        {
            mask[j][i]=k;
            dp.pb(initial_dp);
            if(j==i)
                update(k,pos[j].f,pos[j].s,0);
            else
                for(int x=0;x<h;x++)
                    for(int y=0;y<w;y++)
                        for(int l=j;l<i;l++)
                            update(k,x,y,dp[mask[j][l]][x][y]+dp[mask[l+1][i]][x][y]);
            bfs(k);
            for(int l=0;l<maxDist;l++)
                q[l].clear();
        }
    }
    int ans=1e9;
    for(int x=0;x<h;x++)
        for(int y=0;y<w;y++)
            ans=min(ans,dp[mask[0][n-1]][x][y]);
    if(ans==(int)1e9)
        printf("-1\n");
    else
        printf("%i\n",ans);
    return 0;
}
