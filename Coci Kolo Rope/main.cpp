#include <iostream>
#include <cstdio>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_cxx; //namespace with rope and some additional stuff
int main()
{
    ios_base::sync_with_stdio(false);
    rope <int> v; //use as usual STL container
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        v.push_back(i); //initialization
    int l, r;
    for(int i = 0; i < m; ++i)
    {
        cin >> l >> r;
        --l, --r;
        rope <int> cur = v.substr(l, r - l + 1);
        v.erase(l, r - l + 1);
        v.insert(v.mutable_begin(), cur);
    }
    for(rope <int>::iterator it = v.mutable_begin(); it != v.mutable_end(); ++it)
        cout << *it << " ";
    return 0;
}
/*#include <bits/stdc++.h>
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
vector<int> primes;
const int N=1e7;
vector<bool> visited(N);
int main()
{
    int n,k,a;
    scanf("%i %i %i",&n,&k,&a);
	for(int i=2;i<N;i++)
    {
        if(!visited[i])
            primes.pb(i);
        if(primes.size()==k)
            break;
        for(auto p:primes)
        {
            if(i*p>=N)
                break;
            visited[p*i]=1;
            if(i%p==0)
                break;
        }
    }
    visited.resize(0);
    rope<int> v;
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=0;i<k;i++)
    {
        rope<int> yes=v.substr(0,1);
        v.erase(0,1);
        int gde=primes[i]%n;
        int times=(primes[i]/n)%(n-1);
        if(times)
        {
            rope<int> sp=v.substr(0,times);
            v.erase(0,times);
            v.insert(v.mutable_end(),sp);
        }
        if(gde)
        {
            rope<int> st=v.substr(0,gde);
            v.erase(0,gde);
            v.insert(v.mutable_begin(),yes);
            v.insert(v.mutable_begin(),st);
        }
        else
            v.insert(v.mutable_begin(),yes);
    }
    if(v[0]==a)
    {
        printf("%i %i\n",v[1],v[n-1]);
        return 0;
    }
    if(v[n-1]==a)
    {
        printf("%i %i\n",v[0],v[n-2]);
        return 0;
    }
    for(int i=1;i<v.size()-1;i++)
    {
        if(v[i]==a)
        {
            printf("%i %i\n",v[i+1],v[i-1]);
            return 0;
        }
    }
    return 0;
}*/
