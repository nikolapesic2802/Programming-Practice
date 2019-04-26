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

vector<pair<pair<int,int>,pair<int,int> > > solve(FILE *f,int best)
{
    int n;
    fscanf(f,"%i",&n);
    vector<vector<int> >
}
void reset()
{
    for(int i=1;i<=10;i++)
    {
        string in="xor";
        if(i<10)
            in+=i+'0';
        else
            in+="10";
        string out=in+".out";
        FILE *sol=fopen(out.c_str(),"w");
        fprintf(sol,"999999999\n");
        fclose(sol);
    }
}
void go()
{
    bool update=false;
	for(int i=1;i<=10;i++)
    {
        string in="xor";
        if(i<10)
            in+=i+'0';
        else
            in+="10";
        string out=in+".out";
        in+=".in";
        FILE *sol=fopen(out.c_str(),"r");
        int best;
        fscanf(sol,"%i",&best);
        fclose(sol);
        FILE *f=fopen(in.c_str(),"r");
        auto mysol=solve(f,best);
        fclose(f);
        if(update)
        {
            if((int)mysol.size()<best)
            {
                sol=fopen(out.c_str(),"w");
                fprintf(sol,"%i\n",mysol.size());
                for(auto p:mysol)
                    fprintf(sol,"%i %i %i %i\n",p.f.f,p.f.s,p.s.f,p.s.s);
                fclose(sol);
            }
        }
    }
}
int main()
{
    int ponavljanja=1;
    while(ponavljanja--)
        go();
}
