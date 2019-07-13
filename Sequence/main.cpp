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

//3:20

const int N=1e5+5;
struct node{
    int l,r,sum;
    node(){l=-1;r=-1;sum=0;}
};
struct segTree{
    vector<node> drvo;
    vector<int> roots;
    vector<int> cnt;
    int newNode()
    {
        node a;
        drvo.pb(a);
        return drvo.size()-1;
    }
    int copyNode(int i)
    {
        drvo.pb(drvo[i]);
        return drvo.size()-1;
    }
    void build(int l=0,int r=N-1,int tr=0)
    {
        if(l==r)
            return;
        int m=(l+r)>>1,a=newNode();
        drvo[tr].l=a;
        a=newNode();
        drvo[tr].r=a;
        build(l,m,drvo[tr].l);
        build(m+1,r,drvo[tr].r);
    }
    void init()
    {
        int a=newNode();
        roots.pb(a);
        build();
    }
    void undo()
    {
        for(int i=0;i<cnt.back();i++)
            drvo.pop_back();
        cnt.pop_back();
        roots.pop_back();
    }
    int get(int qs,int qe)
    {
        return gett(qs,qe,roots.back());
    }
    int gett(int qs,int qe,int tr,int l=0,int r=N-1)
    {
        if(qs>r||qe<l||drvo[tr].sum==0)
            return 0;
        if(qs<=l&&qe>=r)
            return drvo[tr].sum;
        int m=(l+r)>>1;
        return gett(qs,qe,drvo[tr].l,l,m)+gett(qs,qe,drvo[tr].r,m+1,r);
    }
    void postavi(int qs,int qe)
    {
        cnt.pb(0);
        int a=sett(qs,qe,roots.back());
        roots.pb(a);
    }
    int sett(int qs,int qe,int tr,int l=0,int r=N-1)
    {
        if(qs>r||qe<l||drvo[tr].sum==0)
            return tr;
        int nov=copyNode(tr);
        cnt.back()++;
        if(qs<=l&&qe>=r)
        {
            drvo[nov].sum=0;
            return nov;
        }
        int m=(l+r)>>1;
        int a=sett(qs,qe,drvo[tr].l,l,m);
        drvo[nov].l=a;
        a=sett(qs,qe,drvo[tr].r,m+1,r);
        drvo[nov].r=a;
        drvo[nov].sum=drvo[drvo[nov].l].sum+drvo[drvo[nov].r].sum;
        return nov;
    }
    void add(int pos,int tr=0,int l=0,int r=N-1)
    {
        if(l>pos||r<pos)
            return;
        if(l==r)
        {
            drvo[tr].sum++;
            return;
        }
        int m=(l+r)>>1;
        add(pos,drvo[tr].l,l,m);
        add(pos,drvo[tr].r,m+1,r);
        drvo[tr].sum=drvo[drvo[tr].l].sum+drvo[drvo[tr].r].sum;
    }
}num[10];
ll sol=LLONG_MAX;
int n,lim=1e7;
vector<int> k;
vector<ll> pwr;
void update(ll tr)
{
    sol=min(sol,tr);
}
void build(int first,int interval,ll tr,int digits,int ostalo,bool trebaNula)
{
    cout << tr << endl;
    if(tr>sol||digits>6)
        return;
    if(ostalo==0)
    {
        if(tr<pwr[digits-1])
        {
            if(trebaNula)
                update(tr+pwr[digits]);
            else
                update(tr);
        }
        else
            update(tr);
        return;
    }
    if(first==n)
    {
        vector<int> dodaj;
        for(int i=9;i>=0;i--)
            if(num[i].get(0,n-1))
                dodaj.pb(i);
        if(dodaj.back()==0&&dodaj.size()>1)
            swap(dodaj[dodaj.size()-1],dodaj[dodaj.size()-2]);
        if(dodaj.back()==0&&dodaj.size()==1)
            trebaNula=true;
        for(auto p:dodaj)
            tr+=pwr[digits]*p,digits++;
        if(tr<pwr[digits-1])
        {
            if(trebaNula)
                update(tr+pwr[digits]);
            else
                update(tr);
        }
        else
            update(tr);
        return;
    }
    for(int i=0;i<=9;i++)
    {
        vector<int> cnt;
        int uzeo=0;
        if(first!=0)
        {
            int tr=num[i].get(0,first-1);
            uzeo+=tr;
            if(tr)
                num[i].postavi(0,first-1),cnt.pb(i);
        }
        int l=first,r=first+interval-1,j=(i+1)%10;
        while(l<n)
        {
            int tr=num[j].get(l,min(r,n-1));
            uzeo+=tr;
            if(tr)
                num[j].postavi(l,min(r,n-1)),cnt.pb(j);
            l+=interval;
            r+=interval;
            j=(j+1)%10;
        }
        if(cnt.empty())
            continue;
        bool nula=false;
        if(i==0&&(cnt.front()==0||trebaNula))
            nula=true;
        build(min(n,first+interval*(9-i)),min(lim,interval*10),tr+pwr[digits]*i,digits+1,ostalo-uzeo,nula);
        for(auto p:cnt)
            num[p].undo();
    }
}
int main()
{
    pwr.pb(1);
    for(int i=0;i<18;i++)
        pwr.pb(pwr.back()*10);
    for(int i=0;i<10;i++)
        num[i].init();
    freopen("in.txt","r",stdin);
    scanf("%i",&n);
    k.resize(n);
    for(int i=0;i<n;i++)
        scanf("%i",&k[i]),num[k[i]].add(i);
    build(1,1,0,0,n,0);
    cout << sol << endl;
    return 0;
}
