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

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

struct persistantSegTree{
    struct Node{
        int l,r,minn,maxx,lazy_mod,lazy_mul;
        ll sum;
    };
    vector<Node> segTree;
    bool bld=false;
    int N;
    int novo()
    {
        Node novo={-1,-1,-1,-1,-1,-1,-1};
        segTree.pb(novo);
        return segTree.size()-1;
    }
    int copy(int i)
    {
        Node a=segTree[i];
        segTree.pb(a);
        return (int)segTree.size()-1;
    }
    void build(int l,int r,int i)
    {
        bld=true;
        if(l==r)
        {
            segTree[i].sum=segTree[i].minn=segTree[i].maxx=l;
            segTree[i].l=segTree[i].r=-1;
            segTree[i].lazy_mod=segTree[i].lazy_mul=0;
            return;
        }
        int mid=(l+r)>>1;
        segTree[i].l=novo();
        segTree[i].r=novo();
        build(l,mid,segTree[i].l);
        build(mid+1,r,segTree[i].r);
        segTree[i].maxx=max(segTree[segTree[i].l].maxx,segTree[segTree[i].r].maxx);
        segTree[i].minn=min(segTree[segTree[i].l].minn,segTree[segTree[i].r].minn);
        segTree[i].sum=segTree[segTree[i].l].sum+segTree[segTree[i].r].sum;
    }
    void build(int maxx)
    {
        Node nov={-1,-1,-1,-1,-1,-1,-1};
        segTree.pb(nov);
        build(0,maxx,0);
        N=maxx;
    }
    void prop(int i,int l,int r)
    {
        if(segTree[i].lazy_mod==0)
            return;
        int m=(l+r)>>1;
        segTree[segTree[i].l].lazy_mod=segTree[i].lazy_mod;
        segTree[segTree[i].r].lazy_mod=segTree[i].lazy_mod;
        segTree[segTree[i].l].lazy_mul=segTree[i].lazy_mul;
        segTree[segTree[i].r].lazy_mul=segTree[i].lazy_mul;
        segTree[i].lazy_mod=segTree[i].lazy_mul=0;
        assert(segTree[segTree[i].l].minn==segTree[segTree[i].l].maxx);
        assert(segTree[segTree[i].r].minn==segTree[segTree[i].r].maxx);
        int a=((ll)segTree[segTree[i].l].minn*segTree[segTree[i].l].lazy_mul)%segTree[segTree[i].l].lazy_mod;
        segTree[segTree[i].l].minn=segTree[segTree[i].l].maxx=a;
        segTree[segTree[i].l].sum=(ll)segTree[segTree[i].l].minn*(m-l+1);
        a=((ll)segTree[segTree[i].r].minn*segTree[segTree[i].r].lazy_mul)%segTree[segTree[i].r].lazy_mod;
        segTree[segTree[i].r].minn=segTree[segTree[i].r].maxx=a;
        segTree[segTree[i].r].sum=(ll)segTree[segTree[i].r].minn*(r-m);
    }
    void update(int i)
    {
        segTree[i].sum=segTree[segTree[i].l].sum+segTree[segTree[i].l].sum;
    }
    void setModMul(int mod,int mul,int l=0,int r=N-1,int i=1)
    {
        if(segTree[i].minn==segTree[i].maxx)
        {
            segTree[i].lazy_mod=mod;
            segTree[i].lazy_mul=mul;
            int a=((ll)segTree[i].minn*mul)%mod;
            segTree[i].sum=segTree
        }
    }
    ll get(int qs,int qe,int l,int r,int i)
    {
        if(qs>r||qe<l)
            return 0;
        if(qs<=l&&qe>=r)
            return segTree[i].sum;
        int mid=(l+r)>>1;
        return get(qs,qe,l,mid,segTree[i].l)+get(qs,qe,mid+1,r,segTree[i].r);
    }
};
int main()
{
    persistantSegTree  pst;
    pst.build(1e6);
    int n,q;
    scanf("%i %i",&n,&q);

    //printf("%lld %lld %lld %lld %lld\n",get(0,5,0,10,0),get(5,5,0,10,0),get(2,8,0,10,0),get(0,2,0,10,0),get(7,7,0,10,0));
    return 0;
}
