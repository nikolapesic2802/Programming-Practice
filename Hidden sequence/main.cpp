/// -https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/Info1Cup/18-Hidden.cpp
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

bool isSubsequence(vector<int> v);
bool q(int a,int b,int c)
{
    vector<int> v(a,c);
    while(b--)
        v.pb(c^1);
    return isSubsequence(v);
}
vector<int> findSequence(int n)
{
    int c=0;
    for(int i=1;i<=n/2+1;i++)
        if(q(i,0,0))
            c=i;
    for(int i=n/2+1;i>0;i--)
        if(!q(i,0,1))
            c=n-i+1;
    vector<int> ans;
    for(int i=0,j=0;i<c;i++)
    {
        for(;j<n-c;j++)
        {
            if(j+c-i<=n/2)
            {
                if(!q(j+1,c-i,1))
                    break;
            }
            else
                if(q(i+1,n-c-j,0))
                    break;
            ans.pb(1);
        }
        ans.pb(0);
    }
    while(ans.size()<n)
        ans.pb(1);
    return ans;
}
