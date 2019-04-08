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

#define ld long double

const ld PI=acos(-1);

struct pt{
    ld x,y;
    pt operator+(pt t){return {x+t.x,y+t.y};}
    pt operator-(pt t){return {x-t.x,y-t.y};}
    pt operator*(ld d){return {x*d,y*d};}
    pt operator/(ld d){return {x/d,y/d};}
};
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
bool operator!=(pt a,pt b){return !(a==b);}
ld sq(pt p){return p.x*p.x+p.y*p.y;}
ld abs(pt p){return sqrt(sq(p));}
istream& operator>>(istream& is,pt &p){is >> p.x >> p.y;return is;}
ostream& operator<<(ostream& os,pt p){return os << "(" << p.x << "," << p.y << ")";}
template<typename T> int sgn(T x){return (T(0)<x)-(x<T(0));}
pt translate(pt v,pt p){return p+v;}
pt scale(pt c,ld factor,pt p){return c+(p-c)*factor;}
pt rot(pt p,ld a){return {p.x*cos(a)-p.y*sin(a),p.x*sin(a)+p.y*cos(a)};}
ld dot(pt v,pt w){return v.x*w.x+v.y*w.y;}
ld cross(pt v,pt w){return v.x*w.y-v.y*w.x;}
ld orient(pt a,pt b,pt c){return cross(b-a,c-b);}
pt perp(pt a){return {a.y,-a.x};}
bool inAngle(pt a,pt b,pt c,pt p){
    assert(orient(a,b,c)!=0);
    if(orient(a,b,c)<0) swap(b,c);
    return orient(a,b,p)>=0&&orient(a,c,p)<=0;
}
bool isConvex(vector<pt> p){
    bool hasPos=false,hasNeg=false;
    for(int i=0,n=p.size();i<n;i++)
        if(orient(p[i],p[(i+1)%n],p[(i+2)%n])<0)
            hasNeg=true;
        else
            hasPos=true;
    return !(hasPos&&hasNeg);
}
void polarSort(vector<pt> &p)
{
    sort(all(p),[](pt v,pt w){
         return atan2(v.y,v.x)<atan2(w.y,w.x);
    });
}
struct line{
    pt v; ld c;
    line(pt vv,ld cc){v=vv;c=cc;}
    line(ld a,ld b,ld c){v.x=b;v.y=-a;c=c;}
    line(pt a,pt b){v.x=b.x-a.x;v.y=b.y-a.y;c=cross(v,a);}
    ld side(pt p){return cross(v,p)-c;}
    ld dist(pt p){return abs(side(p))/abs(v);}
    ld sqDist(pt p){return side(p)*side(p)/(ld)sq(v);}
    line perpThrough(pt p){return {p,p+perp(v)};}
    bool cmpProj(pt p,pt q){return dot(v,p)<dot(v,q);}
    line translate(pt t){return {v,c+cross(v,t)};}
    line shiftLeft(ld dist){return {v,c+dist*abs(v)};}
    pt proj(pt p){return p-perp(v)*side(p)/sq(v);}
    pt refl(pt p){return p-perp(v)*2*side(p)/sq(v);}
};
bool inter(line l1,line l2,pt& p)
{
    ld d=cross(l2.v,l1.v);
    if(d==0)
        return false;
    p=(l1.v*l2.c-l2.v*l1.c)/d;
    return true;
}
line bisector(line l1,line l2,bool interior){
    assert(cross(l1.v,l2.v)!=0);
    double sign=interior?1:-1;
    return {l2.v/abs(l2.v)+l1.v/abs(l1.v)*sign,l2.c/abs(l2.v)+l1.c/abs(l1.v)*sign};
}
bool inDisk(pt a,pt b,pt p){
    return dot(a-p,b-p)<=0;
}
bool onSegment(pt a,pt b,pt p){
    return orient(a,b,p)==0&&inDisk(a,b,p);
}
bool properInter(pt a,pt b,pt c,pt d,pt &p)
{
    ld oa=orient(c,d,a),
       ob=orient(c,d,b),
       oc=orient(a,b,c),
       od=orient(a,b,d);
    if(oa*ob<0&&oc*od<0){
        p=(a*ob-b*oa)/(ob-oa);
        return true;
    }
    return false;
}
ld segPoint(pt a,pt b,pt p){
    if(a!=b){
        line l(a,b);
        if(l.cmpProj(a,p)&&l.cmpProj(p,b))
            return l.dist(p);
    }
    return min(abs(p-a),abs(p-b));
}
ld segSeg(pt a,pt b,pt c,pt d){
    pt dummy;
    if(properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c),segPoint(a,b,d),segPoint(c,d,a),segPoint(c,d,b)});
}
ld areaPolygon(vector<pt> p){
    ld sol=0;
    for(int i=0,n=p.size();i<n;i++)
        sol+=cross(p[i],p[(i+1)%n]);
    return abs(sol/2);
}
bool above(pt a,pt p){
    return p.y>=a.y;
}
bool crossesRay(pt a,pt p,pt q){
    return (above(a,q)-above(a,p))*orient(a,p,q)>0;
}
bool inPolygon(vector<pt> p,pt a,bool strict=true){
    int num=0;
    for(int i=0,n=p.size();i<n;i++){
        if(onSegment(p[i],p[(i+1)%n],a))
            return !strict;
        num+=crossesRay(a,p[i],p[(i+1)%n]);
    }
    return num&1;
}
pt circumCenter(pt a,pt b,pt c){
    b=b-a;c=c-a;
    assert(cross(b,c)!=0);
    return a+perp(b*sq(c)-c*sq(b))/cross(b,c)/2;
}
int circleLine(pt o,ld r,line l,pair<pt,pt> p){
    ld h2=r*r-l.sqDist(o);
    if(h2>=0){
        pt pp=l.proj(o);
        pt h=l.v*sqrt(h2)/abs(l.v);
        p={pp-h,pp+h};
    }
    return 1+sgn(h2);
}
int circleCircle(pt o1, ld r1, pt o2, ld r2, pair<pt,pt> &out) {
    pt d=o2-o1; ld d2=sq(d);
    if (d2 == 0) {assert(r1 != r2); return 0;}
    ld pd = (d2 + r1*r1 - r2*r2)/2;
    ld h2 = r1*r1 - pd*pd/d2;
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}
int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (double sign : {-1,1}) {
        pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}
int main()
{
    int n;
    scanf("%i",&n);
    vector<pt> p(n);
    for(int i=0;i<n;i++)
        cin >> p[i];
    cout << areaPolygon(p);
    return 0;
}
