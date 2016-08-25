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
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) begin(c), end(c)
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c, x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

int C[30];
int D[30];
int E[1000];
int F[1000];

class XorOrderDiv2 {
public:
    vector<long long> getExpectation(int m, vector <int> a)
    {
        int n = a.size();
        vector<ll> ans(n);
        REP(i, n) {
            ZERO(C);
            ZERO(D);
            ZERO(E);
            REP(j, n) if (i != j) ++C[LZC(a[i] ^ a[j]) - 64 + m];

            // cerr << "C:" << endl;
            // REP(j, m) cerr << C[j] << " ";
            // cerr << endl;

            if (0 == C[m - 1]) D[m - 1] = 1;
            RFOR(j, m - 2, 0) D[j] = D[j + 1] + (0 == C[j] ? 1 : 0);

            // cerr << "D:" << endl;
            // REP(j, m) cerr << D[j] << " ";
            // cerr << endl;

            F[0] = E[0] = PW(D[0]);
            REP(j, m) if (0 < C[j]) {
                ZERO(F);
                REP(k, n) if (0 < E[k]) F[k + C[j]] = PW(D[j]);
                REP(k, n) E[k] += F[k];
            }

            // cerr << "E:" << endl;
            // REP(j, n) cerr << E[j] << " ";
            // cerr << endl;

            // cerr << endl;

            REP(j, n) ans[i] += (ll) j * j * E[j];
        }
        return ans;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int aARRAY[] = {42};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        long retrunValueARRAY[] = {0L};
        vector<long long> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        XorOrderDiv2 theObject;
        eq(0, theObject.getExpectation(3, a),retrunValue);
    }

    {
        int aARRAY[] = {0,1,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        long retrunValueARRAY[] = {6L, 6L, 8L };
        vector<long long> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        XorOrderDiv2 theObject;
        eq(0, theObject.getExpectation(2, a),retrunValue);
    }

    {
        int aARRAY[] = {1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        long retrunValueARRAY[] = {0L };
        vector<long long> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        XorOrderDiv2 theObject;
        eq(1, theObject.getExpectation(1, a),retrunValue);
    }
    {
        int aARRAY[] = {13,17};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        long retrunValueARRAY[] = {16L, 16L };
        vector<long long> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        XorOrderDiv2 theObject;
        eq(2, theObject.getExpectation(5, a),retrunValue);
    }
    {
        int aARRAY[] = {1,2,3,4,5,6,7,8,9,10};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        long retrunValueARRAY[] = {29527900160L, 28991029248L, 28991029248L, 27917287424L, 27917287424L, 27917287424L, 27917287424L, 35433480192L, 35433480192L, 35970351104L };
        vector<long long> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        XorOrderDiv2 theObject;
        eq(3, theObject.getExpectation(30, a),retrunValue);
    }

    return 0;
}
// END CUT HERE
