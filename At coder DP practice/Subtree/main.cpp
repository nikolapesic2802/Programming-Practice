/*
    -This implementation is probably overly complicated, go look at some1 elses code! :)
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
int mod;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int mul(int a,int b)
{
    return ((ll)a*b)%mod;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
const int N=1e5+5;
vector<vector<int> > graf(N);
map<int,int> mapa[N];
map<int,int> visited[N];
int cnt=0;
struct segTree{
    int sz;
    vector<int> m;
    set<int> podesen;
    void init(int n)
    {
        sz=n;
        m.resize(4*n,-1);
        for(int i=0;i<n;i++)
            podesen.insert(i);
    }
    void sett(int pos,int x,int l,int r,int i)
    {
        if(l>pos||r<pos)
            return;
        if(l==r&&l==pos){
            m[i]=x;
            return;
        }
        int mi=(l+r)>>1;
        sett(pos,x,l,mi,2*i);
        sett(pos,x,mi+1,r,2*i+1);
        m[i]=mul(m[2*i],m[2*i+1]);
    }
    void set1(int pos,int x)
    {
        podesen.erase(pos);
        sett(pos,x,0,sz-1,1);
    }
    int nije()
    {
        if(podesen.size()==sz)
            return -2;
        if(podesen.size()==0)
            return -1;
        assert(podesen.size()==1);
        return *podesen.begin();
    }
    int gett(int qs,int qe,int l,int r,int i)
    {
        if(qs>r||qe<l)
            return 1;
        if(qs<=l&&qe>=r)
        {
            return m[i];
        }
        int m=(l+r)>>1;
        return mul(gett(qs,qe,l,m,2*i),gett(qs,qe,m+1,r,2*i+1));
    }
    int get(int l,int r)
    {
        return gett(l,r,0,sz-1,1);
    }
};
vector<segTree> st(N);
vector<map<int,int> > mmm(N);
int dfs(int tr,int par)
{
    if(mapa[tr][par]!=0)
        return mapa[tr][par];
    int t=st[tr].nije();
    if(t==-2)
    {
        for(int i=0;i<graf[tr].size();i++)
        {
            int p=graf[tr][i];
            if(p==par)
                continue;
            st[tr].set1(i,dfs(p,tr));
        }
    }
    if(t>=0)
    {
        st[tr].set1(t,dfs(graf[tr][t],tr));
    }
    int ans=1;
    int pos=mmm[tr][par];
    if(pos>0)
        ans=mul(ans,st[tr].get(0,pos-1));
    if(pos<(int)graf[tr].size()-1)
        ans=mul(ans,st[tr].get(pos+1,graf[tr].size()-1));
    ans=add(ans,1);
    return mapa[tr][par]=ans;
}
int main()
{
    int n;
    scanf("%i %i",&n,&mod);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    for(int i=0;i<n;i++)
    {
        mmm[i][-1]=-1;
        for(int j=0;j<graf[i].size();j++)
        {
            mmm[i][graf[i][j]]=j;
        }
        st[i].init(graf[i].size());
    }
    for(int i=0;i<n;i++)
    {
        printf("%i\n",sub(dfs(i,-1),1));
    }
    return 0;
}
