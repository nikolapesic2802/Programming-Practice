/*
    -I will mark the i'th person by strenth on surface p by arr[p][i], and the three different surfaces as 0,1 and 2
    -In order for a person to be unable to win, the following has to hold:
        There is an index j such that sort(arr[0][0...j])==sort(arr[1][0...j])==sort(arr[2][0..j]) and index j is smaller than the index of that person in on any surface.
    -Another way to look at this is to, for each person mark min as the minimum index of that person on the 3 surfaces and max and the maximum.
        Now for each person we can merge that interval of indices like in a DSU.
        And now our query becomes is person x and person arr[0][0] in the same component.
    -Solve the queries offline.
    -Use dynamic connectivity to solve the problem https://codeforces.com/blog/entry/15296.
    -This will transform all the queries into add a person in some position on some surface on some interval of queries.
    -We can do these queries in amortized O(1).
    -This can be done by keeping the current size of the component that contains 0, and when we get a new interval, we either mark it to use later, or test to see if we can use it immediately.
    -We also need to be able to undo the changes we made during some operation.
    -I think the complexity is O(n log n), but it might actually be O(n log^2 n). Anyways, it passes in around 300ms.
*/
#include <bits/stdc++.h>

#define pb push_back
#define f first
#define s second

using namespace std;

const int N=1e5+5;
vector<vector<int> > arr(3,vector<int>(N)),pos(3,vector<int>(N)),last(3,vector<int>(N)),vals(3,vector<int>(N,-1));
vector<vector<tuple<int,int,int> > > dodaj(4*N);
void add(int qs,int qe,tuple<int,int,int> x,int l,int r,int i){
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r){
        dodaj[i].pb(x);
        return;
    }
    int m=(l+r)>>1;
    add(qs,qe,x,l,m,2*i);
    add(qs,qe,x,m+1,r,2*i+1);
}
int tr=0;
vector<int> queries(N);
vector<int> reach(N);
int trReach=0;
vector<vector<pair<int,pair<int,int> > > > undo;
vector<pair<int,pair<int,int> > > em;
void sett(int p,int a,int ind){
    vals[p][a]=ind;
    undo.pb(em);
    undo.back().pb({0,{p,a}});
    if(vals[0][a]!=-1&&vals[1][a]!=-1&&vals[2][a]!=-1){
        int mi=min({vals[0][a],vals[1][a],vals[2][a]}),ma=max({vals[0][a],vals[1][a],vals[2][a]});
        if(mi<=trReach){
            int newReach=ma;
            for(int i=trReach+1;i<=newReach;i++)
                newReach=max(newReach,reach[i]);
            if(newReach>trReach){
                undo.back().pb({1,{trReach,trReach}});
                trReach=newReach;
            }
        }else{
            if(reach[mi]<ma)
                undo.back().pb({2,{mi,reach[mi]}}),reach[mi]=ma;
        }
    }
}
void undo_it(){
    for(auto p:undo.back()){
        if(p.f==0)
            vals[p.s.f][p.s.s]=-1;
        if(p.f==1)
            trReach=p.s.f;
        if(p.f==2)
            reach[p.s.f]=p.s.s;
    }
    undo.pop_back();
}
void solve(int l,int r,int i){
    if(l>=tr)
        return;
    for(auto p:dodaj[i])
        sett(get<0>(p),get<1>(p),get<2>(p));
    if(l==r){
        int index=vals[0][queries[l]];
        if(index<=trReach)
            printf("DA\n");
        else
            printf("NE\n");
        for(auto p:dodaj[i])
            undo_it();
        return;
    }
    int m=(l+r)>>1;
    solve(l,m,2*i);
    solve(m+1,r,2*i+1);
    for(auto p:dodaj[i])
        undo_it();
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,q;
	scanf("%i %i",&n,&q);
	for(int i=0;i<3;i++)
        for(int j=0;j<n;j++)
            scanf("%i",&arr[i][j]),arr[i][j]--,pos[i][arr[i][j]]=j;
    vector<pair<pair<int,int>,tuple<int,int,int> > > ad;
    for(int i=0;i<q;i++){
        int t;
        scanf("%i",&t);
        if(t==1){
            int x;
            scanf("%i",&x);
            queries[tr++]=x-1;
        }else{
            int p,a,b;
            scanf("%i %i %i",&p,&a,&b);
            p--;a--;b--;
            if(last[p][a]!=tr)
                ad.pb({{last[p][a],tr-1},make_tuple(p,a,pos[p][a])});
            if(last[p][b]!=tr)
                ad.pb({{last[p][b],tr-1},make_tuple(p,b,pos[p][b])});
            last[p][b]=last[p][a]=tr;
            swap(arr[p][pos[p][a]],arr[p][pos[p][b]]);
            swap(pos[p][a],pos[p][b]);
        }
    }
    for(auto p:ad)
        add(p.f.f,p.f.s,p.s,0,tr-1,1);
    for(int i=0;i<3;i++)
        for(int j=0;j<n;j++)
            if(last[i][j]!=tr)
                add(last[i][j],tr-1,make_tuple(i,j,pos[i][j]),0,tr-1,1);
    solve(0,tr-1,1);
    return 0;
}
