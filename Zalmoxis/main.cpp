/*
    -First add all the necessary element to make the sequence into {30} and then if we need to add more element we split some of the element we added.
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
int cnt;
void razlozi(int n)
{
    if(cnt>1)
    {
        cnt--;
        razlozi(n-1);
    }
    else
    {
        printf("%i ",n);
    }
    printf("%i ",n);
}
int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    vector<vector<int> > res(n);
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>> >,greater<pair<int,pair<int,int> > > > poz;
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        res[i].pb(a);
        poz.push({a,{i,i}});
    }
    while((poz.top()).first!=30)
    {
        pair<int,pair<int,int> > b=poz.top();
        poz.pop();
        if(poz.size()==0)
        {
            k--;
            res[b.second.second].pb(b.first);
            poz.push({b.first+1,b.second});
            continue;
        }
        pair<int,pair<int,int> > sl=poz.top();
        if(b.first==sl.first&&sl.second.first-1<=b.second.second)
        {
            poz.pop();
            poz.push({b.first+1,{b.second.first,max(b.second.second,sl.second.second)}});
        }
        else
        {
            k--;
            res[b.second.second].pb(b.first);
            poz.push({b.first+1,b.second});
        }
    }
    vector<vector<int> > razlozen(n);
    for(int i=0;i<n;i++)
    {
        razlozen[i].resize(res[i].size());
        for(int j=1;j<(int)res[i].size();j++)
        {
            int po=pow(2,res[i][j]);
            razlozen[i][j]=min(po,k);
            k-=min(po,k);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<(int)res[i].size();j++)
        {
            if(razlozen[i][j])
            {
                cnt=razlozen[i][j];
                razlozi(res[i][j]-1);
            }
            else
            {
                printf("%i ",res[i][j]);
            }
        }
    }
    return 0;
}
