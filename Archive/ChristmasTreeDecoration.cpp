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
// END CUT HERE

typedef vector<int> vi;
typedef vector<vi>  vvi;

typedef vector<bool> vb;
typedef vector<vb>   vvb;

class ChristmasTreeDecoration
{
    int n;
    vvb g;
    vb  v;

    void f(int x)
    {
        if (v[x]) return;
        v[x] = true;
        for (int y = 0; y < n; ++y) {
            if (!g[x][y]) continue;
            f(y);
        }
    }
  public:
    int solve(vector <int> c, vector <int> x, vector <int> y)
    {
        n = c.size();
        for (int i = 0; i < n; ++i) {
            g.push_back(vb(n, false));
        }
        v = vb(n, false);

        for (int i = 0; i < x.size(); ++i) {
            int vx = x[i] - 1;
            int vy = y[i] - 1;
            if (c[vx] != c[vy]) {
                g[vx][vy] = true;
                g[vy][vx] = true;
            }
        }

        f(0);

        int ret = 0;
        for (int x = 0; x < n; ++x) {
            if (!v[x]) {
                ++ret;
                f(x);
            }
        }

        return ret;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int colARRAY[] = {1,1,2,2};
        vector <int> col( colARRAY, colARRAY+ARRSIZE(colARRAY) );
        int xARRAY[] = {1,2,3,4};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {2,3,4,1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        ChristmasTreeDecoration theObject;
        eq(0, theObject.solve(col, x, y),1);
    }
    {
        int colARRAY[] = {1,1,2,2};
        vector <int> col( colARRAY, colARRAY+ARRSIZE(colARRAY) );
        int xARRAY[] = {1,2,3,4,1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {2,3,4,1,3,4};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        ChristmasTreeDecoration theObject;
        eq(1, theObject.solve(col, x, y),0);
    }
    {
        int colARRAY[] = {50,50,50,50};
        vector <int> col( colARRAY, colARRAY+ARRSIZE(colARRAY) );
        int xARRAY[] = {1,2,3,1,1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {2,3,4,4,3,4};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        ChristmasTreeDecoration theObject;
        eq(2, theObject.solve(col, x, y),3);
    }
    {
        int colARRAY[] = {1,4,2,3};
        vector <int> col( colARRAY, colARRAY+ARRSIZE(colARRAY) );
        int xARRAY[] = {1,2,3};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {2,3,4};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        ChristmasTreeDecoration theObject;
        eq(3, theObject.solve(col, x, y),0);
    }
    {
        int colARRAY[] = {1,1,1,2,2,2,3,3,3,4,4,4};
        vector <int> col( colARRAY, colARRAY+ARRSIZE(colARRAY) );
        int xARRAY[] = {1,2,3,4,5,6,7,8,9,10,11,12,1,1,1,1,1,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {2,3,1,5,6,4,8,9,7,11,12,10,5,7,12,11,6,4};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        ChristmasTreeDecoration theObject;
        eq(4, theObject.solve(col, x, y),5);
    }
    return 0;
}
// END CUT HERE
