#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
const int N=305;
ll lim=LLONG_MIN/1000;
pair<ll,int> dp[N][N][2],poc=make_pair((ll)-1,-1);
vector<int> poz,neg;
pair<ll,int> maxDP(int i,int j,int k,int b)
{
    //printf("Usao za %i %i %i  %i %i\n",i,j,k,poz.size(),neg.size());
    if(i+j+1>b)
        return make_pair(0,-1);
    if(dp[i][j][k]!=poc)
        return dp[i][j][k];
    if(k==0)
    {
        ll res1;
        if(i+1<poz.size())
            res1=maxDP(i+1,j,0,b).first-(neg.size()-j+poz.size()-i-1)*(poz[i+1]-poz[i]);
        else
            res1=lim;
        ll res2;
        if(j<neg.size())
            res2=maxDP(i+1,j,1,b).first-(neg.size()-j+poz.size()-i-1)*(poz[i]-neg[j]);
        else
            res2=lim;
        //printf("%i %i %i: %lld  %lld\n",i,j,k,res1,res2);
        if(res1>=res2)
        {
            dp[i][j][k]=make_pair(res1,0);
        }
        else
        {
            dp[i][j][k]=make_pair(res2,1);
        }
    }
    if(k==1)
    {
        ll res1;
        if(i<poz.size())
            res1=maxDP(i,j+1,0,b).first-(neg.size()-j-1+poz.size()-i)*(poz[i]-neg[j]);
        else
            res1=lim;
        ll res2;
        if(j+1<neg.size())
            res2=maxDP(i,j+1,1,b).first-(neg.size()-j-1+poz.size()-i)*(neg[j]-neg[j+1]);
        else
            res2=lim;
        //printf("%i %i %i: %lld  %lld\n",i,j,k,res1,res2);
        if(res1>=res2)
        {
            dp[i][j][k]=make_pair(res1,0);
        }
        else
        {
            dp[i][j][k]=make_pair(res2,1);
        }
    }
    return dp[i][j][k];
}
const long long MOD = 1e9 + 7;
const long long MAXN = 1e6 + 1;
int L[2][305][305];
int R[2][305][305];

int a[305];
int main()
{
    while(true)
    {
    memset(L,0,sizeof(L));
    memset(R,0,sizeof(R));
    memset(a,0,sizeof(a));
    poz.clear();
    neg.clear();
    int n=15,m=rand()%100000;
    //scanf("%i %i",&n,&m);
    //printf("Doin\n");
    int mm=m;
    int p=0;
    vector<int> aa(n);
    set<int> koriscen;
    koriscen.insert(0);
    for(int i=0;i<n;i++)
    {
        //scanf("%i",&a[i]);
        do{
            a[i]=aa[i]=rand()%2000-100;
        }while(koriscen.count(a[i]));
        koriscen.insert(a[i]);
        if(aa[i]==0)
            assert(0);
    }
    ll ans=0;
    poz.pb(0);
    for(int i=0;i<n;i++)
    {
        if(aa[i]>m)
            continue;
        if(aa[i]<0)
            neg.pb(aa[i]);
        if(aa[i]>0)
            poz.pb(aa[i]);
    }
    sort(poz.begin(),poz.end());
    sort(neg.begin(),neg.end());
    reverse(neg.begin(),neg.end());
    for(int b=0;b<poz.size()+neg.size();b++)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                dp[i][j][0]=poc;
                dp[i][j][1]=poc;
            }
        }
        ll res=p*m;
        int l=0,r=0,k=0;
        m=mm;
        while(true)
        {
            int smer=maxDP(l,r,k,b).second;
            //printf("Smer: %i %i %lld  %i  %i   %i\n",smer,m,res,l,r,b);
            if(smer==-1)
                break;
            if(k==0)
            {
                if(smer==0)
                {
                    //if(l+1<poz.size())
                    m-=poz[l+1]-poz[l];
                }
                else
                {
                    //if(l<poz.size()&&r<neg.size())
                    m-=poz[l]-neg[r];
                }
                l++;
            }
            else
            {
                if(smer==0)
                {
                    //if(l<poz.size()&&r<neg.size())
                    m-=poz[l]-neg[r];
                }
                else
                {
                    //if(r+1<neg.size())
                    m-=neg[r]-neg[r+1];
                }
                r++;
            }
            if(m<=0||smer==-1)
                break;
            res+=(ll)m;
            if(l+r+1>b)
                break;
            k=smer;
        }
        ans=max(ans,res);
    }
    m=mm;
    //printf("%lld\n",ans);
    sort(a, a + 1 + n);
    int pos = (int)(lower_bound(a, a + 1 + n, 0) - a);
    int ans2 = 0;
    for (int i = 1; i <= n; i++) {
    	for (int j = 0; j <= n; j++) {
    		for (int k = j; k <= n; k++) {
				L[i%2][j][k] = R[i%2][j][k] = MOD;
				if (j != 0) L[i%2][j][k] = min(L[i%2][j][k], L[(i-1)%2][j-1][k] + i * (a[j] - a[j-1]));
                if (k != n) L[i%2][j][k] = min(L[i%2][j][k], R[(i-1)%2][j][k+1] + i * (a[k+1] - a[j]));
                if (j != 0) R[i%2][j][k] = min(R[i%2][j][k], L[(i-1)%2][j-1][k] + i * (a[k] - a[j-1]));
                if (k != n) R[i%2][j][k] = min(R[i%2][j][k], R[(i-1)%2][j][k+1] + i * (a[k+1] - a[k]));
    		}
    	}
    	ans2 = max(ans2, i * m - L[i%2][pos][pos]);
    }
    if(ans!=ans2)
    {
        printf("%i %lld\n",ans2,ans);
        printf("%i %i\n",n,m);
        for(auto dd:aa)
        {
            printf("%i ",dd);
        }
        printf("\n");
        break;
    }
    }
    return 0;
}
