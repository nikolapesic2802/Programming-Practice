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

const int N=401;
vector<vector<pair<int,int> > > in(N),out(N);
int dp[N][N][27],n,m,oo=INT_MAX/2;
#define dp dp[a][b][c]
int calc(int a,int b,int c){
    if(a==b)
        return 0;
    if(dp!=-1)
        return dp;
    dp=oo;
    if(c==26)
        for(auto p:out[a])
            dp=min(dp,calc(p.f,b,p.s)+1);
    else
        for(auto p:in[b])
            if(p.s==c)
                dp=min(dp,calc(a,p.f,26)+1);
    return dp;
}

deque<char> str;
void gen(int a,int b,int c){
    if(a==b)
        return;
    if(c==26){
        for(auto p:out[a])
            if(dp==calc(p.f,b,p.s)+1){
                gen(p.f,b,p.s);
                str.push_front(p.s+'a');
                break;
            }
    }
    else
        for(auto p:in[b]){
            if(p.s==c&&dp==calc(a,p.f,26)+1){
                gen(a,p.f,26);
                str.push_back(p.s+'a');
                break;
            }
        }
}
#undef dp
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    memset(dp,-1,sizeof(dp));
    scanf("%i %i",&n,&m);
    for(int i=0;i<m;i++){
        int a,b;
        char c;
        scanf("%i %i %c",&a,&b,&c);
        out[a].pb({b,c-'a'});
        in[b].pb({a,c-'a'});
    }
    int d;
    scanf("%i",&d);
    vector<int> a(d);
    for(int i=0;i<d;i++)
        scanf("%i",&a[i]);
    for(int i=1;i<d;i++){
        int tr=calc(a[i-1],a[i],26);
        if(tr>=oo)
            printf("-1\n");
        else{
            printf("%i ",tr);
            str.clear();
            gen(a[i-1],a[i],26);
            for(auto p:str)
                printf("%c",p);
            printf("\n");
        }
    }
    return 0;
}
