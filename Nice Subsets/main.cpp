/*
    -https://discuss.codechef.com/t/subsets-editorial/28722
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

int main()
{
	int t;
	scanf("%i",&t);
	while(t--)
    {
        int n;
        scanf("%i",&n);
        vector<int> a(n);
        vector<map<int,int> > factors(n);
        for(int i=0;i<n;i++)
        {
            scanf("%i",&a[i]);
            for(int j=2;j<=sqrt(a[i]);j++)
                while(a[i]%j==0)
                    factors[i][j]++,a[i]/=j;
            factors[i][a[i]]++;
        }
        vector<ll> masks(n);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                bool moze=1;
                for(auto p:factors[i])
                    if(p.s+factors[j][p.f]>=3)
                        moze=0;
                for(auto p:factors[j])
                    if(p.s+factors[i][p.f]>=3)
                        moze=0;
                if(moze||i==j)
                    masks[i]^=1LL<<j;
            }
        int m=n/2,M=1<<m,m2=n-m,M2=1<<m2;
        vector<int> cnt(M,1);
        for(int i=0;i<M;i++)
            for(int j=0;j<m;j++)
                if(i&(1<<j))
                    if((masks[j]&i)!=i)
                        cnt[i]=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<M;j++)
                if(j&(1<<i))
                    cnt[j]+=cnt[j^(1<<i)];
        ll sol=0;
        for(ll i=0;i<M2;i++)
        {
            bool moze=1;
            for(int j=0;j<m2;j++)
                if(i&(1<<j))
                    if(((masks[j+m]>>m)&i)!=i)
                        moze=0;
            if(!moze)
                continue;
            int msk=0;
            for(int j=0;j<m;j++)
                if((masks[j]&(i<<m))==(i<<m))
                    msk^=1<<j;
            sol+=cnt[msk];
        }
        printf("%lld\n",sol);
    }
    return 0;
}
