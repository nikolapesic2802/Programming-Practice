#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

/*
     - Find the first c with k b's around add it to the answer and "delete" the c and b's.
*/
int main()
{
    int n,k;
    scanf("%i %i",&n,&k);
    char s[n];
    scanf("%s",s);
    vector<vector<int> > sol;
    vector<int> space;
    space.pb(0);
    int c=0;
    vector<int> index;
    for(int i=0;i<n;i++)
    {
        index.pb(i);
        if(s[i]=='c')
        {
            c++;
            space.pb(0);
        }
        else
        {
            space[c]++;
        }
        if(c&&space[c]+space[c-1]>=k)
        {
            vector<int> tr;
            for(int i=0;i<k+1;i++)
            {
                tr.pb(index.back());
                index.pop_back();
            }
            reverse(tr.begin(),tr.end());
            sol.pb(tr);
            int dif=space[c--];
            space.pop_back();
            space[c]-=k-dif;
        }
    }
    reverse(sol.begin(),sol.end());
    for(auto p:sol)
    {
        for(auto d:p)
        {
            printf("%i ",d+1);
        }
        printf("\n");
    }
    return 0;
}
