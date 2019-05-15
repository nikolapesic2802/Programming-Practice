/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/contest6_solutions/solutions.pdf
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
const int N=1e5+5;
vector<ll> dp(N,-1);
vector<int> a,b;
int n;
ll calc(int pos)
{
    if(pos==n)
        return 0;
    if(dp[pos]!=-1)
        return dp[pos];
    dp[pos]=LLONG_MAX/2;
    for(int k=0;k<=min(2,n-pos-1);k++)
    {
        vector<int> tra(k+1),trb(k+1);
        for(int l=0;l<=k;l++)
            tra[l]=a[pos+l],trb[l]=b[pos+l];
        do{
            ll sum=0;
            bool uspeo=true;
            for(int l=0;l<=k;l++)
                if(tra[l]==trb[l])
                {
                    uspeo=false;
                    break;
                }
                else
                    sum+=abs(tra[l]-trb[l]);
            if(!uspeo)
                continue;
            dp[pos]=min(dp[pos],sum+calc(pos+k+1));
        }while(next_permutation(all(trb)));
    }
    return dp[pos];
}
int main()
{
	scanf("%i",&n);
	a.resize(n);b.resize(n);
	for(int i=0;i<n;i++)
        scanf("%i %i",&a[i],&b[i]);
    sort(all(a));
    sort(all(b));
    printf("%lld\n",calc(0));
    return 0;
}
