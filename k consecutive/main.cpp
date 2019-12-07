/*
    -Answer for case k=1: http://oeis.org/A000255
    -When k is more than 1, we will partition the array into chunks of consecutive element of size no more than k and by doing so reduce the problem to the k=1 case.
    -Count the number of ways to partition the elements into exactly i groups and multiply that with the k=1 case for i numbers over all i from 1 to n.
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

const int N=5001,mod=1e9+7;
int add(int a,int b){
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int sub(int a,int b){
    a-=b;
    if(a<0)
        a+=mod;
    return a;
}
int mul(int a,int b){
    return (ll)a*b%mod;
}
int a[N],ways[2][N];
int main()
{
    a[0]=a[1]=1;
    for(int i=2;i<N;i++)
        a[i]=add(mul(i,a[i-1]),mul(i-1,a[i-2]));
    int n,k;
    scanf("%i %i",&n,&k);
    ways[0][0]=1;
    for(int j=1;j<=n;j++){
        ways[j&1][0]=0;
        for(int i=1;i<=n;i++){
            ways[j&1^1][i]=add(ways[j&1^1][i],ways[j&1^1][i-1]);
            ways[j&1][i]=ways[j&1^1][i-1];
            if(i>k)
                ways[j&1][i]=sub(ways[j&1][i],ways[j&1^1][i-k-1]);
        }
        a[j-1]=mul(a[j-1],ways[j&1][n]);
    }
    int ans=0;
    for(int j=1;j<=n;j++)
        ans=add(ans,a[j-1]);
    printf("%i\n",ans);
    return 0;
}

/* Code that gets 31ms
int main()
{
    a[0]=a[1]=1;
    for(int i=2;i<N;i++)
        a[i]=add(mul(i,a[i-1]),mul(i-1,a[i-2]));
    int n,k,ans=0;
    scanf("%i %i",&n,&k);
    ways[0][0]=1;
    for(int j=1;j<=n;j++){
        int l=-k,r=-1,sum=0;
        for(int i=0;i<=min(n-j,k*j);i++){
            sum=add(sum,ways[j&1^1][++r]);
            if(++l>0)
                sum=sub(sum,ways[j&1^1][l-1]);
            ways[j&1][i]=sum;
        }
        printf("%i: %i\n",j,ways[j&1][n-j]);
        ans=add(ans,mul(a[j-1],ways[j&1][n-j]));
    }
    printf("%i\n",ans);
    return 0;
}*/
