/*
    -If we sweep by X axis, we will have rectangles entering and exiting our plane, if we can efficiently add, remove and query for the number of rectangles intersecting some rectangle we can solve the problem.
    -All these operations are supported by a 2D fenwick tree in O(log^2 n) per operation, so in total it is O(n*log^2 n)
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

const int N=1001;
struct fenwick{
    vector<int> sum,neg;
    fenwick(){sum.resize(N);neg.resize(N);}
    void add(int pos,int x)
    {
        for(int i=pos;i<N;i+=i&(-i))
            sum[i]+=x;
    }
    void addneg(int pos,int x)
    {
        for(int i=pos;i<N;i+=i&(-i))
            neg[i]+=x;
    }
    void update(int l,int r,int x)
    {
        add(l,x);
        add(r+1,-x);
        addneg(r+1,x);
    }
    int get(int pos)
    {
        int ans=0;
        for(int i=pos;i;i-=i&(-i))
            ans+=sum[i];
        return ans;
    }
    int getneg(int pos)
    {
        int ans=0;
        for(int i=pos;i;i-=i&(-i))
            ans+=neg[i];
        return ans;
    }
    int get(int l,int r)
    {
        return get(r)+getneg(r)-getneg(l);
    }
};
struct fenwick2D{
    vector<fenwick> sum,neg;
    fenwick2D(){sum.resize(N);neg.resize(N);}
    void add(int pos,int x,int l,int r)
    {
        for(int i=pos;i<N;i+=i&(-i))
            sum[i].update(l,r,x);
    }
    void addneg(int pos,int x,int l,int r)
    {
        for(int i=pos;i<N;i+=i&(-i))
            neg[i].update(l,r,x);
    }
    void update(int l1,int r1,int l2,int r2,int x)
    {
        add(l1,x,l2,r2);
        add(r1+1,-x,l2,r2);
        addneg(r1+1,x,l2,r2);
    }
    int get(int pos,int l,int r)
    {
        int ans=0;
        for(int i=pos;i;i-=i&(-i))
            ans+=sum[i].get(l,r);
        return ans;
    }
    int getneg(int pos,int l,int r)
    {
        int ans=0;
        for(int i=pos;i;i-=i&(-i))
            ans+=neg[i].get(l,r);
        return ans;
    }
    int get(int l1,int r1,int l2,int r2)
    {
        return get(r1,l2,r2)+getneg(r1,l2,r2)-getneg(l1,l2,r2);
    }
};
struct query{
    int x,y1,y2,z1,z2,a;
};
bool cmp(query a,query b)
{
    if(a.x==b.x)
        return a.a<b.a;
    return a.x<b.x;
}
int main()
{
    int n;
    scanf("%i",&n);
    fenwick2D a;
    vector<query> q;
    for(int i=0;i<n;i++)
    {
        int x1,y1,z1,x2,y2,z2;
        scanf("%i %i %i %i %i %i",&x1,&y1,&z1,&x2,&y2,&z2);
        if(x1>x2)
            swap(x1,x2);
        if(y1>y2)
            swap(y1,y2);
        if(z1>z2)
            swap(z1,z2);
        q.pb({x1,y1,y2,z1,z2,1});
        q.pb({x2+1,y1,y2,z1,z2,0});
    }
    sort(all(q),cmp);
    ll cnt=0;
    for(auto p:q)
    {
        if(p.a==1)
        {
            cnt+=a.get(p.y1,p.y2,p.z1,p.z2);
            a.update(p.y1,p.y2,p.z1,p.z2,1);
        }
        else
            a.update(p.y1,p.y2,p.z1,p.z2,-1);
    }
    printf("%lld\n",cnt);
    return 0;
}
