/*
    - Use an implicit segment tree to calculate and update everything.
    - It can be done with only one segment tree that stores the maximum and the sum for every interval.
    - Maximum being the highest value of the rail in the interval and Sum basically being the height of the ending position
*/
#include <bits/stdc++.h>

using namespace std;

struct node{
    node* left;
    node* right;
    int l,r,lazy,m,sum; /// m=maximum
    bool on;
    node()
    {
        left=NULL;
        right=NULL;
        lazy=0;
        m=0;
        sum=0;
        on=false;
    }
    void propagate(){
        if(left==NULL&&l!=r)
        {
            left=new node;
            right=new node;
            int m=(l+r)>>1;
            left->l=l;
            left->r=m;
            right->l=m+1;
            right->r=r;
        }
        if(on){
            if(l!=r)
            {
                left->lazy=right->lazy=lazy;
                left->sum=left->m=(left->r-left->l+1)*lazy;
                left->on=right->on=on;
                right->sum=right->m=(right->r-right->l+1)*lazy;
            }
        }
        on=false;
    }
    int solve(int h)
    {
        if(l==r)
            return l-1;
        propagate();
        if(left->m>h)
            return left->solve(h);
        return right->solve(h-left->sum);
    }
    void update(int qs,int qe,int d)
    {
        if(qs>r||qe<l)
            return;
        if(qs<=l&&qe>=r)
        {
            lazy=d;
            on=true;
            sum=m=(r-l+1)*lazy;
            return;
        }
        propagate();
        left->update(qs,qe,d);
        right->update(qs,qe,d);
        sum=left->sum+right->sum;
        m=max(left->m,right->m+left->sum);
    }
};
int main()
{
    int n;
    scanf("%i",&n);
    node segmentTree;
    segmentTree.l=1;
    segmentTree.r=n;
    while(true)
    {
        string s;
        cin >> s;
        if(s[0]=='E')
            break;
        if(s[0]=='Q')
        {
            int t;
            scanf("%i",&t);
            if(t>=segmentTree.m)
                printf("%i\n",n);
            else
                printf("%i\n",segmentTree.solve(t));
        }
        else
        {
            int l,r,x;
            scanf("%i %i %i",&l,&r,&x);
            segmentTree.update(l,r,x);
        }
    }
    return 0;
}
