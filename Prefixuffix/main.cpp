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
int pwrmod(int x,int k){
    int ans=1;
    for(;k;k>>=1,x=mul(x,x))
        if(k&1)
            ans=mul(ans,x);
    return ans;
}
string s;
vector<int> h(N),pwr(N,1);
int n;
int get(int l,int r){
    if(l>r)
        return 0;
    int ans=h[r];
    if(l)
        ans=sub(ans,mul(h[l-1],pwr[r-l+1]));
    return ans;
}
int meld(int l,int r,int l1,int r1){
    return add(mul(get(l,r),pwr[r1-l1+1]),get(l1,r1));
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
    vector<int> ha(n);
    int best=0;
    for(int i=0;i<n/2;i++){
        int l=0,r=i+1;
        while(l<r){
            int m=(l+r)>>1;
            int ri
        }
    }
    return 0;
}
