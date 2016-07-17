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

int dp[100][3];

class TreeAndCycle {
public:

    int minimize(vector <int> cv, vector <int> pre, vector <int> coste)
    {
        int n = cv.size();
        vector<vector<int> > gg(n);
        vector<vector<int> > ce(n);
        REP(i, n - 1) gg[pre[i]].push_back(i + 1);
        REP(i, n - 1) ce[pre[i]].push_back(coste[i]);
        // REP(i, n) {
        //     cerr << i << " : ";
        //     for (int c : gg[i]) cerr << c << ",";
        //     cerr << endl;
        // }
        function<pair<int, int>(int)> f = [&](int curr) {
            auto cvc = cv[curr];
            if (!gg[curr].size()) {
                auto ans = make_pair(2 * cvc, cvc);
                cerr << curr << ": " << ans.first << "," << ans.second << endl;
                return ans;
            }
            ZERO(dp);
            int m = gg[curr].size();
            REP(i, m) {
                auto pp = f(gg[curr][i]);
                dp[i][0] = pp.first;
                dp[i][1] = pp.second;
                dp[i][2] = ce[curr][i];
            }
            int r0 = 0;
            REP(i, m) r0 += dp[i][0] + dp[i][2];
            int r1 = r0 - dp[0][0] + dp[0][1] - dp[0][2];
            FOR(i, 1, m) {
                int r1t = r0 - dp[i][0] + dp[i][1] - dp[i][2];
                chmin(r1, r1t);
            }
            int r2 = numeric_limits<int>::max() - 20000;
            if (1 < m) {
                r2 = r0 - dp[0][0] + dp[0][1] - dp[0][2] - dp[1][0] + dp[1][1] - dp[1][2];
                REP(i, m - 1) FOR(j, i + 1, m - 1) {
                    int r2t = r0 - dp[i][0] + dp[i][1] - dp[i][2] - dp[j][0] + dp[j][1] - dp[j][2];
                    chmin(r2, r2t);
                }
            }
            auto ans = make_pair(min(r0 + 2 * cvc, min(r1 + cvc, r2)), min(r0 + cvc, r1));
            cerr << curr << ": " << ans.first << "," << ans.second << endl;
            return ans;
        };
        return f(0).first;
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int costVARRAY[] = {7,2,5,8};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,1,2};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {6,4,3};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(0, theObject.minimize(costV, pre, costE),15);
    }
    {
        int costVARRAY[] = {100,5,9,8};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,0,0};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {6,2,2};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(1, theObject.minimize(costV, pre, costE),32);
    }
    {
        int costVARRAY[] = {10,20,30,40,50,60,70,80,90};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,1,2,2,3,4,5,7};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {5,15,25,35,45,55,65,75};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(2, theObject.minimize(costV, pre, costE),205);
    }
    return 0;
}
// END CUT HERE
