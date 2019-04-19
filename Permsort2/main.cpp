/*
    -We can in one operation, move some element of the array to the front(or the back if we use suffixes instead of prefixes).
    -To move some element to the front without changing the order of the others, first flip all the elements before it, and then all the elements up to itself(including itself).
    -So basically if we want to move element i to the front, we do operations P i-1 and P i.
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

int n;
struct segTree{
    vector<int> pos;
    void build(int l,int r,int i)
    {
        if(l==r)
        {
            pos[i]=l;
            return;
        }
        int m=(l+r)>>1;
        build(l,m,2*i);
        build(m+1,r,2*i+1);
    }
    void init()
    {
        pos.resize(4*n);
        build(0,n-1,1);
    }
    void prop(int i)
    {
        pos[2*i]+=pos[i];
        pos[2*i+1]+=pos[i];
        pos[i]=0;
    }
    int get(int poss,int l=0,int r=n-1,int i=1)
    {
        if(l>poss||r<poss)
            return 0;
        if(l==poss&&r==poss)
            return pos[i];
        int m=(l+r)>>1;
        prop(i);
        return max(get(poss,l,m,2*i),get(poss,m+1,r,2*i+1));
    }
    void inc(int qs,int qe,int l=0,int r=n-1,int i=1)
    {
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            pos[i]++;
            return;
        }
        int m=(l+r)>>1;
        inc(qs,qe,l,m,2*i);
        inc(qs,qe,m+1,r,2*i+1);
    }
}ind;
int main()
{
    FILE *in=fopen("permsort2.in","r"),*out=fopen("permsort2.out","w");
	fscanf(in,"%i",&n);
	//n=1e5;
	ind.init();
	vector<int> startpos(n);
	for(int i=0;i<n;i++)
    {
        int a;
        fscanf(in,"%i",&a);
        startpos[a-1]=i;
    }
    fprintf(out,"%i\n",2*n);
    for(int i=n-1;i>=0;i--)
    {
        int trpos=ind.get(startpos[i]);
        fprintf(out,"P %i\n",max(trpos,1));
        fprintf(out,"P %i\n",trpos+1);
        ind.inc(0,startpos[i]);
    }
    return 0;
}
