/*
    -It's impossible if the sum of a subarray [Al,...,Ar] > (r-l+1+d)*k
    -Subtract k from each element and we get sum of subarray [Al,...,Ar] > d*k
    -So we need to get the maximum subarray sum after every update. This can be done with a segment tree.
    -This comment on codeforces explains it well: https://codeforces.com/blog/entry/56416?#comment-401219.
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

const int N=2e5+5;
int n,m,k,d;
vector<ll> sum(4*N),pre(4*N),suf(4*N),sol(4*N);
void update(int i){
    sum[i]=sum[2*i]+sum[2*i+1];
    pre[i]=max(pre[2*i],sum[2*i]+pre[2*i+1]);
    suf[i]=max(suf[2*i+1],sum[2*i+1]+suf[2*i]);
    sol[i]=max({sol[2*i],sol[2*i+1],suf[2*i]+pre[2*i+1]});
}
void add(int pos,int x,int l=0,int r=N-1,int i=1){
    if(l==r){
        sum[i]+=x;
        pre[i]+=x;
        suf[i]+=x;
        sol[i]+=x;
        return;
    }
    int m=(l+r)>>1;
    if(pos<=m)
        add(pos,x,l,m,2*i);
    else
        add(pos,x,m+1,r,2*i+1);
    update(i);
}
void init(int l=0,int r=N-1,int i=1){
    if(l==r){
        sum[i]=pre[i]=suf[i]=sol[i]=-k;
        return;
    }
    int m=(l+r)>>1;
    init(l,m,2*i);
    init(m+1,r,2*i+1);
    update(i);
}
int main()
{
    scanf("%i %i %i %i",&n,&m,&k,&d);
    init();
    ll treba=(ll)d*k+1;
    for(int i=0;i<m;i++){
        int r,x;
        scanf("%i %i",&r,&x);
        add(r,x);
        if(max({pre[1],suf[1],sol[1]})>=treba)
            printf("NIE\n");
        else
            printf("TAK\n");
    }
    return 0;
}
