/*
    -Really similar to https://codeforces.com/problemset/problem/449/D.
    -For each number from 1 to 2^m calculate the number of numbers in the input such that m|Ai=m, this can be done with SOS dp.
    -After that use inclusion exclusion to calculate the number of subsets.
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
const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int sub(int a,int b)
{
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
vector<int> pwr;
int main()
{
    pwr.pb(1);
    for(int i=1;i<(int)1e5+1;i++)
        pwr.pb(add(pwr.back(),pwr.back()));
    for(auto &p:pwr)
        p=sub(p,1);
	int n,m;
	scanf("%i %i",&n,&m);
	int M=1<<m;
	vector<int> cnt(M);
    for(int i=0;i<n;i++)
    {
        char c[m];
        scanf("%s",c);
        int num=0;
        for(int j=0;j<m;j++)
            num=num*2+(c[j]=='1');
        cnt[num]++;
    }
    char c[m];
    scanf("%s",c);
    int num=0;
    for(int j=0;j<m;j++)
        num=num*2+(c[j]=='1');
    for(int j=0;j<m;j++)
        for(int i=0;i<M;i++)
            if(i&(1<<j))
                cnt[i]+=cnt[i^(1<<j)];
    int ans=0;
    for(int j=num;j;j=(j-1)&num)
        if(__builtin_popcount(num^j)&1)
            ans=sub(ans,pwr[cnt[j]]);
        else
            ans=add(ans,pwr[cnt[j]]);
    if(__builtin_popcount(num)&1)
        ans=sub(ans,pwr[cnt[0]]);
    else
        ans=add(ans,pwr[cnt[0]]);
    printf("%i\n",ans);
    return 0;
}
