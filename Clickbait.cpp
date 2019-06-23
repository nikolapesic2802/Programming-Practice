#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
const int N=1005;
vector<vector<pair<int,int> > > pipes(N*N);
int n,m;
vector<string> mat;
vector<vector<pair<int,pair<int,int> > > > container(N,vector<pair<int,pair<int,int> > >(N));
vector<vector<int> > pipe(N,vector<int>(N));
bool inside(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m;
}
void find_containers()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(mat[i][j]=='+')
            {
                int x=i,y=j;
                int rx,ry;
                y++;
                while(inside(x,y)&&mat[x][y]=='-')
                    y++;
                if(!inside(x,y)||mat[x][y]!='+')
                    continue;
                x++;
                while(inside(x,y)&&mat[x][y]=='|')
                    x++;
                if(!inside(x,y)||mat[x][y]!='+')
                    continue;
                rx=x;ry=y;
                y--;
                while(inside(x,y)&&mat[x][y]=='-')
                    y--;
                if(!inside(x,y)||mat[x][y]!='+')
                    continue;
                x--;
                while(inside(x,y)&&mat[x][y]=='|')
                    x--;
                if(!inside(x,y)||mat[x][y]!='+'||x!=i||y!=j)
                    continue;
                int c=0;
                for(x=i+1;x<rx;x++)
                {
                    for(y=j+1;y<ry;y++)
                    {
                        if(mat[x][y]!='.')
                        {
                            c*=10;
                            c+=mat[x][y]-'0';
                        }
                    }
                }
                //printf("Nasao %i od %i %i do %i %i\n",c,i,j,rx,ry);
                for(x=i;x<=rx;x++)
                {
                    for(y=j;y<=ry;y++)
                    {
                        container[x][y].first=c;
                        container[x][y].second.first=i;
                        container[x][y].second.second=j;
                    }
                }
            }
        }
    }
}
void find_pipes()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(mat[i][j]=='+'&&container[i][j].first==0&&!pipe[i][j])
            {
                //printf("Usao za %i %i\n",i,j);
                vector<pair<int,int> > connect;
                queue<pair<int,int> > q;
                q.push({i,j});
                pipe[i][j]=1;
                while(!q.empty())
                {
                    int x=q.front().first;
                    int y=q.front().second;
                    //printf("%i %i\n",x,y);
                    q.pop();
                    if(mat[x][y]=='.')
                    {
                        continue;
                    }
                    if(container[x][y].first!=0){
                        connect.pb({container[x][y].first,x-container[x][y].second.first});
                        continue;
                    }
                    for(int k=-1;k<2;k+=2)
                    {
                        if(inside(x+k,y)&&!pipe[x+k][y]&&mat[x+k][y]!='.')
                        {
                            pipe[x+k][y]=1;
                            q.push({x+k,y});
                        }
                        if(inside(x,y+k)&&!pipe[x][y+k]&&mat[x][y+k]!='.')
                        {
                            pipe[x][y+k]=1;
                            q.push({x,y+k});
                        }
                    }
                }
                assert(connect.size()==2);
                if(connect[0].second!=0)
                {
                    //printf("Dodajem iz %i u %i-%i\n",connect[0].first,N-connect[0].second,connect[1].first);
                    pipes[connect[0].first].pb({N-connect[0].second,connect[1].first});
                }
                else
                {
                    //printf("Dodajem iz %i u %i-%i\n",connect[1].first,N-connect[1].second,connect[0].first);
                    if(connect[1].second!=0)
                        pipes[connect[1].first].pb({N-connect[1].second,connect[0].first});
                }
            }
        }
    }
}
vector<int> solve(int tr)
{
    vector<int> sol;
    for(auto p:pipes[tr])
    {
        vector<int> s=solve(p.second);
        for(auto d:s)
            sol.pb(d);
    }
    sol.pb(tr);
    return sol;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    mat.resize(n);
    for(int i=0;i<n;i++)
        cin >> mat[i];
    find_containers();
    find_pipes();
    for(int i=0;i<N*N;i++)
    {
        sort(pipes[i].begin(),pipes[i].end());
    }
    vector<int> sol=solve(1);
    for(auto p:sol)
        printf("%i\n",p);
    return 0;
}
