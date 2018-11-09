/*
    - Find the way to take up the least space when placing the first guy on the first spot, placing him on the second spot... until we can't find a spot for everyone
    - For every place for the first guy add (poz[first_guy]-previous position of the first guy)*(n-poz[last_guy]+1).
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
const int S=1e5+5,s=105;
int nxt[S];
int find_next(int tr,int l)
{
    while(tr<=l&&tr!=-1)
    {
        tr=nxt[tr];
    }
    return tr;
}
long long conta(int n, int t1[], int m, int person[]) {
    memset(nxt,-1,sizeof(nxt));
    vector<int> tr(s),plate(n+1);
    for(int i=0;i<n;i++)
    {
        plate[i+1]=t1[i];
    }
    for(int i=1;i<=n;i++)
    {
        //printf("plate %i\n",plate[i]);
        nxt[tr[plate[i]]]=i;
        tr[plate[i]]=i;
    }
    vector<int> poz(m);
    int t=0;
    ll res=0;
    int last=0;
    for(int i=1;i<=n;i++)
    {
        if(plate[i]==person[t])
        {
            poz[t]=i;
            //printf("poz od %i: %i\n",t,poz[t]);
            t++;
        }
    }
    for(int i=0;i<m;i++)
        if(poz[i]==0)
            return 0;
    res+=(ll)(poz[0]-last)*(n-poz[m-1]+1);
    last=poz[0];
    while(true)
    {
        poz[0]=find_next(poz[0],poz[0]);
        if(poz[0]==-1)
            break;
        bool test=false;
        for(int i=1;i<m;i++)
        {
            int sl=find_next(poz[i],poz[i-1]);
            if(sl==poz[i])
                break;
            poz[i]=sl;
            if(poz[i]==-1)
            {
                test=true;
                break;
            }
        }
        if(test)
            break;
        res+=(ll)(poz[0]-last)*(n-poz[m-1]+1);
        last=poz[0];
    }
    return res;
}

int main() {
  int S, P;
  assert(2 == scanf("%d %d", &S, &P));
  //S=1e5;
  //P=1e4*5;
  int *s = (int*)malloc(S*sizeof(int));
  int *p = (int*)malloc(P*sizeof(int));
  //for(int i=0; i<S; i++) s[i]=0;
  //for(int i=0; i<P; i++) p[i]=0;
  for(int i=0; i<S; i++) assert(1 == scanf("%d", s+i));
  for(int i=0; i<P; i++) assert(1 == scanf("%d", p+i));

  printf("%lld\n", conta(S, s, P, p));
  return 0;
}
