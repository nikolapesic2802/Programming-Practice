/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/COCI/official/2008/contest4_solutions
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
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=40,D=20;
int matrix[N][N];
set<pair<int,int> > kocke;
int x=D,y=D;
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
string dir="RLUD";
bool inside(int x,int y)
{
    return x>=0&&x<N&&y>=0&&y<N;
}
int okolo(int a,int b)
{
    int cnt=0;
    for(int k=0;k<4;k++)
    {
        int xx=a+dx[k],yy=b+dy[k];
        if(!inside(xx,yy))
            continue;
        if(matrix[xx][yy])
            cnt++;
    }
    return cnt;
}
string sol;
void move(int k)
{
    sol+=dir[k];
    if(matrix[x+dx[k]][y+dy[k]]==1)
    {
        matrix[x+dx[k]][y+dy[k]]=0;
        matrix[x+2*dx[k]][y+2*dy[k]]=1;
        if(kocke.count({x+dx[k],y+dy[k]}))
        {
            kocke.erase({x+dx[k],y+dy[k]});
            kocke.insert({x+2*dx[k],y+2*dy[k]});
        }
    }
    x+=dx[k];
    y+=dy[k];
}
bool pomeriRobota(int i,int j)
{
    vector<vector<pair<pair<int,int>,int> > > visited(N,vector<pair<pair<int,int>,int> >(N,{{-1,-1},-1}));
    queue<pair<int,int> > q;
    q.push({x,y});
    visited[x][y]={{x,y},-1};
    while(q.size())
    {
        int mx=q.front().f,my=q.front().s;
        q.pop();
        for(int k=0;k<4;k++)
        {
            int xx=mx+dx[k];
            int yy=my+dy[k];
            if(!inside(xx,yy)||visited[xx][yy].f.f!=-1||matrix[xx][yy])
                continue;
            visited[xx][yy]={{mx,my},k};
            q.push({xx,yy});
        }
    }
    pair<int,int> poz={i,j};
    if(visited[poz.f][poz.s].f.f==-1)
        return false;
    vector<int> kaovi;
    while(visited[poz.f][poz.s].s!=-1)
    {
        kaovi.pb(visited[poz.f][poz.s].s);
        poz=visited[poz.f][poz.s].f;
    }
    reverse(all(kaovi));
    for(auto p:kaovi)
        move(p);
    return true;
}
void specijalanSlucaj(int i,int j)
{
    assert(pomeriRobota(i,j+2));
    for(int k=0;k<4;k++)
        assert(kocke.count({i+dx[k],j+dy[k]})),kocke.erase({i+dx[k],j+dy[k]});
    assert(kocke.size()==1);
    pair<int,int> tr=*kocke.begin();
    kocke.erase(kocke.begin());
    move(3);
    vector<vector<pair<pair<int,int>,int> > > visited(N,vector<pair<pair<int,int>,int> >(N,{{-1,-1},-1}));
    queue<pair<int,int> > q;
    q.push({tr.f,tr.s});
    visited[tr.f][tr.s]={{tr.f,tr.s},-1};
    matrix[tr.f][tr.s]=0;
    while(q.size())
    {
        int mx=q.front().f,my=q.front().s;
        q.pop();
        for(int k=0;k<4;k++)
        {
            int xx=mx+dx[k];
            int yy=my+dy[k];
            if(!inside(xx,yy)||visited[xx][yy].f.f!=-1||okolo(xx,yy))
                continue;
            visited[xx][yy]={{mx,my},k};
            q.push({xx,yy});
        }
    }
    matrix[tr.f][tr.s]=1;
    pair<int,int> poz={i,j-3};
    assert(visited[poz.f][poz.s].f.f!=-1);
    vector<pair<pair<int,int>,int> > kaovi;
    while(visited[poz.f][poz.s].s!=-1)
    {
        kaovi.pb({{poz.f,poz.s},visited[poz.f][poz.s].s});
        poz=visited[poz.f][poz.s].f;
    }
    reverse(all(kaovi));
    for(auto p:kaovi)
    {
        assert(pomeriRobota(p.f.f-2*dx[p.s],p.f.s-2*dy[p.s]));
        move(p.s);
    }
    assert(pomeriRobota(i,j-4));
    move(2);
    cout << sol << endl;
    exit(0);
}
void construct()
{
    sol+=dir[0];
    sol+=dir[3];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[2];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[3];
    sol+=dir[3];
    sol+=dir[1];
    sol+=dir[3];
    sol+=dir[0];
    sol+=dir[0];
    sol+=dir[0];
    sol+=dir[3];
    sol+=dir[0];
    sol+=dir[2];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[1];
    sol+=dir[2];
    sol+=dir[2];
    sol+=dir[2];
    sol+=dir[1];
    sol+=dir[3];
    sol+=dir[3];
    sol+=dir[1];
    sol+=dir[3];
    sol+=dir[0];
    sol+=dir[0];
    sol+=dir[0];
    sol+=dir[0];
    sol+=dir[0];
    cout << sol << endl;
    exit(0);
}

void solve()
{
    for(int i=1;i<=9;i+=2)
    {
        pair<int,int> poz=*kocke.begin();
        if(!pomeriRobota(poz.f+1,poz.s))
            specijalanSlucaj(poz.f+1,poz.s);
        kocke.erase(kocke.begin());
        while(x-1>i)
            move(1);
        move(2);
        move(1);
        while(y-1>1)
            move(3);
    }
    construct();
}
int main()
{
	for(int i=0;i<5;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a+=D,b+=D;
        kocke.insert({a,b});
        matrix[a][b]=1;
    }
    if(okolo(x,y)==4)
    {
        for(int k=0;k<4;k++)
        {
            if(okolo(x+2*dx[k],y+2*dy[k])==1)
            {
                move(k);
                break;
            }
        }
    }
    solve();
    return 0;
}
