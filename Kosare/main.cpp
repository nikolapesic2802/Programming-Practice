/*
    -Use dp SOS to calculate for each number x from range [0,2^m) how many numbers from the input ai satisfy ai|x=x.
    -Then use inclusion exclusion to calculate the answer.
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

const int mod=1e9+7,N=1e6+1;
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
vector<int> pwr(1,1);
int main()
{
    for(int i=0;i<N;i++)
        pwr.pb(add(pwr.back(),pwr.back()));
	int n,m;
	scanf("%i %i",&n,&m);
	int M=1<<m;
	vector<int> cnt(M);
	for(int i=0;i<n;i++)
    {
        int k,val=0,a;
        scanf("%i",&k);
        for(int i=0;i<k;i++)
            scanf("%i",&a),val+=1<<(a-1);
        cnt[val]++;
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<M;j++)
            if(j&(1<<i))
                cnt[j]+=cnt[j^(1<<i)];
    int sol=0,a=__builtin_popcount(M-1)&1;
    for(int i=0;i<M;i++)
        if((__builtin_popcount(i)&1)==a)
            sol=add(sol,pwr[cnt[i]]);
        else
            sol=sub(sol,pwr[cnt[i]]);
    printf("%i\n",sol);
    return 0;
}
