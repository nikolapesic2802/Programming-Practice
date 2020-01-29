/*
    -dp[i][k] = max number of edges we can "save" (not go over twice) if we need to choose k vertices in the subtree of i.
    -Notice that if we need to choose 4 or 2 vertices in some subtree, we will need to go over the edge connecting the root of that subtree and his parent twice.
    -But if we have to choose 3 or 1, we can "save" that edge.
*/
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5,oo=INT_MIN/100;
vector<vector<int> > graf(N),dp(N,vector<int>(5));
void calc(int tr,int par){
    dp[tr]={0,0,oo,oo,oo};
    for(auto p:graf[tr])
        if(p!=par){
            calc(p,tr);
            for(int i=3;i>=0;i--)
                for(int k=1;k<5-i;k++)
                    dp[tr][i+k]=max(dp[tr][i+k],dp[tr][i]+(k&1)+dp[p][k]);
        }
}
int main()
{
	int n,k,a,b;
	scanf("%i %i",&n,&k);
	for(int i=1;i<n;i++)
        scanf("%i %i",&a,&b),graf[a-1].push_back(b-1),graf[b-1].push_back(a-1);
    calc(0,0);
    printf("%i\n",2*(n-1)-dp[0][2*k]+k);
    return 0;
}
