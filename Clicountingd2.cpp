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
vector<string> split(const string& s, const string& delim = " ")
{
    vector<string> res;
    string t;
    for (size_t i = 0 ; i != s.size() ; ++i) {
        if (delim.find( s[i] ) != string::npos) {
            if (!t.empty()) {
                res.push_back( t );
                t = "";
            }
        }
        else {
            t += s[i];
        }
    }
    if (!t.empty()) {
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
#define LZC(x) ((x) == 0 ? sizeof(ll) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(ll) * 8 : __builtin_ctzll(x))
#define ALL(c) begin(c), end(c)
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c, x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

int id[20][20];
int dp[PW(20) + 1];

class Clicountingd2 {
public:
    int count(vector <string> g)
    {
        ZERO(dp);
        dp[0] = 1;
        int n = g.size();
        int m = 0;
        REP(i, n) FOR(j, i + 1, n) if ('?' == g[i][j]) id[i][j] = m++;
        REP(cli, PW(n)) {
            bool ok = true;
            int mask = 0;
            REP(i, n) if (cli & PW(i)) FOR(j, i + 1, n) if (cli & PW(j)) {
                if ('?' == g[i][j]) mask |= PW(id[i][j]);
                else if ('0' == g[i][j]) ok = false;
            }
            if (!ok) continue;
            chmax(dp[mask], BCNT(cli));
        }
        REP(mask, PW(m)) if (0 == dp[mask]) REP(i, m) chmax(dp[mask], dp[mask & (~PW(i))]);
        return accumulate(dp, dp + PW(20), 0);
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        string gARRAY[] = {"01","10"};
        vector <string> g( gARRAY, gARRAY+ARRSIZE(gARRAY) );
        Clicountingd2 theObject;
        eq(0, theObject.count(g),2);
    }
    {
        string gARRAY[] = {"0?","?0"};
        vector <string> g( gARRAY, gARRAY+ARRSIZE(gARRAY) );
        Clicountingd2 theObject;
        eq(1, theObject.count(g),3);
    }
    {
        string gARRAY[] = {"011","101","110"};
        vector <string> g( gARRAY, gARRAY+ARRSIZE(gARRAY) );
        Clicountingd2 theObject;
        eq(2, theObject.count(g),3);
    }
    {
        string gARRAY[] = {"0?1","?01","110"};
        vector <string> g( gARRAY, gARRAY+ARRSIZE(gARRAY) );
        Clicountingd2 theObject;
        eq(3, theObject.count(g),5);
    }
    {
        string gARRAY[] = {"0???","?0??","??0?","???0"};
        vector <string> g( gARRAY, gARRAY+ARRSIZE(gARRAY) );
        Clicountingd2 theObject;
        eq(4, theObject.count(g),151);
    }
    return 0;
}
// END CUT HERE
