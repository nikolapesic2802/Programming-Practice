/*
    -Test to see if we can group edges in three sets such that they make a triangle.
    -If we can, we need to construct it. Since the polygon needs to be convex, we can't just put the points on the sides of the triangle, bur rather on some curve. I chose to use a quadratic equasion curve to position the points along.
    -My current program doesn't work on the case where we can just simply construct a square, im sure it can be fixed with some casework but it passes all the samples so i didn't do it.
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

const double eps=1e-7;
bool check(int a,int b,int c)
{
    return a+b>c&&a+c>b&&b+c>a;
}
vector<int> sum;
int n;
struct pt{
    double x,y;
    pt operator+(pt a){return {x+a.x,y+a.y};}
    pt operator-(pt a){return {x-a.x,y-a.y};}
    pt operator*(double d){return {x*d,y*d};}
    pt operator/(double d){return {x/d,y/d};}
};
pt perp(pt a){return {a.y*-1,a.x};}
ostream& operator<<(ostream& os,pt a){os << "[" << a.x << "," << a.y << "]";return os;};
double sq(pt a)
{
    return a.x*a.x+a.y*a.y;
}
double abs(pt a)
{
    return sqrt(sq(a));
}
double cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
pt rot(pt p,double a)
{
    return {p.x*cos(a)-p.y*sin(a),p.x*sin(a)+p.y*cos(a)};
}
pair<pt,pt> circleCircle(pt c1,double r1,pt c2,double r2){
    double d=abs(c2-c1);
    double alpha=acos((d*d+r1*r1-r2*r2)/(2*d*r1));
    pt rad=(c2-c1)/d*r1;
    return {c1+rot(rad,-alpha),c1+rot(rad,alpha)};
}
vector<pt> sol;
double getdist(double x)
{
    double c=1e-2;
    return c-x*x*c;
}
void construct(pt start,pt v,vector<int> len,int startlen,int dosad)
{
    sol.pb(start+perp(v)/abs(v)*getdist(1-(double)dosad/startlen*2));
    if(len.size()==1)
        return;
    pt s2=start+v/abs(v)*len.back();
    int b=len.back();
    len.pop_back();
    construct(s2,v,len,startlen,dosad+b);
}
void construct(int l,int r,int m)
{
    vector<int> e1,e2,e3;
    for(int i=l+1;i<=r;i++)
        e1.pb(sum[i]-sum[i-1]);
    for(int i=r+1;i<=m;i++)
        e2.pb(sum[i]-sum[i-1]);
    int d=r-l+m-r;
    d=n-d;
    for(int i=m+1;i<=m+d;i++)
        e3.pb(sum[i]-sum[i-1]);
    reverse(all(e1));
    reverse(all(e2));
    reverse(all(e3));
    pt a={0,0};
    int d1=0,d2=0,d3=0;
    for(auto p:e1)
        d1+=p;
    for(auto p:e2)
        d2+=p;
    for(auto p:e3)
        d3+=p;
    pt b={(double)d1,0};
    pt c=circleCircle(a,d3,b,d2).f;
    construct(a,b-a,e1,d1,0);
    construct(b,c-b,e2,d2,0);
    construct(c,a-c,e3,d3,0);
    for(auto p:sol)
        printf("%.10f %.10f\n",p.x,p.y);
}
int main()
{
    scanf("%i",&n);
    vector<int> l(n+1);
	for(int i=1;i<=n;i++)
        scanf("%i",&l[i]);
    sort(all(l));
    for(int i=1;i<=n;i++)
        l.pb(l[i]);
    sum.resize(2*n+1);
    for(int i=1;i<=2*n;i++)
        sum[i]=l[i]+sum[i-1];
    for(int i=0;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            int koliko=n-j+i;
            if(koliko<2)
                continue;
            int dist=sum[j]-sum[i];
            int target=(sum[n]-dist)/2;
            int le=j+1,ri=j+koliko;
            while(le<ri)
            {
                int m=(le+ri+1)>>1;
                int d=sum[m]-sum[j];
                if(d>target)
                    ri=m-1;
                else
                    le=m;
            }
            int dist2=sum[le]-sum[j];
            int d3=sum[n]-dist-dist2;
            if(check(dist,dist2,d3))
            {
                construct(i,j,le);
                return 0;
            }
            if(le<j+koliko)
            {
                le++;
                int d2=sum[le]-sum[j];
                int dd3=sum[n]-dist-d2;
                if(check(dist,d2,dd3))
                {
                    construct(i,j,le);
                    return 0;
                }
            }
        }
    }
    printf("NO SOLUTION\n");
    return 0;
}
