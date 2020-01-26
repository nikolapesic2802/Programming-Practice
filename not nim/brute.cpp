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

int n;
map<pair<vector<int>,int>,int> dp;
int brute(vector<int> a,int player){
    //cout << a << player << endl;
    bool kraj=true;
    for(int i=0;i<n&&kraj;i++)
        if(a[i]!=0)
            kraj=0;
    if(kraj)
        return 0;
    if(dp.find({a,player})!=dp.end())
        return dp[{a,player}];
    if(player==0){
        int sol=INT_MAX,bacc;
        for(int i=0;i<n;i++)
            if(a[i]!=0)
                bacc=a[i],a[i]=0,sol=min(sol,brute(a,1)+1),a[i]=bacc;
        return dp[{a,player}]=sol;
    }
    int sol=0;
    for(int i=0;i<n;i+=2){
        if(a[i]+a[i+1]>1&&(a[i]==0||a[i+1]==0)){
            for(int k=1;k<=a[i];k++){
                a[i]-=k;
                a[i+1]+=k;
                sol=max(sol,brute(a,0)+1);
                a[i]+=k;
                a[i+1]-=k;
            }
            for(int k=1;k<=a[i+1];k++){
                a[i]+=k;
                a[i+1]-=k;
                sol=max(sol,brute(a,0)+1);
                a[i]-=k;
                a[i+1]+=k;
            }
            return dp[{a,player}]=sol;
        }
    }
    for(int i=0;i<n;i+=2){
        if(a[i]!=0||a[i+1]!=0){
            for(int k=1;k<=a[i];k++){
                a[i]-=k;
                a[i+1]+=k;
                sol=max(sol,brute(a,0)+1);
                a[i]+=k;
                a[i+1]-=k;
            }
            for(int k=1;k<=a[i+1];k++){
                a[i]+=k;
                a[i+1]-=k;
                sol=max(sol,brute(a,0)+1);
                a[i]-=k;
                a[i+1]+=k;
            }
        }
    }
    return dp[{a,player}]=sol;
}
void print(vector<int> a,int player){
    cout << a << player << endl;
    vector<int> moj=a;
    bool kraj=true;
    for(int i=0;i<n&&kraj;i++)
        if(a[i]!=0)
            kraj=0;
    if(kraj)
        return;
    if(player==0)
        for(int i=0;i<n;i++)
            if(a[i]!=0){
                a[i]=0;
                if(dp[{a,1}]+1==dp[{moj,0}]){
                    print(a,1);
                    return;
                }
                a=moj;
            }
    for(int i=0;i<n;i+=2){
        if(a[i]!=0||a[i+1]!=0){
            for(int k=1;k<=a[i];k++){
                a[i]-=k;
                a[i+1]+=k;
                if(dp[{a,0}]+1==dp[{moj,1}]){
                    print(a,0);
                    return;
                }
                a[i]+=k;
                a[i+1]-=k;
            }
            for(int k=1;k<=a[i+1];k++){
                a[i]+=k;
                a[i+1]-=k;
                if(dp[{a,0}]+1==dp[{moj,1}]){
                    print(a,0);
                    return;
                }
                a[i]-=k;
                a[i+1]+=k;
            }
        }
    }
}
bool ok(int tr){
    int d=4;
    while(d<=tr)
        d*=2;
    int dist=d-tr-1;
    if(dist<d/4)
        return 0;
    return 1;
}
void test(){
    int n=3000;
    int sol=n;
    for(int i=1;i<=n;i++){
        int tr=i;
        while(tr)
            sol++,tr/=2;
        sol-=ok(i);
    }
    printf("%i!\n",2*sol-1);
    //printf("%i- %i\n",2*sol-1,2*(sol-n+1)-1);
}
int main()
{
    //freopen("in.txt","r",stdin);
	//freopen("br.txt","w",stdout);
    /*int a;
    scanf("%i",&n);
    vector<int> v;
    for(int i=0;i<n;i++)
        scanf("%i",&a),v.pb(a),v.pb(a);
    n*=2;
    printf("%i\n",brute(v,0));
    return 0;
    test();*/
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int l=2;
	while(true){
        dp.clear();
        n=l++;
        //printf("%i!\n",n);
        scanf("%i",&n);
        //n=3000;
        vector<int> v;
        v.pb(1);v.pb(0);v.pb(n);v.pb(n);v.pb(n);v.pb(n);v.pb(n);v.pb(n);
        /*for(int i=0;i<n;i++){
            int b;
            b=i+1;
            scanf("%i",&b);
            v.pb(b);
            v.pb(b);
        }*/
        int cnt=1;
        int tr=n;
        while(tr)
            cnt++,tr/=2;
        cnt=3*cnt-2;
        n*=2;
        n=8;
        /*int oo=brute(v,0);
        if(oo!=2*cnt-1){
            printf("%i!\n",l-1);
            //print(v,0);
        }*/
        printf("%i %i\n",2*cnt-1,brute(v,0));
        print(v,0);
	}
    return 0;
}
