/*
    -To solve this task we need to do subtree set merging and update the value for every node based on its subtree.
    -We also need to pay attention that when a node has 2 or children, the nodes in every child subtree should also match with each other.
    -We can do this by solving for child nodes sorted by increasing order of subtree sizes and keeping a global variable of already finished nodes.
    -When we finish a child we add its nodes to the global variable, and when we finish the parent, we need to remove those nodes.
    -This solution is still n log^2 n, for the same reason that subtree set merging is n log^2 n.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=3e5+5;
ll cnt=0;
int sta[N];
int sz[N];
vector<vector<int> > graf(N);
void dfs(int tr,int par)
{
    sz[tr]=1;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        dfs(p,tr);
        sz[tr]+=sz[p];
    }
}
struct str{
    set<pair<int,int> > set1;
    int delta;
    void insert(int i,int p=1)
    {
        i-=delta;
        if(set1.lower_bound({i,0})==set1.end())
        {
            set1.insert({i,p});
            return;
        }
        pair<int,int> a=*set1.lower_bound({i,0});
        if(a.first==i)
        {
            set1.erase(a);
            a.second+=p;
            set1.insert(a);
        }
        else
        {
            set1.insert({i,p});
        }
    }
    int count(int i)
    {
        i-=delta;
        if(set1.lower_bound({i,0})==set1.end())
            return 0;
        pair<int,int> a=*set1.lower_bound({i,0});
        if(a.first==i)
            return a.second;
        return 0;
    }
    int size()
    {
        return set1.size();
    }
    void erase(int i)
    {
        i-=delta;
        pair<int,int> a=*set1.lower_bound({i,0});
        if(a.first==i)
        {
            set1.erase(a);
            a.second--;
            if(a.second>0)
                set1.insert(a);
        }
        else
        {
            assert(0);
        }
    }
    int erase()
    {
        int obr=0;
        while(set1.size()&&(*set1.begin()).first+delta<0){
            assert((*set1.begin()).first+delta==-1);
            obr=((*set1.begin()).second);
            set1.erase(set1.begin());
        }
        return obr;
    }
    vector<int> all_elements()
    {
        vector<int> al;
        for(auto p:set1)
        {
            for(int i=0;i<p.second;i++)
                al.pb(p.first+delta);
        }
        return al;
    }
} e;
vector<str> pocetak,kraj;
str poc,krj;
int solve(int tr,int par)
{
    if(graf[tr].size()==1&&tr!=0)
    {
        if(sta[tr]==0)
            cnt+=krj.count(1);
        else
            cnt+=poc.count(1);
        pocetak.pb(e);
        kraj.pb(e);
        if(sta[tr]==0)
            pocetak.back().insert(1);
        else
            kraj.back().insert(1);
        return pocetak.size()-1;
    }
    int obr;
    if(sta[tr]==0)
    {
        cnt+=krj.count(1);
        poc.delta++;
        krj.delta--;
        obr=krj.erase();
    }
    else
    {
        cnt+=poc.count(1);
        poc.delta--;
        krj.delta++;
        obr=poc.erase();
    }
    vector<pair<int,int> > ind;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        ind.pb({sz[p],p});
    }
    sort(ind.begin(),ind.end());
    vector<int> dodao,dodaok;
    for(int i=0;i<(int)ind.size()-1;i++)
    {
        int tren=solve(ind[i].second,tr);
        if(sta[tr]==0)
        {
            cnt+=kraj[tren].count(1);
            pocetak[tren].delta++;
            kraj[tren].delta--;
            kraj[tren].erase();
        }
        else
        {
            cnt+=pocetak[tren].count(1);
            pocetak[tren].delta--;
            kraj[tren].delta++;
            pocetak[tren].erase();
        }
        vector<int> al=pocetak[tren].all_elements();
        for(auto p:al)
        {
            dodao.pb(p);
            poc.insert(p);
        }
        al=kraj[tren].all_elements();
        for(auto p:al)
        {
            dodaok.pb(p);
            krj.insert(p);
        }
    }
    int tren=solve(ind[ind.size()-1].second,tr);
    if(sta[tr]==0)
    {
        cnt+=kraj[tren].count(1);
        pocetak[tren].delta++;
        kraj[tren].delta--;
        kraj[tren].erase();
        pocetak[tren].insert(1);
    }
    else
    {
        cnt+=pocetak[tren].count(1);
        pocetak[tren].delta--;
        kraj[tren].delta++;
        pocetak[tren].erase();
        kraj[tren].insert(1);
    }
    for(auto p:dodao)
    {
        poc.erase(p);
        pocetak[tren].insert(p);
    }
    for(auto p:dodaok)
    {
        krj.erase(p);
        kraj[tren].insert(p);
    }
    if(sta[tr]==0)
    {
        if(obr)
            krj.insert(-1,obr);
        poc.delta--;
        krj.delta++;
    }
    else
    {
        if(obr)
            poc.insert(-1,obr);
        poc.delta++;
        krj.delta--;
    }
    return tren;
}
int main()
{
    e.set1.clear();
    e.delta=0;
    int n;
    scanf("%i",&n);
    string s;
    cin >> s;
    for(int i=0;i<n;i++)
    {
        sta[i]=s[i]==')';
    }
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%i %i",&x,&y);
        x--;
        y--;
        graf[x].pb(y);
        graf[y].pb(x);
    }
    dfs(0,-1);
    solve(0,-1);
    printf("%lld\n",cnt);
    return 0;
}
