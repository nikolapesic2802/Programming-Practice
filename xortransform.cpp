/*
    -Figure out the pattern with brute force.
    -For each field in the matrix there will be a number i such that that number will be in the final xor for every k such that k&i==i.
    -That number can be found using the recursive formula in the calc function.
    -Now we can use DP SOS to find for each value of k that is less than 2^22, what the value the field [0][0] will be after k steps.
    -If we get a value of k greater than 2^22, just remove the most significant bit until it isn't greater than 2^22 or just take k=k&(2^22-1).
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
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int L=22,N=1<<L;
int x[N],cnt[N];
int calc(int i,int j){
    if(cnt[i]==-1&&cnt[j]==-1)
        return 0;
    if(cnt[i]==cnt[j])
        return calc(i-(1<<cnt[i]),j-(1<<cnt[j]))+(1<<cnt[i]);
    if(cnt[i]>cnt[j])
        return calc(i-(1<<cnt[i]),j)+(1<<cnt[i]);
    return calc(i,j-(1<<cnt[j]))+(1<<cnt[j]);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	freopen("xortransform.in","r",stdin);
	freopen("xortransform.out","w",stdout);
	int ans=-1,tr=1;
	for(int i=0;i<N;i++){
        if(i==tr)
            ans++,tr*=2;
        cnt[i]=ans;
    }
	int n,m,q,a;
	cin >> n >> m >> q;
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> a,x[calc(i,j)]^=a;
	for(int i=0;i<L;i++)
        for(int j=0;j<N;j++)
            if(j&(1<<i))
                x[j]^=x[j^(1<<i)];
    int lst=0;
    for(int i=0;i<q;i++){
        cin >> a;
        a^=lst;
        a&=(N-1);
        cout << x[a] << '\n';
        lst=x[a];
    }
    return 0;
}
