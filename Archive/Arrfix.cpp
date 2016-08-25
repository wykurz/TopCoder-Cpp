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

const int dd[] = {1, 0, -1, 0};

class Arrfix {
public:
    int mindiff(vector <int> A, vector <int> B, vector <int> F)
    {
        int n = A.size();
        int m = F.size();
        vector<bool> uX(n);
        vector<bool> uF(m);
        REP(i, n) if (A[i] != B[i]) {
            REP(j, m) if (!uF[j] && F[j] == B[i]) {
                A[i] = F[j];
                uX[i] = true;
                uF[j] = true;
                break;
            }
        }
        REP(i, n) if (!uX[i]) {
            REP(j, m) if (!uF[j] && F[j] == B[i]) {
                A[i] = F[j];
                uX[i] = true;
                uF[j] = true;
                break;
            }
        }
        REP(i, n) if (!uX[i] && A[i] != B[i]) {
            REP(j, m) if (!uF[j]) {
                A[i] = F[j];
                uX[i] = true;
                uF[j] = true;
                break;
            }
        }
        REP(i, n) if (!uX[i]) {
            REP(j, m) if (!uF[j]) {
                A[i] = F[j];
                uX[i] = true;
                uF[j] = true;
                break;
            }
        }
        int ans = 0;
        REP(i, n) if (A[i] != B[i]) ++ans;
        return ans;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int AARRAY[] = {882, 700,   4, 558, 999,  22, 713, 893, 882, 477,  76, 558, 893, 558, 390, 22, 601, 882, 323, 999};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {870, 700, 511, 700, 870, 882, 893, 601, 390,  22, 558, 390, 511, 558, 511, 76, 652,  76, 882, 477};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {601, 76, 601, 558, 477, 862, 862, 870, 558};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(6, theObject.mindiff(A, B, F),13);
    }

    {
        int AARRAY[] = {6, 3, 5, 4, 7, 2};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {2, 6, 2, 2, 7, 2};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {6, 7, 5, 4, 3};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(5, theObject.mindiff(A, B, F),3);
    }
    {
        int AARRAY[] = {1,1,1};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {2,2,2};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {2};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(0, theObject.mindiff(A, B, F),2);
    }
    {
        int AARRAY[] = {1,1,1};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {2,2,1};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {2,2};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(1, theObject.mindiff(A, B, F),0);
    }
    {
        int AARRAY[] = {1,2,3};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {3,2,1};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        Arrfix theObject;
        eq(2, theObject.mindiff(A, B, vector <int>()),2);
    }
    {
        int AARRAY[] = {2,2,2};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {2,2,2};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {1,2,3};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(3, theObject.mindiff(A, B, F),2);
    }
    {
        int AARRAY[] = {1,3,3,3};
        vector <int> A( AARRAY, AARRAY+ARRSIZE(AARRAY) );
        int BARRAY[] = {2,3,3,3};
        vector <int> B( BARRAY, BARRAY+ARRSIZE(BARRAY) );
        int FARRAY[] = {2,2};
        vector <int> F( FARRAY, FARRAY+ARRSIZE(FARRAY) );
        Arrfix theObject;
        eq(4, theObject.mindiff(A, B, F),1);
    }
    return 0;
}
// END CUT HERE
