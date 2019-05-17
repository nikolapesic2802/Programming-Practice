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

const ld PI=acos(-1);
struct pt{
    ld x,y;
    pt operator-(pt a){return {x-a.x,y-a.y};}
    pt operator+(pt a){return {x+a.x,y+a.y};}
    pt operator*(ld a){return {x*a,y*a};}
    pt operator/(ld a){return {x/a,y/a};}
};
bool operator<(pt a,pt b){
    if(a.x==b.x)
        return a.y<b.x;
    return a.x<b.x;
}
ostream& operator<<(ostream& out,pt a){out << "[" << a.x << "," << a.y << "]"; return out;}
istream& operator>>(istream& in,pt &a){in >> a.x >> a.y;return in;}
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
bool operator!=(pt a,pt b){return !(a==b);}
ld cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
ld dot(pt a,pt b){return a.x*b.x+a.y*b.y;}
ld sq(pt a){return a.x*a.x+a.y*a.y;}
ld abs(pt a){return sqrtl(sq(a));}
pt perp(pt a){return {a.y,-a.x};}
pt rot(pt p,ld a){return {p.x*cos(a)-p.y*sin(a),p.x*sin(a)+p.y*cos(a)};}
pt o;
int mn,mx;
ld r;
int n;
vector<pt> poly;
void setmnmx()
{
    for(int i=1;i<n;i++)
    {
        ld c=cross(poly[i],poly[mn]);
        if(c<0||(c==0&&sq(poly[i])>sq(poly[mn])))
            mn=i;
    }
    for(int i=1;i<n;i++)
    {
        ld c=cross(poly[i],poly[mx]);
        if(c>0||(c==0&&sq(poly[i])>sq(poly[mx])))
            mx=i;
    }
}
struct line{
    pt v;
    ld c;
    line(pt a,pt b){v=b-a;c=cross(v,a);}
    ld side(pt a){return c-cross(v,a);}
    ld dist(pt a){return abs(side(a))/abs(v);}
    ld sqDist(pt a){return side(a)*side(a)/sq(v);}
    pt proj(pt a){return a-perp(v)*side(a)/sq(v);}
};
pair<pt,pt> presek(pt a,pt b)
{
    line l(a,b);
    ld d=l.dist(o);
    assert(d<=r);
    ld h=sqrtl(r*r-d*d);
    pt v=l.proj(o);
    return {v+l.v*h/abs(l.v),v-l.v*h/abs(l.v)};
}
pt no={INT_MIN,INT_MIN};
pair<pt,pt> presek(pt o,ld r,line l)
{
    ld d=l.dist(o);
    if(d>r)
        return {no,no};
    ld h=sqrtl(r*r-d*d);
    pt v=l.proj(o);
    return {v+l.v*h/abs(l.v),v-l.v*h/abs(l.v)};
}
pt inter(line l1,line l2)
{
    ld c=cross(l2.v,l1.v);
    if(c==0)
        return no;
    return (l1.v*l2.c-l2.v*l1.c)/c;
}
pair<pt,pt> inter(pt o1,ld r1,pt o2,ld r2)
{
    pt d=o2-o1;ld d2=sq(d);
    ld pd=(d2+r1*r1-r2*r2)/2;
    ld h2=r1*r1-pd*pd/d2;
    if(h2>=0)
    {
        pt p=o1+d*pd/d2,h=perp(d)*sqrtl(h2/d2);
        return {p-h,p+h};
    }
    return {no,no};
}
ld closest(pt a,pt b)
{
    line l(a,b);
    if(dot(b*-1,a-b)>0&&dot(a*-1,b-a)>0)
        return l.dist(o);
    return min(abs(a),abs(b));
}
ld ans;
vector<pair<int,ld> > posetio;
void solve(int tr,int dir,ld ostalo)
{
    posetio[tr]={dir,ostalo};
    if(dir==1)
    {
        pt last=poly[tr]-poly[(tr-1+n)%n];
        if(tr==mn)
            last=poly[tr];
        pt sad=poly[(tr+1)%n]-poly[tr];
        ld l=atan2(last.y,last.x);
        ld r=atan2(sad.y,sad.x);
        if(l<r)
            l+=PI*2;
        ld posto=(l-r)/2/PI;
        ans+=ostalo*ostalo*PI*posto;
        if(abs(sad)<ostalo)
            solve((tr+1)%n,dir,ostalo-abs(sad));
    }
    else
    {
        pt last=poly[tr]-poly[(tr+1)%n];
        if(tr==mx)
            last=poly[tr];
        pt sad=poly[(tr-1+n)%n]-poly[tr];
        ld l=atan2(sad.y,sad.x);
        ld r=atan2(last.y,last.x);
        if(l<r)
            l+=PI*2;
        ld posto=(l-r)/2/PI;
        ans+=ostalo*ostalo*PI*posto;
        if(abs(sad)<ostalo)
            solve((tr-1+n)%n,dir,ostalo-abs(sad));
    }
}
ld getarea(pt o1,ld ra1,pt o2,ld ra2,pt start,line border,line b2,ld l1,ld r1,ld l2,ld r2)
{
    if(abs(o1-o2)>=ra1+ra2)
        return 0;
    const ld eps=2e-5;
    vector<pt> levo,desno;
    deque<pt> hull;
    for(ld i=l1;i<=r1;i+=eps,start=rot(start-o1,eps)+o1)
    {
        line l(o1,start);
        pair<pt,pt> pr=presek(o2,ra2,l);
        if(pr.f==no)
            continue;
        pt sek;
        if(abs(pr.f-o1)>abs(pr.s-o1))
            swap(pr.f,pr.s);
        sek=pr.f;
        if(abs(sek-o1)>ra1)
            continue;
        ld ang=atan2((sek-o2).y,(sek-o2).x);
        if(ang<l2&&(l2-ang)>PI)
            ang+=2*PI;
        if(ang<l2)
            continue;
        if((start<o1)!=(sek<o1))
            continue;
        if(ang>r2)
        {
            pt novo=inter(l,border);
            sek=novo;
        }
        if((start<o1)!=(sek<o1))
            continue;
        pair<pt,pt> pr1=presek(o1,ra1,l);
        pt a;
        if(abs(pr1.f-sek)<abs(pr1.s-sek))
            a=pr1.f;
        else
            a=pr1.s;
        pt novo=inter(l,b2);
        if(abs(novo-o1)<abs(a-o1))
            a=novo;
        if(abs(a-o1)<abs(sek-o1))
            continue;
        if(abs(pr.s-o1)<abs(a-o1))
            a=pr.s;
        hull.push_front(sek);
        hull.push_back(a);
    }
    if(hull.size()<3)
        return 0;
    ld ar=0;
    for(int i=0,n=hull.size();i<n;i++)
        ar+=cross(hull[i],hull[(i+1)%n]);
    ar=fabs(ar)/2;
    return ar;
}
int main()
{
    cin >> o >> r;
    scanf("%i",&n);
    poly.resize(n);
    posetio.resize(n);
    for(int i=0;i<n;i++)
        cin >> poly[i],poly[i]=poly[i]-o;
    o={0,0};
    setmnmx();
    int tr=mn;
    vector<pt> area;
    if(abs(poly[mn])<=r)
        solve(mn,1,r-abs(poly[tr])),area.pb(poly[mn]);
    tr=(tr-1+n)%n;
    while(true)
    {
        pt sad=poly[tr],prosla=poly[(tr+1)%n];
        if(abs(sad)<=r)
        {
            if(abs(prosla)>r)
            {
                pair<pt,pt> pr=presek(sad,prosla);
                if(pr.f.x<min(sad.x,prosla.x)||pr.f.x>max(sad.x,prosla.x))
                    swap(pr.f,pr.s);
                area.pb(pr.f);
            }
            area.pb(sad);
        }
        else
        {
            if(abs(prosla)<=r)
            {
                pair<pt,pt> pr=presek(sad,prosla);
                if(pr.f.x<min(sad.x,prosla.x)||pr.f.x>max(sad.x,prosla.x))
                    swap(pr.f,pr.s);
                area.pb(pr.f);
                break;
            }
            else
            {
                if(closest(sad,prosla)<=r)
                {
                    pair<pt,pt> pr=presek(sad,prosla);
                    area.pb(pr.f);
                    area.pb(pr.s);
                    break;
                }
            }
        }
        if(tr==mx)
        {
            if(abs(sad)<=r)
                solve(mx,-1,r-abs(sad));
            break;
        }
        tr=(tr-1+n)%n;
    }
    area.pb(o);
    if(area.size()>1){
        ld sol=0;
        int n=area.size();
        assert(n>2);
        for(int i=0;i<n;i++)
            sol+=cross(area[i],area[(i+1)%n]);
        sol=fabs(sol)/2;
        ld le=atan2(area[0].y,area[0].x),ri=atan2(area[n-2].y,area[n-2].x);
        if(le<ri)
            le+=2*PI;
        ld posto=(2*PI-le+ri)/2/PI;
        sol+=r*r*PI*posto;
        ans+=sol;
    }
    else
        ans=r*r*PI;
    vector<int> prvi,drugi;
    for(int i=mn;;i=(i+1)%n)
    {
        if(posetio[i].f==1)
            prvi.pb(i);
        if(posetio[i].f==-1)
            drugi.pb(i);
        if(i==mx)
            break;
    }
    for(auto p:prvi)
    {
        for(auto d:drugi)
        {
            pt a=poly[p];
            pt b=poly[(p+1)%n];
            pt c=poly[(p-1+n)%n];
            pt x=poly[d];
            pt y=poly[(d-1+n)%n];
            pt z=poly[(d+1)%n];
            ld ra1=posetio[p].s,ra2=posetio[d].s;
            line e1(c,a),e2(z,x),i1(a,b),i2(x,y);
            ld r1=atan2(e1.v.y,e1.v.x),l1=atan2(i1.v.y,i1.v.x),r2=atan2(i2.v.y,i2.v.x),l2=atan2(e2.v.y,e2.v.x);
            if(r1<l1)
                r1+=2*PI;
            if(r2<l2)
                r2+=2*PI;
            ld g=getarea(a,ra1,x,ra2,b,i2,e2,l1,r1,l2,r2);
            if(g==0&&d!=drugi.front())
                break;
            ans-=g;
        }
    }
    printf("%Lf\n",ans);
    return 0;
}
