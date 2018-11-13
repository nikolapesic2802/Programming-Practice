/*
    - I had 20 minutes left for this problem during the competition so i just started coding the first greedy that came to mind: it was as follows:
    - Keep the value of how many tables(t)/formulas(f) we had to finish the last page with.
    - If x<y OR x==y&f>0 (i forgot to add this OR in the competition :( ) than add last pages formulas to the current ones and check if  number_of_tables*k<number_of_formulas
      if that is the case then we need to set our f value to number_of_formulas-number_of_tables*k.
    - Its all the same but reversed if the if isn't true
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()

int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    vector<int> xx(n),yy(n);
    for(int i=0;i<n;i++)
        scanf("%i",&xx[i]);
    for(int i=0;i<n;i++)
        scanf("%i",&yy[i]);
    int t=0,f=0;
    for(int i=0;i<n;i++)
    {
        int x=xx[i],y=yy[i];
        //printf("%i %i\n",t,f);
        if(t>k||f>k)
        {
            printf("NO\n");
            return 0;
        }
        if(x<y||x==y&&f>0)
        {
                y+=f;
                if((ll)x*k<y)
                {
                    f=y-x*k;
                    t=0;
                }
                else
                {
                    f=0;
                    t=0;
                }
        }
        else
        {
                x+=t;
                if((ll)y*k<x)
                {
                    t=x-y*k;
                    f=0;
                }
                else
                {
                    f=0;
                    t=0;
                }
        }
    }
    if(t>k||f>k)
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    return 0;
    return 0;
}
