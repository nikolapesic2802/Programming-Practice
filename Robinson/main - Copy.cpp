#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=2e3+2,xOff=N,yOff=2e3+1;
int n,dist[2*N][4*N],w,x=-1,y,len,lft,rght;
char mat[2*N][4*N];
vector<pair<int,int> > shape;
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
bool ok(int a,int b){
    for(auto p:shape)
        if(mat[a+p.f][b+p.s]=='X')
            return 0;
    return 1;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	int cc=0;
	for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++)
            mat[i+xOff][j+yOff]=s[j];
	}
	for(int i=0;i<2*N;i++)
        for(int j=0;j<2*N;j++)
            if(mat[i][j]=='r'){
                if(x==-1)
                    x=i,y=j;
                shape.pb({i-x,j-y});
            }
    for(auto p:shape)
        len=max(len,p.f),lft=min(lft,p.s),rght=max(rght,p.s);
    int xMax=xOff+n,xMin=xOff-len-1,yMin=yOff-1+lft,yMax=yOff+n+rght;
    queue<pair<int,int> > q;
    q.push({x,y});
    dist[x][y]=1;
    assert(ok(x,y));
    while(q.size()){
        int xx=q.front().f,yy=q.front().s;
        q.pop();
        if(xx==xMin||xx==xMax||yy==yMin||yy==yMax){
            printf("%i\n",dist[xx][yy]-1);
            return 0;
        }
        for(int k=0;k<4;k++){
            int xxx=xx+dx[k],yyy=yy+dy[k];
            if(!dist[xxx][yyy]&&ok(xxx,yyy))
                q.push({xxx,yyy}),dist[xxx][yyy]=dist[xx][yy]+1;
        }
    }
    printf("NIE\n");
    return 0;
}
