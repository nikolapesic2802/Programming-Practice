/*
	-http://ioi2017.org/tasks/editorial/prize.pdf , https://github.com/timpostuvan/CompetitiveProgramming/blob/master/Olympiad/IOI/Prize2017.cpp
*/
#include <bits/stdc++.h>
#include "prize.h"
using namespace std;

const int N=2e5+5;
map<int,vector<int> > mapa[N];
int sol=-1;
void solve(int l,int r)
{
    if(sol!=-1||l>r)
        return;
    int m=(l+r)>>1;
    vector<int> cur=ask(m);
    int sum=cur[0]+cur[1];
    if(sum==0)
    {
        sol=m;
        return;
    }
    int left=1,right=1;
    auto it=mapa[sum].upper_bound(m);
    if(it!=mapa[sum].end())
    {
        if((*it).second[0]==cur[0])
            right=0;
    }
    if(it!=mapa[sum].end())
    {
        if((*it).second[0]==cur[0])
            right=0;
    }
    if(it!=mapa[sum].begin())
        it--;
    if(it!=mapa[sum].begin())
    {
        if((*it).second[1]==cur[1])
            left=0;
    }
    mapa[sum][m]=cur;
    if(left)
        solve(l,m-1);
    if(right)
        solve(m+1,r);
}
int find_best(int n) {
    solve(0,n-1);
    return sol;
}
