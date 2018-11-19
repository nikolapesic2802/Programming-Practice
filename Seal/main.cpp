/*
    -Greedily apply the pattern to the upper left most 'x'.
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back

using namespace std;
void test_case()
{
    int X,Y,x,y;
    //cin >> X >> Y >> x >> y;
    scanf("%i %i %i %i",&X,&Y,&x,&y);
    vector<string> document(X),pattern(x);
    char c[Y+1],c2[y+1];
    for(int i=0;i<X;i++)
    {
        scanf("%s",c);
        document[i]=c;
    }
    for(int i=0;i<x;i++)
    {
        scanf("%s",c2);
        pattern[i]=c2;
    }
    vector<pair<int,int> > poz;
    for(int row=0;row<x;row++)
    {
        for(int col=0;col<y;col++)
        {
            if(pattern[row][col]=='x')
            {
                int r=row,c=col;
                for(int row1=0;row1<x;row1++)
                {
                    for(int col1=0;col1<y;col1++)
                    {
                        if(pattern[row1][col1]=='x')
                        {
                            //printf("%i %i\n",row1-r,col1-c);
                            poz.pb({row1-r,col1-c});
                        }
                    }
                }
                row=x;
                break;
            }
        }
    }
    for(int row=0;row<X;row++)
    {
        for(int col=0;col<Y;col++)
        {
            if(document[row][col]=='x')
            {
                //printf("Usao za %i %i\n",row,col);
                for(int i=0;i<poz.size();i++)
                {
                    x=row+poz[i].first;
                    y=col+poz[i].second;
                    //printf("Testiram %i %i\n",x,y);
                    if(x<0||x>=X||y<0||y>=Y)
                    {
                        printf("NIE\n");
                        return;
                    }
                    if(document[x][y]!='x')
                    {
                        printf("NIE\n");
                        return;
                    }
                    document[x][y]='.';
                }
            }
        }
    }
    printf("TAK\n");
}
int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    int t;
    scanf("%i",&t);
    //cin >> t;
    while(t--)
        test_case();
    return 0;
}
