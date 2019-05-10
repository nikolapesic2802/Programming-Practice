/*
    -For each starting position of the roller(there are n-x+1 of them) find how far up we can go.
    -Use this to calculate the first number by getting the biggest height we can paint up to for every plank and subtracting the height of the plant from that number.
    -This can be done (and is pretty much required) in O(n) instead of O(n log n) using a deque(something similar to convex hull optimization)
    -For the second part of the task, there is a greedy algorithm that solves it.
    -Go from the first position we can paint for the last and keep 2 variables, the position on which we last painted the fence and the height at which we painted the fence.
    -There are 3 conditions under which we have to paint the current position:
        The height to which we can currently paint is higher than the height we last painted at,
        The distance between the last position we painted and the current is greater than of equal to x,
        The height up to which we can paint in the current position is higher than the height we can pant for the next position.

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
    int n,x;
	scanf("%i %i",&n,&x);
	vector<int> niz(n);
	for(int i=0;i<n;i++)
        scanf("%i",&niz[i]);
    vector<int> visina(n);
    deque<pair<int,int> > q;
    for(int i=0;i<x;i++)
    {
        pair<int,int> tr={niz[i],i};
        while(q.size()&&q.back().f>=tr.f)
            q.pop_back();
        q.pb(tr);
    }
    for(int i=0;i<=n-x;i++)
    {
        visina[i]=q.front().f;
        if(q.front().s==i)
            q.pop_front();
        if(i<n-x)
        {
            pair<int,int> tr={niz[i+x],i+x};
            while(q.size()&&q.back().f>=tr.f)
                q.pop_back();
            q.pb(tr);
        }
    }
    q.clear();
    ll sol=0;
    for(int i=0;i<n;i++)
    {
        if(i<=n-x)
        {
            pair<int,int> tr={visina[i],i+x};
            while(q.size()&&q.back().f<=tr.f)
                q.pop_back();
            q.pb(tr);
        }
        if(q.front().s==i)
            q.pop_front();
        sol+=niz[i]-q.front().f;
    }
    printf("%lld\n",sol);
    int cnt=0,last=0,lastvis=0;
    for(int i=0;i<=n-x;i++)
    {
        if(visina[i]>lastvis||i-last>=x||visina[i]>visina[i+1])
        {
            lastvis=visina[i];
            last=i;
            cnt++;
        }
    }
    printf("%i\n",cnt);
    return 0;
}
