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
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ",\n";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

#define ld long double
struct pt{
    ld x,y;
    pt(){x=0;y=0;}
    pt(ld a,ld b){x=a;y=b;}
    pt operator+(pt a){return {x+a.x,y+a.y};}
    pt operator-(pt a){return {x-a.x,y-a.y};}
    pt operator*(ld d){return {x*d,y*d};}
    pt operator/(ld d){return {x/d,y/d};}
    ld dist(pt a){return (a.x-x)*(a.x-x)+(a.y-y)*(a.y-y);}
};
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
ostream& operator<<(ostream& out,pt a)
{
    out << "(" << a.x << "," << a.y << ")";
    return out;
}
ld dot(pt a,pt b){
    return a.x*b.x+a.y*b.y;
}
ld cross(pt a,pt b){
    return a.x*b.y-a.y*b.x;
}
ld sq(pt a){
    return a.x*a.x+a.y*a.y;
}
ld abs(pt a){
    return sqrt(sq(a));
}
ld orient(pt a,pt b,pt p){return cross(a-p,b-p);}
pt perp(pt a){return {a.y,-a.x};}
struct line{
    pt aa,bb;
    pt v;
    ld c;
    line(pt a,pt b){aa=a;bb=b;v=b-a;c=cross(v,a);}
    ld side(pt p){return cross(v,p)-c;}
    ld dist(pt p){return abs(side(p))/abs(v);}
    pt proj(pt p){return p+perp(v)*side(p)/sq(v);}
};
ostream& operator<<(ostream& out,line a)
{
    out << "{" << a.aa << "," << a.bb << "}";
    return out;
}
bool operator==(line a,line b){return a.aa==b.aa&&a.bb==b.bb;}
bool operator!=(line a,line b){return !(a==b);}
bool operator<(line a,line b){return false;}
pt inter(line l1,line l2){return (l1.v*l2.c-l2.v*l1.c)/cross(l2.v,l1.v);}
int n;
vector<pt> poly;
ld to(line l1,line l2){
    pt i=inter(l1,l2);
    return atan2(i.y,i.x);
}
void solve(ld x,ld y)
{
    pt tr(x,y);
    vector<pair<ld,line> > lines;
    for(int i=0;i<n;i++)
    {
        int l=i+1,r=i+n-1;
        while(l<r)
        {
            int m=(l+r+1)>>1;
            if(orient(poly[m],tr,poly[i])>0)
                l=m;
            else
                r=m-1;
        }
        line l1(poly[i],poly[l]),l2(poly[i],poly[l+1]);
        pt p1=l1.proj(tr),p2=l2.proj(tr);
        p1=p1-tr;
        p2=p2-tr;
        lines.pb({atan2(p1.y,p1.x),l1});
        lines.pb({atan2(p2.y,p2.x),l2});
    }
    sort(all(lines));
    vector<pair<ld,line> > ne;
    ne.pb(lines[0]);
    for(int i=1;i<(int)lines.size();i++)
        if(lines[i].f!=lines[i-1].f)
            ne.pb(lines[i]);
    lines=ne;
    deque<line> hull;
    for(int i=0;i<(int)lines.size();i++)
    {
        while(hull.size()>1)
        {
            pt i1=inter(hull[hull.size()-1],lines[i].s),i2=inter(hull[hull.size()-1],hull[hull.size()-2]);
            if(orient(i2,i1,tr)<=0)
                hull.pop_back();
            else
                break;
        }
        hull.pb(lines[i].s);
    }
    for(int i=0;i<(int)lines.size();i++)
    {
        if(hull.front()!=lines[i].s)
            continue;
        hull.pop_front();
        while(hull.size()>1)
        {
            pt i1=inter(hull[hull.size()-1],lines[i].s),i2=inter(hull[hull.size()-1],hull[hull.size()-2]);
            if(orient(i2,i1,tr)<=0)
                hull.pop_back();
            else
                break;
        }
        hull.pb(lines[i].s);
    }
    ld max_dist=0;
    for(int i=0,n=hull.size();i<n;i++)
    {
        pt ii=inter(hull[i],hull[(i+1)%n]);
        ld d=tr.dist(ii);
        max_dist=max(max_dist,d);
    }
    printf("%.20Lf\n",sqrt(max_dist));
}
int main()
{
    cin >> n;
    poly.resize(n);
    for(int i=0;i<n;i++)
        cin >> poly[i].x >> poly[i].y;
    for(int i=0;i<n;i++)
        poly.pb(poly[i]);
    int m;
    cin >> m;
    while(m--)
    {
        int x,y;
        cin >> x >> y;
        solve(x,y);
    }
    return 0;
}
