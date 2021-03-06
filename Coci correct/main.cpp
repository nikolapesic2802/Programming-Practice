/*
    -First simulate the game for A, and then simulate it for the 2 spots next to A in the backwards direction.
    Solutions that simulate the whole game using data structures and fail on time:
    -Treap: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Coci%20kolo%20Treap/main.cpp (85/100 points)
    -Splay tree: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Coci%20Kolo/main.cpp (50/100 points)
    -Using the built-in Rope: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Coci%20Kolo%20Rope/main.cpp (75/100 points)
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
vector<int> primes;
const int N=1e7;
vector<bool> visited(N);
int n,k,a;
int forward(int x)
{
    for(int i=0;i<k;i++)
    {
        int p=primes[i];
        if(x==0)
            x=p%n;
        else
        {
            x=(x-(p/n)%(n-1)+n-2)%(n-1);
            if(x>=p%n)
                x++;
        }
    }
    return x;
}
int backward(int x)
{
    for(int i=k-1;i>=0;i--)
    {
        int p=primes[i];
        if(x==p%n)
            x=0;
        else
        {
            if(x>p%n)
                x--;
            x=(x+(p/n)%(n-1))%(n-1);
            x++;
        }
    }
    return x;
}
int main()
{
    scanf("%i %i %i",&n,&k,&a);
	for(int i=2;i<N;i++)
    {
        if(!visited[i])
            primes.pb(i);
        if((int)primes.size()==k)
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
    a=forward(a-1);
    printf("%i %i\n",backward((a+1)%n)+1,backward((a-1+n)%n)+1);
    return 0;
}
