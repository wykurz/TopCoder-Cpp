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
#define ALL(c) (c).begin(),(c).end()
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c,x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

bool gg[100][100];
bool hh[100];
bool mm[100];

class BiconnectedDiv2 {
public:
    int n;
    bool biconn()
    {
        REP(i, n) {
            COPY1D(gg[i], mm);
            ZERO(gg[i]);
            ZERO(hh);
            conn((i + 1) % n);
            COPY1D(mm, gg[i]);
            REP(j, n) if (j != i && !hh[j]) return false;
        }
        return true;
    }
    void conn(int i)
    {
        hh[i] = true;
        REP(j, n) if (gg[i][j] && !hh[j]) conn(j);
    }
    void print()
    {
        REP(i, n) REP(j, n) cerr << "g[" << i << "][" << j << "] = " << gg[i][j] << endl;
    }
    int minimize(vector <int> w1, vector <int> w2)
    {
        n = w1.size() + 1;
        ZERO(gg);
        REP(i, w1.size()) gg[i][i + 1] = true, gg[i + 1][i] = true;
        REP(i, w2.size()) gg[i][i + 2] = true, gg[i + 2][i] = true;
        auto vv = vector<tuple<int, int, int> >();
        for (int i = 0; i < w1.size(); ++i)
            vv.push_back(make_tuple(w1[i], 1, i));
        for (int i = 0; i < w2.size(); ++i)
            vv.push_back(make_tuple(w2[i], 2, i));
        sort(ALL(vv));
        reverse(ALL(vv));
        auto res = accumulate(ALL(w1), 0) + accumulate(ALL(w2), 0);
        // print();
        for (auto tt : vv) {
            int w; int delta; int i;
            tie(w, delta, i) = tt;
            if (w <= 0) break;
            gg[i][i + delta] = false;
            gg[i + delta][i] = false;
            if (!biconn()) {
                gg[i][i + delta] = true;
                gg[i + delta][i] = true;
                continue;
            }
            res -= w;
            // cerr << "Removing w" << delta << ": " << w << " " << i << endl;
        }
        // print();
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int w1ARRAY[] = {7094, -4355, 3191, -1241};
        vector <int> w1( w1ARRAY, w1ARRAY+ARRSIZE(w1ARRAY) );
        int w2ARRAY[] = {-1886, 8914, -7386};
        vector <int> w2( w2ARRAY, w2ARRAY+ARRSIZE(w2ARRAY) );
        BiconnectedDiv2 theObject;
        eq(0, theObject.minimize(w1, w2),1140);
    }

    {
        int w1ARRAY[] = {1,2};
        vector <int> w1( w1ARRAY, w1ARRAY+ARRSIZE(w1ARRAY) );
        int w2ARRAY[] = {3};
        vector <int> w2( w2ARRAY, w2ARRAY+ARRSIZE(w2ARRAY) );
        BiconnectedDiv2 theObject;
        eq(0, theObject.minimize(w1, w2),6);
    }
    {
        int w1ARRAY[] = {-1,-2,-3};
        vector <int> w1( w1ARRAY, w1ARRAY+ARRSIZE(w1ARRAY) );
        int w2ARRAY[] = {-4,-5};
        vector <int> w2( w2ARRAY, w2ARRAY+ARRSIZE(w2ARRAY) );
        BiconnectedDiv2 theObject;
        eq(1, theObject.minimize(w1, w2),-15);
    }

    {
        int w1ARRAY[] = {1,100,-3,2};
        vector <int> w1( w1ARRAY, w1ARRAY+ARRSIZE(w1ARRAY) );
        int w2ARRAY[] = {-2,1,4};
        vector <int> w2( w2ARRAY, w2ARRAY+ARRSIZE(w2ARRAY) );
        BiconnectedDiv2 theObject;
        eq(2, theObject.minimize(w1, w2),3);
    }

    return 0;
}
// END CUT HERE
