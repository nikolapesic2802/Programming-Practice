/*
    -Use mo's algorithm to get the count for every element for every query in O(N*sqrt(N)) for all queries.
    -If we split the query into segments(segment tree), the majority element in the whole range has to be the majority element in some segment of it. So we have log n candidates for the majority element for every query.
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

const int N=3e5+5,M=1e4+5,S=sqrt(N);
int l=0,r=-1;
vector<int> cnt(M);
vector<int> arr(N);
void adjust(int qs,int qe)
{
    while(qs<l)
    {
        l--;
        cnt[arr[l]]++;
    }
    while(qe>r)
    {
        r++;
        cnt[arr[r]]++;
    }
    while(qs>l)
    {
        cnt[arr[l]]--;
        l++;
    }
    while(qe<r)
    {
        cnt[arr[r]]--;
        r--;
    }
}
bool cmp(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.f.f/S==b.f.f/S )
    {
        if((a.f.f/S)%2)
            return a.f.s>b.f.s;
        return a.f.s<b.f.s;
    }
    return a.f.f<b.f.f;
}
int n,c;
struct segTree{
    vector<int> candidate;
    void build(int l,int r,int i)
    {
        int c=0,it=0;
        for(int j=l;j<=r;j++)
            if(it==0)
                c=arr[j],it=1;
            else
                if(arr[j]==c)
                    it++;
                else
                    it--;
        candidate[i]=c;
        if(l==r)
            return;
        int m=(l+r)>>1;
        build(l,m,2*i);
        build(m+1,r,2*i+1);
    }
    void init()
    {
        candidate.resize(4*n);
        build(0,n-1,1);
    }
    vector<int> get(int qs,int qe,int l=0,int r=n-1,int i=1)
    {
        if(qs>r||qe<l)
        {
            vector<int> a;
            return a;
        }
        if(qs<=l&&qe>=r)
        {
            vector<int> a;
            a.pb(candidate[i]);
            return a;
        }
        int m=(l+r)>>1;
        vector<int> le=get(qs,qe,l,m,2*i),ri=get(qs,qe,m+1,r,2*i+1);
        for(auto p:ri)
            le.pb(p);
        return le;
    }
}st;
int main()
{
	scanf("%i %i",&n,&c);
    for(int i=0;i<n;i++)
        scanf("%i",&arr[i]);
    st.init();
    int q;
    scanf("%i",&q);
    vector<pair<pair<int,int>,int> > qu(q);
    for(int i=0;i<q;i++)
        scanf("%i %i",&qu[i].f.f,&qu[i].f.s),qu[i].f.f--,qu[i].f.s--,qu[i].s=i;
    sort(all(qu),cmp);
    vector<int> sol(q);
    for(auto p:qu)
    {
        adjust(p.f.f,p.f.s);
        int siz=(r-l+1)/2;
        vector<int> candidates=st.get(p.f.f,p.f.s);
        sol[p.s]=-1;
        for(auto d:candidates)
            if(cnt[d]>siz)
                sol[p.s]=d;
    }
    for(int i=0;i<q;i++)
        if(sol[i]==-1)
            printf("no\n");
        else
            printf("yes %i\n",sol[i]);
    return 0;
}
