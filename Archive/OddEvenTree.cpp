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

typedef uint64_t     ull;
typedef vector<ull>  vull;
typedef vector<int>  vi;
typedef vector<bool> vb;

class OddEvenTree
{
  public:
    vector <int> getTree(vector <string> x)
    {
        const int n = x.size();
        const vi no(1, -1);
        const ull mask = (1L << n) - 1;
        vull t;
        for (auto& s : x) {
            ull r = 0;
            for (char c : s) {
                r <<= 1;
                if ('O' == c) r |= 1;
            }
            t.push_back(r);
        }
        for (int i = 0; i < n; ++i) {
            if (t[i] & (1L << (n - i - 1))) {
                return no;
            }
        }
        map<ull, vi> m;
        for (int i = 0; i < n; ++i) {
            m[t[i]].push_back(i);
        }

        if (2 < m.size()) {
            return no;
        }

        ull u = m.begin()->first;
        ull v = (++m.begin())->first;
        if (((u ^ v) & mask) != mask) {
            return no;
        }

        // cerr << "u: " << u << endl;
        // cerr << "v: " << v << endl;

        vi a = m.begin()->second;
        vi b = (++m.begin())->second;

        // cerr << "a" << endl;
        // for (int i : a) {
        //     cerr << i << endl;
        // }

        // cerr << "b" << endl;
        // for (int i : b) {
        //     cerr << i << endl;
        // }

        vi ret;
        for (int i = 0; i < a.size(); ++i) {
            ret.push_back(b[0]);
            ret.push_back(a[i]);
        }

        for (int i = 1; i < b.size(); ++i) {
            ret.push_back(a[0]);
            ret.push_back(b[i]);
        }

        return ret;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        string xARRAY[] = {"EEEOOOOO", "EEEOOOOO", "EEEOOOOO", "OOOEEEEE", "OOOEEEEE", "OOOEEEEE", "OOOEEEEE", "OOOEEEEE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 1, 3, 2, 3};
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(10, theObject.getTree(x),retrunValue);
    }

    {
        string xARRAY[] = {"EOE",
            "OEO",
            "EOE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {0, 1, 2, 1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(0, theObject.getTree(x),retrunValue);
    }

    {
        string xARRAY[] = {"EO",
            "OE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {0, 1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(1, theObject.getTree(x),retrunValue);
    }

    {
        string xARRAY[] = {"OO",
            "OE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {-1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(2, theObject.getTree(x),retrunValue);
    }
    {
        string xARRAY[] = {"EO",
            "EE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {-1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(3, theObject.getTree(x),retrunValue);
    }
    {
        string xARRAY[] = {"EOEO",
            "OEOE",
            "EOEO",
            "OEOE"};
        vector <string> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int retrunValueARRAY[] = {0, 1, 0, 3, 2, 1 };
        vector <int> retrunValue( retrunValueARRAY, retrunValueARRAY+ARRSIZE(retrunValueARRAY) );
        OddEvenTree theObject;
        eq(4, theObject.getTree(x),retrunValue);
    }

    return 0;
}
// END CUT HERE
