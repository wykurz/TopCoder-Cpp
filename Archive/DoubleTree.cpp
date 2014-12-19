#include <future>
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

class DoubleTree
{
  public:
    int N;

    int maximalScore(vector <int> a, vector <int> b, vector <int> c, vector <int> d, vector <int> score)
    {
        // Solution:
        // 1) DP on a tree
        // 2) On each level run a DP like that of http://en.wikipedia.org/wiki/Subset_sum_problem
        // 3) for each 2 nodes, when combining them, add a hidden value from must-add nodes
        //    a) This can be done quickly using a lookup method, since there are only N^2 paths
        //    b) Store every path between two nodes as an int64
        //    c) ... this doesn't work
        //
        // This may not work... D'oh!

        return 0;
    }
};

// If a function cannot throw an exception or if the program isn't written to handle
// exceptions thrown by a function, that function can be declared noexcept. For example:
extern "C" double sqrt(double) noexcept;
vector<double> my_computation(const vector<double>& v) noexcept
{
    vector<double> res(v.size());	// might throw
    for(int i; i<v.size(); ++i) res[i] = sqrt(v[i]);
    return res;
}
// It is possibly to make a function conditionally noexcept, do_f can throw if f(v.at(0)) can
template<class T> void do_f(vector<T>& v) noexcept(noexcept(f(v.at(0))))
{
    for(int i; i<v.size(); ++i)
        v.at(i) = f(v.at(i));
}

#include <complex>

constexpr std::complex<double> operator""i(unsigned long long d)
{
    return std::complex<double>{0.0, static_cast<double>(d)};
}
constexpr std::complex<double> operator""i(long double d)
{
    return std::complex<double>{0.0, static_cast<double>(d)};
}

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    auto z = 2.0 + 1i;

    {
        int aARRAY[] = {0,0,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,3,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,3};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,3,2};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {1000,24,100,-200};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(0, theObject.maximalScore(a, b, c, d, score),1024);
    }
    {
        int aARRAY[] = {0,0,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,3,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,3};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,3,2};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {1000,24,100,200};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(1, theObject.maximalScore(a, b, c, d, score),1324);
    }
    {
        int aARRAY[] = {0,0,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,3,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,3};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,3,2};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {-1000,-24,-100,-200};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(2, theObject.maximalScore(a, b, c, d, score),0);
    }
    {
        int aARRAY[] = {0,0,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,3,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,3};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,3,2};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {-1000,24,100,200};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(3, theObject.maximalScore(a, b, c, d, score),200);
    }
    {
        int aARRAY[] = {0,0,1,1,2,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5,6};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,1,1,2,2};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,2,3,4,5,6};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {-3,2,2,-1,2,2,-1};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(4, theObject.maximalScore(a, b, c, d, score),5);
    }
    {
        int aARRAY[] = {0,0,1,1,2,2};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1,2,3,4,5,6};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        int cARRAY[] = {0,0,0,0,0,0};
        vector <int> c( cARRAY, cARRAY+ARRSIZE(cARRAY) );
        int dARRAY[] = {1,2,3,4,5,6};
        vector <int> d( dARRAY, dARRAY+ARRSIZE(dARRAY) );
        int scoreARRAY[] = {-3,2,2,-1,2,2,-1};
        vector <int> score( scoreARRAY, scoreARRAY+ARRSIZE(scoreARRAY) );
        DoubleTree theObject;
        eq(5, theObject.maximalScore(a, b, c, d, score),5);
    }
    return 0;
}
// END CUT HERE
