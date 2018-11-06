#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
const int N=305;
int L[2][N][N];
int R[2][N][N];
int main()
{
    int n,m;
    scanf("%i %i",&n,&m);
    vector<int> a(n+1);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&a[i]);
    }
    sort(a.begin(),a.end());
    int poz;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]==0)
        {
            poz=i;
            break;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            for(int k=j;k<=n;k++)
            {
                L[i%2][j][k] = R[i%2][j][k] = 1e9;
                if(j!=0) L[i%2][j][k]=min(L[i%2][j][k],L[(i-1)%2][j-1][k]+i*(a[j]-a[j-1]));
                if(j!=0) R[i%2][j][k]=min(R[i%2][j][k],L[(i-1)%2][j-1][k]+i*(a[k]-a[j-1]));
                if(k!=n) R[i%2][j][k]=min(R[i%2][j][k],R[(i-1)%2][j][k+1]+i*(a[k+1]-a[k]));
                if(k!=n) L[i%2][j][k]=min(L[i%2][j][k],R[(i-1)%2][j][k+1]+i*(a[k+1]-a[j]));
            }
        }
        ans=max(ans,i*m-L[i%2][poz][poz]);
    }
    printf("%i\n",ans);
    return 0;
}
