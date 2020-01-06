#include <bits/stdc++.h>
//#include "grader.h"

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";
#define ld long double

using namespace std;

const int N=1000,H=36,M=1001;
int n;
vector<vector<int> > graf(N);
vector<int> dist(N);
void send(int a){
    for(int i=0;i<10;i++)
        encode_bit(a&1),a/=2;
}
void bfs(int s){
    fill(all(dist),M);
    dist[s]=0;
    queue<int> q;
    q.push(s);
    while(q.size()){
        int tr=q.front();
        q.pop();
        for(int i=0;i<graf[tr].size();i++)
            if(dist[graf[tr][i]]==M)
                dist[graf[tr][i]]=dist[tr]+1,q.push(graf[tr][i]);
    }
}
void encode(int _n,int h,int p,int *a,int *b){
    n=_n;
    for(int i=0;i<p;i++)
        graf[a[i]].pb(b[i]),graf[b[i]].pb(a[i]);
    for(int i=0;i<h;i++){
        bfs(i);
        for(int j=0;j<n;j++)
            send(dist[j]);
    }
}

int recieve(){
    int tr=1,ans=0;
    for(int i=0;i<10;i++){
        if(decode_bit())
            ans+=tr;
        tr*=2;
    }
    return ans;
}
void decode(int n,int h){
    for(int i=0;i<h;i++)
        for(int j=0;j<n;j++)
            hops(i,j,recieve());
}
int main(){
    freopen("saveit/grader.in.01")
}
