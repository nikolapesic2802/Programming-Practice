/*
    -Sort the fields in the matrix by the number in that field in decreasing order.
    -Go through the fields in that order and if there is a field with bigger or equal value as the current field next to the current field (in one of the four directions), we can merge them in our dsu.
    -Notice that now we can to from one field to another with the minimal cost field of the last field we visited in the last step if they are in the same dsu set when we do the merging for that field.
    -We can do the queries offline.
    -For every dsu set, make a std::set that holds the indexes of all the querys which have one of the fields from the query in that set.
    -When we merge 2 dsu sets, we need to check if they both contain some query index and if so, we can tell what is the best solution to that query (The value of the last matrix field we considered) and erase the indexes from the sets.
    -If we make sure to merge the sets by always inserting all the elements from the smaller set to the bigger set, we can get a complexity of O(n log^2 n), (any element will get inserted at most log n times and every insert takes log n operations)
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

const int N=300*300+1;
vector<int> par(N),ans(N);
vector<set<int> > qu(N);
void init()
{
    for(int i=0;i<N;i++)
        par[i]=i;
}
int find(int a)
{
    if(par[a]==a)
        return a;
    return par[a]=find(par[a]);
}
int curans;
void merge(int a,int b)
{
    a=find(a);
    b=find(b);
    if(a==b)
        return;
    if(qu[a].size()>qu[b].size())
        swap(a,b);
    par[a]=b;
    for(auto p:qu[a])
    {
        if(qu[b].count(p))
        {
            ans[p]=curans;
            qu[b].erase(p);
            continue;
        }
        qu[b].insert(p);
    }
}
int n;
int convert(int a,int b)
{
    return a*n+b;
}
bool inside(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<n;
}
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
int main()
{
    init();
    FILE *in=fopen("matrice2.in","r"),*out=fopen("matrice2.out","w");
	int q;
	fscanf(in,"%i %i",&n,&q);
	vector<int> vals;
	vector<pair<int,pair<int,int> > > mat;
	vector<int> order;
	for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            int m;
            fscanf(in,"%i",&m);
            mat.pb({m,{i,j}});
            vals.pb(m);
            order.pb(m);
        }
    for(int i=0;i<q;i++)
    {
        int x1,y1,x2,y2;
        fscanf(in,"%i %i %i %i",&x1,&y1,&x2,&y2);
        x1--;y1--;x2--;y2--;
        int a=convert(x1,y1),b=convert(x2,y2);
        qu[a].insert(i);
        qu[b].insert(i);
    }
    sort(all(vals));
    sort(all(mat));
    vals.erase(unique(all(vals)),vals.end());
    reverse(all(vals));
    reverse(all(mat));
    int m=vals.size();
    int tr=0;
    for(int i=0;i<m;i++)
    {
        curans=vals[i];
        while(tr<(int)mat.size()&&mat[tr].f==vals[i])
        {
            int x=mat[tr].s.f,y=mat[tr].s.s;
            for(int k=0;k<4;k++)
            {
                int xx=x+dx[k],yy=y+dy[k];
                if(inside(xx,yy)&&order[convert(xx,yy)]>=mat[tr].f)
                    merge(convert(xx,yy),convert(x,y));
            }
            tr++;
        }
    }
    for(int i=0;i<q;i++)
        fprintf(out,"%i\n",ans[i]);
    return 0;
}
