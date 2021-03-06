/*
    -The tricky part is figuring out how to construct the tree that we need to answer the question effectively.
    -For every 2^k*2^k square starting on point 0,0 the point that we are looking for can be in several "regions":"inside region", in the 2^(k-1)*2^(k-1) square,
                                                                                                                  "left region" (square of size 2^(k-1)*2^(k-1) starting on 2^(k-1),0
                                                                                                                  "up region"(square of size 2^(k-1)*2^(k-1) starting on 0,2^(k-1)
                                                                                                                  "outside region", not in the square at all(its in some bigger square)
    -Notice that if 2 points are not in the same "region", we need to go the edge of the current square to travel between them.
    -This gives us the solution to construct a tree and calculate the answer that way.
    -The construction is done recursively starting from the smallest square and calling recursively for the regions in order  "inside"->"left"->"up"->"outside" (the order of left and up doesn't matter)
    -I used a map to memorize which tree nodes to connect, it adds some time complexity but it was easier to type for me.
    -Then we need to calculate the answer by calculating the cost of moving all the tourists for every node in the tree and print the minimum (in some complexity better than O(n^2) of course).
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
void show()
{
    int n=128;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i&j)
                printf("%c",178);
            else
                printf("%c",176);
        }
        printf("\n");
    }
}
map<int,pair<int,int> > mapax,mapay;  ///{kordinata,poz_u_grafu}
int nxt=1;
vector<pair<int,int> > dummy;
int dummy1;
vector<vector<pair<int,int> > > graf(2);
vector<int> cnt(2);
void construct(vector<pair<int,int> > points,ll velicina,ll x,ll y)
{
    vector<pair<int,int> > posle,levo,desno,gore;
    for(auto p:points)
    {
        if(p.first>=x+velicina||p.second>=y+velicina){
            posle.pb(p);
            continue;
        }
        if(p.first<x+velicina/2&&p.second<y+velicina/2)
        {
            gore.pb(p);
            continue;
        }
        if(p.first>=x+velicina/2)
        {
            levo.pb(p);
        }
        else
        {
            desno.pb(p);
        }
    }
    if(gore.size())
    {
        construct(gore,velicina/2,x,y);
    }
    if(levo.size())
    {
        graf[mapay[y].second].pb({nxt,x+velicina/2-mapay[y].first});
        mapay[y]=make_pair(x+velicina/2,nxt);
        mapax[x+velicina/2]=make_pair(y,nxt);
        vector<pair<int,int> > ne;
        for(auto p:levo)
        {
            if(p.first==x+velicina/2&&p.second==y)
                cnt[nxt]++;
            else
                ne.pb(p);
        }
        nxt++;
        if(nxt>=graf.size())
            graf.pb(dummy),cnt.pb(dummy1);
        if(ne.size())
            construct(ne,velicina/2,x+velicina/2,y);
    }
    if(desno.size())
    {
        graf[mapax[x].second].pb({nxt,y+velicina/2-mapax[x].first});
        mapax[x]=make_pair(y+velicina/2,nxt);
        mapay[y+velicina/2]=make_pair(x,nxt);
        vector<pair<int,int> > ne;
        for(auto p:desno)
        {
            if(p.first==x&&p.second==y+velicina/2)
                cnt[nxt]++;
            else
                ne.pb(p);
        }
        nxt++;
        if(nxt>=graf.size())
            graf.pb(dummy),cnt.pb(dummy1);
        if(ne.size())
            construct(ne,velicina/2,x,y+velicina/2);
    }
    if(posle.size())
    {
        construct(posle,(ll)velicina*2,x,y);
    }
}
void printgraf(int tr)
{
    printf("Cnt od %i: %i\n",tr,cnt[tr]);
    for(auto p:graf[tr])
    {
        printf("Idem od %i do %i, tezina: %i\n",tr,p.first,p.second);
        printgraf(p.first);
    }
}
vector<int> siz;
vector<ll> val;
void postavi(int tr)
{
    siz[tr]+=cnt[tr];
    for(auto p:graf[tr])
    {
        postavi(p.first);
        siz[tr]+=siz[p.first];
        val[tr]+=val[p.first]+(ll)siz[p.first]*p.second;
    }
}
ll minn;
void get_min(int tr,ll value)
{
    minn=min(minn,value);
    for(auto p:graf[tr])
    {
        ll ne=value-(ll)siz[p.first]*p.second;
        ne+=(ll)(siz[0]-siz[p.first])*p.second;
        get_min(p.first,ne);
    }
}
int main()
{
    //show();
    int n;
    scanf("%i",&n);
    vector<pair<int,int> > points;
    for(int i=0;i<n;i++){
        int x,y;
        scanf("%i %i",&x,&y);
        if(x==0&&y==0)
            cnt[0]++;
        else
            points.pb({x,y});
    }
    mapax[0]=make_pair(0,0);
    mapay[0]=make_pair(0,0);
    construct(points,2,0,0);
    //printgraf(0);
    int N=graf.size();
    siz.resize(N);
    val.resize(N);
    postavi(0);
    minn=val[0];
    get_min(0,minn);
    printf("%lld\n",minn);
    return 0;
}
