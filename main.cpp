#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;

template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}

const int N=13,M=8;
vector<pair<int,int> > piece[N];
bool inside(int x,int y)
{
    return x>=0&&x<M&&y>=0&&y<M;
}
int done[M][M];
int main()
{
	piece[0]={{0,0},{1,0},{0,1},{1,1}};
	piece[1]={{0,0},{0,1},{1,0},{2,0},{2,-1}};
	piece[2]={{0,0},{1,0},{1,-1},{0,1},{0,2}};
	piece[3]={{0,0},{1,0},{1,-1},{1,-2},{2,-1}};
	piece[4]={{0,0},{1,0},{1,1},{1,2},{1,3}};
	piece[5]={{0,0},{0,1},{1,1},{2,1},{2,0}};
	piece[6]={{0,0},{1,0},{2,0},{1,1},{1,2},{0,2},{2,2}};
	piece[7]={{0,0},{1,0},{2,0},{0,1},{0,2}};
	piece[8]={{0,0},{1,0},{1,-1},{1,1}};
	piece[9]={{0,0},{0,1},{1,1},{1,2}};
	piece[10]={{0,0},{0,1},{1,1},{2,1}};
	piece[11]={{0,0},{1,0},{1,-1},{1,1},{1,2}};
	piece[12]={{0,0},{0,1},{0,2},{1,0},{1,1},{1,2}};
	int cntt=0;
	for(int i=0;i<N;i++)
        cntt+=piece[i].size();
	vector<int> a;
	ll total=1;
	for(int i=0;i<N;i++)
        a.pb(i),total*=i+1;
    ll cnt=1;
    ll start=clock();
    do{
        if(cnt%(int)1e6==0)
        {
            ll proslo=clock()-start;
            printf("Procena vremena: %lld s   %lld/%lld\n",proslo*total/cnt/1000,cnt,total);
        }
        vector<pair<int,int> > reset;
        bool uspeo=true;
        int tr=0;
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<M;j++)
            {
                if(done[i][j])
                    continue;
                for(auto p:piece[a[tr]])
                {
                    if(!inside(i+p.f,j+p.s)||done[i+p.f][j+p.s])
                    {
                        uspeo=false;
                        break;
                    }
                    done[i+p.f][j+p.s]=1;
                    reset.pb({i+p.f,j+p.s});
                }
                tr++;
                if(!uspeo)
                    break;
            }
            if(!uspeo)
                break;
        }
        for(auto p:reset)
            done[p.f][p.s]=0;
        if(uspeo&&reset.size()==64)
        {
            cout << a << endl;
        }
        cnt++;
    }while(next_permutation(all(a)));
    return 0;
}
