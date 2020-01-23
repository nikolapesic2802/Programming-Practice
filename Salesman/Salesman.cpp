/*
    -First solve the case where no two fairs happen on the same day.
    -We will do the following dp: dp[i] is the maximum profit we can make and end up on field i.
    -We can maintain this dp with two segment trees, one for going upstream and one for going downstream.
    -In the upstream segment tree we will keep dp[i]-i*s and in the downstream we will keep dp[i]+i*d.
    -Now when we want to calculate the maximum profit we can make and get to field j, we will query the maximum element in the upstream segment tree in range (j,N) + j*s, with this
        we will get dp[m]-m*s+j*s = dp[m]-(m-j)*s  where m is the best previous location. This is exactly what we need, now just need add the Mj to the value.
    -For downstream we will query in (1,N) - j*s, and again we will get what we need when we add Mj to the value.
    -This is enough for 60 points.

    -To extend this to a 100 point solution, we need to notice that when multiple fairs are going on during a single day, first sort them by their location.
    -Now notice that it's always optimal to start at some fair, and visit an interval to the left or to the right of this fair, ending at the other end of the interval.
    -To calculate this we can do something similar to kadane's algorithm, go through the fairs in increasing order of location, and do dp2[i]=max(dp[i],dp2[i-1]- the cost to get from the location of
        fair i-1 to fair i + Mi). Where dp[i] is the maximum profit we can get and and up at the location of fair i while only visiting fairs that happened on days before the day it's happening.
        A really similar thing can be done in decreasing order of location, and we take the maximum of these to as the answer.
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
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=5e5+5;
struct fair{
    int t,l,m;
};
bool operator<(fair a,fair b){
    if(a.t!=b.t)
        return a.t<b.t;
    if(a.l!=b.l)
        return a.l<b.l;
    return a.m<b.m;
}
vector<fair> f;
vector<int> r(N);
int n,u,d,s;
int getDist(int a,int b){
    if(a<b)
        return b*d-a*d;
    return a*u-b*u;
}
struct segTree{
    vector<int> mx;
    segTree(){mx.resize(4*N,INT_MIN/2);}
    void sett(int pos,int x,int l=0,int r=N-1,int i=1){
        if(l==r){
            assert(l==pos);
            mx[i]=x;
            return;
        }
        int m=(l+r)>>1;
        if(pos<=m)
            sett(pos,x,l,m,2*i);
        else
            sett(pos,x,m+1,r,2*i+1);
        mx[i]=max(mx[2*i],mx[2*i+1]);
    }
    int get(int qs,int qe,int l=0,int r=N-1,int i=1){

        if(qs>r||qe<l)
            return INT_MIN/2;
        if(qs<=l&&qe>=r)
            return mx[i];
        int m=(l+r)>>1;
        int sol= max(get(qs,qe,l,m,2*i),get(qs,qe,m+1,r,2*i+1));
        return sol;
    }
}up,down;
int main()
{
	scanf("%i %i %i %i",&n,&u,&d,&s);
	f.resize(n+1);
	for(int i=1;i<=n;i++)
        scanf("%i %i %i",&f[i].t,&f[i].l,&f[i].m);
    sort(all(f));
    f.pb({0,0,0});
    for(int i=n;i>=0;i--)
        if(f[i].t==f[i+1].t)
            r[i]=r[i+1];
        else
            r[i]=i;
    down.sett(s,d*s);
    up.sett(s,-u*s);
    for(int i=1;i<=n;i++){
        vector<int> dp(r[i]-i+1),dp2(r[i]-i+1),dp3(r[i]-i+1);
        for(int j=i;j<=r[i];j++)
            dp[j-i]=max(down.get(1,f[j].l)-f[j].l*d,up.get(f[j].l,N-1)+f[j].l*u)+f[j].m;
        for(int j=i;j<=r[i];j++){
            dp2[j-i]=dp[j-i];
            if(j!=i)
                dp2[j-i]=max(dp2[j-i],dp2[j-i-1]-getDist(f[j-1].l,f[j].l)+f[j].m);
        }
        for(int j=r[i];j>=i;j--){
            dp3[j-i]=dp[j-i];
            if(j!=r[i])
                dp3[j-i]=max(dp3[j-i],dp3[j-i+1]-getDist(f[j+1].l,f[j].l)+f[j].m);
            dp[j-i]=max(dp2[j-i],dp3[j-i]);
        }
        for(int j=i;j<=r[i];j++)
            down.sett(f[j].l,dp[j-i]+d*f[j].l),up.sett(f[j].l,dp[j-i]-u*f[j].l);
        i=r[i];
    }
    int sol=max(down.get(1,s)-s*d,up.get(s,N-1)+s*u);
    sol=max(sol,0);
    printf("%i\n",sol);
    return 0;
}
