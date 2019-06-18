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

const int M=3e4+5,NN=1e6;
vector<int> ima(M,-1);
int m,l,n;
gp_hash_table<int,int> dp[M];
int cnt=0;
int calc(int pos,int uzeo)
{
    if(uzeo==n||pos>m-l)
        return 0;
    if(dp[pos].find(uzeo)!=dp[pos].end())
        return dp[pos][uzeo];
    cnt++;
    if(cnt>NN)
    {
        if(ima[pos]!=-1)
            return 2+calc(pos+l,uzeo+1);
        return max(calc(pos+1,uzeo),1+calc(pos+l,uzeo+1));
    }
    if(ima[pos]!=-1)
        return dp[pos][uzeo]=2+calc(pos+l,uzeo+1);
    return dp[pos][uzeo]=max(calc(pos+1,uzeo),1+calc(pos+l,uzeo+1));
}
int main()
{
    scanf("%i %i %i",&m,&l,&n);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        a--;
        ima[a]=i;
    }
    printf("%i\n",calc(0,0));
    printf("%i\n",cnt);
    int x=0,y=0;
    vector<int> preostala;
    vector<bool> uzeo(n);
    vector<pair<int,int> > sol;
    while(x<=m-l&&y<n)
    {
        if(ima[x]!=-1)
        {
            sol.pb({x,ima[x]});
            uzeo[ima[x]]=1;
            x+=l;y++;
            continue;
        }

        int a=dp[x+1][y],b=1+dp[x+l][y+1];
        if(a>b)
        {
            x++;
        }
        else
        {
            preostala.pb(x);
            x+=l;
            y++;
        }
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
    /*printf("%i\n",sol.size());
    for(auto p:sol)
        printf("%i %i\n",p.s+1,p.f+1);*/
    return 0;
}
