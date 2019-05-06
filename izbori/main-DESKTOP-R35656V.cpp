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
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

struct raz{
    int a,b;
    int nextNumber(bool mozeIsti)
    {

    }
    raz operator*(int d)
    {
        return {a-d,b};
    }
};
bool operator<(raz i,raz j)
{
    return (ll)i.a*j.b<(ll)j.a*i.b;
}
bool operator>(raz i,raz j)
{
    return (ll)i.a*j.b>(ll)j.a*i.b;
}
ostream& operator<<(ostream& out,raz a)
{
    out << "[" << a.a << "/" << a.b << "]";
    return out;
}
int main()
{
	int v,n,m;
	scanf("%i %i %i",&v,&n,&m);
	int total=0;
	vector<int> niz(n);
	for(int i=0;i<n;i++)
        scanf("%i",&niz[i]),total+=niz[i];
    total=v-total;
    raz mora={5*v,100};
    vector<int> sol(n);
    for(int i=0;i<n;i++)
    {
        niz[i]+=total;
        set<pair<raz,int>,greater<pair<raz,int> > > nxt;
        for(int j=0;j<n;j++)
        {
            raz tr={niz[j],1};
            if(tr<mora)
                continue;
            nxt.insert({tr,n-j});
        }
        int cnt=0;
        for(int j=0;j<m;j++)
        {
            auto tr=*nxt.begin();
            nxt.erase(nxt.begin());
            if(tr.s==n-i)
                cnt++;
            tr.f.b++;
            nxt.insert(tr);
        }
        niz[i]-=total;
        sol[i]=cnt;
        printf("%i ",cnt);
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=sol[i];j++)
        {
            raz granica={niz[i],j+1};
            set<pair<int,pair<int,int> > > nxt;
            for(int k=0;k<i;k++)
            {
                niz.insert({})
            }
        }
    }
    return 0;
}
