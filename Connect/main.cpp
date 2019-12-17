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

const int N=25,M=504;
vector<string> mat(N);
vector<int> dx={1,-1,0,0},dy={0,0,1,-1};
vector<vector<int> > graf(M);
int getNum(int x,int y){
    return (x/2)*42+(y/2);
}
pair<int,int> getField(int tr){
    return {tr/42,tr%42};
}
int main()
{
    //freopen("in.txt","r",stdin);
	int n,m,cnt=0;
	scanf("%i %i\n",&n,&m);
	for(int i=0;i<n;i++)
        getline(cin,mat[i]);
    for(int i=0;i<n;i++)
        cout << mat[i] << endl;
    for(int i=1;i<n;i+=2)
        for(int j=1;j<m;j+=2){
            for(int k=0;k<4;k++){
                int x=i+dx[k],y=j+dy[k];
                if(mat[x][y]==' ')
                    graf[getNum(i,j)].pb(getNum(x+dx[k],y+dy[k]));
            }
            if(mat[i][j]=='X')
                cnt++;
        }
    assert(cnt<300);
    printf("%i\n",cnt);
    return 0;
}
