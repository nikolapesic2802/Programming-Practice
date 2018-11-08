/*
    - Find the closest key that unlocks the door to the left and to the right for every door.
    - For every room expand the interval that we can get to from that room based on if we can find the key to the door to the left or to the right
      in the current interval we can reach from that room.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
const int N=5*1e5+5;
vector<int> hi(N),lo(N),l(N),r(N);
bool on(int l,int r,int x){return x>=l&&x<=r;}
bool can(int l,int r,int x){return (hi[x]>=0&&on(l,r,hi[x]))||(lo[x]>=0&&on(l,r,lo[x]));}
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> cor(n-1);
    for(int i=0;i<n-1;i++)
        scanf("%i",&cor[i]);
    vector<vector<int> > sobe(n);
    for(int i=0;i<n;i++)
    {
        int b;
        scanf("%i",&b);
        for(int j=0;j<b;j++)
        {
            int a;
            scanf("%i",&a);
            sobe[i].pb(a);
        }
    }
    vector<int> keys(n,-1);
    for(int i=0;i<n-1;i++)
    {
        for(auto p:sobe[i])
            keys[p]=i;
        lo[i]=keys[cor[i]];
    }
    fill(keys.begin(),keys.end(),-1);
    for(int i=n-1;i>0;i--)
    {
        for(auto p:sobe[i])
            keys[p]=i;
        hi[i-1]=keys[cor[i-1]];
    }
    for(int i=0;i<n;i++)
    {
        l[i]=r[i]=i;
        while(true)
        {
            if(l[i]>0&&can(l[i],r[i],l[i]-1))
            {
                r[i]=max(r[i],r[l[i]-1]);
                l[i]=l[l[i]-1];
            }
            else
                if(r[i]<n-1&&can(l[i],r[i],r[i]))
                    r[i]++;
                else
                    break;
        }
    }
    int q;
    scanf("%i",&q);
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%i %i",&x,&y);
        x--;
        y--;
        if(on(l[x],r[x],y))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
