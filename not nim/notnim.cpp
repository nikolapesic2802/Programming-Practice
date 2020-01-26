// - https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI16-Not_Nim.cpp
// -It's the same as this solution and i really can't explain it better than he did.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,a,sol=0,saved=0;
    priority_queue<int> q;
    scanf("%i",&n);
    for(int i=0;i<n;i++){
        scanf("%i",&a);
        int cnt=0;
        for(int j=30;~j;j--)
            if(a&(1<<j))
                for(int k=j;~k&&(a&(1<<k));k--,cnt++)
                    j=0;
        q.push(cnt);
        while(a)
            sol++,a/=2;
        sol++;
    }
    q.pop();
    while(q.size()){
        int tr=q.top();
        q.pop();
        if(tr==1)
            sol--;
        else
            q.push(tr-1),q.pop();
    }
    printf("%i",2*sol-1);
    return 0;
}
