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

int main()
{
    int n,m,s;
    scanf("%i %i %i",&n,&m,&s);
    vector<pair<int,int> > pairs;
    for(int i=0;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        pairs.emplace_back(a,b);
    }
    ll sol=0;
    sort(all(pairs));
    reverse(all(pairs));
    multiset<pair<int,pair<int,int> >,greater<pair<int,pair<int,int> > > > taken;
    multiset<pair<int,pair<int,int> >,greater<pair<int,pair<int,int> > > > not_taken_b;
    multiset<pair<int,pair<int,int> >,greater<pair<int,pair<int,int> > > > not_taken_a;
    for(int i=0;i<m;i++)
    {
        pair<int,int> p=pairs[i];
        taken.insert({p.s-p.f,{p.f,p.s}});
        sol+=(ll)p.f;
    }
    for(int i=m;i<n;i++)
    {
        pair<int,int> p=pairs[i];
        not_taken_b.insert({p.s,{p.f,p.s}});
        not_taken_a.insert({p.f,{p.f,p.s}});
    }
    for(int i=0;i<s;i++)
    {
        if(not_taken_a.size()==0)
            assert(0);
        int o1=(*not_taken_b.begin()).f;
        int o2=(*taken.begin()).s.s-(*taken.begin()).s.f+(*not_taken_a.begin()).f;
        if(o1>=o2)
        {
            if(o1>0)
            {
                sol+=(ll)o1;
                int a=(*not_taken_b.begin()).s.f,b=(*not_taken_b.begin()).s.s;
                not_taken_b.erase(not_taken_b.find({b,{a,b}}));
                not_taken_a.erase(not_taken_a.find({a,{a,b}}));
            }
        }
        else
        {
            if(o2>0)
            {
                sol+=(ll)o2;
                taken.erase(taken.begin());
                int a=(*not_taken_a.begin()).s.f,b=(*not_taken_a.begin()).s.s;
                not_taken_b.erase(not_taken_b.find({b,{a,b}}));
                not_taken_a.erase(not_taken_a.find({a,{a,b}}));
                taken.insert({b-a,{a,b}});
            }
        }
    }
    printf("%lld\n",sol);
    return 0;
}
