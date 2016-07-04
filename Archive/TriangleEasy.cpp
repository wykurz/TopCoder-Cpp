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

const int dd[] = {1, 0, -1, 0};

bool gg[50][50];

class TriangleEasy {
public:
    int find(int n, vector <int> x, vector <int> y)
    {
        ZERO(gg);
        int m = x.size();
        REP(i, m) gg[x[i]][y[i]] = true, gg[y[i]][x[i]] = true;
        REP(i, n) REP(j, n) REP(k, n) if (i != j && j != k && k != i) if (gg[i][j] && gg[j][k] && gg[k][i]) return 0;
        REP(i, n) REP(j, n) REP(k, n) if (i != j && j != k && k != i) if (gg[i][j] && gg[j][k]) return 1;
        return 0 < x.size() ? 2 : 3;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        TriangleEasy theObject;
        eq(0, theObject.find(3, vector <int>(), vector <int>()),3);
    }
    {
        int xARRAY[] = {0,2,1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {3,0,2,3};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TriangleEasy theObject;
        eq(1, theObject.find(4, x, y),0);
    }
    {
        int xARRAY[] = {0,0,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {3,1,4};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TriangleEasy theObject;
        eq(2, theObject.find(6, x, y),1);
    }
    {
        int xARRAY[] = {0,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {1,3};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TriangleEasy theObject;
        eq(3, theObject.find(4, x, y),2);
    }
    {
        int xARRAY[] = {16,4,15,6,1,0,10,12,7,15,2,4,8,1,10,15,13,10,1,16,3,19,8,7,13,1,15,15,15,5,16,7,5,6,4,18,3,8,6,2,16,8,19,14,17,16,4,6,9,17,4,10,8,12,2,3,18,9,13,17,4,7,10,0,13,11,15,17,11,15,11,19,19,4,10,14,16,6,3,17,1,4,14,9,7,18,10,11,5,0,5,9,9,7,16,12,4,10,17,3};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {17,18,6,16,18,6,11,2,15,10,1,15,17,8,5,9,7,0,0,4,16,1,9,0,9,5,17,14,1,12,14,11,9,18,0,12,11,3,19,14,7,6,3,19,0,1,19,5,11,19,2,13,12,0,6,2,14,16,14,18,5,5,19,3,6,14,12,5,17,3,1,12,7,11,8,8,10,11,13,2,13,13,0,18,2,7,2,12,14,9,3,19,2,8,12,13,8,18,13,18};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TriangleEasy theObject;
        eq(4, theObject.find(20, x, y),1);
    }
    // {50, {12, 48, 42, 42, 29, 46, 46, 18, 48, 4, 9, 11, 12, 45, 45, 47, 39, 22, 45, 29, 49, 35, 37, 5, 42, 42, 11, 5, 22, 10, 18, 3, 18, 35, 37, 10, 4, 27, 22, 7, 45, 12, 46, 11, 8, 27, 39, 28, 8, 42, 10, 37, 46, 9, 27, 5, 46, 31, 4, 18, 10, 5, 9, 7, 22, 37, 17, 12, 35, 8, 28, 48, 3, 7, 7, 3, 35, 22, 9, 8, 49, 8, 22, 42, 3, 4, 12, 28, 29, 42, 11, 3, 4, 7, 48, 42, 31, 47, 31, 27, 11, 4, 46, 10, 49, 39, 48, 22, 28, 46, 49, 48, 10, 37, 49, 29, 11, 28, 29, 47, 47, 39, 29, 10, 11, 17, 10, 35, 49, 22, 10, 5, 37, 12, 22, 22, 49, 18, 42, 39, 8, 28, 42, 42, 37, 37, 17, 37, 22, 48, 5, 47, 48, 31, 48, 8, 29, 29, 10, 29, 48, 3, 46, 45, 17, 10, 22, 27, 27, 42, 35, 48, 11, 10, 8, 46, 29, 7, 47, 37, 45, 45, 37, 3, 22, 27, 9, 45, 49, 17, 39, 47, 35, 37, 10, 18, 17, 39, 42, 49, 17, 49, 31, 10, 39, 49, 17, 12, 35, 31, 7, 39, 42, 29, 10, 8, 31, 39, 49, 48, 5, 39, 37, 9, 4, 4, 5, 39, 27, 35, 28, 8, 9, 31, 17, 45, 42, 11, 27, 39, 11, 28, 3, 28, 28, 35, 4, 46, 48, 11, 39, 28, 35, 47, 12, 37, 35, 18, 47, 28, 49, 17, 27, 9, 37, 9, 8, 18, 46, 18, 46, 8, 48, 11, 22, 29, 9, 37, 7, 8, 8, 27, 7, 10, 49, 35, 11, 45, 5, 29, 27, 31, 28, 3, 5, 11, 11, 45, 39, 12, 49, 7, 12, 4, 42, 46, 31, 42, 28, 22, 29, 39, 45, 4, 29, 28, 29, 35, 7, 3, 17, 47, 11, 11, 37, 45, 45, 9, 22, 18, 47, 31, 27, 12, 18, 4, 35, 47, 31, 35, 42, 22, 27, 28, 31, 3, 29, 39, 49, 8, 12, 17, 12, 18, 35, 48, 9, 17, 8, 10, 3, 35, 8, 35, 27, 10, 8, 49, 10, 42, 5, 18, 37, 12, 5, 5, 9, 42, 9, 45, 31, 4, 4, 31, 35, 37, 17, 12, 9, 17, 12, 48, 47, 7, 7, 37, 28, 22, 49, 39, 39, 5, 37, 3, 18, 11, 46, 17, 4, 12, 9, 4, 7, 48, 28, 48, 47, 45, 31, 11, 17, 22, 46, 7, 10, 29, 9, 31, 22, 3, 27, 45, 39, 27, 42, 3, 10, 17, 8, 47, 28, 7, 27, 4, 5, 45, 22, 45, 28, 31, 31, 35, 4, 7, 48, 35, 35, 46, 28, 8, 45, 22, 45, 45, 28, 48, 48, 31, 4, 45, 5, 18, 12, 39, 10, 35, 49, 47, 48, 35, 11, 22, 46, 12, 37, 4, 49, 49, 12, 17, 27, 37, 10, 42, 7, 11, 37, 27, 31, 17, 48, 8, 31, 10, 49, 42, 9, 4, 11, 22, 39, 29, 46, 29, 8, 5, 5, 3, 4, 12, 39, 48, 12, 3, 3, 8, 18, 31, 18, 29, 18, 4, 39, 11, 42, 11, 49, 27, 47, 18, 7, 5, 11, 47, 17, 46, 5, 46, 29, 12, 18, 46, 18, 10, 17, 3, 9, 3, 31, 49, 28, 45, 29, 4, 9, 17, 9, 29, 31, 47, 27, 3, 17, 9, 46, 9, 28, 29, 45, 18, 42, 5, 48, 46, 5, 7, 18, 5, 9, 18, 27, 27, 12, 7, 5, 46, 47, 8, 7, 7, 28, 18, 3, 12, 46, 47, 3, 22, 39, 9, 3, 47, 47, 37, 5, 17, 7, 7, 49, 3, 47, 47, 8, 27, 4}, {21, 20, 25, 6, 15, 41, 44, 30, 6, 16, 21, 21, 14, 26, 6, 41, 1, 40, 32, 40, 6, 33, 24, 44, 41, 43, 33, 40, 0, 38, 25, 38, 1, 41, 15, 2, 0, 33, 38, 36, 43, 36, 19, 16, 36, 14, 26, 36, 30, 32, 0, 23, 34, 40, 30, 6, 0, 43, 38, 13, 41, 38, 0, 30, 21, 1, 36, 2, 32, 1, 21, 32, 41, 6, 40, 26, 40, 23, 20, 19, 30, 20, 43, 13, 0, 26, 34, 41, 24, 20, 41, 43, 41, 19, 23, 0, 16, 24, 41, 13, 26, 2, 25, 21, 25, 34, 43, 24, 14, 16, 44, 15, 44, 0, 26, 0, 34, 34, 19, 43, 16, 2, 23, 40, 30, 14, 25, 14, 1, 6, 20, 1, 41, 33, 44, 2, 36, 14, 30, 40, 23, 1, 24, 21, 38, 2, 25, 43, 20, 21, 16, 30, 33, 34, 25, 24, 6, 14, 34, 16, 16, 23, 6, 21, 33, 43, 33, 41, 19, 19, 30, 0, 38, 19, 21, 21, 13, 43, 33, 36, 33, 13, 34, 14, 16, 34, 13, 19, 13, 34, 13, 0, 13, 40, 30, 32, 13, 6, 44, 33, 21, 16, 38, 24, 16, 23, 2, 1, 20, 44, 1, 14, 1, 44, 33, 6, 36, 44, 43, 38, 2, 38, 44, 19, 25, 19, 32, 24, 25, 25, 0, 16, 24, 30, 43, 24, 23, 25, 44, 23, 19, 25, 6, 26, 30, 0, 30, 1, 14, 36, 19, 33, 19, 36, 40, 25, 36, 21, 23, 15, 41, 26, 23, 2, 32, 16, 32, 23, 13, 34, 15, 2, 13, 44, 14, 21, 6, 16, 14, 0, 40, 0, 34, 32, 20, 44, 6, 20, 41, 32, 2, 33, 44, 21, 33, 1, 14, 16, 30, 25, 2, 20, 0, 13, 16, 36, 32, 33, 13, 15, 26, 25, 41, 21, 43, 20, 36, 43, 13, 33, 30, 44, 23, 20, 6, 2, 44, 1, 1, 36, 14, 0, 20, 38, 26, 6, 26, 34, 13, 21, 38, 32, 36, 19, 26, 36, 2, 15, 32, 14, 26, 1, 41, 16, 16, 24, 44, 32, 44, 13, 20, 6, 34, 1, 26, 6, 15, 14, 26, 34, 24, 33, 20, 43, 23, 0, 15, 40, 25, 25, 20, 32, 23, 14, 34, 33, 23, 32, 26, 38, 24, 41, 13, 2, 0, 19, 23, 30, 15, 21, 0, 26, 26, 40, 43, 13, 38, 24, 24, 30, 23, 14, 16, 44, 6, 34, 21, 34, 19, 24, 44, 13, 14, 21, 23, 34, 41, 6, 26, 25, 38, 0, 36, 15, 2, 24, 14, 16, 33, 25, 40, 38, 21, 1, 15, 36, 36, 23, 38, 40, 21, 23, 43, 26, 2, 24, 38, 24, 24, 38, 38, 41, 40, 1, 43, 1, 40, 23, 20, 30, 13, 19, 13, 33, 36, 15, 34, 15, 26, 2, 32, 25, 23, 20, 14, 44, 21, 19, 19, 20, 24, 13, 1, 14, 25, 15, 21, 32, 25, 15, 19, 41, 15, 16, 38, 15, 30, 36, 2, 34, 20, 30, 26, 41, 25, 34, 25, 2, 34, 23, 41, 30, 15, 13, 44, 13, 20, 24, 6, 25, 15, 40, 32, 43, 26, 40, 0, 16, 40, 38, 32, 43, 0, 20, 19, 2, 20, 43, 20, 44, 40, 20, 24, 15, 6, 19, 33, 1, 1, 24, 2, 15, 1, 33, 14, 41, 38, 38, 2, 1, 43, 16, 40, 43, 40, 36, 32, 33, 14, 44, 36, 36, 36, 30, 30, 41, 41, 21, 32, 2, 6, 1, 16, 44, 14, 33, 32, 43, 24, 23, 16, 0, 30, 6, 32, 6, 34, 19, 43, 34, 15, 26, 19, 30, 19, 0, 15, 33, 40, 32, 38, 2, 26, 40, 15}}
    return 0;
}
// END CUT HERE
