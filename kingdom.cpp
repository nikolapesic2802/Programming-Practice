/*
    -Do an algorithm that has complexity O(2^n * n) but we can speed it up and use less memory than 2^n.
    -For the memory part, we will do the following trick: we won't put cities 0 and 1 in our initial mask, and we will put them in later.
    -Calculate for each of the 2^(n-2) masks, the number of edges between cities in that mask.
    -This can be done in O(number of cities in a mask) by taking the first city in a mask, taking the value of the mask without this city (which we previously calculated) and then for each other city in the mask add 1 if there is an edge between the first city and that city.
    -Now we consider the case where cities 0 and 1 are not in the same kingdom, for this we will go through all the masks that have n/2-1 cities in them, and first add cnt[mask] and cnt[inverse of mask] to the edge count.
     and for each city that is in the mask, we will add 1 if that city is connected to city 0 and for each city that is not in the mask, we will add to the edge count if that city is connected to city 1. Now our answer is m-edge_count.
    -For the case where cities 0 and 1 are in the same component, we will go through all the masks that have n/2-2 cities, and for each city in the mask add 1 if its connected to city 0 and the same for city 1.
     !!Don't forget to also add 1 if cities 0 and 1 are connected!!
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
#define ld long double

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,m,a,b;
    scanf("%i %i",&n,&m);
    if(n==2) return 0*printf("1\n");
    bool grana[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            grana[i][j]=0;
    int lim=1<<(n-2);
    char cnt[lim],lg[lim/2+1];
    for(int i=0;i<m;i++)
        scanf("%i %i",&a,&b),a--,b--,grana[a][b]=grana[b][a]=1;
    for(int i=0,tr=1;i<n-2;i++,tr*=2)
        lg[tr]=i+2;
    cnt[0]=0;
    for(int mask=0;mask<lim;mask++){
        int c=__builtin_popcount(mask);
        if(c>n/2)
            continue;
        int l=mask&(-mask);
        int ms=mask^l;
        cnt[mask]=cnt[mask^l];
        l=lg[l];
        for(int i=1;i<c;i++){
            cnt[mask]+=grana[l][lg[ms&-ms]];
            ms^=ms&-ms;
        }
    }
    int ans=m,msk;
    for(int mask=0;mask<lim;mask++){
        int c=__builtin_popcount(mask);
        if(c==n/2-1){
            int my=cnt[mask]+cnt[(lim-1)^mask];
            for(int i=0;i<n-2;i++)
                if(mask&(1<<i))
                    my+=grana[0][i+2];
                else
                    my+=grana[1][i+2];
            my=m-my;
            if(my<ans)
                ans=my,msk=mask*4+1;
        }
        if(c==n/2-2){
            int my=cnt[mask]+cnt[(lim-1)^mask]+grana[0][1],ms=mask;
            for(int i=0;i<c;i++){
                my+=grana[0][lg[ms&-ms]]+grana[1][lg[ms&-ms]];
                ms^=ms&-ms;
            }
            my=m-my;
            if(my<ans)
                ans=my,msk=mask*4+3;
        }
    }
    for(int i=0;i<n;i++)
        if((1<<i)&msk)
            printf("%i ",i+1);
    return 0;
}
