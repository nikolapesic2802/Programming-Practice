#include <stdio.h>
#include <vector>
#include <queue>
#define pb push_back
using namespace std;

int main()
{
	int m,n,l;
	scanf("%i %i %i",&m,&n,&l);
	vector<int> poc(l);
	for(int i=0;i<l;i++)
        scanf("%i",&poc[i]),poc[i]--;
    vector<vector<int> > start(n);
    vector<vector<int> > graf(m);
    vector<vector<int> > pripada(n,vector<int>(n,-1));
    for(int i=0;i<m;i++)
    {
        int a;
        scanf("%i",&a);
        vector<int> niz(a);
        for(int i=0;i<a;i++)
            scanf("%i",&niz[i]),niz[i]--;
        niz.pb(niz[0]);
        for(int j=0;j<a;j++)
        {
            start[niz[j]].pb(i);
            int x=min(niz[j],niz[j+1]);
            int y=max(niz[j],niz[j+1]);
            if(pripada[x][y]!=-1)
                graf[i].pb(pripada[x][y]),graf[pripada[x][y]].pb(i);
            else
                pripada[x][y]=i;
        }
    }
    vector<int> sol(m);
    for(int i=0;i<poc.size();i++)
    {
        int p=poc[i];
        vector<int> depth(m);
        queue<int> q;
        for(int j=0;j<start[p].size();j++)
        {
            int d=start[p][j];
            depth[d]=1;
            q.push(d);
        }
        while(q.size())
        {
            int tr=q.front();
            q.pop();
            for(int j=0;j<graf[tr].size();j++)
            {
                int d=graf[tr][j];
                if(depth[d])
                    continue;
                depth[d]=depth[tr]+1;
                q.push(d);
            }
        }
        for(int i=0;i<m;i++)
            sol[i]+=depth[i]-1;
    }
    int mi=1000000000;
    for(int i=0;i<m;i++)
        mi=min(mi,sol[i]);
    printf("%i\n",mi);
    return 0;
}
