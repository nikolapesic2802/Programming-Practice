/*
    -Trick is to xor all the positions where there is a 1
    -By flipping the right coin, you can make this value exactly equal to c
*/
#include <bits/stdc++.h>
//#include "coins.h"

using namespace std;

#define ll long long
#define pb push_back


vector<int> coin_flips(vector<int> b, int c) {
    vector<int> flips(1);
    for(int i=0;i<b.size();i++)
    {
        if(b[i]==1)
            c^=i;
    }
    flips[0]=c;
    return flips;
}

int find_coin(vector<int> b) {
    int p=0;
    for(int i=0;i<b.size();i++)
    {
        if(b[i]==1)
            p^=i;
    }
    return p;
}

int main()
{
    int n=10;
    vector<int> b(n);
    for(int i=0;i<n;i++)
        b[i]=rand()%2;
    int poz=rand()%n;
    for(auto p:b)
        printf("%i ",p);
    printf("\n%i\n",poz);
    vector<int> pp=coin_flips(b,poz);
    printf("Flipujem %i\n",pp[0]);
    for(auto p:pp)
        b[p]=(b[p]+1)%2;
    int ret=find_coin(b);
    printf("%i %i\n",poz,ret);
    return 0;
}
