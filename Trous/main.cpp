/*
    -I think n log n wasn't supposed to pass, but this one does, i needed to use my own deque instead of the built in one.
    -Binary search for the answer, for every interval of points that we can attack, we will have some choices on where to put the great plank, we choose the one with the maximum sum that it blocks.
    -If the total sum of the interval - the maximum sum is less than or equal to p, we can do it, and continue the binary search accordingly.
    -To get the maximum sum we can use the stack trick/convex hull optimization.

    -At the bottom i implemented the O(n) solution from the editorial.
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

const int N=2e6+1;
int n,d,le,ri;
ll p;
vector<int> w(N);
vector<ll> sums(N);
pair<ll,int> q[N];
bool test(int m){
    ll sum=0;
    for(int i=0;i<m;i++)
        sum+=w[i];
    le=ri=0;
    for(int i=0;i<=m-d;i++)
    {
        while(ri>le&&q[ri-1].f<=sums[i])
            ri--;
        q[ri++]={sums[i],i};
    }
    if(sum-q[le].f<=p)
        return 1;
    for(int i=m;i<n;i++){
        sum+=w[i]-w[i-m];
        while(ri>le&&q[ri-1].f<=sums[i-d+1])
            ri--;
        q[ri++]={sums[i-d+1],i-d+1};
        if(q[le].s==i-m)
            le++;
        if(sum-q[le].f<=p)
            return 1;
    }
    return 0;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> p >> d;
	for(int i=0;i<n;i++)
        cin >> w[i];
    ll sum=0;
    for(int i=0;i<d;i++)
        sum+=w[i];
    sums[0]=sum;
    for(int i=d;i<n;i++)
        sum+=w[i]-w[i-d],sums[i-d+1]=sum;
    int l=d,r=n;
    while(l<r){
        int m=(l+r+1)>>1;
        if(test(m))
            l=m;
        else
            r=m-1;
    }
    cout << l;
    return 0;
}


/* O(N) solution from editorial
const int N=2e6+1;
int n,d,le,ri;
ll p;
vector<int> w(N);
vector<ll> sums(N);
pair<ll,int> q[N];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> p >> d;
	for(int i=0;i<n;i++)
        cin >> w[i];
    ll sum=0;
    for(int i=0;i<d;i++)
        sum+=w[i];
    ll startsum=sum;
    sums[0]=sum;
    for(int i=d;i<n;i++)
        sum+=w[i]-w[i-d],sums[i-d+1]=sum;
    int l=0,r=d-1,ans=d;
    q[ri++]={sums[0],0};
    sum=startsum;
    while(r<n-1){
        while(r<n-1){
            r++;
            sum+=w[r];
            while(ri>le&&q[ri-1].f<=sums[r-d+1])
                ri--;
            q[ri++]={sums[r-d+1],r-d+1};
            if(sum-q[le].f>p)
                break;
        }
        if(sum-q[le].f<=p)
            ans=max(ans,r-l+1);
        else
            ans=max(ans,r-l);
        while(sum-q[le].f>p){
            sum-=w[l];
            if(q[le].s==l)
                le++;
            l++;
        }
    }
    cout << ans;
    return 0;
}*/
