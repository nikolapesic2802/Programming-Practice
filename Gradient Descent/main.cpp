#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
vector<pair<int,int> > coins;
int calc(int x,int y)
{
    int res=0;
    for(auto p:coins)
    {
        res+=abs(p.first-x)+abs(p.second-y);
    }
    return res;
}
int main()
{
    int n,m,k;
    scanf("%i %i %i",&n,&m,&k);
    int lx=1,rx=n,ly=1,ry=m;
    while(lx!=rx||ly!=ry)
    {
        int midx=(lx+rx)/2;
        int midy=(ly+ry)/2;
        int mm,md,mr;
        printf("? %i %i\n",midx,midy);
        scanf("%i",&mm);
        if(lx!=rx)
        {
            printf("? %i %i\n",midx+1,midy);
            scanf("%i",&md);
            if(mm<md)
            {
                rx=midx;
            }
            if(mm>md)
            {
                lx=midx+1;
            }
            if(mm==md)
            {
                lx=rx=midx;
            }
        }
        if(ly!=ry)
        {
            printf("? %i %i\n",midx,midy+1);
            scanf("%i",&mr);
            if(mm<mr)
            {
                ry=midy;
            }
            if(mm>mr)
            {
                ly=midy+1;
            }
            if(mm==mr)
            {
                ly=ry=midy;
            }
        }
    }
    int sol;
    printf("? %i %i\n",lx,ly);
    scanf("%i",&sol);
    printf("! %i\n",sol);
    return 0;
}
