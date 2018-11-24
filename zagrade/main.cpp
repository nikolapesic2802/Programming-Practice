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
struct str{
    set<pair<int,int> > set;
    int delta;
    void insert(int i)
    {
        i-=delta;
        pair<int,int> a=*set.lower_bound({i,0});
        if(a.first==i)
        {
            set.erase(a);
            a.second++;
            set.insert(a);
        }
        else
        {
            set.insert({i,1});
        }
    }
    int count(int i)
    {
        i-=delta;
        pair<int,int> a=*set.lower_bound({i,0});
        if(a.first==i)
            return a.second;
        return 0;
    }
    int size()
    {
        return set.size();
    }
    void erase()
    {
        while((*set.begin()).first+delta<=0)
            set.erase(set.begin());
    }
};
str e;
vector<str> pocetak,kraj;
vector<int> index(N);
vector<int> sta(N); /// 0-start, 1-end
vector<vector<int> > graf(N);
ll cnt=0;
pair<int,int> ss=mp(-1,-1);
pair<int,int> solve(int tr,int par,pair<int,int> ind)
{
    if(sta[tr]==0)
    {
        cnt+=kraj[ind.second].count(1);
    }
    else
    {
        cnt+=pocetak[ind.first].count(1);
    }
    if(tr!=0&&graf[tr].size()==1)
    {
        pair<int,int> poz=mp(pocetak.size(),kraj.size());
        pocetak.pb(e);
        kraj.pb(e);
        if(sta[tr]==0)
            pocetak.back().insert(1);
        else
            kraj.back().insert(1);
        return poz;
    }
    pair<int,int> res=ss;
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        pair<int,int> x=solve(p,tr,ind);
        if(res==ss)
            res=x;
        else
        {
            if(pocetak[x.first].size()>pocetak[res.first].size())
            {
                for(auto p:pocetak[res.first].set)
                {
                    pocetak[x.first].insert(p+pocetak[res.first].delta);
                }
                res.first=x.first;
            }
            else
            {
                for(auto p:pocetak[x.first].set)
                {
                    pocetak[res.first].insert(p+pocetak[x.first].delta);
                }
            }
            if(kraj[x.second].size()>kraj[res.second].size())
            {
                for(auto p:kraj[res.second].set)
                {
                    kraj[x.second].insert(p+kraj[res.second].delta);
                }
                res.second=x.second;
            }
            else
            {
                for(auto p:kraj[x.second].set)
                {
                    kraj[res.second].insert(p+kraj[x.second].delta);
                }
            }
        }
    }
}
int main()
{
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
    pocetak.pb(e);
    kraj.pb(e);
    solve(0,-1,mp(0,0));
    printf("%lld\n",cnt);
    return 0;
}
