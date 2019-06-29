#include <bits/stdc++.h>

using namespace std;

int main()
{
    while(true)
    {
        int x,y;
        cin >> x >> y;
        if(x<y)
        {
            for(int k=0;;k++)
                if((1<<(k+1))*(x+1)-1>=y)
                {
                    cout << "H " << (1<<k)*(x+1)-1 << endl;
                    y=(1<<k)*(x+1)-1;
                    break;
                }
        }
        else
            for(int k=0;;k++)
                if((1<<(k+1))*(y+1)-1>=x){
                    cout << "V " << (1<<k)*(y+1)-1 << endl;
                    x=(1<<k)*(y+1)-1;
                    break;
                }
        if(x==1&&y==1)
            break;
    }
}
