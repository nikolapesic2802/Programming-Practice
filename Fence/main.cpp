/*
    -We can make a dp[i][j][d], i-number of posts less than the last post, j-number of posts greater than the last post, d-the direction in which we need to place the next post(smaller/larger/both)
    -Then simulate the process for each test case and find the Cth lexicographical smallest fence.
*/
#include <stdio.h>
#include <vector>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;

const int N=20;
ll dp[N][N][3];
ll calc(int manji,int veci,int dir) ///0-manje 1-vece 2-oba
{
    if(manji+veci==0)
        return 1;
    if(dp[manji][veci][dir]!=-1)
        return dp[manji][veci][dir];
    dp[manji][veci][dir]=0;
    if(dir==0||dir==2)
        for(int i=0;i<manji;i++)
            dp[manji][veci][dir]+=calc(manji-i-1,veci+i,1);
    if(dir==1||dir==2)
        for(int i=0;i<veci;i++)
            dp[manji][veci][dir]+=calc(manji+i,veci-i-1,0);
    return dp[manji][veci][dir];
}
vector<int> sol;
void solve(vector<int> manji,vector<int> veci,int dir,ll c)
{
    int m=manji.size(),v=veci.size();
    if(m+v==0)
        return;
    if(dir==3)
    {
        for(int i=0;i<v;i++)
        {
            vector<int> mm,vv;
            for(int j=0;j<i;j++)
                mm.pb(veci[j]);
            for(int j=i+1;j<v;j++)
                vv.pb(veci[j]);
            c-=calc(mm.size(),vv.size(),2);
            if(c<0)
            {
                sol.pb(veci[i]);
                solve(mm,vv,2,c+calc(mm.size(),vv.size(),2));
                return;
            }
        }
    }
    if(dir==0||dir==2)
    {
        for(int i=0;i<m;i++)
        {
            vector<int> mm,vv;
            for(int j=0;j<m;j++){
                if(j<i)
                    mm.pb(manji[j]);
                if(j>i)
                    vv.pb(manji[j]);
            }
            for(int j=0;j<v;j++)
                vv.pb(veci[j]);
            c-=calc(mm.size(),vv.size(),1);
            if(c<0)
            {
                sol.pb(manji[i]);
                solve(mm,vv,1,c+calc(mm.size(),vv.size(),1));
                return;
            }
        }
    }
    if(dir==1||dir==2)
    {
        for(int i=0;i<v;i++)
        {
            vector<int> mm,vv;
            for(int j=0;j<m;j++)
                mm.pb(manji[j]);
            for(int j=0;j<v;j++){
                if(j<i)
                    mm.pb(veci[j]);
                if(j>i)
                    vv.pb(veci[j]);
            }
            c-=calc(mm.size(),vv.size(),0);
            if(c<0)
            {
                sol.pb(veci[i]);
                solve(mm,vv,0,c+calc(mm.size(),vv.size(),0));
                return;
            }
        }
    }
}
int main()
{
	for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int o=0;o<3;o++)
                dp[i][j][o]=-1;
    int k;
    scanf("%i",&k);
    while(k--)
    {
        sol.clear();
        int n;
        ll c;
        scanf("%i %lld",&n,&c);
        vector<int> v,m;
        for(int i=1;i<=n;i++)
            v.pb(i);
        solve(m,v,3,c-1);
        for(int i=0,n=sol.size();i<n;i++)
            printf("%i ",sol[i]);
        printf("\n");
    }
    return 0;
}
