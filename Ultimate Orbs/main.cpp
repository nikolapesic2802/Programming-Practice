/*
    -Do divide and conquer. Find the maximum element of the current interval, that index can for sure win in the current interval. Split the interval to the left of that index and to the right of that index.
    -If the sum of the element in the left/right interval + D is greater than the maximum, all the indexes that can win in that left/right interval can win in the current interval too.
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

int n,d,tr=1;
const int N=1e6+1;
vector<int> g(N);
vector<pair<int,int> > maxx(4*N);
vector<ll> sum(4*N);
vector<int> moze(4*N),lazymoze(4*N,-1);
void build(int l=0,int r=N-1,int i=1)
{
    if(l==r)
    {
        maxx[i]={g[l],l};
        sum[i]=g[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,2*i);
    build(m+1,r,2*i+1);
    maxx[i]=max(maxx[2*i],maxx[2*i+1]);
    sum[i]=sum[2*i]+sum[2*i+1];
}
ll get(int qs,int qe,int l=0,int r=N-1,int i=1)
{
    if(qs>qe)
        return LLONG_MIN/2;
    if(qs>r||qe<l)
    return 0;
    if(qs<=l&&qe>=r)
    return sum[i];
    int m=(l+r)>>1;
    return get(qs,qe,l,m,2*i)+get(qs,qe,m+1,r,2*i+1);
}
pair<int,int> getm(int qs,int qe,int l=0,int r=N-1,int i=1)
{
    if(qs>r||qe<l)
        return {0,0};
    if(qs<=l&&qe>=r)
        return maxx[i];
    int m=(l+r)>>1;
    return max(getm(qs,qe,l,m,2*i),getm(qs,qe,m+1,r,2*i+1));
}
void prop2(int i)
{
    if(lazymoze[i]==-1)
        return;
    moze[2*i]=lazymoze[i];
    moze[2*i+1]=lazymoze[i];
    lazymoze[2*i]=lazymoze[i];
    lazymoze[2*i+1]=lazymoze[i];
    lazymoze[i]=-1;
}
void postavi(int qs,int qe,int x,int l=0,int r=N-1,int i=1)
{
    if(qs>qe)
        return;
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        lazymoze[i]=x;
        moze[i]=x;
        return;
    }
    prop2(i);
    int m=(l+r)>>1;
    postavi(qs,qe,x,l,m,2*i);
    postavi(qs,qe,x,m+1,r,2*i+1);
}
void print(int l=0,int r=N-1,int i=1)
{
    if(l==r)
    {
        if(moze[i])
            printf("%i ",l+1);
        return;
    }
    prop2(i);
    int m=(l+r)>>1;
    print(l,m,2*i);
    print(m+1,r,2*i+1);
}
void solve(int l,int r)
{
    if(l>r)
        return;
    pair<int,int> m=getm(l,r);
    solve(l,m.s-1);
    solve(m.s+1,r);
    if(get(l,m.s-1)+d<m.f)
        postavi(l,m.s-1,0);
    if(get(m.s+1,r)+d<m.f)
        postavi(m.s+1,r,0);
    postavi(m.s,m.s,1);
}
int main()
{
	scanf("%i %i",&n,&d);
	for(int i=0;i<n;i++)
        scanf("%i",&g[i]);
    build();
    solve(0,n-1);
    print();
    return 0;
}
