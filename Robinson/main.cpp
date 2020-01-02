/*
    -Same as editorial.
    -Fix the boat to some single point.
    -For each field figure out if the fixed point of the boat is at that location, does the boat intersect with some obstacle, and if the boat is out of the map (in the high seas) or not.
    -We can do this by first orienting the boat such that its axis of symmetry is vertical.
    -Now store the shape of the ship in an array where each element describes the width of the ship at that x coordinate.
    -Now sweep in ascending order of x coordinate for every column and for every X, we will mark all the fields that that X intersects as invalid.
    -To do this keep a deque of the widest part of the ship in a similar style to convex hull dp optimization, and mark the interval that we cant visit in an array.
    -We can mark this by putting 1 where the forbidden area starts and -1 one field after it ends, and do prefix sums on the array later.
    -Do the same to figure out if the boat is in high sees or not just by inserting not only for every X but for every field in the matrix.
    -Now just run a BFS to find the closest path to the high sees.
*/
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

const int N=2e3+2,xOff=N,yOff=1e3+1;
int n,cnt[2*N][2*N],inside[2*N][2*N],w,x,y;
char mat[2*N][2*N],in[N][N];
vector<int> shape,dx={1,-1,0,0},dy={0,0,1,-1};
bool symetric(){
    shape.clear();
    w=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(in[i][j]=='r'){
                int ww=1;
                for(int k=j+1;k<n;k++)
                    if(in[i][k]=='r')
                        ww++;
                j+=ww/2;
                x=i+xOff,y=j+yOff;
                for(int k=i;k<n;k++){
                    if(in[k][j]=='r'){
                        int le=0,ri=0;
                        for(int l=j-1;l>=0;l--)
                            if(in[k][l]=='r')
                                le++;
                            else
                                break;
                        for(int l=j+1;l<n;l++)
                            if(in[k][l]=='r')
                                ri++;
                            else
                                break;
                        shape.pb(le);
                        w=max(w,le);
                        if(le!=ri)
                            return 0;
                    }
                }
                return 1;
            }
        }
}
void swapit(){
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            swap(in[i][j],in[j][i]);
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++)
            in[i][j]=s[j];
	}
	if(!symetric())
        swapit();
    assert(symetric());
    int s=shape.size();
    while(shape.size()<2*N)
        shape.pb(INT_MIN);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i+xOff][j+yOff]=in[i][j];
    int xMax=xOff+n,xMin=xOff-s,yMin=yOff-1-w,yMax=yOff+n+w;
    for(int j=yMin;j<=yMax;j++){
        deque<int> best,ins;
        for(int i=xMax;i>=xMin;i--){
            if(mat[i][j]=='X')
                best.pb(i);
            if(i>=xOff&&i<xOff+n&&j>=yOff&&j<yOff+n)
                ins.pb(i);
            while(best.size()>1&&shape[best[0]-i]<shape[best[1]-i])
                best.pop_front();
            while(ins.size()>1&&shape[ins[0]-i]<shape[ins[1]-i])
                ins.pop_front();
            if(ins.size()&&shape[ins[0]-i]>=0)
                inside[i][j-shape[ins[0]-i]]++,inside[i][j+shape[ins[0]-i]+1]--;
            if(best.size()&&shape[best[0]-i]>=0)
                cnt[i][j-shape[best[0]-i]]++,cnt[i][j+shape[best[0]-i]+1]--;
        }
    }
    for(int i=xMin;i<=xMax;i++)
        for(int j=yMin;j<=yMax;j++)
            cnt[i][j]+=cnt[i][j-1],inside[i][j]+=inside[i][j-1];
    queue<pair<pair<int,int>,int> > q;
    q.push({{x,y},0});
    cnt[x][y]=1;
    while(q.size()){
        int xx=q.front().f.f,yy=q.front().f.s,dist=q.front().s;
        q.pop();
        if(!inside[xx][yy])
            return 0*printf("%i\n",dist);
        for(int k=0;k<4;k++){
            int xxx=xx+dx[k],yyy=yy+dy[k];
            if(!cnt[xxx][yyy])
                cnt[xxx][yyy]=1,q.push({{xxx,yyy},dist+1});
        }
    }
    printf("NIE\n");
    return 0;
}
