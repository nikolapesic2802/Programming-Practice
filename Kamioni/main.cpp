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
vector<vector<int> > route;
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	route.resize(n);
	vector<pair<pair<ll,int>,int> > events;
	vector<int> turn_position(n),dir(n),sol(m);
	vector<ll> last_turn(n);
	vector<ll> ubducted(n);
	vector<vector<pair<int,int> > > q(n);
	for(int i=0;i<n;i++)
    {
        int k;
        scanf("%i",&k);
        ll time=0;
        for(int j=0;j<k;j++)
        {
            int a;
            scanf("%i",&a);
            route[i].pb(a);
        }
        turn_position[i]=route[i][0];
        if(route[i][0]<route[i][1])
            dir[i]=1;
        else
            dir[i]=-1;
        for(int j=0;j<(int)route[i].size()-1;j++)
            time+=abs(route[i][j]-route[i][j+1]),events.pb({{time,i},route[i][j+1]});
        ubducted[i]=time;
    }
    sort(all(events));
    for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        if(route[a].size()<route[b].size())
            swap(a,b);
        q[a].pb({b,i});
        q[b].pb({a,i});
    }
    for(auto p:events)
    {
        ll time=p.f.f;
        int t=p.f.s;
        int nxt=p.s;
        //printf("%lld %i %i\n",time,t,nxt);
        for(auto p:q[t])
        {
            int i=p.f;
            int qq=p.s;
            //printf("%i %i  %i %i\n",t,i,dir[t],dir[i]);
            if(ubducted[i]<time||dir[i]==dir[t])
                continue;
            int d1=time-last_turn[i],d2=time-last_turn[t];
            //printf("%i %i\n",d1,d2);
            int a1,a2,b1,b2;
            if(d1>d2)
            {
                a1=turn_position[i]+dir[i]*(d1-d2);
                b1=turn_position[t];
                a2=a1+dir[i]*d2;
                b2=nxt;
            }
            else
            {
                a1=turn_position[i];
                b1=turn_position[t]+dir[t]*(d2-d1);
                a2=a1+dir[i]*d1;
                b2=nxt;
            }
            //printf("%i->%i  %i->%i\n",a1,a2,b1,b2);
            if((a1<b1&&a2>b2)||(a1>b1&&a2<b2))
                sol[qq]++;
        }
        last_turn[t]=time;
        turn_position[t]=nxt;
        if(dir[t]==1)
            dir[t]=-1;
        else
            dir[t]=1;
    }
    for(int i=0;i<m;i++)
        printf("%i\n",sol[i]);
    return 0;
}
