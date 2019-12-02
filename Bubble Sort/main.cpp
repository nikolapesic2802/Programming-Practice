/*
    -The number of steps taken by the algorithm is equal to the number of inversions in the array.
    -When we swap two elements i and j such that a[i]>a[j], we reduce the number of inversions by the number of elements k, i<k<j such that a[k]<a[i] and a[k]>a[j] times 2 plus the number of elements k, i<k<j such that a[k]==a[i] or a[k]==a[j] plus 1.
    -The challenge is finding the optimal pair.
    -We can find a set of candidates for the first element and for the second element (comes from the fact that if a[i] > a[j] and i < j, its always optimal to take a[i], and similar for the second element).
    -For each value find the interval of the second candidates that it will fit into. Now do a sweep maintaining the values for every second candidate.
    -When we reach a candidate for the first element, we remove all the elements we added before that were bigger than it (undo what we added for them) and get the answer.
    -Its a little tricky to do the case where two elements can be the same.
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

const int N=1e5+5,oo=INT_MAX/2;;
vector<int> maxx(4*N),lazy(4*N);
void prop(int i){
    maxx[2*i]+=lazy[i];
    maxx[2*i+1]+=lazy[i];
    lazy[2*i]+=lazy[i];
    lazy[2*i+1]+=lazy[i];
    lazy[i]=0;
}
void add(int qs,int qe,int x,int l=0,int r=N-1,int i=1){
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        maxx[i]+=x;
        lazy[i]+=x;
        return;
    }
    int m=(l+r)>>1;
    prop(i);
    add(qs,qe,x,l,m,2*i);
    add(qs,qe,x,m+1,r,2*i+1);
    maxx[i]=max(maxx[2*i],maxx[2*i+1]);
}
int get(int qs,int qe,int l=0,int r=N-1,int i=1){
    if(qs>r||qe<l)
        return 0;
    if(qs<=l&&qe>=r)
        return maxx[i];
    int m=(l+r)>>1;
    prop(i);
    return max(get(qs,qe,l,m,2*i),get(qs,qe,m+1,r,2*i+1));
}
vector<int> fen(N);
void addFen(int i){
    for(;i<N;i+=i&(-i))
        fen[i]++;
}
int getFen(int i){
    int ans=0;
    for(;i;i-=i&(-i))
        ans+=fen[i];
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    scanf("%i",&n);
    vector<int> a(n),vals;
    for(int i=0;i<n;i++)
        scanf("%i",&a[i]),vals.pb(a[i]);
    sort(all(vals));
    vals.erase(unique(all(vals)),vals.end());
    map<int,int> mapa;
    for(int i=0;i<(int)vals.size();i++)
        mapa[vals[i]]=i;
    for(auto &p:a)
        p=mapa[p];
    ll inverza=0;
    for(int i=n-1;i>=0;i--)
        inverza+=getFen(a[i]),addFen(a[i]+1);
    if(inverza==0){
        if(vals.size()!=n)
            printf("0\n");
        else
            printf("1\n");
        return 0;
    }
    vector<pair<int,int> > down;
    vector<int> up;
    int val=-1,sol=0;
    for(int i=0;i<n;i++)
        if(a[i]>val)
            val=a[i],up.pb(i);
    val=INT_MAX;
    for(int i=n-1;i>=0;i--)
        if(a[i]<val)
            val=a[i],down.pb({a[i],0});
    reverse(all(down));
    for(int i=0;i<(int)down.size();i++)
        down[i].s=i;
    down.pb({INT_MAX,down.size()});
    vector<pair<int,int> > update(n);
    vector<int> koliko(n);
    int pos=down.size()-1;
    for(int i=n-1;i>=0;i--){
        if(pos&&down[pos-1].f==a[i])
            pos--;
        int dokle=(*lower_bound(all(down),make_pair(a[i],n))).s-1;
        update[i]={pos,dokle};
    }
    set<pair<int,int>,greater<pair<int,int> > > nums;
    for(int i=n-1;i>=0;i--){
        add(update[i].f,update[i].s,2);
        if(down[update[i].s].f==a[i])
            add(update[i].s,update[i].s,-1);
        nums.insert({a[i],i});
        if(i==up.back())
        {
            while(nums.size()&&(*nums.begin()).f>a[i])
                add(update[(*nums.begin()).s].f,update[(*nums.begin()).s].s,-2),nums.erase(nums.begin());
            vector<pair<int,int> > work;
            while(nums.size()&&(*nums.begin()).f==a[i])
                work.pb(update[(*nums.begin()).s]),nums.erase(nums.begin());
            for(auto p:work)
                add(p.f,p.s,-1);
            sol=max(sol,get(update[i].f,update[i].s));
            up.pop_back();
            for(auto p:work)
                add(p.f,p.s,-1);
        }
    }
    printf("%lld\n",inverza-sol+1);
}
