/*
    - Keep a variable k - how many cards need to be wrong until the end.
    - If there is a card with value k in our current set, pick it
    - else, If there is a card with a value greater than k, pick it and decrease k by 1.
    - else, pick the card with the lowest value and decrease k by 1.
    - Test if the cards we picked form a solution that is correct, if yes print it, if no print -1
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    int t=k;
    multiset<int> karte;
    karte.insert(INT_MAX);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        karte.insert(a);
    }
    vector<int> sol;
    for(int i=0;i<n;i++)
    {
        int a=*karte.lower_bound(k);
        if(a==INT_MAX)
        {
            a=*karte.begin();
        }
        sol.pb(a);
        karte.erase(karte.find(a));
        if(a!=k)
            k--;
        continue;
    }
    int cnt=0;
    for(int i=n-1;i>=0;i--)
    {
        if(sol[i]>cnt)
            cnt++;
    }
    if(cnt==t)
    {
        for(int i=0;i<n;i++)
        {
            printf("%i ",sol[i]);
        }
    }
    else
    {
        printf("-1");
    }
    return 0;
}
