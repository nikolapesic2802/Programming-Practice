/*
    -https://ivaniscoding.wordpress.com/2018/08/25/communication-2-navigation/
*/
///Anna
#include "Annalib.h"
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int n=1e5+5;
vector<vector<int> > graf(n);
vector<int> sol(n);
void dfs(int tr,int par)
{
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        if((sol[tr]+sol[p]+(tr<p))%2==1)
            sol[p]++;
        dfs(p,tr);
    }
}
void Anna(int K, int N, int T, int A[], int B[]) {
  for (int i = 0; i < N-1; i++) {
    graf[A[i]].pb(B[i]);
    graf[B[i]].pb(A[i]);
  }
  dfs(T,-1);
  for(int i=1;i<=N;i++)
    Flag(i,sol[i]);
}

///Bruno
#include "Brunolib.h"
#include <bits/stdc++.h>

using namespace std;

void Bruno(int K, int S, int F, int L, int P[], int Q[]) {
  int nxt=-1;
  for(int i=0;i<L;i++)
  {
      if((F+Q[i]+(S<P[i]))%2==1)
        nxt=i;
  }
  if(nxt==-1)
    Answer(S);
  else
    Answer(P[nxt]);
}
