/*
    -Do DP SOS.
    -The | and first & (1. and 2.) are pretty straight forward.
    -For the second & we will calculate the number of elements such that x&y=0 and the answer is n-that.
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

const int N=2e5+5,L=20,M=1<<L;
int n;
vector<int> niz,ans1(N),ans2(N),ans3(N);
void solveOr()
{
    vector<int> cnt(M),nxt(M);
    for(auto p:niz)
        cnt[p]++;
    for(int i=0;i<20;i++)
    {
        for(int x=0;x<M;x++)
            if(x&(1<<i))
                nxt[x]=cnt[x]+cnt[x-(1<<i)];
            else
                nxt[x]=cnt[x];
        cnt=nxt;
    }
    for(int i=0;i<n;i++)
        ans1[i]=cnt[niz[i]];
}
void solveAnd1()
{
    vector<int> cnt(M),nxt(M);
    for(auto p:niz)
        cnt[p]++;
    for(int i=0;i<20;i++)
    {
        for(int x=0;x<M;x++)
            if(x&(1<<i))
                nxt[x]=cnt[x];
            else
                nxt[x]=cnt[x]+cnt[x+(1<<i)];
        cnt=nxt;
    }
    for(int i=0;i<n;i++)
        ans2[i]=cnt[niz[i]];
}
void solveAnd2()
{
    vector<int> cnt(M),nxt(M);
    for(auto p:niz)
        cnt[p]++;
    for(int i=0;i<20;i++)
    {
        for(int x=0;x<M;x++)
            if(x&(1<<i))
                nxt[x]=cnt[x-(1<<i)];
            else
                nxt[x]=cnt[x]+cnt[x+(1<<i)];
        cnt=nxt;
    }
    for(int i=0;i<n;i++)
        ans3[i]=n-cnt[niz[i]];
}
int main()
{
    scanf("%i",&n);
    niz.resize(n);
    for(int i=0;i<n;i++)
        scanf("%i",&niz[i]);
    solveOr();
    solveAnd1();
    solveAnd2();
    for(int i=0;i<n;i++)
        printf("%i %i %i\n",ans1[i],ans2[i],ans3[i]);
    return 0;
}
