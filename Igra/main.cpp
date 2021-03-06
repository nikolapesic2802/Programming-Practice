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


int dp[5][5][5][5][2][2][2];
int bestmove[5][5][5][5][2][2][2]; ///0-a-a, 1-a-b, 2-b-a, 3-b-b, 4-split
#define dp dp[a1][b1][a2][b2][potez][split1][split2]
int calc(int a1,int b1,int a2,int b2,int potez,int split1,int split2)
{
    if(a1==0&&b1==0)
        return 2;
    if(a2==0&&b2==0)
        return 1;
    if(dp!=-1)
        return dp;
    dp=0;
    if(potez==1)
    {
        bool imaDraw=false;
        int sta;
        if(a1==0&&split1==0)
        {
            if(b1%2==0)
            {
                int sol=calc(b1/2,b1/2,a2,b2,2,1,split2);
                if(sol==1)
                {
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=4;
                    //printf("SPLIT!\n");
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=4;
            }
        }
        if(b1==0&&split1==0)
        {
            if(a1%2==0)
            {
                int sol=calc(a1/2,a1/2,a2,b2,2,1,split2);
                if(sol==1)
                {
                    //printf("SPLIT!\n");
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=4;
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=4;
            }
        }
        if(a1!=0)
        {
            if(a2!=0)
            {
                int sol=calc(a1,b1,(a2+a1)%5,b2,2,split1,split2);
                if(sol==1){
                    //printf("a-a\n");
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=0;
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=0;
            }
            if(b2!=0)
            {
                int sol=calc(a1,b1,a2,(b2+a1)%5,2,split1,split2);
                if(sol==1){
                    //printf("a-b\n");
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=1;
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=1;
            }
        }
        if(b1!=0)
        {
            if(a2!=0)
            {
                int sol=calc(a1,b1,(a2+b1)%5,b2,2,split1,split2);
                if(sol==1){
                    //printf("b-a\n");
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=2;
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=2;
            }
            if(b2!=0)
            {
                int sol=calc(a1,b1,a2,(b2+b1)%5,2,split1,split2);
                if(sol==1){
                    //printf("b-b\n");
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=3;
                    return dp=1;
                }
                if(sol==0)
                    imaDraw=true,sta=3;
            }
        }
        if(imaDraw)
        {
            bestmove[a1][b1][a2][b2][potez][split1][split2]=sta;
            return dp=0;
        }
        return dp=2;
    }
    else
    {
        bool imaDraw=false;
        int sta;
        if(a2==0&&split2==0)
        {
            if(b2%2==0)
            {
                int sol=calc(a1,b1,b2/2,b2/2,1,split1,1);
                if(sol==2)
                {
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=4;
                    //printf("SPLIT!\n");
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=4;
            }
        }
        if(b2==0&&split2==0)
        {
            if(a2%2==0)
            {
                int sol=calc(a1,b1,a2/2,a2/2,1,split1,1);
                if(sol==2)
                {
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=4;
                    //printf("SPLIT!\n");
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=4;
            }
        }
        if(a2!=0)
        {
            if(a1!=0)
            {
                int sol=calc((a1+a2)%5,b1,a2,b2,1,split1,split2);
                if(sol==2){
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=0;
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=0;
            }
            if(b1!=0)
            {
                int sol=calc(a1,(b1+a2)%5,a2,b2,1,split1,split2);
                if(sol==2){
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=1;
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=1;
            }
        }
        if(b2!=0)
        {
            if(a1!=0)
            {
                int sol=calc((a1+b2)%5,b1,a2,b2,1,split1,split2);
                if(sol==2){
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=2;
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=2;
            }
            if(b1!=0)
            {
                int sol=calc(a1,(b1+b2)%5,a2,b2,1,split1,split2);
                if(sol==2){
                    bestmove[a1][b1][a2][b2][potez][split1][split2]=3;
                    return dp=2;
                }
                if(sol==0)
                    imaDraw=true,sta=3;
            }
        }
        if(imaDraw)
        {
            bestmove[a1][b1][a2][b2][potez][split1][split2]=sta;
            return dp=0;
        }
        return dp=1;
    }
}
#undef dp
struct state{
    int a1,b1,a2,b2,player,split1,split2;

};
state no={-1,-1,-1,-1,-1,-1,-1};
state makeMove(int sta,state tr)
{
    if(sta==0)
    {
        if(tr.a1==0||tr.a2==0)
            return no;
        tr.a2=(tr.a2+tr.a1)%5;
    }
    if(sta==1)
    {
        if(tr.a1==0||tr.b2==0)
            return no;
        tr.b2=(tr.a1+tr.b2)%5;
    }
    if(sta==2)
    {
        if(tr.b1==0||tr.a2==0)
            return no;
        tr.a2=(tr.a2+tr.b1)%5;
    }
    if(sta==3)
    {
        if(tr.b1==0||tr.b2==0)
            return no;
        tr.b2=(tr.b2+tr.b1)%5;
    }
    if(sta==4)
    {
        if(tr.split1)
            return no;
        if(tr.a1!=0&&tr.b1!=0)
            return no;
        if(tr.a1==0)
        {
            if(tr.b1%2)
                return no;
            tr.a1=tr.b1/2;
            tr.b1/=2;
        }
        if(tr.b1==0)
        {
            if(tr.a1%2)
                return no;
            tr.b1=tr.a1/2;
            tr.a1/=2;
        }
        tr.split1=1;
    }
    return tr;
}
void calc(state tr)
{
    queue<state> q;
    q.push(tr);
    map<state,int> dp;
}

int a1=1,b1=1,a2=1,b2=1,split1=0,split2=0;
void printBoard()
{
    system("cls");
    printf(" ");
    for(int i=0;i<(a1-1)/2;i++)
        printf(" ");
    printf("a");
    for(int i=0;i<(a1)/2;i++)
        printf(" ");
    printf("   ");
    if(a1!=0)
        printf(" ");
    for(int i=0;i<(b1-1)/2;i++)
        printf(" ");
    printf("b");
    for(int i=0;i<(b1)/2;i++)
        printf(" ");
    printf("\n");
    printf("%c",222);
    for(int i=0;i<a1;i++)
        printf("%c",220);
    printf("%c  %c",221,222);
    for(int i=0;i<b1;i++)
        printf("%c",220);
    printf("%c  <-Programove ruke, ",221);
    if(split1)
        printf("Program nema split!\n");
    else
        printf("Program ima split!\n");
    printf(" ");
    for(int i=0;i<a1;i++)
        printf("%c",186);
    printf("    ");
    for(int i=0;i<b1;i++)
        printf("%c",186);
    printf("\n\n\n");
    printf(" ");
    for(int i=0;i<a2;i++)
        printf("%c",186);
    printf("    ");
    for(int i=0;i<b2;i++)
        printf("%c",186);
    printf("\n");
    printf("%c",222);
    for(int i=0;i<a2;i++)
        printf("%c",223);
    printf("%c  %c",221,222);
    for(int i=0;i<b2;i++)
        printf("%c",223);
    printf("%c  <-Tvoje ruke, ",221);
    if(split2)
        printf("Nemas split!\n");
    else
        printf("Imas split!\n");
    printf(" ");
    for(int i=0;i<(a2-1)/2;i++)
        printf(" ");
    printf("a");
    for(int i=0;i<(a2)/2;i++)
        printf(" ");
    printf("   ");
    if(a2!=0)
        printf(" ");
    for(int i=0;i<(b2-1)/2;i++)
        printf(" ");
    printf("b");
    for(int i=0;i<(b2)/2;i++)
        printf(" ");
    printf("\n");
}
vector<string> potezi={"a->a","a->b","b->a","b->b","split"};
void swapuj()
{
    swap(a1,a2);swap(b1,b2);swap(split1,split2);
}

void playMyMove()
{
    int tr=calc(a1,b1,a2,b2,1,split1,split2);
    if(tr==0)
        printf("Program misli da partima ide u beskonacnost\n");
    if(tr==1)
        printf("Program misli da pobedjuje\n");
    if(tr==2)
        printf("Program misli da gubi :'( (I samim tim uvek igra random potez)\n");
    printf("Program bira: ");
    if(tr==2)
    {
        int t=rng()%5;
        while(!makeMove(t))
            t=rng()%5;
        cout << potezi[t] << endl;
    }
    else
    {
        cout << potezi[bestmove[a1][b1][a2][b2][1][split1][split2]] << endl;
        assert(makeMove(bestmove[a1][b1][a2][b2][1][split1][split2]));
    }
    system("PAUSE\n");
}
void simulateMove()
{
    system("cls");
    printBoard();
    printf("Odaberi potez:\n1)a->a\n2)a->b\n3)b->a\n4)b->b\n5)split\n");
    int t;
    scanf("%i",&t);
    while(true)
    {
        if(t>5||t<1)
        {
            printf("Taj broj nije opcija\n");
            scanf("%i",&t);
            continue;
        }
        swapuj();
        if(!makeMove(t-1))
        {
            swapuj();
            printf("Nemoguc potez!\n");
            scanf("%i",&t);
            continue;
        }
        swapuj();
        system("cls");
        printf("Odigrali ste: ");
        cout << potezi[t-1] << endl;
        printBoard();
        return;
    }
}
int t;
bool test()
{
    if(a1==0&&b1==0)
    {
        printBoard();
        if(t==2)
            printf("Lako me je pobediti kad igras prvi...\n");
        else
            printf("Wow! Uspeo si, bravo! Nisam mislio da je moguce!\n");
        return false;
    }
    if(a2==0&&b2==0)
    {
        printBoard();
        if(t==2)
            printf("Lol, igras prvi i jos izgubis xD\n");
        else
            printf("Get rekt kid!\n");
        return false;
    }
    return true;
}
int main()
{
    while(true)
    {
        a1=1;b1=1;a2=1;b2=1;split1=0;split2=0;
        memset(dp,-1,sizeof(dp));
        printf("Ko igra prvi?\n1)Program (Pick this)\n2)Ti (Ako program misli da gubi, igra random potez. Misli da gubi od pocetka ako igra drugi i samim tim ga tesko pobediti ako igra drugi)\n");
        scanf("%i",&t);
        while(t!=1&&t!=2)
        {
            printf("Unesi pravu opciju!\n");
            scanf("%i",&t);
        }
        calc(1,1,1,1,t,0,0);
        if(t==2)
            simulateMove();
        else
            printBoard();
        while(test())
        {
            playMyMove();
            if(!test())
                break;
            simulateMove();
        }

        printf("Play again?\n1)I never give up!\n2)I give up!\n");
        scanf("%i",&t);
        while(t!=1&&t!=2)
        {
            printf("Unesi pravu opciju!\n");
            scanf("%i",&t);
        }
        if(t==2)
            break;
        system("cls");
    }
    return 0;
}
