/*
    - https://codeforces.com/blog/entry/17717?#comment-226989
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
int n;
bool inside(int tr)
{
    return tr>=0&&tr<n;
}
int main()
{
    int m;
    scanf("%i %i",&n,&m);
    vector<set<int,greater<int> > > jumps(n);
    int b,p;
    scanf("%i %i",&b,&p);
    int start=b;
    jumps[b].insert(p);
    scanf("%i %i",&b,&p);
    int e=b;
    for(int i=2;i<m;i++)
    {
        scanf("%i %i",&b,&p);
        jumps[b].insert(p);
    }
    vector<vector<pair<int,int> > > graf(n);
    for(int i=0;i<n;i++)
    {
        for(auto p:jumps[i])
        {
            for(int j=1;;j++)
            {
                int pos=i+j*p;
                if(!inside(pos))
                    break;
                graf[i].pb({pos,j});
                if(jumps[pos].count(j))
                    break;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(auto p:jumps[i])
        {
            for(int j=1;;j++)
            {
                int pos=i-j*p;
                if(!inside(pos))
                    break;
                graf[i].pb({pos,j});
                if(jumps[pos].count(j))
                    break;
            }
        }
    }
    vector<int> done(n);
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int>> > q;
    q.push({0,start});
    fill(done.begin(),done.end(),INT_MAX);
    done[start]=0;
    while(!q.empty())
    {
        int pos=q.top().second;
        int num=q.top().first;
        if(pos==e)
        {
            printf("%i\n",num);
            return 0;
        }
        q.pop();
        done[pos]=2;
        for(auto p:graf[pos])
        {
            if(done[p.first]>num+p.second)
            {
                q.push({num+p.second,p.first});
                done[p.first]=num+p.second;
            }
        }
    }
    printf("-1\n");
    return 0;
}
