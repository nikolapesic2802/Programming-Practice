/*
    -Do dp[i][j],i-what position im on, j-how much i have left to collect.
    -We will only consider 5 digits in front of us as we can not get over sum of j.
    -Need to be a little careful not to take only zeros if that is not the end.
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

string a;
int s,n;
vector<pair<int,int> > digits;
vector<string> solution;
bool solve(int pos,int ostalo)
{
    if(pos==n)
        return ostalo==0;
    int tr=a[pos]-'0';
    string trsol;
    trsol+=a[pos];
    while(true)
    {
        if(tr!=0||pos==n-1)
        {
            if(solve(pos+1,ostalo-tr))
            {
                solution.pb(trsol);
                return true;
            }
        }
        pos++;
        if(pos>=n)
            return false;
        trsol+=a[pos];
        tr=tr*10+a[pos]-'0';
        if(tr>ostalo)
            return false;
    }
}
int main()
{
    //freopen("jednakost.in.10","r",stdin);
	cin >> a;
	int gde=0;
	for(int i=0;i<(int)a.size();i++)
        if(a[i]=='=')
            gde=i;
    for(int i=gde+1;i<(int)a.size();i++)
        s=s*10+a[i]-'0';
    a=a.substr(0,gde);
    n=a.size();
    assert(solve(0,s));
    reverse(all(solution));
    int cnt=0;
    string ss;
    for(int i=0;i<(int)solution.size();i++)
    {
        ss=ss+solution[i];
        cout << solution[i];
        cnt+=stoi(solution[i]);
        if(i!=(int)solution.size()-1)
            cout << "+";
        else
            cout << "=" << s << endl;
    }
    assert(ss==a);
    assert(cnt==s);
    //printf("%i %i\n",cnt,s);
    return 0;
}
