/*
    -Consider each point as the point where the right angle is, translate the plane such that that point is in the center, and calculate the angle of each point using atan2.
    -Now for every point calculate the number of points which have an angle of 90 degrees (PI/2 radians) more than itself. I did this using an ordered set, but there are many other solutions.
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
#define ld long double

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

struct pt{
    int x,y;
    pt operator-(pt a){return {x-a.x,y-a.y};}
};
const ld eps=1e-14;
const ld PI=acos(-1);
int main()
{
    int n;
    scanf("%i",&n);
    vector<pt> po(n);
    for(int i=0;i<n;i++)
        scanf("%i %i",&po[i].x,&po[i].y);
    ll ans=0;
    for(int i=0;i<n;i++)
    {
        ordered_set<pair<ld,int> > o;
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            pt a=po[j]-po[i];
            ld ang=atan2(a.y,a.x);
            o.insert({ang,j});
        }
        for(auto p:o)
        {
            ld ang=p.f;
            ld fr=ang+PI/2-eps,sc=ang+PI/2+eps;
            if(fr>PI)
                fr-=2*PI;
            if(sc>PI)
                sc-=2*PI;
            auto it=o.lower_bound({fr,0});
            if(it==o.end())
                it=o.begin();
            int st=o.order_of_key(*it);
            it=o.lower_bound({sc,0});
            if(it==o.end())
                it=o.begin();
            int en=o.order_of_key(*it);
            if(en<st)
                en+=o.size();
            ans+=en-st;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
