#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

// BEGIN CUT HERE
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
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
#pragma GCC diagnostic ignored "-Wunused-function"
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
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need )
{
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
// Debug:
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[ ";
    for (const T& x : v) {
        os << x << " ";
    }
    os << "]";
    return os;
}
// END CUT HERE

typedef vector<int>  vi;
typedef vector<vi>   vvi;
typedef vector<bool> vb;
typedef vector<vb>   vvb;

class MissingLCM
{
    vi primes(int pMax)
    {
        vi p;
        p.reserve(sqrt(pMax));
        p.push_back(2);
        int x = 3;
        bool ok;
        for (;;) {
            int last = p.size() - 1;
            if (pMax <= p[last]) break;
            ok = true;
            for (int i = 0; i < last and p[i] * p[i] <= x; ++i) {
                if (x % p[i] == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                p.push_back(x);
            }
            x += 2;
        }
        return p;
    }

    bool pp(vi& primes, int x)
    {
        for (int p : primes) {
            bool found = false;
            while (0 == x % p) {
                found = true;
                x /= p;
            }
            if (found) {
                if (1 == x) return true;
                return false;
            }
        }
        return false;
    }

  public:
    int getMin(int N)
    {
        if (N < 2) return 2;
        vi p = primes(N);
        // print(p);
        for (int i = N; 1 < i; --i) {
            if (pp(p, i)) {
                // cerr << "pp(" << i << ") = true;" << endl;
                return 2 * i;
            }
            // cerr << "pp(" << i << ") = false;" << endl;
        }
        return 0;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        MissingLCM theObject;
        eq(0, theObject.getMin(1),2);
    }
    {
        MissingLCM theObject;
        eq(1, theObject.getMin(2),4);
    }

    {
        MissingLCM theObject;
        eq(2, theObject.getMin(3),6);
    }
    {
        MissingLCM theObject;
        eq(3, theObject.getMin(4),8);
    }
    {
        MissingLCM theObject;
        eq(4, theObject.getMin(5),10);
    }
    {
        MissingLCM theObject;
        eq(5, theObject.getMin(42),82);
    }
    {
        MissingLCM theObject;
        eq(6, theObject.getMin(999999),1999966);
    }

    return 0;
}
// END CUT HERE
