#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#pragma GCC optimize("Ofast")
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()

void solveN(int n,int k)
{
    vector<string> niz(n);
    for(int i=0;i<n;i++)
        cin >> niz[i];
    vector<int> res(n);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int dif=0;
            for(int l=0;l<k;l++)
            {
                if(niz[i][l]!=niz[j][l])
                    dif++;
                if(dif>2)
                    break;
            }
            if(dif<=2)
            {
                res[i]=1;
                res[j]=1;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%i",res[i]);
    }
    printf("\n");
}
void solveK(int n,int k)
{
    vector<string> niz(n);
    for(int i=0;i<n;i++)
        cin >> niz[i];
    const ll mod=92233720368547753;
    unordered_map<ll,ll> found;
    vector<int> res(n);
    ll table[k][27];
    int last=26;
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<27;j++)
        {
            ll r1=((ll)rand())%mod;
            ll r2=((ll)rand())%mod;
            //printf("%lld ")
            table[i][j]=(((ll)((ll)rand())<<31)%mod+(ll)rand()%mod)%mod;
            //printf("%lld\n",table[i][j]);
        }
    }
    vector<ll> Hash(n),h(n);;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            Hash[i]^=table[j][niz[i][j]-'a'];
        }
    }
    for(int i=0;i<k;i++)
    {
        for(int j=i+1;j<k;j++)
        {
            found.clear();
            for(int l=0;l<n;l++)
            {
                h[l]=Hash[l];
                h[l]^=table[i][niz[l][i]-'a'];
                h[l]^=table[j][niz[l][j]-'a'];
                found[h[l]]++;
            }
            for(int l=0;l<n;l++)
            {
                if(found[h[l]]>1)
                {
                    res[l]=1;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%i",res[i]);
    }
    printf("\n");
}
void test()
{
    int n,k;
    cin >> n >> k;
    int lim=180;
    if(n<lim)
    {
        solveN(n,k);
        return;
    }
    solveK(n,k);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)
        test();
    return 0;
}
