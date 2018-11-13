/*
    -Binary search for the answer
    -Test if 2 squares can cover every point by placing one square in the lower left, lower right, upper right and upper left corners and calculating the greatest distance between the points that are not in the square
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "group.h"

#define ll long long
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()
vector<pair<int,int> > cords;
int getMinimumDelay(int n, std::vector<int> X, std::vector<int> Y)
{
    if(n==1)
        return 0;
    cords.resize(n);
    multiset<int> y;
    for(int i=0; i<n; i++)
    {
        cords[i].first=X[i]+Y[i];
        cords[i].second=X[i]-Y[i];
        //printf("%i %i\n",cords[i].first,cords[i].second);
        y.insert(X[i]-Y[i]);
    }
    sort(cords.begin(),cords.end());
    vector<int> xx,yy;
    for(int i=0; i<n; i++)
    {
        xx.pb(cords[i].first);
        yy.pb(cords[i].second);
    }
    sort(xx.begin(),xx.end());
    sort(yy.begin(),yy.end());
    int x1=xx[0];
    int y1=yy[0];
    int x2=xx[n-1];
    int y2=yy[n-1];
    int l=0,r=INT_MAX;
    while(l<r)
    {
        int mid=((ll)l+r)/2;
        vector<int> x,y;
        for(int i=0; i<n; i++)
        {
            if(cords[i].first<=(ll)x1+mid&&cords[i].second<=(ll)y1+mid)
            {

            }
            else
            {
                x.pb(cords[i].first);
                y.pb(cords[i].second);
            }
        }
        if(x.size()<2)
        {
            r=mid;
            continue;
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        int xx1=x[0];
        int yy1=y[0];
        int xx2=x[x.size()-1];
        int yy2=y[y.size()-1];
        bool test=false;
        if(max(xx2-xx1,yy2-yy1)<=mid)
        {
            test=true;
        }
        x.clear();
        y.clear();
        for(int i=0; i<n; i++)
        {
            if(cords[i].first>=(ll)x2-mid&&cords[i].second>=(ll)y2-mid)
            {

            }
            else
            {
                x.pb(cords[i].first);
                y.pb(cords[i].second);
            }
        }
        if(x.size()<2)
        {
            r=mid;
            continue;
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        xx1=x[0];
        yy1=y[0];
        xx2=x[x.size()-1];
        yy2=y[y.size()-1];
        if(max(xx2-xx1,yy2-yy1)<=mid)
        {
            test=true;
        }
        x.clear();
        y.clear();
        for(int i=0; i<n; i++)
        {
            if(cords[i].first>=(ll)x2-mid&&cords[i].second<=(ll)y1+mid)
            {

            }
            else
            {
                x.pb(cords[i].first);
                y.pb(cords[i].second);
            }
        }
        if(x.size()<2)
        {
            r=mid;
            continue;
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        xx1=x[0];
        yy1=y[0];
        xx2=x[x.size()-1];
        yy2=y[y.size()-1];
        if(max(xx2-xx1,yy2-yy1)<=mid)
        {
            test=true;
        }
        x.clear();
        y.clear();
        for(int i=0; i<n; i++)
        {
            if(cords[i].first<=(ll)x1+mid&&cords[i].second>=(ll)y2-mid)
            {

            }
            else
            {
                x.pb(cords[i].first);
                y.pb(cords[i].second);
            }
        }
        if(x.size()<2)
        {
            r=mid;
            continue;
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        xx1=x[0];
        yy1=y[0];
        xx2=x[x.size()-1];
        yy2=y[y.size()-1];
        if(max(xx2-xx1,yy2-yy1)<=mid)
        {
            test=true;
        }
        if(test)
        {
            r=mid;
        }
        else
        {
            l=mid+1;
        }
    }
    return l;
}

int main()
{
    int N;
    scanf("%d", &N);

    std::vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &X[i], &Y[i]);
    }

    printf("%d\n", getMinimumDelay(N, X, Y));
    return 0;
}
