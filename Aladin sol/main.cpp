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
struct node{
    ll sum;
    int a,b,start;
    int le,ri;
};
vector<node> drvo;
int newNode()
{
    node a;
    a.sum=0;
    a.a=a.le=-1;
    drvo.pb(a);
    return drvo.size()-1;
}
void extend(int i)
{
    if(drvo[i].le!=-1)
        return;
    int a=newNode();
    drvo[i].le=a;
    int b=newNode();
    drvo[i].ri=b;
}
int n;
void sett(int qs,int qe,int a,int b,int l=0,int r=n,int i=0)
{
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        drvo[i].a=a;
        drvo[i].b=b;
        drvo[i].start=l-qs;
        drvo[i].sum=get(a,b,drvo[i].start,drvo[i].start+r-l);
        return;
    }
    extend(i);
    int m=(l+r)>>1;
    if(drvo[i].a!=-1)
    {
        drvo[drvo[i].le].a=drvo[i].a;
        drvo[drvo[i].ri].a=drvo[i].a;
        drvo[drvo[i].le].b=drvo[i].b;
        drvo[drvo[i].ri].b=drvo[i].b;
        drvo[drvo[i].le].start=drvo[i].start;
        drvo[drvo[i].ri].start=drvo[i].start+m-l+1;
        drvo[drvo[i].le].sum=get(drvo[drvo[i].le].a,drvo[drvo[i].le].b,drvo[drvo[i].le].start,drvo[drvo[i].le].start+m-l);
        drvo[drvo[i].ri].sum=get(drvo[drvo[i].ri].a,drvo[drvo[i].ri].b,drvo[drvo[i].ri].start,drvo[drvo[i].ri].start+r-m-1);
        drvo[i].a=-1;
    }
    sett(qs,qe,a,b,l,m,drvo[i].le);
    sett(qs,qe,a,b,m+1,r,drvo[i].ri);
    drvo[i].sum=drvo[drvo[i].le].sum+drvo[drvo[i].ri].sum;
}
ll getsum(int qs,int qe,int l=0,int r=n,int i=0)
{
    if(qs>r||qe<l)
        return 0;
    if(qs<=l&&qe>=r)
        return drvo[i].sum;
    extend(i);
    int m=(l+r)>>1;
    if(drvo[i].a!=-1)
    {
        drvo[drvo[i].le].a=drvo[i].a;
        drvo[drvo[i].ri].a=drvo[i].a;
        drvo[drvo[i].le].b=drvo[i].b;
        drvo[drvo[i].ri].b=drvo[i].b;
        drvo[drvo[i].le].start=drvo[i].start;
        drvo[drvo[i].ri].start=drvo[i].start+m-l+1;
        drvo[drvo[i].le].sum=get(drvo[drvo[i].le].a,drvo[drvo[i].le].b,drvo[drvo[i].le].start,drvo[drvo[i].le].start+m-l);
        drvo[drvo[i].ri].sum=get(drvo[drvo[i].ri].a,drvo[drvo[i].ri].b,drvo[drvo[i].ri].start,drvo[drvo[i].ri].start+r-m-1);
        drvo[i].a=-1;
    }
    return getsum(qs,qe,l,m,drvo[i].le)+getsum(qs,qe,m+1,r,drvo[i].ri);
}
int main()
{
    FILE *f=fopen("in.txt","r");
    newNode();
    int q;
    fscanf(f,"%i %i",&n,&q);
    for(int i=0;i<q;i++)
    {
        int t;
        fscanf(f,"%i",&t);
        int l,r;
        fscanf(f,"%i %i",&l,&r);
        l--;r--;
        if(t==1)
        {
            int a,b;
            fscanf(f,"%i %i",&a,&b);
            sett(l,r,a,b);
        }
        else
        {
            getsum(l,r);
            //printf("%lld\n",getsum(l,r));
        }
    }
    return 0;
}
