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
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int L=10,M=5,mod=10039;
vector<vector<int> > sequences;
vector<int> seq,ways,fact,sums;
void gen(int last,int n)
{
    if(n==M){
        sequences.pb(seq);
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
    if(row[0]<2||col[0]<2) ///Must have a two, its logical that the best place to put it at the place where the biggest sums are :D (Might be wrong lol)
        return false;
    row[0]-=2;
    col[0]-=2;
    priority_queue<pair<int,int> > columns;
    //multiset<pair<int,int>,greater<pair<int,int> > > columns;
    for(int i=0;i<M;i++)
        if(i==0)
            columns.push({col[i],2});
        else
            columns.push({col[i],0});
    for(int i=0;i<M;i++)
    {
        priority_queue<pair<int,int> > newSet;
        while(row[i]!=0)
        {
            while(columns.size()&&columns.top().s==2)
                newSet.push({columns.top().f,0}),columns.pop();
            if(columns.empty())
                return false;
            pair<int,int> tr=columns.top();
            columns.pop();
            tr.f--;
            tr.s++;
            row[i]--;
            columns.push(tr);
        }
        while(columns.size())
            newSet.push({columns.top().f,0}),columns.pop();
        columns=newSet;
    }
    return true;
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
    sequences.pb({6,5,5,5,5});
    sums.pb(10);
    printf("%i\n",check(0,0));
    return 0;
    fact.pb(1);
    for(int i=1;i<=M;i++)
        fact.pb(fact.back()*i);
	gen(L,0);
	n=sequences.size();
	sums.resize(n);
	ways.resize(n,fact[5]);
	calcWays();
	ll ans=0;
	for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(check(i,j))
                ans+=ways[i]*ways[j];
    printf("Answer:%lld  Answer under modulo:%i\n",ans,ans%mod);
    return 0;
}
