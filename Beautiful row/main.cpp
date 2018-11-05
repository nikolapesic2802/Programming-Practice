#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
vector<set<int> > graf(20);

int cnt2(int n)
{
    int c=0;
    while(n>0)
    {
        if(n%2==1)
            c++;
        n/=2;
    }
    return c;
}
int cnt3(int n)
{
    int c=0;
    while(n>0)
    {
        if(n%3==1)
            c++;
        n/=3;
    }
    return c;
}
ll dp[20][(1<<20)];

ll calc(int tr,int mask)
{
    //printf("Usao za %i %i\n",tr,mask);
    if(dp[tr][mask]!=-1)
        return dp[tr][mask];
    if(tr==0||(mask&(1))==0)
    {
        if(mask==0&&tr==0)
        {
            dp[tr][mask]=1;
            return 1;
        }
        else
        {
            dp[tr][mask]=0;
            return 0;
        }
    }
    dp[tr][mask]=0;
    for(auto p:graf[tr])
    {
        if((1<<p)&mask)
        {
            //printf("Pozivam za %i %i\n",p,1<<p);
            dp[tr][mask]+=calc(p,(1<<p)^mask);
        }
    }
    return dp[tr][mask];
}

int main()
{
    //srand(time(NULL));
    memset(dp,-1,sizeof(dp));
    vector<int> connect[32][2];
    int n;
    scanf("%i",&n);
    vector<int> niz(n);
    //int a=1e9;
    //int r=rand()%a+1;
    for(int i=0;i<n;i++)
    {
        //niz[i]=r;
        scanf("%i",&niz[i]);
        int c2=cnt2(niz[i]);
        int c3=cnt3(niz[i]);
        //printf("%i %i\n",c2,c3);
        connect[c2][0].pb(i);
        //if(c2!=c3)
        connect[c3][1].pb(i);
    }
    for(int i=0;i<n;i++)
    {
        int c2=cnt2(niz[i]);
        int c3=cnt3(niz[i]);
        for(auto p:connect[c2][0])
        {
            if(p!=i)
            {
                //printf("%i -> %i\n",i,p);
                graf[i].insert(p);
            }
        }
        for(auto p:connect[c3][1])
        {
            if(p!=i)
            {
                    //printf("%i -> %i\n",i,p);
                graf[i].insert(p);
            }
        }
    }
    //printf("gotov %i\n",clock());
    for(int i=0;i<n;i++)
    {
        for(int m=0;m<(1<<n);m++)
        {
            calc(i,m);
        }
    }
    //printf("Gotov %i\n",clock());
    ll cnt=0;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            for(int m=0;m<(1<<(n-1));m++)
            {
                //printf("%i\n",m);
                int tr=m;
                tr<<=1;
                tr+=1;
                if(tr&(1<<i)||tr&(1<<j))
                    continue;
                int inverse=((1<<(n))-1)^tr;
                //printf("%inverse!\n",inverse);
                inverse&=((1<<(n))-1)-(1<<i);
                inverse&=((1<<(n))-1)-(1<<j);
                inverse+=1;
                //printf("%i-%i  %i-%i\n",i,tr,j,inverse);
                //if((ll)calc(i,tr)*calc(j,inverse)>0)
                //printf("%lld %lld  %i-%i   %i-%i  %i\n",calc(i,tr),calc(j,inverse),i,tr,j,inverse,((1<<(n-1))-1));
                cnt+=(ll)2*(ll)dp[i][tr]*dp[j][inverse];
            }
        }
    }
    //printf("Gotov2 %i\n",clock());
    for(int i=1;i<n;i++)
    {
        int mask=((1<<n)-1)-(1<<i);
        //printf("%i %i\n",i,mask);
        cnt+=(ll)2*dp[i][mask];
    }
    printf("%lld\n",cnt);
    return 0;
}
