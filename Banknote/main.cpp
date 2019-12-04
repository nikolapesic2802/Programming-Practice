/*
    -Bounded knapsack problem, http://www.algonotes.com/en/knapsacks/.
    -For each remainder modulo b[i] we can do convex hull dp optimization and calculate the answer in O(n*k)
*/
#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back

using namespace std;

const int N=201,M=20001,oo=INT_MAX/2;
int n,b[N],c[N],dp[N][M],bst[N][M];
int main()
{
	scanf("%i",&n);
	for(int i=0;i<n;i++)
        scanf("%i",&b[i]);
    for(int i=0;i<n;i++)
        scanf("%i",&c[i]);
    int k;
    scanf("%i",&k);
    for(int i=1;i<=k;i++)
        dp[n][i]=oo;
    dp[n][0]=0;
    for(int i=n-1;i>=0;i--){
        deque<pair<int,int> > dq[b[i]];
        for(int j=0;j<=k;j++){
            int pos=j/b[i],gde=j%b[i];
            pair<int,int> tr={dp[i+1][j]+k-pos,pos};
            while(dq[gde].size()&&dq[gde].back().f>=tr.first)
                dq[gde].pop_back();
            dq[gde].pb(tr);
            while(dq[gde].front().s==pos-c[i]-1)
                dq[gde].pop_front();
            dp[i][j]=dq[gde].front().f-k+pos;
            bst[i][j]=pos-dq[gde].front().s;
        }
    }
    printf("%i\n",dp[0][k]);
    for(int a=0;a<n;a++)
        printf("%i ",bst[a][k]),k-=b[a]*bst[a][k];
    return 0;
}
/*
Solution 2: use the fact that samples are weak and some wrong greedy passes all the tests except for test 4 which is dealt by not breaking (doing the n*k*k dp)
            this passes because n is small for test 4 :).

#include <bits/stdc++.h>

using namespace std;

const int N=201,M=20001,oo=INT_MAX/2;
vector<int> b(N),c(N);
int n;
int dp[N][M],bst[N][M];
int calc(int tr,int k){
    if(tr==n)
        return k==0?0:oo;
    if(dp[tr][k]!=-1)
        return dp[tr][k];
    dp[tr][k]=oo;
    int cnt=0,kk=k;
    for(;kk>=0&&cnt<=c[tr];kk-=b[tr],cnt++)
        if(calc(tr+1,kk)+cnt<dp[tr][k]){
            dp[tr][k]=calc(tr+1,kk)+cnt,bst[tr][k]=cnt;
            if(n>=20)
                break;
        }
    return dp[tr][k];
}
int main()
{
    memset(dp,-1,sizeof(dp));
	scanf("%i",&n);
	for(int i=0;i<n;i++)
        scanf("%i",&b[i]);
    for(int i=0;i<n;i++)
        scanf("%i",&c[i]);
    int k;
    scanf("%i",&k);
    printf("%i\n",calc(0,k));
    for(int a=0;a<n;a++)
        printf("%i ",bst[a][k]),k-=b[a]*bst[a][k];
    return 0;
}
*/
