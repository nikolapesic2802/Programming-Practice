/*
    -The trick is to store the values for the interval from [0,i] for every i in a segment tree
    -Initially the values are 1,2,3,4(lengths of the segments) then we can multiply the corresponding segments in the tree by the minimum/maximum in that range.
    -To move from a tree storing [0,i] to [1,i] we can keep another sum array in the tree which starts at 1,1,1,1 which we update the same way as the first one and then subtract it some number of times to get the correct sum.
    -We can also notice that its enough to use __int128 which works on dunjudge but unfortunately not on codeforces.
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

const int N=524288,mod=1e9;
struct segTree{
    vector<__int128> sum,sumone;
    vector<ll> lazymul;
    void build(int l,int r,int i)
    {
        if(l==r)
        {
            sum[i]=l+1;
            sumone[i]=1;
            return;
        }
        int m=(l+r)>>1;
        build(l,m,2*i);
        build(m+1,r,2*i+1);
        sum[i]=sum[2*i]+sum[2*i+1];
        sumone[i]=sumone[2*i]+sumone[2*i+1];
    }
    void init()
    {
        sum.resize(2*N);
        sumone.resize(2*N);
        lazymul.resize(2*N,1);
        build(0,N-1,1);
    }
    void prop(int i)
    {
        sum[2*i]*=lazymul[i];
        sum[2*i+1]*=lazymul[i];
        sumone[2*i]*=lazymul[i];
        sumone[2*i+1]*=lazymul[i];
        lazymul[2*i]*=lazymul[i];
        lazymul[2*i+1]*=lazymul[i];
        lazymul[i]=1;
    }
    void update(int i)
    {
        sum[i]=sum[2*i]+sum[2*i+1];
        sumone[i]=sumone[2*i]+sumone[2*i+1];
    }
    void upd(bool ismul,int qs,int qe,int x,int l=0,int r=N-1,int i=1)
    {
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            if(ismul){
                lazymul[i]*=x;
                sum[i]*=x;
                sumone[i]*=x;
                return;
            }
            if(lazymul[i]%x==0)
            {
                lazymul[i]/=x;
                sum[i]/=x;
                sumone[i]/=x;
                return;
            }
        }
        prop(i);
        int m=(l+r)>>1;
        upd(ismul,qs,qe,x,l,m,2*i);
        upd(ismul,qs,qe,x,m+1,r,2*i+1);
        update(i);
    }
    pair<__int128,__int128> getsums(int qs,int qe,int l=0,int r=N-1,int i=1)
    {
        if(qs>r||qe<l)
            return {0,0};
        if(qs<=l&&qe>=r)
            return {sum[i],sumone[i]};
        prop(i);
        int m=(l+r)>>1;
        pair<__int128,__int128> a=getsums(qs,qe,l,m,2*i);
        pair<__int128,__int128> b=getsums(qs,qe,m+1,r,2*i+1);
        return {a.f+b.f,a.s+b.s};
    }
}st;
int main()
{
    st.init();
	int n;
	scanf("%i",&n);
	vector<int> arr(n);
	for(int i=0;i<n;i++)
        scanf("%i",&arr[i]);
    vector<pair<int,int> > setup;
    vector<int> smaller(n,n),bigger(n,n);
    for(int i=0;i<n;i++)
    {
        while(setup.size()&&setup.back().f>arr[i])
        {
            smaller[setup.back().s]=i;
            setup.pop_back();
        }
        setup.pb({arr[i],i});
    }
    setup.clear();
    for(int i=0;i<n;i++)
    {
        while(setup.size()&&setup.back().f<arr[i])
        {
            bigger[setup.back().s]=i;
            setup.pop_back();
        }
        setup.pb({arr[i],i});
    }
    vector<int> dones(n+1),doneb(n+1);
    dones[n]=doneb[n]=1;
    int sol=0;
    for(int i=0;i<n;i++)
    {
        int tr=i;
        while(true)
        {
            if(dones[tr])
                break;
            dones[tr]=1;
            st.upd(1,tr,smaller[tr]-1,arr[tr]);
            tr=smaller[tr];
        }
        tr=i;
        while(true)
        {
            if(doneb[tr])
                break;
            doneb[tr]=1;
            st.upd(1,tr,bigger[tr]-1,arr[tr]);
            tr=bigger[tr];
        }
        pair<__int128,__int128> a=st.getsums(i,n-1);
        sol=(a.f-a.s*i+sol)%mod;
        st.upd(0,i,smaller[i]-1,arr[i]);
        st.upd(0,i,bigger[i]-1,arr[i]);
    }
    printf("%i\n",sol);
    return 0;
}
