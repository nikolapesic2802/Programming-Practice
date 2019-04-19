/*
    -https://csacademy.com/contest/romanian-ioi-2017-selection-1/task/rooms/solution/
*/

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define f first
#define s second
using namespace std;
const int N=2005;
int visited[N][N];
char matrix[N][N];
int special[N][N];
pair<int,int> cnt[N*N];
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
int n,m;
bool inside(int x,int y)
{
	return x>0&&x<=n&&y>0&&y<=m;
}
bool inside(int x1,int y1,int x2,int y2,int x,int y)
{
    return x1<=x&&x2>=x&&y1<=y&&y2>=y;
}
int main()
{
	scanf("%i %i",&n,&m);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		scanf(" %c",&matrix[i][j]);
    int tr=1;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		if(visited[i][j]!=0)
    			continue;
            special[i][j]=1;
            cnt[tr]={i,j};
    		queue<pair<int,int> > q;
    		q.push({i,j});
    		visited[i][j]=tr;
    		while(q.size())
    		{
    			int x=q.front().first,y=q.front().second;
    			q.pop();
    			for(int k=0;k<4;k++)
    			{
    				int xx=x+dx[k];
    				int yy=y+dy[k];
    				if(!inside(xx,yy)||visited[xx][yy]!=0)
    					continue;
    				if(matrix[xx][yy]!=matrix[x][y])
    					continue;
    				q.push({xx,yy});
    				visited[xx][yy]=tr;
    			}
    		}
    		tr++;
    	}
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            special[i][j]+=special[i-1][j]+special[i][j-1]-special[i-1][j-1];
    vector<bool> boje(N*N);
    int q;
    scanf("%i",&q);
    for(int i=0;i<q;i++)
    {
        int x1,y1,x2,y2;
        scanf("%i %i %i %i",&x1,&y1,&x2,&y2);
        int ans=special[x2][y2]-special[x1-1][y2]-special[x2][y1-1]+special[x1-1][y1-1];
        for(int i=y1;i<=y2;i++)
        {
            if(inside(x1-1,i)&&matrix[x1-1][i]==matrix[x1][i])
                if(!inside(x1,y1,x2,y2,cnt[visited[x1][i]].f,cnt[visited[x1][i]].s)&&boje[visited[x1][i]]==0)
                    boje[visited[x1][i]]=1,ans++;
            if(inside(x2+1,i)&&matrix[x2+1][i]==matrix[x2][i])
                if(!inside(x1,y1,x2,y2,cnt[visited[x2][i]].f,cnt[visited[x2][i]].s)&&boje[visited[x2][i]]==0)
                    boje[visited[x2][i]]=1,ans++;
        }
        for(int i=x1;i<=x2;i++)
        {
            if(inside(i,y1-1)&&matrix[i][y1-1]==matrix[i][y1])
                if(!inside(x1,y1,x2,y2,cnt[visited[i][y1]].f,cnt[visited[i][y1]].s)&&boje[visited[i][y1]]==0)
                    boje[visited[i][y1]]=1,ans++;
            if(inside(i,y2+1)&&matrix[i][y2+1]==matrix[i][y2])
                if(!inside(x1,y1,x2,y2,cnt[visited[i][y2]].f,cnt[visited[i][y2]].s)&&boje[visited[i][y2]]==0)
                    boje[visited[i][y2]]=1,ans++;
        }
        printf("%i\n",ans);
        for(int i=y1;i<=y2;i++)
            boje[visited[x1][i]]=boje[visited[x2][i]]=0;
        for(int i=x1;i<=x2;i++)
            boje[visited[i][y1]]=boje[visited[i][y2]]=0;
    }
    return 0;
}
