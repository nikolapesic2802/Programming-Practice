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

//O(n^2*26),8:31
int n;
const int N=1000,L=26;
int mat[N][N];
int first[N][L][N];
int second[N][L][N];
int siz[N][L];
int same[N][L];
ll getAns1()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<L;j++)
            siz[i][j]=-1;
    ll ans=0;
    for(int i=0;i<n;i++){
        vector<int> big(L,-1);
        for(int j=0;j<n;j++){
            for(int k=0;k<L;k++){
                if(big[k]==-1)
                    continue;
                while(siz[j][k]!=-1&&second[j][k][siz[j][k]]<=big[k])
                    siz[j][k]--;
                siz[j][k]++;
                first[j][k][siz[j][k]]=i;
                second[j][k][siz[j][k]]=big[k];
            }
            if(siz[j][mat[i][j]]!=-1){
                ans+=siz[j][mat[i][j]]+1;
                if(first[j][mat[i][j]][siz[j][mat[i][j]]]==i)
                {
                    ans--;
                    if(siz[j][mat[i][j]]>0&&second[j][mat[i][j]][0]==j)
                        ans--;
                }
                else
                    if(second[j][mat[i][j]][0]==j)
                        ans--;
            }
            for(int k=0;k<=mat[i][j];k++){
                big[k]=j;
                while(siz[j][k]!=-1&&second[j][k][siz[j][k]]<=big[k])
                    siz[j][k]--;
                siz[j][k]++;
                first[j][k][siz[j][k]]=i;
                second[j][k][siz[j][k]]=big[k];
            }
        }
    }
    return ans;
}
ll getAns2()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<L;j++)
            siz[i][j]=-1;
    ll ans=0;
    for(int i=0;i<n;i++){
        vector<int> big(L,-1);
        for(int j=0;j<n;j++){
            for(int k=0;k<L;k++){
                if(big[k]==-1)
                    continue;
                while(siz[j][k]!=-1&&second[j][k][siz[j][k]]<=big[k]){
                    if(mat[first[j][k][siz[j][k]]][second[j][k][siz[j][k]]]==k)
                        same[j][k]--;
                    siz[j][k]--;
                }
                if(mat[i][big[k]]==k)
                   same[j][k]++;
                siz[j][k]++;
                first[j][k][siz[j][k]]=i;
                second[j][k][siz[j][k]]=big[k];

            }
            if(siz[j][mat[i][j]]!=-1){
                ans+=siz[j][mat[i][j]]+1-same[j][mat[i][j]];
                if(first[j][mat[i][j]][siz[j][mat[i][j]]]==i)
                {
                    ans--;
                    if(mat[first[j][mat[i][j]][siz[j][mat[i][j]]]][second[j][mat[i][j]][siz[j][mat[i][j]]]]==mat[i][j])
                        ans++;
                    if(siz[j][mat[i][j]]>0&&second[j][mat[i][j]][0]==j){
                        if(mat[first[j][mat[i][j]][0]][second[j][mat[i][j]][0]]==mat[i][j])
                            ans++;
                        ans--;
                    }
                }
                else
                    if(second[j][mat[i][j]][0]==j){
                        if(mat[first[j][mat[i][j]][0]][second[j][mat[i][j]][0]]==mat[i][j])
                            ans++;
                        ans--;
                    }
            }
            for(int k=0;k<=mat[i][j];k++){
                big[k]=j;
                while(siz[j][k]!=-1&&second[j][k][siz[j][k]]<=big[k]){
                    if(mat[first[j][k][siz[j][k]]][second[j][k][siz[j][k]]]==k)
                        same[j][k]--;
                    siz[j][k]--;
                }
                if(mat[i][big[k]]==k)
                   same[j][k]++;
                siz[j][k]++;
                first[j][k][siz[j][k]]=i;
                second[j][k][siz[j][k]]=big[k];
            }
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    freopen("ssdj.in","r",stdin);
    freopen("ssdj.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    vector<string> ss(n);
    for(int i=0;i<n;i++)
        cin >> ss[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[i][j]=ss[i][j]-'a';
    ll ans=getAns1();
    ss.clear();
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mat[n-1-i][n-1-j]=ss[i][j]-'a';
    cout << ans+getAns2();
    return 0;
}
