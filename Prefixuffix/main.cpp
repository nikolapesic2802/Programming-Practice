/*
    -The solution is uvTvu where u,v,T are some strings.
    -Use hashing to check if two substrings are equal with constant time and O(n) preprocessing.
    -If we can find the longest length of v for every size of u, that is enough to solve the task. (we can just go through every length of u, and if the prefix is the same as the suffix of that length, we can make a solution of size len(u) + maxLen(v)).
    -Write a[0] as the maximum length of v when we take 0 as the length of u, a[1], the maximum when we take 1 as the length of u, ans so on.
    -It holds that a[i-1]<=a[i]+2. (It's pretty simple to understand why when you draw a picture, editorial has a nice picture to make it clear).
    -Now start by calculating a[n/2]. Now we know that a[n/2-1] is smaller than or equal to a[n/2]+2, so we can start from that value, and go down until we find a value that works.
    -Do this for every a[i] in decreasing order. Notice that we will do O(n) steps in total over all a[i]. So our algorithm is O(n).
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

const int N=1e6+1,mod=1e9+7,pu=26;
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
string s;
vector<int> h(N),pwr(N,1);
int n;
int get(int l,int r){
    int ans=h[r];
    if(l)
        ans=sub(ans,mul(h[l-1],pwr[r-l+1]));
    return ans;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cin >> n >> s;
	for(int i=1;i<n;i++)
        pwr[i]=mul(pwr[i-1],pu);
	h[0]=s[0]-'a';
	for(int i=1;i<n;i++)
        h[i]=add(mul(h[i-1],pu),s[i]-'a');
    int ans=0,j=0;
    for(int i=(n/2)-1;i>=0;i--){
        while((~j&&get(i+1,i+1+j)!=get(n-2-i-j,n-2-i))||j>=(n-2-2*i)/2)
            j--;
        if(get(0,i)==get(n-1-i,n-1))
            ans=max(ans,i+j+2);
        j+=2;
    }
    printf("%i\n",ans);
    return 0;
}
