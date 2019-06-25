/*
    -We can go from the highest value to the lowest and do the following:
    -If the current and the next value is positive, reduce them and increase the value two steps ahead of the current, continue the algorithm from the values two steps ahead.
    -If the current and the previous value is positive, reduce them and increase the next value, continue the algorithm from the next value.
    -If the current values is greater than two, reduce it by two and increase the value 2 steps before and the next value, continue the algorithm with the next value.
    -Otherwise continue the algorithm from the previous value.
    -Recursive implementation gets TLE but iterative passes barely.
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

const int N=1e6+5;
vector<int> cnt(N);
int main()
{
    for(int i=0;i<2;i++)
    {
        int n,a;
        scanf("%i",&n);
        for(int j=0;j<n;j++)
            scanf("%i",&a),cnt[j]+=a;
    }
    int i=N-1;
    while(i!=-1)
    {
        if(i==0)
        {
            if(cnt[i]>1){
                cnt[i]-=2;
                cnt[i+1]++;
                i++;
                continue;
            }
            else
                break;
        }
        if(cnt[i]&&cnt[i-1]){
            cnt[i]--;
            cnt[i-1]--;
            cnt[i+1]++;
            i++;
            continue;
        }
        if(cnt[i]&&cnt[i+1]){
            cnt[i]--;
            cnt[i+1]--;
            cnt[i+2]++;
            i+=2;
            continue;
        }
        if(cnt[i]>1)
        {
            cnt[i]-=2;
            cnt[i+1]++;
            cnt[max(0,i-2)]++;
            i++;
            continue;
        }
        i--;
    }
    int last=0;
    for(int i=0;i<N;i++)
        if(cnt[i])
            last=i;
    printf("%i ",last+1);
    for(int i=0;i<=last;i++)
        printf("%i ",cnt[i]);
    return 0;
}
