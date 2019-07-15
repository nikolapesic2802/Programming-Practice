#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct par{
    int first, second;
};

const int N=13, M=8; ///Broj delova i dimenzija table
vector<vector<par> > deo[N];
vector<vector<par> > resenja; ///Sva resenja
int tabla[M][M]; ///Da li je polje popunjeno
bool uzeo[N]; ///Da li je deo iskoriscen
vector<par> trenutnoResenje; ///Lista delova koje sam trenutno uzeo

bool unutra(int x, int y){
    return (x>=0)&&(x<M)&&(y>=0)&&(y<M);
}
bool moze(int x, int y, int k, int o){
    for (auto p:deo[k][o])
        if ((!unutra(x+p.first,y+p.second))||(tabla[x+p.first][y+p.second]!=-1))
            return false;
    return true;
}
void editDeo(int x, int y, int k, int o, int sta){
    for (auto p:deo[k][o])
        tabla[x+p.first][y+p.second]=sta==0?-1:k;
    uzeo[k]=sta==0?0:1;
    if (sta==0)
        trenutnoResenje.pop_back();
    else
        trenutnoResenje.push_back({k,o});
}

void nadjiSvaResenja(int x=0, int y=0){ ///Dalja pretraga krece od kordinata x,y
    for (int i=x; i<M; i++){
        int j=0;
        if (i==x)
            j=y;
        for (; j<M; j++){
            if (tabla[i][j]!=-1) ///Ako je trenutno polje popunjeno, preskacemo ga
                continue;
            for (int k=0; k<N; k++){  ///Probamo da stavimo sve delove na trenutno polje
                if (uzeo[k]) ///Preskacemo delove koji su uzeti vec
                    continue;
                for (int o=0; o<(int)deo[k].size(); o++){  ///Prolazimo kroz sve orijentacije za trenutni deo
                    if (!moze(i,j,k,o))
                        continue;
                    editDeo(i,j,k,o,1);
                    nadjiSvaResenja(i,j);
                    editDeo(i,j,k,o,0);
                }
            }
            return; ///Postoji ne popunjeno polje sto znaci da ne moze biti resenje
        }
    }
    resenja.push_back(trenutnoResenje);
}

void init(){

    srand(time(NULL));

    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
            tabla[i][j]=-1;

    deo[0].push_back({{0,0},{1,0},{0,1},{1,1}});

	deo[1].push_back({{0,0},{0,1},{1,0},{2,0},{2,-1}});
	deo[1].push_back({{0,0},{1,0},{1,1},{1,2},{2,2}});

	deo[2].push_back({{0,0},{1,0},{1,-1},{0,1},{0,2}});

	deo[3].push_back({{0,0},{1,0},{1,-1},{1,-2},{2,-1}});
	deo[3].push_back({{0,0},{1,0},{1,-1},{2,0},{2,1}});
	deo[3].push_back({{0,0},{1,0},{1,-1},{2,-1},{1,1}});
	deo[3].push_back({{0,0},{0,1},{1,1},{2,1},{1,2}});

	deo[4].push_back({{0,0},{1,0},{1,1},{1,2},{1,3}});
	deo[4].push_back({{0,0},{0,1},{1,0},{2,0},{3,0}});
	deo[4].push_back({{0,0},{0,1},{0,2},{0,3},{1,3}});
	deo[4].push_back({{0,0},{1,0},{2,0},{3,0},{3,-1}});

	deo[5].push_back({{0,0},{0,1},{1,1},{2,1},{2,0}});
	deo[5].push_back({{0,0},{1,0},{1,1},{1,2},{0,2}});
	deo[5].push_back({{0,0},{0,1},{1,0},{2,0},{2,1}});
	deo[5].push_back({{0,0},{0,1},{0,2},{1,0},{1,2}});

	deo[6].push_back({{0,0},{1,0},{2,0},{1,1},{1,2},{0,2},{2,2}});
	deo[6].push_back({{0,0,},{0,1},{0,2},{1,1},{2,0},{2,1},{2,2}});

	deo[7].push_back({{0,0},{1,0},{2,0},{0,1},{0,2}});
	deo[7].push_back({{0,0},{0,1},{0,2},{1,2},{2,2}});
	deo[7].push_back({{0,0},{1,0},{2,0},{2,-1},{2,-2}});
	deo[7].push_back({{0,0},{1,0},{2,0},{2,1},{2,2}});

	deo[8].push_back({{0,0},{1,0},{1,-1},{1,1}});
	deo[8].push_back({{0,0},{1,0},{2,0},{1,1}});
	deo[8].push_back({{0,0},{0,1},{0,2},{1,1}});
	deo[8].push_back({{0,0},{1,0},{1,-1},{2,0}});

	deo[9].push_back({{0,0},{0,1},{1,1},{1,2}});
	deo[9].push_back({{0,0},{1,0},{1,-1},{2,-1}});

	deo[10].push_back({{0,0},{0,1},{1,1},{2,1}});
	deo[10].push_back({{0,0},{1,0},{1,-1},{1,-2}});
	deo[10].push_back({{0,0},{1,0},{2,0},{2,1}});
	deo[10].push_back({{0,0},{1,0},{0,1},{0,2}});

	deo[11].push_back({{0,0},{1,0},{1,-1},{1,1},{1,2}});
	deo[11].push_back({{0,0},{1,0},{1,1},{2,0},{3,0}});
	deo[11].push_back({{0,0},{0,1},{0,2},{1,2},{0,3}});
	deo[11].push_back({{0,0},{1,0},{2,0},{3,0},{2,-1}});

	deo[12].push_back({{0,0},{0,1},{0,2},{1,0},{1,1},{1,2}});
	deo[12].push_back({{0,0},{0,1},{1,1},{1,0},{2,0},{2,1}});
}


vector<int> dx,dy;
vector<char> mapa={'.','#'};
int D=2; ///Broj piksela po kvadratu puzle
void printDeo(int a,int b){
    if(dx.empty())
        for(int i=0;i<D;i++)
            for(int j=0;j<D;j++)
                dx.push_back(i),dy.push_back(j);
    vector<vector<bool> > imam(2*D*M,vector<bool>(2*D*M));
    int minx=INT_MAX,maxx=0,miny=INT_MAX,maxy=0;
    for(auto p:deo[a][b]){
        int x=D*p.first+D*M,y=D*p.second+D*M;
        for(int k=0;k<D*D;k++){
            int xx=x+dx[k],yy=y+dy[k];
            imam[xx][yy]=1;
            minx=min(minx,xx);
            maxx=max(maxx,xx);
            miny=min(miny,yy);
            maxy=max(maxy,yy);
        }
    }
    for(int i=minx;i<=maxx;i++){
        for(int j=miny;j<=maxy;j++)
            printf("%c",mapa[imam[i][j]]);
        printf("\n");
    }
}
void printResenje2(int a){
    for(auto p:resenja[a]){
        printf("Stavi oblik sa slike rotiran kao na slici tako da pokriva prvo slobodno mesto(Od gore ka dole i od levo ka desno)\n");
        printDeo(p.first,p.second);
        system("PAUSE");
        system("cls");
    }

}

void printResenje(int a){
    int ind=0;
    for (int i=0; i<M; i++)
        for (int j=0; j<M; j++)
            if(tabla[i][j]==-1)
                editDeo(i,j,resenja[a][ind].first,resenja[a][ind].second,1),ind++;
    for (int i=0; i<M; i++){
        for (int j=0; j<M; j++)
            printf("%2i ", tabla[i][j]);
        printf("\n");
    }
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
            tabla[i][j]=-1;
    system("PAUSE");
}

void meni(){
    int n=resenja.size();
    while(true){
        system("cls");
        printf("%i resenja pronadjeno, odaberi jedno od njih (ukucaj broj od 0 do %i ili -1 za random resenje!)\n",n,n-1);
        int a;
        scanf("%i",&a);
        while(a<-1||a>=n){
            printf("Unesi validnu opciju!\n");
            scanf("%i",&a);
        }
        if(a==-1)
            a=rng()%n;
        system("cls");
        printResenje(a);
        system("cls");
        printf("Da li hoces jos jedno resenje?\n1-Da\n2-Ne\n");
        scanf("%i",&a);
        while(a<1||a>2){
            printf("Unesi validnu opciju!\n");
            scanf("%i",&a);
        }
        if(a==2)
            break;
    }
}

int main(){
    init();
    nadjiSvaResenja();
    meni();
    return 0;
}
