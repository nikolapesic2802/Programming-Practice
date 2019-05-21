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

struct edge{
    char u,v;
    short w;
};
ostream& operator<<(ostream& out,edge a){out << "(" << a.u << "->" << a.v << " " << a.w << ")";return out;}
bool operator<(edge a,edge b){return a.w<b.w;}
const int RC=400,L=8;
int N;
vector<edge> sparce[RC][RC][L];
vector<char> par(41),siz(41);
void reset()
{
    for(int i=1;i<N;i++)
        par[i]=i,siz[i]=1;
}
int find(int tr)
{
    if(tr==par[tr])
        return tr;
    return par[tr]=find(par[tr]);
}
bool merge(int a,int b)
{
    a=find(a);
    b=find(b);
    if(a==b)
        return false;
    if(siz[a]<=siz[b])
        par[a]=b,siz[b]+=siz[a];
    else
        par[b]=a,siz[a]+=siz[b];
    return true;
}
vector<edge> merge(vector<edge> a,vector<edge> b)
{
    reset();
    vector<edge> sol;
    int i=0,j=0,aa=a.size(),bb=b.size();
    while(i<aa||j<bb)
    {
        if(i<aa&&j<bb)
        {
            if(a[i].w<=b[j].w){
                if(merge(a[i].u,a[i].v))
                    sol.pb(a[i]);
                i++;
            }
            else{
                if(merge(b[j].u,b[j].v))
                    sol.pb(b[j]);
                j++;
            }
            continue;
        }
        if(i==aa){
            if(merge(b[j].u,b[j].v))
                sol.pb(b[j]);
            j++;
        }
        else{
            if(merge(a[i].u,a[i].v))
                sol.pb(a[i]);
            i++;
        }
    }
    return sol;
}
int calc(vector<edge> a)
{
    reset();
    int cnt=1,sol=0;
    for(auto p:a)
        if(merge(p.u,p.v))
            cnt++,sol+=p.w;
    if(cnt!=N-1)
        return -1;
    return sol;
}
void Resi(int n, int r, int c, int q, int** u, int** v, int** w,int* x1, int* y1, int* x2, int* y2, int* o)
{
    N=n+1;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            sparce[i][j][0].pb({u[i][j],v[i][j],w[i][j]});
    for(int k=1;k<L;k++)
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                sparce[i][j][k]=merge(merge(sparce[i][j][k-1],sparce[i+(1<<(k-1))][j][k-1]),merge(sparce[i][j+(1<<(k-1))][k-1],sparce[i+(1<<(k-1))][j+(1<<(k-1))][k-1]));
    for(int i=1;i<=q;i++)
    {
        int d=min(x2[i]-x1[i]+1,y2[i]-y1[i]+1);
        int k=0,tr=1;
        while(tr<=d)
            k++,tr*=2;
        k--;
        tr/=2;
        tr--;
        int x=x1[i],y=y1[i];
        vector<edge> sol;
        while(x+tr!=x2[i])
        {
            while(y+tr!=y2[i])
            {
                sol=merge(sol,sparce[x][y][k]);
                y+=tr+1;
                if(y+tr>y2[i])
                    y=y2[i]-tr;
            }
            sol=merge(sol,sparce[x][y][k]);
            y=y1[i];
            x+=tr+1;
            if(x+tr>x2[i])
                x=x2[i]-tr;
        }
        while(y+tr!=y2[i])
        {
            sol=merge(sol,sparce[x][y][k]);
            y+=tr+1;
            if(y+tr>y2[i])
                y=y2[i]-tr;
        }
        sol=merge(sol,sparce[x][y][k]);
        o[i]=calc(sol);
    }
}

static int** matrica(int R, int C) {
	int** a = new int*[R+1];
	for (int i=1; i<=R; i++)
		a[i] = new int[C+1];
	return a;
}

static void pocisti(int** a, int R) {
	for (int i=1; i<=R; i++)
		delete[] a[i];
	delete a;
}

int main() {
    freopen("1.in","r",stdin);

	int N, R, C, Q;
	cin >> N >> R >> C >> Q;

	int** U = matrica(R, C);
	int** V = matrica(R, C);
	int** W = matrica(R, C);

	int* X1 = new int[Q+1];
	int* Y1 = new int[Q+1];
	int* X2 = new int[Q+1];
	int* Y2 = new int[Q+1];
	int* O  = new int[Q+1];

	for (int i=1; i<=R; i++)
		for (int j=1; j<=C; j++)
			cin >> U[i][j] >> V[i][j] >> W[i][j];

	for (int i=1; i<=Q; i++)
		cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

	Resi(N, R, C, Q, U, V, W, X1, Y1, X2, Y2, O);

	for (int i=1; i<=Q; i++)
		cout << O[i] << '\n';

	delete[] X1;
	delete[] Y1;
	delete[] X2;
	delete[] Y2;
	delete[] O;

	pocisti(U, R);
	pocisti(V, R);
	pocisti(W, R);
}
