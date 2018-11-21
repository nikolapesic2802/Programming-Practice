/*
    -https://codeforces.com/blog/entry/51010
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
int h,w;
const int N=5e4+5;
int sparce[2][2][N][20];
vector<int> ver(N),hor(N);
map<int,ll> memo[2][N];///0-up,down, 1-levo,desno;
///0,0 up  0,1 down 1,0 left
int up(int tr,int v)
{
    for(int j=0;j<20;j++)
    {
        if(sparce[0][0][tr][j]>v)
        {
            if(j==0)
                return tr-1;
            else
                return up(tr-(1<<(j-1)),v);
        }
    }
    return -1;
}
int down(int tr,int v)
{
    for(int j=0;j<20;j++)
    {
        if(sparce[0][1][tr][j]>v)
        {
            if(j==0)
                return tr+1;
            else
                return down(tr+(1<<(j-1)),v);
        }
    }
    return -1;
}
int left(int tr,int v)
{
    for(int j=0;j<20;j++)
    {
        if(sparce[1][0][tr][j]>v)
        {
            if(j==0)
                return tr-1;
            else
                return left(tr-(1<<(j-1)),v);
        }
    }
    return -1;
}
int right(int tr,int v)
{
    for(int j=0;j<20;j++)
    {
        if(sparce[1][1][tr][j]>v)
        {
            if(j==0)
                return tr+1;
            else
                return right(tr+(1<<(j-1)),v);
        }
    }
    return -1;
}
ll calc(int x,int y,int br)
{
    if(memo[br][x][y]!=0)
        return memo[br][x][y];
    //printf("Usao za %i %i %i\n",x,y,br);
    if(br==0)
    {
        int upp=up(x,ver[y]);
        int downn=down(x,ver[y]);
        //printf("Up: %i, down: %i\n",upp,downn);
        if(upp==-1)
        {
            memo[br][x][y]=x;
        }
        else
        {
            memo[br][x][y]=(ll)calc(upp,y,1)+x-upp;
        }

        if(downn==-1)
        {
            memo[br][x][y]=max(memo[br][x][y],(ll)h-1-x);
        }
        else
        {
            memo[br][x][y]=max(memo[br][x][y],(ll)calc(downn,y,1)+downn-x);
        }
    }
    else
    {
        int levo=left(y,hor[x]);
        int desno=right(y,hor[x]);
        //printf("Levo: %i, desno: %i\n",levo,desno);
        if(levo==-1)
        {
            memo[br][x][y]=y;
        }
        else
        {
            memo[br][x][y]=(ll)calc(x,levo,0)+y-levo;
        }
        if(desno==-1)
        {
            memo[br][x][y]=max(memo[br][x][y],(ll)w-1-y);
        }
        else
        {
            memo[br][x][y]=max(memo[br][x][y],(ll)calc(x,desno,0)+desno-y);
        }
    }
    return memo[br][x][y];
}

int main()
{
	int q;
	scanf("%i %i %i",&h,&w,&q);
	for(int i=0;i<h;i++)
        scanf("%i",&hor[i]);
    sparce[0][0][0][0]=-1;
    for(int i=1;i<h;i++)
    {
        sparce[0][0][i][0]=hor[i-1];
    }
    for(int j=1;j<20;j++)
    {
        int m=1<<(j-1);
        for(int i=0;i<h;i++)
        {
            if(i-m<0)
                sparce[0][0][i][j]=sparce[0][0][i][j-1];
            else
                sparce[0][0][i][j]=max(sparce[0][0][i-m][j-1],sparce[0][0][i][j-1]);
        }
    }
    sparce[0][1][h-1][0]=-1;
    for(int i=0;i<h-1;i++)
    {
        sparce[0][1][i][0]=hor[i+1];
    }
    for(int j=1;j<20;j++)
    {
        int m=1<<(j-1);
        for(int i=0;i<h;i++)
        {
            if(i+m>h-1)
                sparce[0][1][i][j]=sparce[0][1][i][j-1];
            else
                sparce[0][1][i][j]=max(sparce[0][1][i+m][j-1],sparce[0][1][i][j-1]);
        }
    }
    for(int i=0;i<w;i++)
        scanf("%i",&ver[i]);
    sparce[1][0][0][0]=-1;
    for(int i=1;i<w;i++)
    {
        sparce[1][0][i][0]=ver[i-1];
    }
    for(int j=1;j<20;j++)
    {
        int m=1<<(j-1);
        for(int i=0;i<w;i++)
        {
            if(i-m<0)
                sparce[1][0][i][j]=sparce[1][0][i][j-1];
            else
                sparce[1][0][i][j]=max(sparce[1][0][i-m][j-1],sparce[1][0][i][j-1]);
        }
    }
    sparce[1][1][w-1][0]=-1;
    for(int i=0;i<w-1;i++)
    {
        sparce[1][1][i][0]=ver[i+1];
    }
    for(int j=1;j<20;j++)
    {
        int m=1<<(j-1);
        for(int i=0;i<w;i++)
        {
            if(i+m>w-1)
                sparce[1][1][i][j]=sparce[1][1][i][j-1];
            else
                sparce[1][1][i][j]=max(sparce[1][1][i+m][j-1],sparce[1][1][i][j-1]);
        }
    }
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%i %i",&x,&y);
        x--;
        y--;
        printf("%lld\n",max(calc(x,y,0),calc(x,y,1)));
    }
    return 0;
}
