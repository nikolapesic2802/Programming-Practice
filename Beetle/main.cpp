/**
first of all sort.
tot ans = K*m - sum dist[i], where i from 1 to K.
it's obvious to choose drop which is min dist from current drop.
then L[i][j][k] means we drink k drops of water, and we drank waters between i and j, and we are in ith drop. We go to left. R[i][j][k] - we go to the right.

*/
/**
SXR0aXAkI0JwbXptI3FhI3Z3I293bCNqY2IjUG0jMCNicG0jVHFkcXZvLyNCcG0jQW10bjBhY2phcWFicXZvLyNNYm16dml0MSNWdyNhdGN1am16I2tpdiNhbXF9bSNQcXUjVnd6I0F0bW14MSNQcWEjaXptI2l0dCNicHF2b2EjUXYjYnBtI3BtaWRtdmEjaXZsI3d2I21pemJwMSNFcHcjcWEjYnBtem0ja2l2I3F2Ym16a21sbSNRdiNQcWEjeHptYW12a20jbXtrbXhiI0lhI3BtI3htenVxYmJtYnBHI1BtI3N2d2VtYnAjRXBpYiMraXh4bWl6bWJwI2J3I1BxYSNrem1pYmN6bWEjSWEsI0ptbnd6bSN3eiNJbmJteiN3eiNKbXBxdmwjYnBtdTEjVnd6I2FwaXR0I2JwbXwja3d1eGlhYSNJY29wYiN3biNwcWEjc3Z3ZXRtbG9tI017a214YiNpYSNQbSNlcXR0bWJwMSNQcWEjYnB6d3ZtI2x3YnAjbXtibXZsI1dkbXojYnBtI3BtaWRtdmEjSXZsI3d2I21pemJwLyNpdmwjUG0jbm1tdG1icCNWdyNuaWJxb2NtI3F2I29jaXpscXZvI0l2bCN4em1hbXpkcXZvI2JwbXUvI053eiNQbSNxYSNicG0jVXdhYiNQcW9wMSNCcG0jQWN4em11bSMrcXYjb3R3enwsMQ==
*/
#include <bits/stdc++.h>

#define F first
#define S second
#define endl '\n'
#define deb(x) cout<<#x<<' '<<x<<endl;
#define pb push_back

/*
#ifdef IZI_KATKA
#define int __int64_t
#else
#define int __int64
#endif
*/

const long long MOD = 1e9 + 7;
const long long MAXN = 1e6 + 1;
using namespace std;

typedef long long ll;

long long readInt() {
    bool minus1 = false;
    long long result = 0;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-') break;
        if (ch >= '0' && ch <= '9') break;
        ch = getchar();
    }
    if (ch == '-') minus1 = true; else result = ch-'0';
    while (true) {
        ch = getchar();
        if (ch < '0' || ch > '9') break;
        result = result*10 + (ch - '0');
    }
    if (minus1)
        return -result;
    else
        return result;
}


int L[2][305][305];
int R[2][305][305];

int a[305];

int main() {
	#ifdef IZI_KATKA
	assert(freopen("input", "r", stdin));
    assert(freopen("output", "w", stdout));
    #endif
    int n = readInt(), m = readInt();
    for (int i = 0; i < n; i++) {
    	a[i] = readInt();
    }
    sort(a, a + 1 + n);
    int pos = (int)(lower_bound(a, a + 1 + n, 0) - a);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
    	for (int j = 0; j <= n; j++) {
    		for (int k = j; k <= n; k++) {
				L[i%2][j][k] = R[i%2][j][k] = MOD;
				if (j != 0) L[i%2][j][k] = min(L[i%2][j][k], L[(i-1)%2][j-1][k] + i * (a[j] - a[j-1]));
                if (k != n) L[i%2][j][k] = min(L[i%2][j][k], R[(i-1)%2][j][k+1] + i * (a[k+1] - a[j]));
                if (j != 0) R[i%2][j][k] = min(R[i%2][j][k], L[(i-1)%2][j-1][k] + i * (a[k] - a[j-1]));
                if (k != n) R[i%2][j][k] = min(R[i%2][j][k], R[(i-1)%2][j][k+1] + i * (a[k+1] - a[k]));
    		}
    	}
    	ans = max(ans, i * m - L[i%2][pos][pos]);
    }
    cout << ans;
    return 0;
}
