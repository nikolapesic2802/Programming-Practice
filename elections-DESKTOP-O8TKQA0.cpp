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
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=5e5+5;
struct segTree{
    vector<int> mx,a;
    segTree(){
        mx.resize(4*N);
    }
    void init(int l=0,int r=N-1,int i=1){
        if(l==r){
            mx[i]=a[l];
            return;
        }
        int m=(l+r)>>1;
        init(l,m,2*i);
        init(m+1,r,2*i+1);
        mx[i]=max(mx[2*i],mx[2*i+1]);
    }
    int get(int qs,int qe,int l=0,int r=N-1,int i=1){
        if(qs>r||qe<l)
            return INT_MIN;
        if(qs<=l&&qe>=r)
            return mx[i];
        int m=(l+r)>>1;
        return max(get(qs,qe,l,m,2*i),get(qs,qe,m+1,r,2*i+1));
    }
} pre,suf;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,q;
	string s;
	cin >> n >> s >> q;
	vector<int> prearr(N),sufarr(N);
	for(int i=0;i<n;i++)
        prearr[i]=sufarr[i]=s[i]=='C'?1:-1;
    for(int i=1;i<n;i++)
        prearr[i]+=prearr[i-1];
    for(int i=n-2;i>=0;i--)
        sufarr[i]+=sufarr[i+1];
    for(int i=0)
    pre.a=prearr;
    suf.a=sufarr;
    pre.init();
    suf.init();
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--;r--;
        int a=pre.get(l,r),b=suf.get(l,r);
        if(l)
            a-=pre.get(l-1,l-1);
        if(r!=n-1)
            b-=suf.get(r+1,r+1);
        printf("%i\n",max(a,b));
    }
    return 0;
}
