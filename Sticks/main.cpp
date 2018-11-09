/*
    - For every stick, go through all the colors and find 2 sticks from different sets closest to it by size but smaller,
      and the two closest to it but larder and try to make triangles with them.
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

void fastscan(int &n)
{
    bool minus=false;
    n=0;
    register int c=getchar();
    if(c=='-')
    {
        minus=true;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        n*=10;
        n+=c-'0';
        c=getchar();
    }
    if(minus)
        n*=-1;
}
int main()
{
    int k;
    //scanf("%i",&k);
    fastscan(k);
    vector<vector<int> > sets(k);
    for(int i=0;i<k;i++)
    {
        sets[i].pb(INT_MAX);
        int n;
        //scanf("%i",&n);
        fastscan(n);
        for(int j=0;j<n;j++)
        {
            int a;
            //scanf("%i",&a);
            fastscan(a);
            sets[i].pb(a);
        }
        sort(sets[i].begin(),sets[i].end());
    }
    for(int i=0;i<k;i++)
    {
        for(auto p:sets[i])
        {
            if(p==INT_MAX)
                continue;
            int m1=INT_MAX,m2=INT_MAX,c1,c2;
            int ma1=-1,ma2=-1,ca1,ca2;
            for(int j=0;j<k;j++)
            {
                if(i==j)
                    continue;
                int l=0,r=sets[j].size()-1;
                while(l<r)
                {
                    int mid=(l+r)/2;
                    if(mid==0&&sets[j][mid]>=p)
                    {
                        l=mid;
                        break;
                    }
                    if(sets[j][mid]>=p&&sets[j][mid-1]<p){
                        l=mid;
                        break;
                    }
                    if(sets[j][mid]<p)
                    {
                        l=mid+1;
                    }
                    else
                    {
                        r=mid;
                    }
                }
                int v=sets[j][l];
                if(v<m1)
                {
                    m2=m1;
                    c2=c1;
                    m1=v;
                    c1=j;
                }
                else
                {
                    if(v<m2)
                    {
                        m2=v;
                        c2=j;
                    }
                }
                if(l==0)
                    continue;
                v=sets[j][l-1];
                if(v>ma1)
                {
                    ma2=ma1;
                    ca2=ca1;
                    ma1=v;
                    ca1=j;
                }
                else
                {
                    if(v>ma2)
                    {
                        ma2=v;
                        ca2=j;
                    }
                }
            }
            if(m1!=INT_MAX&&m2!=INT_MAX)
            {
                if(p+m1>m2)
                {
                    printf("%i %i %i %i %i %i\n",i+1,p,c1+1,m1,c2+1,m2);
                    return 0;
                }
            }
            if(ma1!=-1&&ma2!=-1)
            {
                if(ma1+ma2>p)
                {
                    printf("%i %i %i %i %i %i\n",i+1,p,ca1+1,ma1,ca2+1,ma2);
                    return 0;
                }
            }
        }
    }
    printf("NIE\n");
    return 0;
}
