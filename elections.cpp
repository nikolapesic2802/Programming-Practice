#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("avx2")  //Enable AVX

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
template<class T> ostream& operator<<(ostream& os, const deque<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T,greater<T> >& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=5e5+1,L=300,M=N/L;
string s;
int uzimam[M][L+1],sum[M][L+1],mn[M][L+1],delta[M][L+1];
int cnt[M];
void init(){
    for(int o=0;o<M;o++){
        int l=o*L,r=(o+1)*L-1;
        //printf("%i-%i!\n",l,r);
        for(int i=l;i<=r;i++)
            if(s[i]=='T')
                cnt[o]++;
        int m=0,d=0;
        for(int i=r;i>=l;i--){
            if(s[i]=='T')
                d--;
            else
                d++;
            m=min(m,d);
        }
        for(int i=cnt[o];i<=L;i++){
            sum[o][i]=i+L-2*cnt[o];
            mn[o][i]=m;
            delta[o][i]=d;
        }
        for(int i=0;i<cnt[o];i++){
            vector<bool> uzet(L);
            int tr=i,cntt=0;
            for(int j=l;j<=r;j++){
                if(s[j]=='T')
                    tr--;
                else
                    tr++;
                if(tr<0)
                    uzet[j-l]=1,tr++,cntt++;
            }
            uzimam[o][i]=cntt;
            sum[o][i]=tr;
            m=0,d=0;
            for(int j=r;j>=l;j--){
                if(s[j]=='T'){
                    if(!uzet[j-l])
                        d--;
                }
                else
                    d++;
                m=min(m,d);
            }
            mn[o][i]=m;
            delta[o][i]=d;
        }
        /*for(int i=0;i<=L;i++)
            printf("%i %i: uzimam: %i sum: %i mn: %i delta: %i\n",o,i,uzimam[o][i],sum[o][i],mn[o][i],delta[o][i]);*/
    }
}
int vals[M];
bool uzetL[L],uzetR[L];
int calc(int l,int r){
    memset(uzetL,0,sizeof(uzetL));
    memset(uzetR,0,sizeof(uzetR));
    int le=l/L,ri=r/L;
    //printf("%i %i  %i %i\n",l,r,le,ri);
    if(le==ri){
        vector<bool> uzet(L);
        int tr=0,ans=0;
        for(int i=l;i<=r;i++){
            if(s[i]=='T')
                tr--;
            else
                tr++;
            if(tr<0)
                ans++,tr++,uzet[i-l]=1;
        }
        tr=0;
        for(int i=r;i>=l;i--){
            if(s[i]=='T'){
                if(!uzet[i-l])
                    tr--;
            }
            else
                tr++;
            if(tr<0)
                tr++,ans++;
        }
        return ans;
    }
    int tr=0,ans=0;
    for(int i=l;i<(le+1)*L;i++){
        if(s[i]=='T')
            tr--;
        else
            tr++;
        if(tr<0)
            ans++,tr++,uzetL[i-l]=1;
    }
    for(int i=le+1;i<ri;i++){
        vals[i]=min(L,tr);
        if(tr>=L){
            tr+=L-2*cnt[i];
        }
        else{
            ans+=uzimam[i][tr];
            tr=sum[i][tr];
        }
    }
    for(int i=ri*L;i<=r;i++){
        if(s[i]=='T')
            tr--;
        else
            tr++;
        if(tr<0)
            ans++,tr++,uzetR[r-i]=1;
    }
    tr=0;
    for(int i=r;i>=ri*L;i--){
        if(s[i]=='T'){
            if(!uzetR[r-i])
                tr--;
        }
        else
            tr++;
        if(tr<0)
            ans++,tr++;
    }
    for(int i=ri-1;i>le;i--){
        int d=-mn[i][vals[i]]-tr;
        if(d>0){
            ans+=d;
            tr+=d;
        }
        tr+=delta[i][vals[i]];
    }
    for(int i=(le+1)*L-1;i>=l;i--){
        if(s[i]=='T'){
            if(!uzetL[i-l])
                tr--;
        }
        else
            tr++;
        if(tr<0)
            ans++,tr++;
    }
    return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,q,l,r;
	cin >> n >> s >> q;
	while(s.size()!=N)
        s+='C';
    init();
    while(q--){
        cin >> l >> r;
        cout << calc(l-1,r-1) << endl;
    }
    return 0;
}
