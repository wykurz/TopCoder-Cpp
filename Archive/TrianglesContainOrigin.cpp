#include <algorithm>
#include <cctype>
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
#include <iomanip>      // std::setw
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

class TrianglesContainOrigin
{
  public:
    struct Point
    {
        double a;
        int x, y;
        bool operator<(const Point& rhs) const
        {
            return a < rhs.a;
        }
    };
    vector<Point> v;

    int cp(int i, int j)
    {
        return v[i].x * v[j].y - v[j].x * v[i].y;
    }
    long long count(vector <int> x, vector <int> y)
    {
        int N = x.size();

        for (int i = 0; i < N; ++i) {
            v.push_back({atan2(y[i], x[i]), x[i], y[i]});
        }

        sort(v.begin(), v.end());

        vector<int> k(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = (i + 1) % N; 0 < cp(i, j) && j != i; j = (j + 1) % N) {
                ++k[i];
            }
        }

        long long ret = 0;
        for (int i = 0; i < N; ++i) {
            int d = 0;
            for (int j = (i + 1) % N; 0 < cp(i, j) && j != i; j = (j + 1) % N) {
                int c = k[j] - k[i] + (++d);
                ret += c;
            }
        }

        return ret / 3;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int xARRAY[] = {-1,-1,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {1,-1,0};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TrianglesContainOrigin theObject;
        eq<long long>(0, theObject.count(x, y),1L);
    }
    {
        int xARRAY[] = {-1,-1,1,2};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {1,-1,2,-1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TrianglesContainOrigin theObject;
        eq<long long>(1, theObject.count(x, y),2L);
    }
    {
        int xARRAY[] = {-1,-2,3,3,2,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-2,-1,1,2,3,3};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TrianglesContainOrigin theObject;
        eq<long long>(2, theObject.count(x, y),8L);
    }
    {
        int xARRAY[] = {1,5,10,5,-5,7,-9,-6,-3,0,8,8,1,-4,7,-3,10,9,-6};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {5,-6,-3,4,-2,-8,-7,2,7,4,2,0,-4,-8,7,5,-5,-2,-9};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        TrianglesContainOrigin theObject;
        eq<long long>(3, theObject.count(x, y),256L);
    }
    return 0;
}
// END CUT HERE
