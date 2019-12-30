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

const int N=4e3+5,xOff=2e3+1,yOff=1e3+1;
int n,x=-1,y,s,xLimMin,xLimMax,yLimMin,yLimMax,comp=0;
vector<int> leftSide,rightSide,dx={1,-1,0,0},dy={0,0,1,-1};
struct line{
    int x,y;
    int getVal(int pos){
        if(pos>x||x-pos>=s){
            if(comp)
                return N;
            return -1;
        }
        return y+leftSide[x-pos];
    }
} LiChao[4*N];
char mat[N][N];
bool moze[N][N];
void resetLiChao(){
    for(int i=0;i<4*N;i++)
        LiChao[i]={N,N};
}
void addLine(line li,int l=0,int r=N,int i=1){
    int qs=li.x-s+1,qe=li.x;
    //printf("%i %i  %i-%i   %i  %i  %i\n",li.x,li.y,qs,qe,l,r,i);
    if(qs>=r||qe<l)
        return;
    int m=(l+r)>>1;
    if(qs>l||qe<r-1){
        addLine(li,l,m,2*i);
        addLine(li,m,r,2*i+1);
        return;
    }
    bool lef,mid;
    if(comp)
        lef=li.getVal(l)<LiChao[i].getVal(l),mid=li.getVal(m)<LiChao[i].getVal(m);
    else
        lef=li.getVal(l)>LiChao[i].getVal(l),mid=li.getVal(m)>LiChao[i].getVal(m);
    if(mid)
        swap(li,LiChao[i]);
    if(l==r-1)
        return;
    if(lef!=mid)
        addLine(li,l,m,2*i);
    else
        addLine(li,m,r,2*i+1);
}
int getPos(int pos,int l=0,int r=N,int i=1){
    if(l==r-1)
        return LiChao[i].getVal(pos);
    int m=(l+r)>>1;
    if(comp){
        if(pos<m)
            return min(LiChao[i].getVal(pos),getPos(pos,l,m,2*i));
        return min(LiChao[i].getVal(pos),getPos(pos,m,r,2*i+1));
    }
    if(pos<m)
        return max(LiChao[i].getVal(pos),getPos(pos,l,m,2*i));
    return max(LiChao[i].getVal(pos),getPos(pos,m,r,2*i+1));
}
int main()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            moze[i][j]=1;
    resetLiChao();
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for(int i=0;i<n;i++){
        string in;
        cin >> in;
        for(int j=0;j<n;j++)
            mat[i+xOff][j+yOff]=in[j];
	}
	return 0;
	int l=0,r=0;
    for(int i=0;i<N;i++){
        int frst=N,lst=0;
        for(int j=0;j<N;j++)
            if(mat[i][j]=='r')
                frst=min(frst,j),lst=max(lst,j);
        if(frst!=N){
            if(x==-1){
                x=i;
                y=(lst+frst)/2;
            }
            leftSide.pb(y-frst);
            rightSide.pb(y-lst);
        }
        l=max(l,y-frst);
        r=max(r,lst-y);
    }
    s=leftSide.size();
    //reverse(all(leftSide));
    //reverse(all(rightSide));
    //cout << leftSide << rightSide << endl;
    xLimMax=xOff+n;
    xLimMin=xOff-s;
    yLimMin=yOff-1-r;
    yLimMax=yOff+n+l;
    return 0;
    for(int j=yLimMin;j<=yLimMax;j++)
        for(int i=xLimMax;i>=xLimMin;i--){
            if(mat[i][j]=='X')
                addLine({i,j});
            if(getPos(i)>=j)
                moze[i][j]=0;
        }
    resetLiChao();
    comp=1;
    swap(leftSide,rightSide);
    for(int j=yLimMax;j>=yLimMin;j--)
        for(int i=xLimMax;i>=xLimMin;i--){
            if(mat[i][j]=='X')
                addLine({i,j});
            if(getPos(i)<=j)
                moze[i][j]=0;
        }
    /*for(int i=xLimMin;i<=xLimMax;i++){
        for(int j=yLimMin;j<=yLimMax;j++){
            if(i==x&&j==y)
                printf("S");
            else
                printf("%c",moze[i][j]?'.':'#');
        }
        printf("\n");
    }*/
    queue<pair<pair<int,int>,int> > q;
    q.push({{x,y},0});
    moze[x][y]=0;
    while(q.size()){
        int xx=q.front().f.f,yy=q.front().f.s,dist=q.front().s;
        q.pop();
        if(xx==xLimMin||xx==xLimMax||yy==yLimMin||yy==yLimMax){
            printf("%i\n",dist);
            return 0;
        }
        for(int k=0;k<4;k++){
            int xxx=xx+dx[k],yyy=yy+dy[k];
            if(moze[xxx][yyy])
                moze[xxx][yyy]=0,q.push({{xxx,yyy},dist+1});
        }
    }
    printf("NIE\n");
    return 0;
}
