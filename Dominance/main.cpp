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

vector<pair<pair<int,int>,pair<int,int> > > events;
vector<int> values;
int M=1e9,N=9001;
gp_hash_table<int,int> mapa;
vector<int> arr(N),cnt(2);
vector<ll> dom(2);
void add(int l,int r,int v)
{
    for(int i=l;i<=r;i++)
    {
        if(arr[i]>0)
            cnt[0]-=values[i+1]-values[i];
        if(arr[i]<0)
            cnt[1]-=values[i+1]-values[i];
        arr[i]+=v;
        if(arr[i]>0)
            cnt[0]+=values[i+1]-values[i];
        if(arr[i]<0)
            cnt[1]+=values[i+1]-values[i];
    }
}
void calc()
{
    int n=events.size();
    for(int i=0;i<n;i++)
    {
        if(i)
            for(int j=0;j<2;j++)
                dom[j]+=(ll)cnt[j]*(events[i].f.f-events[i-1].f.f);
        add(mapa[events[i].s.f],mapa[events[i].s.s],events[i].f.s);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
	int h,w;
	scanf("%i %i",&h,&w);
	int n;
	scanf("%i",&n);
	char c[n][2];
	int x[n],y[n],r[n];
	for(int i=0;i<n;i++)
    {
        scanf("%s %i %i %i",c[i],&x[i],&y[i],&r[i]);
        int minx=x[i]-r[i],miny=y[i],maxx=x[i],maxy=y[i]-r[i];
        int otherx=x[i]+r[i],othery=y[i];
        int add=-1;
        if(c[i][0]=='W')
            add*=-1;
        if((maxx+maxy)%2)
        {
            events.pb({{(maxx+maxy)/2,add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
            events.pb({{(otherx+othery)/2+1,-add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
        }
        minx++;
        maxy++;
        otherx--;
        if((maxx+maxy)%2)
        {
            events.pb({{(maxx+maxy)/2,add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
            events.pb({{(otherx+othery)/2+1,-add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
        }
    }
    for(auto p:events)
        values.pb(p.s.f),values.pb(p.s.s),values.pb(p.s.s+1);
    sort(all(values));
    sort(all(events));
    values.erase(unique(all(values)),values.end());
    for(int i=0;i<(int)values.size();i++)
        mapa[values[i]]=i;
    calc();
    values.clear();
    mapa.clear();
    events.clear();
    for(int i=0;i<n;i++)
    {
        int minx=x[i]-r[i],miny=y[i],maxx=x[i],maxy=y[i]-r[i];
        int otherx=x[i]+r[i],othery=y[i];
        int add=-1;
        if(c[i][0]=='W')
            add*=-1;
        if((maxx+maxy)%2==0)
        {
            events.pb({{(maxx+maxy)/2,add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
            events.pb({{(otherx+othery)/2+1,-add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
        }
        minx++;
        maxy++;
        otherx--;
        if((maxx+maxy)%2==0)
        {
            events.pb({{(maxx+maxy)/2,add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
            events.pb({{(otherx+othery)/2+1,-add},{(minx-miny+M)/2,(maxx-maxy+M)/2}});
        }
    }
    for(auto p:events)
        values.pb(p.s.f),values.pb(p.s.s),values.pb(p.s.s+1);
    sort(all(values));
    sort(all(events));
    values.erase(unique(all(values)),values.end());
    for(int i=0;i<(int)values.size();i++)
        mapa[values[i]]=i;
    calc();
    printf("%lld %lld\n",dom[0],dom[1]);
    return 0;
}
