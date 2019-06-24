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
int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
vector<pt> poly;
pt start={0,0};
int m;
vector<pt> solA,solB;
map<pt,pair<pair<int,int>,pair<int,int> > > mapa[2];
vector<pair<int,int> > nope={{-1,-1}};
vector<pair<int,int> > moze(pt a,int ostaloA,int ind,bool uzeoB)
{
    if(ostaloA==0)
    {
        pair<pair<int,int>,pair<int,int> > tr=mapa[1][a*-1];
        if(tr.s.f>=ind)
            return {tr.f,tr.s};
        tr=mapa[0][a*-1];
        if((uzeoB&&tr.s.f>=ind)||tr.s.f>ind)
            return {tr.f,tr.s};
        return nope;
    }
    if(ind==m)
        return nope;
    int g=gcd(abs(poly[ind].x),abs(poly[ind].y));
    for(int i=g;i>=0;i--)
    {
        vector<pair<int,int> > ans=moze(a+poly[ind]/g*i,ostaloA-(i!=0),ind+1,uzeoB||(i!=g));
        if(ans!=nope)
        {
            if(i)
                ans.pb({ind,i});
            return ans;
        }
    }
    return nope;
}
void genAll(pt a,int ind,int uzeo,pair<pair<int,int>,pair<int,int> > taken,bool uzeoB)
{
    if(uzeo==2)
    {
        if(ind!=m)
            uzeoB=1;
        mapa[uzeoB][a]=max(mapa[uzeoB][a],taken);
        return;
    }
    if(ind==m)
        return;
    int g=gcd(abs(poly[ind].x),abs(poly[ind].y));
    for(int i=g;i>0;i--)
        if(uzeo==0)
            genAll(a+poly[ind]/g*i,ind+1,uzeo+1,{taken.f,{ind,i}},0);
        else
            genAll(a+poly[ind]/g*i,ind+1,uzeo+1,{{ind,i},taken.s},uzeoB||(i!=g));
    genAll(a,ind+1,uzeo,taken,1);
}
void getAns(vector<pair<int,int> > ans,int ind)
{
    if(ind==m)
        return;
    int g=0;
    int gg=gcd(abs(poly[ind].x),abs(poly[ind].y));
    if(ans.size()&&ans.back().f==ind)
        g=ans.back().s,ans.pop_back();
    if(g)
        solA.pb(poly[ind]/gg*g);
    if(g!=gg)
        solB.pb(poly[ind]/gg*(gg-g));
    getAns(ans,ind+1);
}
int main()
{
	for(int k=1;k<=11;k++)
    {
        mapa[0].clear();
        mapa[1].clear();
        poly.clear();
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
        vector<pt> novi,stari=poly;
        for(int i=0;i<n;i++)
            novi.pb(poly[(i+1)%n]-poly[i]);
        poly=novi;
        m=poly.size();
        genAll(start,0,0,{{0,0},{0,0}},0);
        for(int i=2;i>=0;i--){
            vector<pair<int,int> > ans=moze(start,i,0,0);
            if(ans!=nope)
            {
                getAns(ans,0);
                break;
            }
        }
        string out;
        out+='0'+(k)/10;
        out+='0'+(k)%10;
        out+=".out";
        freopen(out.c_str(),"w",stdout);
        printf("%i\n",solA.size());
        pt minxy={0,0};
        pt a={0,0};
        for(int i=0;i<(int)solA.size()-1;i++)
            a=a+solA[i],minxy.x=min(minxy.x,a.x),minxy.y=min(minxy.y,a.y);
        a=minxy*-1;
        vector<pt> polyA,polyB;
        polyA.pb(a);
        for(int i=0;i<(int)solA.size()-1;i++)
            a=a+solA[i],polyA.pb(a);
        a={0,0};
        minxy={0,0};
        for(int i=0;i<(int)solB.size()-1;i++)
            a=a+solB[i],minxy.x=min(minxy.x,a.x),minxy.y=min(minxy.y,a.y);
        a=minxy*-1;
        polyB.pb(a);
        for(int i=0;i<(int)solB.size()-1;i++)
            a=a+solB[i],polyB.pb(a);
        stari=fix(stari);
        polyA=fix(polyA);
        polyB=fix(polyB);
        pt trstart=polyA[0]+polyB[0];
        pt razlika=stari[0]-trstart;
        assert(razlika.x>=0&&razlika.y>=0);
        for(auto p:polyA)
            printf("%i %i\n",(p+razlika).x,(p+razlika).y);
        printf("%i\n",solB.size());
        for(auto p:polyB)
            printf("%i %i\n",p.x,p.y);
        solA.clear();
        solB.clear();
    }
    return 0;
}
