/*
    -We can use dp to solve the problem in O(3*number of red flowers*number of green flowers*number of yellow flowers)
    -Start from the beginning and choose what color flower to put next. Notice that its always optimal to put the closest flower of that kind.
    -This allows us to sort the flowers of each kind by position and we know that we will at any time only take the first i flowers of that kind
    -So we can form a state as follows: dp[position to which we are putting the flower][color of last flower][how many red flowers we took][same for green][same for yellow]
    -When we decide to take a flower, we need to increase the positions of all the flowers between it and the position we are putting it to by 1.
    -If we do this increment in O(n) its enough to pass the tests with N<=60.
    -Next notice that we can calculate the position that we are currently putting the flower to from the number of red,green and yellow flowers we took so far, so we can remove it.
    -Also notice that we can do some precalculation to get the number of flowers with bigger index than the one we currently want to take from the number of red,green and yellow flowers we took so far.
    -This brings our dp down to the before mentioned O(3*number of red flowers*number of green flowers*number of yellow flowers), which is enough to solve the full task.
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

vector<vector<int> > pos(3);
const int N=401,oo=INT_MAX/10;
int n;
int vecih[3][3][N][N];
vector<vector<vector<vector<int> > > > dp;
#define dp dp[color][p1][p2][p3]
int calc(int color,int p1,int p2,int p3)
{
    int tr=p1+p2+p3;
    if(color==-1)
    {
        int best=oo;
        if(p1<(int)pos[0].size())
        {
            int veci=0;
            if(p2)
                veci+=vecih[0][1][p1][p2-1];
            if(p3)
                veci+=vecih[0][2][p1][p3-1];
            int where=pos[0][p1]+veci;
            int sol=calc(0,p1+1,p2,p3)+abs(where-tr);
            best=min(best,sol);
        }
        if(p2<(int)pos[1].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[1][0][p2][p1-1];
            if(p3)
                veci+=vecih[1][2][p2][p3-1];
            int where=pos[1][p2]+veci;
            int sol=calc(1,p1,p2+1,p3)+abs(where-tr);
            best=min(best,sol);
        }
        if(p3<(int)pos[2].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[2][0][p3][p1-1];
            if(p2)
                veci+=vecih[2][1][p3][p2-1];
            int where=pos[2][p3]+veci;
            int sol=calc(2,p1,p2,p3+1)+abs(where-tr);
            best=min(best,sol);
        }
        return best;
    }
    if(tr==n)
    {
        assert(p1==pos[0].size()&&p2==pos[1].size()&&p3==pos[2].size());
        return 0;
    }
    if(dp!=-1)
        return dp;
    dp=oo;
    if(color==0)
    {
        if(p2<(int)pos[1].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[1][0][p2][p1-1];
            if(p3)
                veci+=vecih[1][2][p2][p3-1];
            int where=pos[1][p2]+veci;
            int sol=calc(1,p1,p2+1,p3)+abs(where-tr);
            dp=min(dp,sol);
        }
        if(p3<(int)pos[2].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[2][0][p3][p1-1];
            if(p2)
                veci+=vecih[2][1][p3][p2-1];
            int where=pos[2][p3]+veci;
            int sol=calc(2,p1,p2,p3+1)+abs(where-tr);
            dp=min(dp,sol);
        }
    }
    if(color==1)
    {
        if(p1<(int)pos[0].size())
        {
            int veci=0;
            if(p2)
                veci+=vecih[0][1][p1][p2-1];
            if(p3)
                veci+=vecih[0][2][p1][p3-1];
            int where=pos[0][p1]+veci;
            int sol=calc(0,p1+1,p2,p3)+abs(where-tr);
            dp=min(dp,sol);
        }
        if(p3<(int)pos[2].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[2][0][p3][p1-1];
            if(p2)
                veci+=vecih[2][1][p3][p2-1];
            int where=pos[2][p3]+veci;
            int sol=calc(2,p1,p2,p3+1)+abs(where-tr);
            dp=min(dp,sol);
        }
    }
    if(color==2)
    {
        if(p1<(int)pos[0].size())
        {
            int veci=0;
            if(p2)
                veci+=vecih[0][1][p1][p2-1];
            if(p3)
                veci+=vecih[0][2][p1][p3-1];
            int where=pos[0][p1]+veci;
            int sol=calc(0,p1+1,p2,p3)+abs(where-tr);
            dp=min(dp,sol);
        }
        if(p2<(int)pos[1].size())
        {
            int veci=0;
            if(p1)
                veci+=vecih[1][0][p2][p1-1];
            if(p3)
                veci+=vecih[1][2][p2][p3-1];
            int where=pos[1][p2]+veci;
            int sol=calc(1,p1,p2+1,p3)+abs(where-tr);
            dp=min(dp,sol);
        }
    }
    return dp;
}
#undef dp
int main()
{
	cin >> n;
	string s;
	cin >> s;
	for(int i=0;i<n;i++)
    {
        if(s[i]=='R')
            pos[0].pb(i);
        if(s[i]=='G')
            pos[1].pb(i);
        if(s[i]=='Y')
            pos[2].pb(i);
    }
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(i==j)
                continue;
            for(int k=0;k<pos[i].size();k++)
            {
                for(int l=0;l<pos[j].size();l++)
                {
                    vecih[i][j][k][l]=pos[j][l]>pos[i][k];
                    if(l)
                        vecih[i][j][k][l]+=vecih[i][j][k][l-1];
                }
            }
        }
    dp.resize(3,vector<vector<vector<int> > >(pos[0].size()+1,vector<vector<int> >(pos[1].size()+1,vector<int>(pos[2].size()+1,-1))));
    int ans=calc(-1,0,0,0);
    if(ans>=oo)
        ans=-1;
    printf("%i\n",ans);
    return 0;
}
