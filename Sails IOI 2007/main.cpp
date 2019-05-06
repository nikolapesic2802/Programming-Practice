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
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T>>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
int n;
const int N=200;
vector<vector<int> > jar(N);
ll sol=LLONG_MAX;
bool test(int m)
{
    priority_queue<int,vector<int>,greater<int> > veci;
    priority_queue<int> manji;
    ll trsol=0;
    int offset=0;
    for(int j=N-1;j>0;j--)
    {
        for(auto p:jar[j])
            manji.push(p);
        while(veci.size()&&veci.top()-offset==0)
            veci.pop();
        while(veci.size()<m&&manji.size())
        {
            veci.push(manji.top()+offset);
            manji.pop();
        }
        while(manji.size()&&veci.size()&&manji.top()>veci.top()-offset)
        {
            int a=manji.top();
            int b=veci.top()-offset;
            manji.pop();
            veci.pop();
            manji.push(b);
            veci.push(a+offset);
        }
        trsol+=(ll)veci.size()*((ll)veci.size()-1)/2;
        offset++;
    }
    printf("%i: %lld\n",m,trsol);
    while(veci.size()&&veci.top()-offset==0)
        veci.pop();
    bool ret=veci.size()==0&&manji.size()==0;
    if(ret){
        sol=min(sol,trsol);
    }
    return ret;
}
int main()
{
    freopen("sails.in.4a","r",stdin);
	scanf("%i",&n);
	jar.resize(n);
	for(int i=0;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        jar[a].pb(b);
    }
    for(int i=1;i<N;i++)
        test(i);
    /*int l=0,r=N;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(test(m))
            r=m;
        else
            l=m+1;
    }
    test(l);*/
    printf("%lld\n",sol);
    return 0;
}
