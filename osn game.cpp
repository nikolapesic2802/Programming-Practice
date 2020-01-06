/*
    -For R=0, we can ask 1 2 3 ... n-1 n n n-1 ... 2 1. After that, until we get 2 hits, just ask 1 (or any other number). When we get 2 hits, we can uniquely determine what the bomb is. So just print that number until we get n hits.
    -For R=1, we change our strategy a little bit: ask 1 2 3 ... n/2-1 n/2 n/2 n/2-1 ... 2 1.
        if(we get a hit){
            ask 1 until we have 2 hits, determine what the number is, and ask it until we get n hits;
        }else{
            ask n/2+1 n/2+2 ... n-1 n.

            if(we get 2 hits){
                //This means that the answer is somewhere in [1,n/2] and k is pretty big.
                This means that we can uniquely determine what the number is, and ask it until we get n hits;
            }else{
                ask n n-1 ... n/2+2 n/2+1 but make sure to stop if we get 2 hits.
                if(we got 2 hits){
                    This means that we can uniquely determine what the number is, and ask it until we get n hits;
                }else{
                    ask 1 until we have 2 hits, determine what the number is, and ask it until we get n hits;
                }
            }
        }
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

bool ask(int i){
    printf("%i\n",i);
    string s;
    cin >> s;
    return s[0]=='B';
}
int n;
void solve(){
    vector<int> boom;
    vector<int> guess(5*n);
    int tr=0;
    for(int i=0;i<n/2;i++){
        if(ask(i+1))
            boom.pb(tr);
        guess[tr++]=i+1;
    }
    for(int i=0;i<n/2;i++){
        if(ask(n/2-i))
            boom.pb(tr);
        guess[tr++]=n/2-i;
    }
    if(!boom.empty()){
        while(boom.size()<2){
            if(ask(1))
                boom.pb(tr);
            guess[tr++]=0;
        }
        int cnt=0,gde;
        for(int k=0;k<n;k++){
            int pos1=boom[0]-k,pos2=boom[1]-k;
            if(pos1>=0&&pos2>=0&&guess[pos1]==guess[pos2]&&guess[pos1]!=0)
                cnt++,gde=guess[pos1];
        }
        assert(cnt==1);
        while(boom.size()<n){
            if(ask(gde))
                boom.pb(0);
        }
        return;
    }
    for(int i=n/2;i<n;i++){
        if(ask(i+1))
            boom.pb(tr);
        guess[tr++]=i+1;
    }
    if(boom.size()==2){
        int cnt=0,gde;
        for(int k=0;k<n;k++){
            int pos1=boom[0]-k,pos2=boom[1]-k;
            if(pos1>=0&&pos2>=0&&guess[pos1]==guess[pos2]&&guess[pos1]!=0)
                cnt++,gde=guess[pos1];
        }
        assert(cnt==1);
        while(boom.size()<n){
            if(ask(gde))
                boom.pb(0);
        }
        return;
    }
    for(int i=n;i>n/2&&boom.size()<2;i--){
        if(ask(i))
            boom.pb(tr);
        guess[tr++]=i;
    }
    while(boom.size()<2){
        if(ask(1))
            boom.pb(tr);
        guess[tr++]=0;
    }
    int cnt=0,gde;
    for(int k=0;k<n;k++){
        int pos1=boom[0]-k,pos2=boom[1]-k;
        if(pos1>=0&&pos2>=0&&guess[pos1]==guess[pos2]&&guess[pos1]!=0)
            cnt++,gde=guess[pos1];
    }
    assert(cnt==1);
    while(boom.size()<n){
        if(ask(gde))
            boom.pb(0);
    }
    return;
}
int main()
{
    string s;
    cin >> s;
    int t,r;
    scanf("%i %i %i",&n,&t,&r);
    solve();
    return 0;
}
