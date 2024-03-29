#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
/*
accept everything that you can.
if you can not accept the current order find if you accepted an order bigger than the current one and accept the current one instead.
*/
int main()
{
    int n;
    scanf("%i",&n);
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++)
    {
        scanf("%i",&a[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%i",&b[i]);
    }
    set<pair<int,int>,greater<pair<int,int> > > completed;
    ll boxes=0;
    for(int i=0;i<n;i++)
    {
        boxes+=a[i];
        if(boxes>=b[i])
        {
            boxes-=b[i];
            completed.insert({b[i],i+1});
        }
        else
        {
            int s=(*completed.begin()).first;
            if(s>b[i])
            {
                boxes+=s-b[i];
                completed.erase(completed.begin());
                completed.insert({b[i],i+1});
            }
        }
    }
    vector<int> index;
    for(auto p:completed)
        index.pb(p.second);
    sort(index.begin(),index.end());
    printf("%i\n",index.size());
    for(auto p:index)
    {
        printf("%i ",p);
    }
    return 0;
}
