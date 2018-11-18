/*
    -The main thing to do in this task is to think about which arrays are possible to construct and which are not
    -It turns out that the array choice is very limited so we can do something greedy:
    -For every element in order, we try to take the next available element as its right child, if we succeed we recursively call for that element and increase next by one.
    -If we get to an element that didn't get picked before it must mean that it is the new root of the tree so we set it as the root and set the old root as its left child and start calling the recursive function from the new root
    -The only useful query we can ask is of format (pos,pos,pos,pos+x) and that query tests if the element at position pos can be an ancestor of all the nodes from pos to pos+x.
*/
#include <bits/stdc++.h>
#include "popa.h"

using namespace std;

#define ll long long
#define pb push_back

int nxt;
vector<int> parent;
void take(int poz,int n,int* Left,int* Right)
{
    nxt++;
    while(nxt<n&&query(poz,poz,poz,nxt))
    {
        Left[nxt]=Right[poz];
        Right[poz]=nxt;
        parent[nxt]=poz;
        take(nxt,n,Left,Right);
    }
}
int solve(int n,int* Left,int* Right)
{
    for(int i=0;i<n;i++)
    {
        Left[i]=-1;
        Right[i]=-1;
    }
    parent.resize(n);
    fill(parent.begin(),parent.end(),-1);
    int root=-1;
    nxt=0;
    for(int i=0;i<n;i++)
    {
        if(parent[i]==-1){
            if(root!=-1){
                Left[i]=root;
                parent[root]=i;
            }
            root=i;
            take(i,n,Left,Right);
        }
    }
    return root;
}
