/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2014_solutions/sequence/sequence.tex
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

ll sol=LLONG_MAX,lim=16;
vector<ll> pwr;
void gen(vector<int> req,int digit,ll trsol,bool nula)
{
    if(req.empty())
    {
        if(nula)
            trsol+=pwr[digit];
        sol=min(sol,trsol);
        return;
    }
    if(req.size()==1)
    {
        if(req[0]==1)
            trsol+=pwr[digit+1];
        else
        {
            if(req[0]&1)
            {
                int frst;
                for(int i=9;i>0;i--)
                    if(req[0]&(1<<i))
                        frst=i;
                for(int i=9;i>frst;i--)
                    if(req[0]&(1<<i))
                        trsol+=i*pwr[digit],digit++;
                trsol+=frst*pwr[digit+1];
            }
            else
                for(int i=9;i>0;i--)
                    if(req[0]&(1<<i))
                        trsol+=i*pwr[digit],digit++;
        }
        sol=min(sol,trsol);
        return;
    }
    if(digit>5)
        return;
    int n=req.size();
    for(int y=0;y<10;y++)
    {
        vector<int> sl;
        if(y)
            sl.pb(0);
        int tr=y;
        bool nulaffs=0;
        if(y==0&&(req[0]&1))
            nulaffs=1;
        for(auto p:req)
        {
            if(tr==0)
                sl.pb(0);
            sl.back()|=p&(~(1<<tr));
            tr=(tr+1)%10;
        }
        while(sl.size()&&sl.back()==0)
            sl.pop_back();
        gen(sl,digit+1,trsol+pwr[digit]*y,nulaffs);
    }
}
int main()
{
	pwr.pb(1);
	for(int i=0;i<16;i++)
        pwr.pb(pwr.back()*10);
    int n,a;
    scanf("%i",&n);
    vector<int> req;
    for(int i=0;i<n;i++)
        scanf("%i",&a),req.pb(1<<a);
    gen(req,0,0,0);
    printf("%lld\n",sol);
    return 0;
}
