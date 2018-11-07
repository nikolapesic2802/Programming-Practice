
/*
    - Look at x and y coordinate separately
    - For every rectangle make segments [x1,x2+1] and [y1,y2+1]
    - For every position greedily choose the segment that started before or at that position and ends the soonest and place that rook at the current position
    - If there is no available interval at some position or we don't pick a position for an interval before it ends the answer is No
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
    int n;
    scanf("%i",&n);
    vector<pair<int,int> > startx[n+1],starty[n+1];
    for(int i=0;i<n;i++)
    {
        int x1,y1,x2,y2;
        scanf("%i %i %i %i",&x1,&y1,&x2,&y2);
        startx[x1].pb({x2+1,i});
        starty[y1].pb({y2+1,i});
    }
    vector<pair<int,int> > sol(n);
    set<pair<int,int> > intervals;
    for(int i=1;i<=n;i++)
    {
        for(auto p:startx[i])
            intervals.insert(p);
        if(intervals.size()==0)
        {
            printf("NIE\n");
            return 0;
        }
        pair<int,int> prvi=*intervals.begin();
        intervals.erase(intervals.begin());
        int end=prvi.first;
        int index=prvi.second;
        if(end<=i)
        {
            printf("NIE\n");
            return 0;
        }
        sol[index].first=i;
    }
    intervals.clear();
    for(int i=1;i<=n;i++)
    {
        for(auto p:starty[i])
            intervals.insert(p);
        if(intervals.size()==0)
        {
            printf("NIE\n");
            return 0;
        }
        pair<int,int> prvi=*intervals.begin();
        intervals.erase(intervals.begin());
        int end=prvi.first;
        int index=prvi.second;
        if(end<=i)
        {
            printf("NIE\n");
            return 0;
        }
        sol[index].second=i;
    }
    for(auto p:sol)
    {
        printf("%i %i\n",p.first,p.second);
    }
    return 0;
}
