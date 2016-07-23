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

const int dd[] = {1, 0, -1, 0};

class BearPasswordAny {
public:
    string findPassword(vector <int> x)
    {
        string s = "";
        int n = x.size();
        reverse(ALL(x));
        while (true) {
            int i = 0;
            while (i < n && x[i] == 0) ++i;
            if (i == n) break;
            int c = 0;
            FOR(j, i, n - 1) {
                x[j] -= ++c;
                if (x[j] < 0) return "";
            }
            char l = 'a';
            if (0 < s.size() && s[s.size() - 1] == 'a') l = 'b';
            REP(j, n - i) s += l;
        }
        return s.size() == n ? s : "";
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int xARRAY[] = {5,0,0,0,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(0, theObject.findPassword(x),"ababa");
    }
    {
        int xARRAY[] = {4,2,1,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(1, theObject.findPassword(x),"baaa");
    }
    {
        int xARRAY[] = {3,1,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(2, theObject.findPassword(x),"");
    }
    {
        int xARRAY[] = {4,3,2,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(3, theObject.findPassword(x),"aaaa");
    }
    {
        int xARRAY[] = {0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(4, theObject.findPassword(x),"");
    }
    {
        int xARRAY[] = {4,0,3,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(5, theObject.findPassword(x),"");
    }
    {
        int xARRAY[] = {6,3,1,0,0,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(6, theObject.findPassword(x),"abbaaa");
    }
    {
        int xARRAY[] = {10,5,2,1,0,0,0,0,0,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(7, theObject.findPassword(x),"bbbbaababb");
    }
    {
        int xARRAY[] = {5,4,2,1,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        BearPasswordAny theObject;
        eq(8, theObject.findPassword(x),"");
    }
    return 0;
}
// END CUT HERE
