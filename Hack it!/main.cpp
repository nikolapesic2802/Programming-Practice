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

const int L=10,M=5,mod=10039;
vector<vector<int> > sequences;
vector<int> seq,ways,fact,sums;
void gen(int last,int n)
{
    if(n==M){
        sequences.pb(seq);
        //cout << seq << endl;
        return;
    }
    for(int i=last;i>=0;i--){
        seq.pb(i);
        gen(i,n+1);
        seq.pop_back();
    }
}
bool check(int x,int y)
{
    if(sums[x]!=sums[y])    ///Saves a little bit of time 1250 ms -> 1000ms
        return false;
    vector<int> row=sequences[x],col=sequences[y];
    bool hasTwo=false;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<M;j++)
        {
            int m=min({2,row[i],col[j]});
            row[i]-=m;
            col[j]-=m;
            if(m==2)
                hasTwo=true;
        }
        if(row[i]!=0)
            break;
    }
    for(auto p:row)
        if(p!=0)
            hasTwo=false;
    for(auto p:col)
        if(p!=0)
            hasTwo=false;
    return hasTwo;
}
int n;
void calcWays()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<M;j++)
            sums[i]+=sequences[i][j];
        vector<int> same={1};
        for(int j=1;j<M;j++)
            if(sequences[i][j]==sequences[i][j-1])
                same.back()++;
            else
                same.pb(1);
        for(auto p:same)
            ways[i]/=fact[p];
    }
}
int main()
{
    fact.pb(1);
    for(int i=1;i<=M;i++)
        fact.pb(fact.back()*i);
	gen(L,0);
	n=sequences.size();
	sums.resize(n);
	ways.resize(n,fact[5]);
	calcWays();
	ll ans=0,cnt=0;
	for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(check(i,j))
                ans+=ways[i]*ways[j],cnt++;
    ans/=2; ///maybe
    printf("Answer:%lld  Answer under modulo:%i\n",ans,ans%mod);
    return 0;
}
