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

//4:25
ll hashuj(string s)
{
    ll h=0;
    for(auto p:s)
        h=((ll)h*27+p-'A'+1);
    return h;
}
int n,m;
vector<vector<ll> > codeA,codeB;
vector<deque<int> > pojavljuje(6e3+1);
int done[(int)6e3+1];
int mul=3001;
const int mod1=1e9+7,mod2=1e9+9;
bool test(int r)
{
    if(r==0)
        return true;
    vector<int> hashesA(n),hashesB(m);
    for(int i=0;i<n-r+1;i++)
    {
        memset(done,-1,sizeof(done));
        int h=0,cnt=1;
        for(int j=i;j<i+r;j++)
            for(int k=0;k<3;k++)
                pojavljuje[codeA[j][k]].pb({j*3+k});
        for(int j=i;j<i+r;j++)
        {
            for(int k=0;k<3;k++)
                pojavljuje[codeA[j][k]].pop_front();
            if(done[codeA[j][0]]==-1)
                done[codeA[j][0]]=cnt++;
            int cntt=0;
            if(done[codeA[j][1]]==-1)
                cntt++;
            if(done[codeA[j][2]]==-1)
                cntt++;
            if(cntt==2)
            {
                if(pojavljuje[codeA[j][1]].empty()&&(int)pojavljuje[codeA[j][2]].size()>0)
                    swap(codeA[j][1],codeA[j][2]);
                if((int)pojavljuje[codeA[j][1]].size()>0&&(int)pojavljuje[codeA[j][2]].size()>0&&pojavljuje[codeA[j][1]][0]>pojavljuje[codeA[j][2]][0])
                    swap(codeA[j][1],codeA[j][2]);
                done[codeA[j][1]]=cnt++;
                done[codeA[j][2]]=cnt++;
            }
            if(cntt==0)
            {
                if(done[codeA[j][1]]>done[codeA[j][2]])
                    swap(codeA[j][1],codeA[j][2]);
            }
            if(cntt==1)
            {
                if(done[codeA[j][2]]==-1)
                    swap(codeA[j][1],codeA[j][2]);
                done[codeA[j][1]]=cnt++;
            }
            for(int k=0;k<3;k++)
                h=h*mul+done[codeA[j][k]];
        }
        hashesA[i]=h;
    }
    for(int i=0;i<m-r+1;i++)
    {
        memset(done,-1,sizeof(done));
        int h=0,cnt=1;
        for(int j=i;j<i+r;j++)
            for(int k=0;k<3;k++)
                pojavljuje[codeB[j][k]].pb({j*3+k});
        for(int j=i;j<i+r;j++)
        {
            for(int k=0;k<3;k++)
                pojavljuje[codeB[j][k]].pop_front();
            if(done[codeB[j][0]]==-1)
                done[codeB[j][0]]=cnt++;
            int cntt=0;
            if(done[codeB[j][1]]==-1)
                cntt++;
            if(done[codeB[j][2]]==-1)
                cntt++;
            if(cntt==2)
            {
                if(pojavljuje[codeB[j][1]].empty()&&(int)pojavljuje[codeB[j][2]].size()>0)
                    swap(codeB[j][1],codeB[j][2]);
                if((int)pojavljuje[codeB[j][1]].size()>0&&(int)pojavljuje[codeB[j][2]].size()>0&&pojavljuje[codeB[j][1]][0]>pojavljuje[codeB[j][2]][0])
                    swap(codeB[j][1],codeB[j][2]);
                done[codeB[j][1]]=cnt++;
                done[codeB[j][2]]=cnt++;
            }
            if(cntt==0)
            {
                if(done[codeB[j][1]]>done[codeB[j][2]])
                    swap(codeB[j][1],codeB[j][2]);
            }
            if(cntt==1)
            {
                if(done[codeB[j][2]]==-1)
                    swap(codeB[j][1],codeB[j][2]);
                done[codeB[j][1]]=cnt++;
            }
            for(int k=0;k<3;k++)
                h=h*mul+done[codeB[j][k]];
        }
        hashesB[i]=h;
    }
    for(int i=0;i<n-r+1;i++)
        for(int j=0;j<m-r+1;j++)
            if(hashesA[i]==hashesB[j])
                return true;
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    codeA.resize(n);
    codeB.resize(m);
    vector<ll> values;
    for(int i=0;i<n;i++)
    {
        string a,b,c;
        char d,e;
        cin >> a >> d >> b >> e >> c;
        codeA[i]={hashuj(a),hashuj(b),hashuj(c)};
        for(auto p:codeA[i])
            values.pb(p);
    }
    for(int i=0;i<m;i++)
    {
        string a,b,c;
        char d,e;
        cin >> a >> d >> b >> e >> c;
        codeB[i]={hashuj(a),hashuj(b),hashuj(c)};
        for(auto p:codeB[i])
            values.pb(p);
    }
    sort(all(values));
    values.erase(unique(all(values)),values.end());
    gp_hash_table<ll,int> mapa;
    for(int i=0;i<(int)values.size();i++)
        mapa[values[i]]=i;
    for(auto &p:codeA)
        for(auto &d:p)
            d=mapa[d];
    for(auto &p:codeB)
        for(auto &d:p)
            d=mapa[d];
    int l=0,r=min(n,m);
    while(l<r)
    {
        int mi=(l+r+1)>>1;
        if(test(mi))
            l=mi;
        else
            r=mi-1;
    }
    cout << l << endl;
    return 0;
}
