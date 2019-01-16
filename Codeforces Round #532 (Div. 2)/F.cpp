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

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
int gaus[20],tm1[20];
void add(int x,int ti)
{
    for(int i=19;i>=0;i--)
    {
        if(x&(1<<i))
        {
            if(gaus[i])
            {
                if(tm1[i]<ti)
                {
                    swap(gaus[i],x);
                    swap(tm1[i],ti);
                }
                x^=gaus[i];
            }
            else
            {
                gaus[i]=x;
                tm1[i]=ti;
                break;
            }
        }
    }
}
int get(int ti)
{
    int x=0;
    for(int i=19;i>=0;i--)
    {
        if(tm1[i]>=ti)
            x=max(x,x^gaus[i]);
    }
    return x;
}
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> c(n);
    for(int i=0;i<n;i++)
        scanf("%i",&c[i]);
    int q;
    scanf("%i",&q);
    vector<int> sol(q);
    vector<vector<pair<int,int> > > qu(n);
    for(int i=0;i<q;i++)
    {
        int l,r;
        scanf("%i %i",&l,&r);
        l--;r--;
        qu[r].pb({l,i});
    }
    for(int i=0;i<n;i++)
    {
        add(c[i],i);
        for(auto p:qu[i])
        {
            sol[p.s]=get(p.f);
        }
    }
    for(int i=0;i<q;i++)
        printf("%i\n",sol[i]);
    return 0;
}
