// -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2002/bus-handout.pdf
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

int d[505][505],x[505],y[505],a[505],q;
bool cmp(int a,int b){return d[a][q]>d[b][q];}
int main()
{
	int n,sol=INT_MAX;
	scanf("%i",&n);
	vector<pair<int,int> > p(n);
	for(int i=0;i<n;i++)
        scanf("%i %i",&x[i],&y[i]),a[i]=i;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            d[i][j]=abs(x[i]-x[j])+abs(y[i]-y[j]);
    for(int i=0;i<n;i++){
        q=i;
        sort(a,a+n,cmp);
        for(int j=0;j<n;j++){
            int low=0;
            for(int k=0;k<n;k++)
                if(d[j][a[low]]<d[j][a[k]])
                    sol=min(sol,d[i][j]+d[j][a[low]]+d[i][a[k]]),low=k;
        }
    }
    printf("%i\n",sol);
    return 0;
}
