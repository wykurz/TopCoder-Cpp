#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <typeinfo>
#include <functional>

using namespace std;
// BEGIN CUT HERE
vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( size_t i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}
vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( size_t i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))
template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( size_t i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( size_t i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) begin(c), end(c)
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c, x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

ll dp[300][300][3];
bool g[300][300];
bool vis[300];
const ll mod = 1e9 + 7;

class BearUniqueDiameter {
public:

    int countSubtrees(vector <int> a, vector <int> b)
    {
        ZERO(dp);
        ZERO(g);
        ZERO(vis);
        int m = a.size();
        int n = m + 1;
        REP(i, m) {
            g[a[i]][b[i]] = true;
            g[b[i]][a[i]] = true;
        }
        ll ans = 0;
        std::function<void(int)> f = [&](int i) {
            vis[i] = true;
            auto chld = [&](int j) { return g[i][j] && !vis[j]; };
            dp[i][0][0] = 1;
            dp[i][0][2] = 1;
            FOR(j, 0, m) dp[i][j][1] = 1;
            REP(j, n) if (chld(j)) {
                f(j);
                REP(l, m) FOR(t, 0, m - l) {
                    bool print = false; // i == 0 && (l + t + 1) == 4;
                    if (print) cerr << j << " " << t << " " << l << endl;
                    if (print) cerr << dp[i][l + t + 1][2] << " += " << dp[i][t][0] << " * " << dp[j][l][0] << endl;
                    dp[i][l + t + 1][2] += dp[i][t][0] * dp[j][l][0] - dp[i][t][0];
                    dp[i][l + t + 1][2] %= mod;
                }
                RFOR(l, m - 1, 0) {
                    bool print = false; //i == 1 && (l + 1) == 2;
                    if (print) cerr << l << endl;
                    if (print) cerr << dp[i][l + 1][0] << " += " << dp[i][l][1] << " * " << dp[j][l][0] << endl;
                    dp[i][l + 1][0] += dp[i][l][1] * dp[j][l][0];
                    dp[i][l + 1][0] %= mod;
                    if (print) cerr << dp[i][l + 1][1] << " += " << dp[i][l][1] << " * " << dp[j][l][1] << endl;
                    dp[i][l + 1][1] += dp[i][l][1] * dp[j][l][1];
                    dp[i][l + 1][1] %= mod;
                }
            }
            REP(j, n) {
                ans += dp[i][j][2];
                ans %= mod;
            }
        };
        f(0);

        REP(i, n) {
            cerr << i << ":  ";
            REP(j, n) cerr << "len(" << j << ")" << ":[" << dp[i][j][0] << ", " << dp[i][j][1] << ", " << dp[i][j][2] << "] ";
            cerr << endl;
        }

        return ans;
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int aARRAY[] = {0,1,1,3,5};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,0};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        BearUniqueDiameter theObject;
        eq(2, theObject.countSubtrees(a, b),22);
    }

    // {
    //     int aARRAY[] = {0,0,0};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {1,2,3};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(0, theObject.countSubtrees(a, b),10);
    // }

    // {
    //     int aARRAY[] = {3,2,1,4,0};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {1,3,4,0,5};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(1, theObject.countSubtrees(a, b),21);
    // }

    // {
    //     int aARRAY[] = {0,1,2,3,2};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {1,2,3,4,5};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(2, theObject.countSubtrees(a, b),22);
    // }

    // {
    //     int aARRAY[] = {1};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {0};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(3, theObject.countSubtrees(a, b),3);
    // }
    // {
    //     int aARRAY[] = {36,23,33,33,33,24,33,33,33,33,37,33,33,33,33,28,33,33,22,33,
    //        29,16,33,33,33,33,33,31,35,33,33,8,13,26,12,33,33,0,33,33};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {33,33,0,9,39,33,32,40,15,19,33,30,38,7,25,33,27,11,33,3,33,33,
    //        21,18,5,6,4,33,11,14,10,33,33,33,33,20,2,1,34,17};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(4, theObject.countSubtrees(a, b),719477120);
    // }
    // {
    //     int aARRAY[] = {0,0,0,1,2,3,4,5,6};
    //     vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
    //     int bARRAY[] = {1,2,3,4,5,6,7,8,9};
    //     vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
    //     BearUniqueDiameter theObject;
    //     eq(5, theObject.countSubtrees(a, b),70);
    // }

    return 0;
}
// END CUT HERE
