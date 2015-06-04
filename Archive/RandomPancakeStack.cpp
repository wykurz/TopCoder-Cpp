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

typedef vector<double> vd;
typedef vector<vd>     vvd;

class RandomPancakeStack
{
  public:
    double expectedDeliciousness(vector<int> d)
    {
        int N = d.size();
        vvd dp(N + 1, vd(N + 1, 0));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                for (int k = 0; k < i; ++k) {
                    dp[i][j] += dp[k][j - 1] + d[k];
                }
                dp[i][j] /= j;
            }
        }
        return dp[N][N];
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int dARRAY[] = {1,1,1};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(0, theObject.expectedDeliciousness(d),1.6666666666666667);
    }
    {
        int dARRAY[] = {3,6,10,9,2};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(1, theObject.expectedDeliciousness(d),9.891666666666667);
    }
    {
        int dARRAY[] = {10,9,8,7,6,5,4,3,2,1};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(2, theObject.expectedDeliciousness(d),10.999999724426809);
    }
    {
        int dARRAY[] = {1,2,3,4,5,6,7,8,9,10};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(3, theObject.expectedDeliciousness(d),7.901100088183421);
    }
    {
        int dARRAY[] = {2,7,1,8,2,8,1,8,2,8,4,5,90,4,5,2,3,5,60,2,8,74,7,1};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(4, theObject.expectedDeliciousness(d),19.368705050402465);
    }
    {
        int dARRAY[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        RandomPancakeStack theObject;
        eq(5, theObject.expectedDeliciousness(d),1.718281828459045);
    }
    return 0;
}
// END CUT HERE
