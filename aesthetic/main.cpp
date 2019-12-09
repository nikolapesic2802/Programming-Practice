/*
    -dp[i][j]-Minimum possible coefficient of aestheticism when we still need to use words [i - n] and the last line was words [j - (i-1)].
    -We can speed up the transition with prefix/suffix max and some clever length manipulation.
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

const int N=2e3+5;
int m,n,oo=INT_MAX/2,ans=oo;
vector<int> a;
int getLen(int l,int r){
    if(r<0)
        return 0;
    int ans=a[r]+r-l;
    if(l)
        ans-=a[l-1];
    return ans;
}
int main()
{
	scanf("%i %i",&m,&n);
	a.resize(n);
	for(int i=0;i<n;i++)
        scanf("%i",&a[i]);
    for(int i=1;i<n;i++)
        a[i]+=a[i-1];
    if(getLen(0,n-1)<=m)
        return 0*printf("0\n");
	vector<vector<int> > dp(n+1,vector<int>(n+1,oo));
	for(int i=0;i<=n;i++)
        dp[n][i]=0;
	for(int i=n-1;i>=0;i--){
        vector<int> lens;
        for(int j=i+1;j<=n&&getLen(i,j-1)<=m;j++)
            lens.pb(getLen(i,j-1));
        int k=lens.size();
        vector<int> add(k),sub(k);
        for(int j=0;j<k;j++)
            add[j]=dp[j+i+1][i]+lens[j],sub[j]=dp[j+i+1][i]-lens[j];
        for(int j=1;j<k;j++)
            sub[j]=min(sub[j-1],sub[j]);
        for(int j=k-2;j>=0;j--)
            add[j]=min(add[j+1],add[j]);
        lens.pb(oo);
        int sl=0;
        for(int j=i-1;j>=0&&getLen(j,i-1)<=m;j--)
        {
            int len=getLen(j,i-1);
            while(lens[sl]<len)
                sl++;
            dp[i][j]=oo;
            if(sl)
                dp[i][j]=min(dp[i][j],sub[sl-1]+len);
            if(sl<k)
                dp[i][j]=min(dp[i][j],add[sl]-len);
            if(j==0)
                ans=min(ans,dp[i][j]);
        }
	}
	printf("%i\n",ans);
    return 0;
}
