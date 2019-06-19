/*
    -Do dp[i][j] where i is the number of people you assigned tickets so far and j is the position.
    -We can notice that if there is someone that wants the seats starting at the current position, its always optimal to give them the seats.
    -This reduces the states we visit to about 3e6 (from all the official tests) in the worst case allowing us to do this dp.
    -If we did the dp recursively we would need to store all the solutions in a map which would cause memory limit.
    -We need to do this dp iteratively and save memory that way.
    -This is not the intended complexity and it probably wouldn't pass the tests in 2005.
    -This solution wouldn't pass for N=M=3e4,L=1 and all positions are 1.
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

const int M=3e4+5;
vector<int> ima(M,-1);
int m,l,n;
void solve()
{
    vector<priority_queue<int,vector<int>,greater<int> > > states(M);
    vector<vector<int> > order(M);
    vector<vector<bool> > nxt(M);
    states[0].push(0);
    for(int i=0;i<M;i++)
    {
        while(states[i].size())
        {
            int pos=states[i].top();
            states[i].pop();
            while(states[i].size()&&states[i].top()==pos)
                states[i].pop();
            order[i].pb(pos);
            if(i==n||pos>m-l)
                continue;
            if(ima[pos]!=-1)
            {
                states[i+1].push(pos+l);
                continue;
            }
            states[i].push(pos+1);
            states[i+1].push(pos+l);
        }
    }
    vector<vector<int> > val(2,vector<int>(M));
    for(int i=M-1;i>=0;i--)
    {
        for(int j=order[i].size()-1;j>=0;j--)
        {
            int pos=order[i][j];
            if(i==n||pos>m-l)
            {
                val[i&1][pos]=0;
                nxt[i].pb(0);
                continue;
            }
            if(ima[pos]!=-1)
            {
                val[i&1][pos]=2+val[(i+1)&1][pos+l];
                nxt[i].pb(0);
                continue;
            }
            int a=val[i&1][pos+1],b=1+val[(i+1)&1][pos+l];
            val[i&1][pos]=max(a,b);
            if(a<=b)
                nxt[i].pb(1);
            else
                nxt[i].pb(0);
        }
    }
    printf("%i ",val[0][0]);
    int x=0,y=0;
    vector<int> preostala;
    vector<bool> uzeo(n);
    vector<pair<int,int> > sol;
    int i=-1,j=-1,last=-1;
    while(true)
    {
        if(x!=last)
            i=0,j=nxt[x].size()-1,last=x;
        if(x==n||y>m-l)
            break;
        while(order[x][i]!=y)
            i++,j--;
        if(ima[y]!=-1)
        {
            sol.pb({y,ima[y]});
            uzeo[ima[y]]=1;
            y+=l;
            x++;
            continue;
        }
        if(nxt[x][j])
        {
            preostala.pb(y);
            y+=l;
            x++;
        }
        else
            y++;
    }
    for(int i=0;i<n;i++)
    {
        if(preostala.size()==0)
            break;
        if(!uzeo[i])
        {
            sol.pb({preostala.back(),i});
            preostala.pop_back();
        }
    }
    sort(all(sol));
    printf("%i\n",sol.size());
    for(auto p:sol)
        printf("%i %i\n",p.s+1,p.f+1);
}
int main()
{
    freopen("in.txt","r",stdin);
    scanf("%i %i %i",&m,&l,&n);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        a--;
        ima[a]=i;
    }
    solve();
    return 0;
}
