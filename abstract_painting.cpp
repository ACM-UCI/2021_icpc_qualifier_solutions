#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

#define input freopen("input.txt", "rt", stdin)
#define output freopen("output.txt", "wt", stdout)
#define resetArr(arr, val) memset(arr, val, sizeof(arr));
#define endl "\n"
const int MOD = 1e9 + 7;
const double EPS = 1e-9;
const double PI = acos(-1);

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAX_SIZE = 1e4 + 5;

int t, r, c;
ll res;

ll powMod(ll base, ll ex, ll mod)
{
    if (ex == 0) return 1;
    if (ex == 1) return base;
    ll tmp = powMod(base, ex / 2, mod);
    if (ex & 1) return (tmp * tmp * base) % mod;
    else return (tmp * tmp) % mod;
}

int main()
{
#ifdef  TEST_CASE
#define gets(x) gets_s(x)

    input;
    //output;
    ios::sync_with_stdio(false);
    cin.tie(NULL);
#endif //  TEST_CASE

    cin >> t;

    while (t--)
    {
        cin >> r >> c;
        res = 3 * powMod(6, r + c - 1, MOD);
        res = res * powMod(2, (r - 1) * (c - 1), MOD) % MOD;

        cout << res << endl;
    }
    
    return 0;
}
