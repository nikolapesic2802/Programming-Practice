#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
const int N=2000;
int mat[N][N],row[N],col[N];
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int k,m,n;
	scanf("%i %i %i",&k,&m,&n);
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%i",&mat[i][j]),row[i]+=mat[i][j],col[j]+=mat[i][j];
    int x1=0,y1=0,x2=n-1,y2=m-1,sol=0;
    while(x2>=x1&&y2>=y1){
        sol++;
        if(x2-x1<y2-y1){
            if(row[x1]<=k)
            {
                for(int i=y1;i<=y2;i++)
                    col[i]-=mat[x1][i];
                x1++;
                continue;
            }
            if(row[x2]<=k)
            {
                for(int i=y1;i<=y2;i++)
                    col[i]-=mat[x2][i];
                x2--;
                continue;
            }
        }
        if(col[y1]<=k)
        {
            for(int i=x1;i<=x2;i++)
                row[i]-=mat[i][y1];
            y1++;
            continue;
        }
        if(col[y2]<=k)
        {
            for(int i=x1;i<=x2;i++)
                row[i]-=mat[i][y2];
            y2--;
            continue;
        }
        if(row[x1]<=k)
        {
            for(int i=y1;i<=y2;i++)
                col[i]-=mat[x1][i];
            x1++;
            continue;
        }
        if(row[x2]<=k)
        {
            for(int i=y1;i<=y2;i++)
                col[i]-=mat[x2][i];
            x2--;
            continue;
        }
    }
    printf("%i\n",sol);
    return 0;
}
