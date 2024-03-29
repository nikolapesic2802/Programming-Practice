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

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int main()
{
	string s;
	cin >> s;
	int p1=-1;
	int n=s.size();
	for(int i=0;i<n;i++)
    {
        if(s[i]=='[')
        {
            p1=i;
            break;
        }
    }
    if(p1==-1)
    {
        printf("-1\n");
        return 0;
    }
    int p2=-1;
    for(int i=p1+1;i<n;i++)
    {
        if(s[i]==':')
        {
            p2=i;
            break;
        }
    }
    if(p2==-1)
    {
        printf("-1\n");
        return 0;
    }
    int p3=-1;
    for(int i=n-1;i>p2;i--)
    {
        if(s[i]==']')
        {
            p3=i;
            break;
        }
    }
    if(p3==-1)
    {
        printf("-1\n");
        return 0;
    }
    int p4=-1;
    for(int i=p3-1;i>p2;i--)
    {
        if(s[i]==':')
        {
            p4=i;
            break;
        }
    }
    if(p4==-1)
    {
        printf("-1\n");
        return 0;
    }
    int cnt=0;
    for(int i=p2;i<p4;i++)
    {
        if(s[i]=='|')
            cnt++;
    }
    printf("%i\n",cnt+4);
    return 0;
}
