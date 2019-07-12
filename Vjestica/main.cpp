#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=10;
int tabla[N][N];
int x=N/2,y=N/2;
vector<char> mapa={'.','X','#','P'};
bool nasaoPickaxe=false;
int materijali;
bool inside(int x,int y)
{
    return x>=0&&x<N&&y>=0&&y<N&&(tabla[x][y]==0||tabla[x][y]==3||(tabla[x][y]==2&&nasaoPickaxe));
}
void printBoard()
{
    system("cls");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            printf("%c",mapa[tabla[i][j]]);
        printf("\n");
    }
    printf("Materijali: %i\n",materijali);
}
void dodajZidove()
{
    int L=20;
    while(L)
    {
        int x=rng()%N,y=rng()%N;
        if(tabla[x][y]==0)
        {
            tabla[x][y]=2;
            L--;
        }
    }
}
void dodajPickaxe()
{
    int L=1;
    while(L)
    {
        int x=rng()%N,y=rng()%N;
        if(tabla[x][y]==0)
        {
            tabla[x][y]=3;
            L--;
        }
    }
}
int main()
{
    cout << '\a';
    tabla[x][y]=1;
    dodajZidove();
    dodajPickaxe();
	while(true)
    {
        printBoard();
        string s;
        cin >> s;
        tabla[x][y]=0;
        if(s=="w")
            if(inside(x-1,y))
                x--;
        if(s=="a")
            if(inside(x,y-1))
                y--;
        if(s=="s")
            if(inside(x+1,y))
                x++;
        if(s=="d")
            if(inside(x,y+1))
                y++;
        if(s=="bw")
            if(inside(x-1,y)&&tabla[x-1][y]==0)
                tabla[x-1][y]=2,materijali--;
        if(s=="ba")
            if(inside(x,y-1)&&tabla[x][y-1]==0)
                tabla[x][y-1]=2,materijali--;
        if(s=="bs")
            if(inside(x+1,y)&&tabla[x+1][y]==0)
                tabla[x+1][y]=2,materijali--;
        if(s=="bd")
            if(inside(x,y+1)&&tabla[x][y+1]==0)
                tabla[x][y+1]=2,materijali--;
        if(tabla[x][y]==3)
            nasaoPickaxe=true;
        if(tabla[x][y]==2)
            materijali++;
        tabla[x][y]=1;
    }
    return 0;
}
