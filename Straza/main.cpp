/*
    -Merge lines that have the same angle and overlap each other.
    -Then try for all triples if they form a triangle in which we can place the guards.
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

ld oo=INT_MAX;
ld eps=1e-9;
struct pt{
  ld x,y;
  pt operator+(pt a){return {x+a.x,y+a.y};}
  pt operator-(pt a){return {x-a.x,y-a.y};}
  pt operator*(ld d){return {x*d,y*d};}
  pt operator/(ld d){return {x/d,y/d};}
};
bool operator<(pt a,pt b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
pt no={oo,oo};
ostream& operator<<(ostream& out,pt a){out << "[" << a.x << "," << a.y << "]";return out;}
istream& operator>>(istream& in,pt &a){in >> a.x >> a.y;return in;}
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
bool operator!=(pt a,pt b){return abs(a.x-b.x)<eps&&abs(a.y-b.y)<eps;}
int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
ld cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
struct line{
    pt v;ld c;
    line(pt a,pt b){v=b-a;c=cross(v,a);}
};
pt inter(line l1,line l2)
{
    ld c=cross(l2.v,l1.v);
    if(c==0)
        return no;
    return (l1.v*l2.c-l2.v*l1.c)/c;
}
struct segment{
    pt a,b;
    pt get()
    {
        pt v=b-a;
        if(v.x<0)
            v=v*-1;
        if(v.x==0)
            v.y=fabs(v.y);
        int g=gcd(v.x,v.y);
        v=v/g;
        return v;
    }
};
bool operator<(segment a,segment b)
{
    pt va=a.get(),vb=b.get();
    if(va==vb)
    {
        if(cross(va,a.a)==cross(vb,b.a))
        {
            if(a.a==b.a)
                return a.b<b.b;
            return a.a<b.a;
        }
        return cross(va,a.a)<cross(vb,b.a);
    }
    return va<vb;
}
pt inter(segment s1,segment s2)
{
    line l1(s1.a,s1.b),l2(s2.a,s2.b);
    pt in=inter(l1,l2);
    if(in==no)
        return no;
    if(in.x>=min(s1.a.x,s1.b.x)-eps&&in.x<=max(s1.a.x,s1.b.x)+eps)
        if(in.y>=min(s1.a.y,s1.b.y)-eps&&in.y<=max(s1.a.y,s1.b.y)+eps)
            if(in.x>=min(s2.a.x,s2.b.x)-eps&&in.x<=max(s2.a.x,s2.b.x)+eps)
                if(in.y>=min(s2.a.y,s2.b.y)-eps&&in.y<=max(s2.a.y,s2.b.y)+eps)
                    return in;
    return no;
}
int main()
{
	int n;
	scanf("%i",&n);
	vector<segment> s(n);
	for(int i=0;i<n;i++)
        cin >> s[i].a >> s[i].b;
    for(int i=0;i<n;i++)
        if(s[i].b<s[i].a)
            swap(s[i].a,s[i].b);
    sort(all(s));
    vector<segment> novo;
    novo.pb(s[0]);
    for(int i=1;i<n;i++)
    {
        if(novo.back().get()==s[i].get()&&cross(novo.back().get(),novo.back().a)==cross(s[i].get(),s[i].a))
        {
            if(s[i].a<novo.back().b||s[i].a==novo.back().b)
            {
                if(novo.back().b<s[i].b)
                    novo.back().b=s[i].b;
                continue;
            }
        }
        novo.pb(s[i]);
    }
    s=novo;
    n=novo.size();
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            for(int k=j+1;k<n;k++)
            {
                pt a=inter(s[i],s[j]),b=inter(s[i],s[k]),c=inter(s[j],s[k]);
                if(a==no||b==no||c==no)
                    continue;
                if(a!=b||a!=c||b!=c)
                    continue;
                cnt++;
            }
        }
    }
    printf("%i\n",cnt);
    return 0;
}
