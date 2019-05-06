/*
    -do dp[i][num][last][i0][i1]:
        i-current position,
        num-number of elephants we placed so far,
        i0-do we have a place to put a cat without it attacking a dot
        i1-do we have a place to put a dog without it attacking a cat
    -transitions are:
        *move the current animal somewhere else
        *if possible, leave the current animal
    -we need to use memory optimization to pass.
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

const int oo=1e4;
void test()
{
    int n;
    scanf("%i",&n);
    vector<int> niz(n);
    vector<int> safe(n);
    vector<int> num(3);
    for(int i=0;i<n;i++)
        scanf("%i",&niz[i]),num[niz[i]]++;
    if(num[0]==0||num[1]==0)
    {
        printf("0\n");
        return;
    }
    if(num[2]==0)
    {
        printf("-1\n");
        return;
    }
    num[2]++;
    vector<vector<vector<vector<vector<int> > > > > dp(2,vector<vector<vector<vector<int> > > >(2*num[2]+1,vector<vector<vector<int> > >(3,vector<vector<int> >(2,vector<int>(2,oo)))));
    int last=-1;
    for(int i=0;i<n;i++)
    {
        if(niz[i]!=2)
        {
            last=niz[i];
            continue;
        }
        if(i==n-1||niz[i+1]==2||niz[i+1]==last||last==-1)
            safe[i]=1;
    }
    for(int tr=n;tr>=0;tr--)
    {
        int now=tr%2,nxt=(tr+1)%2;
        for(int br=1;br<2*num[2];br++)
        {
            for(int last=0;last<3;last++)
            {
                for(int i0=0;i0<2;i0++)
                {
                    for(int i1=0;i1<2;i1++)
                    {
                        if(tr==n)
                        {
                            if(br==num[2]&&((i0+i1+(last==2))>1))
                                dp[now][br][last][i0][i1]=0;
                            else
                                dp[now][br][last][i0][i1]=oo;
                            continue;
                        }
                        dp[now][br][last][i0][i1]=dp[nxt][br][last][i0][i1]+1;
                        if(niz[tr]==0)
                        {
                            if(last!=1)
                                dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br][0][1][i1]);
                            dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br+1][0][1][i1]);
                        }
                        if(niz[tr]==1)
                        {
                            if(last!=0)
                                dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br][1][i0][1]);
                            dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br+1][1][i0][1]);
                        }
                        if(niz[tr]==2)
                        {
                            if(last==2)
                                dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br][2][i0][1]),dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br][2][1][i1]);
                            dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br][2][i0][i1]);
                            dp[now][br][last][i0][i1]=min(dp[now][br][last][i0][i1],dp[nxt][br-1][last][i0][i1]+1);
                        }
                    }
                }
            }
        }
    }
    printf("%i\n",dp[0][num[2]][2][0][0]);
}
int main()
{
    int t=1;
    scanf("%i",&t);
    while(t--)
    {
        test();
    }
    return 0;
}
