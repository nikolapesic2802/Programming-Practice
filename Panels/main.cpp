/*
    -https://github.com/zoooma13/Competitive-Programming/blob/master/pan.cpp
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

int main()
{
	int n;
	scanf("%i",&n);
	while(n--)
    {
        int a,b,c,d;
        scanf("%i %i %i %i",&a,&b,&c,&d);
        vector<int> div1,div2;
        int sol=-1,lim=max(sqrt(b)+1,sqrt(d)+1);
        vector<pair<int,int> > ranges1={{a,b}},ranges2={{c,d}};
        for(int m=1;m<lim;m++)
            ranges1.pb({(a-1)/(m+1)+1,min((a-1)/m,b/(m+1))}),ranges2.pb({(c-1)/(m+1)+1,min((c-1)/m,d/(m+1))});
        int i=0,j=0;
        while(i<(int)ranges1.size()&&j<(int)ranges2.size()&&ranges1[i].s>lim&&ranges2[j].s>lim)
        {
            if(max(ranges1[i].f,ranges2[j].f)<=min(ranges1[i].s,ranges2[j].s))
            {
                sol=min(ranges1[i].s,ranges2[j].s);
                break;
            }
            if(ranges1[i].f>ranges2[j].f)
                i++;
            else
                j++;
        }
        if(sol==-1)
            for(int i=lim;i>=1;i--)
                if(i*((a-1)/i+1)<=b&&i*((c-1)/i+1)<=d)
                {
                    sol=i;
                    break;
                }
        printf("%i\n",sol);
    }
    return 0;
}
