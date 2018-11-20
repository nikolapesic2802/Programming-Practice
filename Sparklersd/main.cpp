#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main()
{
    int n,k,t;
    scanf("%i %i %i",&n,&k,&t);
    vector<int> arr(n+1);
    for(int i=1;i<=n;i++)
    {
        scanf("%i",&arr[i]);
    }
    int le=0,ri=5e8;
    while(le<ri)
    {
        int m=(le+ri)>>1;
        vector<ll> X(n+1);
        for(int i=1;i<=n;i++)
        {
            X[i]=arr[i]-(ll)2*m*t*(i-1);
        }
        int l=k,r=k;
        ll minn=X[k],maxx=X[k];
        int ok=1;
        while(ok)
        {
            ok=0;
            while(l>1&&X[l-1]>=minn)
            {
                ok=1;
                l--;
                maxx=max(maxx,X[l]);
            }
            while(r<n&&X[r+1]<=maxx)
            {
                ok=1;
                r++;
                minn=min(minn,X[r]);
            }
        }
        if(l==1&&r==n)
        {
            if(X[l]<X[r])
            {
                le=m+1;
                continue;
            }
            maxx=X[l];
            minn=X[r];
            ok=1;
            while(ok)
            {
                ok=0;
                while(l<k&&X[l+1]>=minn)
                {
                    ok=1;
                    l++;
                    maxx=max(maxx,X[l]);
                }
                while(r>k&&X[r-1]<=maxx)
                {
                    ok=1;
                    r--;
                    minn=min(minn,X[r]);
                }
            }
            if(r==k&&l==k)
            {
                ri=m;
            }
            else
            {
                le=m+1;
            }
        }
        else
        {
            le=m+1;
        }
    }
    printf("%i\n",le);
    return 0;
}
