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

const int N=910,X=2e5;
struct pt{
    int x,y;
    pt operator-(pt a){return {x-a.x,y-a.y};}
    pt operator+(pt a){return {x+a.x,y+a.y};}
    pt operator*(int d){return {x*d,y*d};}
    pt operator/(int d){return {x/d,y/d};}
};
ostream& operator<<(ostream &out,pt a){out << "[" << a.x << "," << a.y << "]";return out;}
bool operator<(pt a,pt b){
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
ll cross(pt a,pt b){return (ll)a.x*b.y-(ll)a.y*b.x;}
vector<pt> fix(vector<pt> a)
{
    pt mn=a[0];
    for(auto p:a)
        if(p<mn)
            mn=p;
    vector<pt> nov;
    for(int i=0,n=a.size();i<n;i++)
        if(a[i]==mn)
            for(int j=0;j<n;j++)
                nov.pb(a[(i+j)%n]);
    return nov;
}
vector<pt> operator*(vector<pt> a,vector<pt> b)
{
    a=fix(a);b=fix(b);
    int na=a.size(),nb=b.size(),i=0,j=0;
    vector<pt> sum;
    while(i<na||j<nb)
    {
        sum.pb(a[i%na]+b[j%nb]);
        ll c=cross(a[(i+1)%na]-a[i%na],b[(j+1)%nb]-b[j%nb]);
        if(c==0)
            i++,j++;
        if(c>0)
            i++;
        if(c<0)
            j++;
    }
    return sum;
}
int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
vector<pt> poly;
bool moze(pt a,int ostaloA,int ind)
{
    cout << ostaloA << a << ind << endl;
    cout << poly[ind]-a << endl;
    if(ind==(int)poly.size()-1)
        return ostaloA==0;
    if(moze(a,ostaloA,ind+1))
        return true;
    pt nxt=poly[ind+1];
    pt diff=nxt-poly[ind];
    int g=gcd(diff.x,diff.y);
    diff=diff/g;
    for(int i=1;i<=g;i++)
        if(moze(a+diff*i,ostaloA-1,ind+1))
            return true;
    return false;
}
int main()
{
    int mn=0,mx=0;
	for(int k=1;k<=11;k++)
    {
        string in;
        in+='0'+k/10;
        in+='0'+k%10;
        freopen(in.c_str(),"r",stdin);
        int n;
        scanf("%i",&n);
        poly.resize(n);
        for(int i=0;i<n;i++)
            scanf("%i %i",&poly[i].x,&poly[i].y);
        poly=fix(poly);
        cout << poly << endl;
        pt start={0,0};
        for(int i=3;i>=1;i--)
            printf("%i: %i\n",i,moze(start,i,0));
    }
    printf("%i %i\n",mn,mx);
    return 0;
}
