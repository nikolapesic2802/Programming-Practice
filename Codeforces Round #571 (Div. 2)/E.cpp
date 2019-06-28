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

const int N=1e3,L=31;
int mat[N][N],sum[N][N];
pair<ll,ll> num[L];
pair<ll,ll> get(int d,int l=L-1)
{
    if(l==-1)
        return {0,0};
    int dd=1<<l;
    pair<ll,ll> sol;
    if(d>=dd)
        sol=get(d-dd,l-1);
    else
        sol=get(d,l-1);
    if(d>=dd)
        swap(sol.f,sol.s),sol.f+=num[l].f,sol.s+=num[l].s;
    return sol;
}
bool isInverted(int d,int l=L-1)
{
    if(l==-1)
        return 0;
    int dd=1<<l;
    if(d>=dd)
        return !isInverted(d-dd,l-1);
    return isInverted(d,l-1);
}
pair<ll,ll> getSum(int x1,int y1,int x2,int y2)
{
    //printf("%i-%i  %i-%i\n",x1,x2,y1,y2);
    ll sol=sum[x2][y2],area=(ll)((ll)x2-x1+1)*(y2-y1+1);
    if(x1)
        sol-=sum[x1-1][y2];
    if(y1)
        sol-=sum[x2][y1-1];
    if(x1&&y1)
        sol+=sum[x1-1][y1-1];
    return {sol,area-sol};
}
int n,m,q;
pair<ll,ll> calcRow(int l,int r,int y1,int y2)
{
    //printf("%i %i %i %i\n",l,r,y1,y2);
    if(y1/m==y2/m){
        pair<ll,ll> a=getSum(l,y1%m,r,y2%m);
        if(isInverted(y1/m))
            swap(a.f,a.s);
        return a;
    }
    pair<ll,ll> lft=getSum(l,y1%m,r,m-1),rght=getSum(l,0,r,y2%m);
    if(isInverted(y1/m))
        swap(lft.f,lft.s);
    if(isInverted(y2/m))
        swap(rght.f,rght.s);
    pair<ll,ll> normal=getSum(l,0,r,m-1);
    pair<ll,ll> levo=get(y1/m+1,L-1),desno=get(y2/m,L-1);
    desno.f-=levo.f;
    desno.s-=levo.s;
    return {lft.f+rght.f+desno.f*normal.f+desno.s*normal.s,lft.s+rght.s+desno.f*normal.s+desno.s*normal.f};
}
int main()
{
    //freopen("in.txt","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m >> q;
	for(int i=0;i<n;i++)
    {
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            mat[i][j]=sum[i][j]=s[j]=='1';
            if(i)
                sum[i][j]+=sum[i-1][j];
            if(j)
                sum[i][j]+=sum[i][j-1];
            if(i&&j)
                sum[i][j]-=sum[i-1][j-1];
        }
    }
    num[0]={1,0};
    for(int j=1;j<L;j++)
        num[j]={num[j-1].f+num[j-1].s,num[j-1].f+num[j-1].s};
    for(int i=0;i<q;i++)
    {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--;y1--;x2--;y2--;
        if(x1/n==x2/n)
        {
            pair<ll,ll> sol=calcRow(x1%n,x2%n,y1,y2);
            if(isInverted(x1/n))
                swap(sol.f,sol.s);
            cout << sol.f << endl;
            continue;
        }
        pair<ll,ll> lft=calcRow(x1%n,n-1,y1,y2),rght=calcRow(0,x2%n,y1,y2);
        if(isInverted(x1/n))
            swap(lft.f,lft.s);
        if(isInverted(x2/n))
            swap(rght.f,rght.s);
        pair<ll,ll> normal=calcRow(0,n-1,y1,y2);
        pair<ll,ll> levo=get(x1/n+1,L-1),desno=get(x2/n,L-1);
        desno.f-=levo.f;
        desno.s-=levo.s;
        cout << lft.f+rght.f+desno.f*normal.f+desno.s*normal.s << endl;
    }
    return 0;
}
