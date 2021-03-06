// -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2006/editorial.pdf
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

const int N=25,NN=12,C=39,oo=INT_MAX/N/C;
vector<string> mat(N);
int dp[NN][C][1<<NN][2],n,m;
#define dp dp[r][c][msk][last]
int calc(int r,int c,int msk,int last){
    if(r==n/2)
        r=0,c++;
    if(c==m/2)
        return 0;
    if(dp!=-1)
        return dp;
    int i=2*r+1,j=2*c+1;
    if(mat[i][j]=='X'){
        if(msk&(1<<r)){
            if(last)
                return dp=oo;
            return dp=calc(r+1,c,msk^(1<<r),0);
        }
        if(last)
            return dp=calc(r+1,c,msk,0);
        dp=oo;
        if(mat[i+1][j]==' ')
            dp=min(dp,calc(r+1,c,msk,1)+1);
        if(mat[i][j+1]==' ')
            dp=min(dp,calc(r+1,c,msk^(1<<r),0)+1);
        return dp;
    }
    if(msk&(1<<r)){
        if(last)
            return dp=calc(r+1,c,msk^(1<<r),0)+1;
        dp=oo;
        if(mat[i+1][j]==' ')
            dp=min(dp,calc(r+1,c,msk^(1<<r),1)+2);
        if(mat[i][j+1]==' ')
            dp=min(dp,calc(r+1,c,msk,0)+2);
        return dp;
    }
    if(last){
        dp=oo;
        if(mat[i+1][j]==' ')
            dp=min(dp,calc(r+1,c,msk,1)+2);
        if(mat[i][j+1]==' ')
            dp=min(dp,calc(r+1,c,msk^(1<<r),0)+2);
        return dp;
    }
    dp=calc(r+1,c,msk,0);
    if(mat[i][j+1]==' '&&mat[i+1][j]==' ')
        dp=min(dp,calc(r+1,c,msk^(1<<r),1)+3);
    return dp;
}
void genBest(int r,int c,int msk,int last){
    if(r==n/2)
        r=0,c++;
    if(c==m/2)
        return;
    int i=2*r+1,j=2*c+1;
    if(mat[i][j]=='X'){
        if(msk&(1<<r)){
            if(last)
                assert(0);
            genBest(r+1,c,msk^(1<<r),0);
            return;
        }
        if(last){
            genBest(r+1,c,msk,0);
            return;
        }
        if(mat[i+1][j]==' '&&dp==calc(r+1,c,msk,1)+1){
            mat[i+1][j]='.';
            genBest(r+1,c,msk,1);
            return;
        }
        mat[i][j+1]='.';
        genBest(r+1,c,msk^(1<<r),0);
        return;
    }
    if(msk&(1<<r)){
        if(last){
            mat[i][j]='.';
            genBest(r+1,c,msk^(1<<r),0);
            return;
        }
        if(mat[i+1][j]==' '&&dp==calc(r+1,c,msk^(1<<r),1)+2){
            mat[i][j]=mat[i+1][j]='.';
            genBest(r+1,c,msk^(1<<r),1);
            return;
        }
        mat[i][j]=mat[i][j+1]='.';
        genBest(r+1,c,msk,0);
        return;
    }
    if(last){
        if(mat[i+1][j]==' '&&dp==calc(r+1,c,msk,1)+2){
            mat[i][j]=mat[i+1][j]='.';
            genBest(r+1,c,msk,1);
            return;
        }
        mat[i][j]=mat[i][j+1]='.';
        genBest(r+1,c,msk^(1<<r),0);
        return;
    }
    if(dp==calc(r+1,c,msk,0)){
        genBest(r+1,c,msk,0);
        return;
    }
    mat[i][j]=mat[i][j+1]=mat[i+1][j]='.';
    genBest(r+1,c,msk^(1<<r),1);
    return;
}
#undef dp
int main()
{
    memset(dp,-1,sizeof(dp));
	scanf("%i %i\n",&n,&m);
	for(int i=0;i<n;i++)
        getline(cin,mat[i]);
    int cnt=0;
    for(auto p:mat)
        for(auto d:p)
            if(d=='X')
                cnt++;
    printf("%i\n",calc(0,0,0,0)+cnt/2);
    genBest(0,0,0,0);
    for(int i=0;i<n;i++)
        cout << mat[i] << endl;
    return 0;
}
