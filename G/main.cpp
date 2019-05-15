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
int N=4901;
vector<int> primes;
vector<int> visited(N);
ll lim1=1LL<<62;
unsigned long long lim=(unsigned long long)lim1*2;
vector<vector<pair<int,int> > > brojevi;
int n;
gp_hash_table<int,int> gde;
gp_hash_table<int,ll> vis[60][2];
ll gen(int pos,bool uzeo,int mask)
{
    //printf("%i %i %i\n",pos,uzeo,mask);
    if(mask==0&&uzeo)
    {
        return 1;
    }
    if(pos==n)
        return -1;
    if(vis[pos][uzeo][mask]!=0)
        return vis[pos][uzeo][mask];
    ll sol=gen(pos+1,uzeo,mask);
    ll tr=1;
    int nemask=mask;
    for(auto p:brojevi[pos])
    {
        for(int i=0;i<p.s/2;i++)
            tr*=p.f;
        if(p.s%2)
        {
            int tt=gde[p.f];
            nemask^=(1<<tt);
            if(nemask&(1<<tt))
                tr*=p.f;
        }
    }
    if(tr>lim)
        return vis[pos][uzeo][mask]=sol;
    ll sol2=gen(pos+1,1,nemask);
    if(sol2!=-1){
        if(lim>sol2&&lim/sol2>=tr)
        {
            if(sol==-1)
                sol=sol2*tr;
            else
                sol=min(sol,sol2*tr);
        }
    }
    return vis[pos][uzeo][mask]=sol;
}
int test(int a,int b)
{
    //scanf("%i %i",&a,&b);
    for(int i=a;i<=b;i++)
    {
        int tr=sqrt(i);
        if(tr*tr==i)
        {
            printf("%i\n",tr);
            return 0;
        }
    }

    vector<vector<pair<int,int> > > br;
    vector<pair<int,int> > em;
    vector<int> cnt(N);
    for(int i=a;i<=b;i++)
    {
        br.pb(em);
        int tr=i;
        for(auto p:primes)
        {
            if(p*p>tr)
                break;
            if(tr%p==0)
            {
                cnt[p]++;
                br.back().pb({p,0});
                while(tr%p==0)
                    br.back().back().s++,tr/=p;
                if(br.back().back().s%2==0)
                    cnt[p]++;
            }
        }
        if(tr!=1)
            cnt[tr]++,br.back().pb({tr,1});
    }
    brojevi.clear();
    for(auto p:br)
    {
        bool ima=false;
        for(auto d:p)
            if(cnt[d.f]==1)
                ima=true;
        if(!ima)
            brojevi.pb(p);
    }
    vector<int> imam;
    for(auto p:brojevi)
        for(auto d:p)
            imam.pb(d.f);
    sort(all(imam));
    imam.erase(unique(all(imam)),imam.end());
    gde.clear();
    for(int i=0;i<(int)imam.size();i++)
        gde[imam[i]]=i;
    n=brojevi.size();
    for(int i=1;i<=63;i++)
    {
        for(int i=0;i<60;i++)
        for(int j=0;j<2;j++)
            vis[i][j].clear();
        lim=1LL<<i-1;
        lim*=2;
        ll sol=gen(0,0,0);
        if(sol!=-1)
        {
            printf("%lld\n",sol);
            return 0;
        }
    }
    printf("none\n");
    return 0;
    ll sol=gen(0,0,0);
    if(sol==-1)
        printf("none\n");
    else
        printf("%lld\n",sol);
    return brojevi.size();
}
int main()
{
    for(int i=2;i<N;i++)
    {
        if(visited[i])
            continue;
        primes.pb(i);
        for(int j=2*i;j<N;j+=i)
            visited[j]=1;
    }
    test(4625,4760);
    /*int maxx=0;
    for(int i=1;i<N;i++)
    {
        //printf("%i\n",i);
        for(int j=0;j<200;j++)
        {
            if(i+j>=N)
                break;
            int tr=test(i,i+j);
            if(maxx<tr)
            {
                maxx=tr;
                printf("%i %i-%i!\n",maxx,i,i+j);
            }
            //maxx=max(maxx,test(i,i+j));
        }
    }
    printf("%i\n",maxx);*/
	int t;
	scanf("%i",&t);
	while(t--)
        test(0,0);
    return 0;
}
