/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2010/contest1_solutions/solutions.pdf
    -This plus my implementation of a segment tree with coordinate compression (an implicit segment tree gets 90/100 points because of memory :( )
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
#define ld long double

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

///Part to calculate the sum of the sequence (taken from the official solution)
ll gcd(ll a,ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
ll calc(ll a,ll b,ll n)
{
    ll x=a/b;
    ll sum=x*n*(n+1)/2;
    a%=b;
    if(a==0||b==0)
        return sum;
    ll diag=n/b;
    ll zadnji=a*n/b;
    return sum+n*zadnji-calc(b,a,zadnji)+diag;
}
ll solve(ll a,ll b,ll n)
{
    if(n>b)
    {
        ll k=n/b;
        ll ost=n%b;
        return solve(a,b,b)*k+solve(a,b,ost);
    }
    if(n<1)
        return 0;
    ll g=gcd(a,b);
    return (ll)((ld)n*(ld)(n+1)/(ld)2*(ld)a-(ld)b*(ld)calc(a/g,b/g,n));
}
ll get(ll a,ll b,int l,int r)
{
    return solve(a,b,r+1)-solve(a,b,l);
}

///Segment tree
vector<int> val;
int N;
int value(int i)
{
    if(i<0)
        return val[0]-1;
    return val[i];
}
struct segTree{
    vector<ll> sum;
    vector<int> a,b,start;
    void init()
    {
        sum.resize(4*N);
        a.resize(4*N,-1);
        b.resize(4*N);
        start.resize(4*N);
    }
    void sett(int qs,int qe,int a1,int b1,int l=0,int r=N,int i=1)
    {
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            a[i]=a1;
            b[i]=b1;
            start[i]=value(l-1)+1-val[qs];
            sum[i]=get(a1,b1,start[i],start[i]+val[r]-value(l-1)-1);
            return;
        }
        int m=(l+r)>>1;
        if(a[i]!=-1)
        {
            a[2*i]=a[i];
            a[2*i+1]=a[i];
            b[2*i]=b[i];
            b[2*i+1]=b[i];
            start[2*i]=start[i];
            start[2*i+1]=start[i]+val[m]-value(l-1);
            sum[2*i]=get(a[i],b[i],start[i],start[i]+val[m]-value(l-1)-1);
            sum[2*i+1]=get(a[i],b[i],start[2*i+1],start[2*i+1]+val[r]-value(m)-1);
            a[i]=-1;
        }
        sett(qs,qe,a1,b1,l,m,2*i);
        sett(qs,qe,a1,b1,m+1,r,2*i+1);
        sum[i]=sum[2*i]+sum[2*i+1];
    }
    ll getsum(int qs,int qe,int l=0,int r=N,int i=1)
    {
        if(qs>r||qe<l)
            return 0;
        if(qs<=l&&qe>=r)
            return sum[i];
        int m=(l+r)>>1;
        if(a[i]!=-1)
        {
            a[2*i]=a[i];
            a[2*i+1]=a[i];
            b[2*i]=b[i];
            b[2*i+1]=b[i];
            start[2*i]=start[i];
            start[2*i+1]=start[i]+val[m]-value(l-1);
            sum[2*i]=get(a[i],b[i],start[i],start[i]+val[m]-value(l-1)-1);
            sum[2*i+1]=get(a[i],b[i],start[2*i+1],start[2*i+1]+val[r]-value(m)-1);
            a[i]=-1;
        }
        return getsum(qs,qe,l,m,2*i)+getsum(qs,qe,m+1,r,2*i+1);
    }
}st;
int main()
{
    int n,q;
    scanf("%i %i",&n,&q);
    queue<int> input;
    for(int i=0;i<q;i++)
    {
        int t;
        scanf("%i",&t);
        input.push(t);
        int l,r;
        scanf("%i %i",&l,&r);
        l--;r--;
        input.push(l);
        input.push(r);
        val.pb(l);
        val.pb(l-1);
        val.pb(r-1);
        val.pb(r);
        if(t==1)
        {
            int a,b;
            scanf("%i %i",&a,&b);
            input.push(a);
            input.push(b);
        }
    }
    sort(all(val));
    val.erase(unique(val.begin(),val.end()),val.end());
    N=val.size();
    st.init();
    map<int,int> mapa;
    for(int i=0;i<val.size();i++)
        mapa[val[i]]=i;
    for(int i=0;i<q;i++)
    {
        int t=input.front();
        input.pop();
        int l,r;
        l=input.front();
        input.pop();
        r=input.front();
        input.pop();
        l=mapa[l];
        r=mapa[r];
        if(t==1)
        {
            int a,b;
            a=input.front();
            input.pop();
            b=input.front();
            input.pop();
            st.sett(l,r,a,b);
        }
        else
            printf("%lld\n",st.getsum(l,r));
    }
    return 0;
}
