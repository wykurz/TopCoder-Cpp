#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    std::cerr << a;
}
static void print( long long a ) {
    std::cerr << a << "L";
}
static void print( std::string a ) {
    std::cerr << '"' << a << '"';
}
template<typename T> void print( std::vector<T> a ) {
    std::cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) std::cerr << ", ";
        print( a[i] );
    }
    std::cerr << "}" << std::endl;
}
#pragma GCC diagnostic ignored "-Wunused-function"
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        std::cerr << "Case " << n << " passed." << std::endl;
    } else {
        std::cerr << "Case " << n << " failed: expected ";
        print( need );
        std::cerr << " received ";
        print( have );
        std::cerr << "." << std::endl;
    }
}
template<typename T> void eq( int n, std::vector<T> have, std::vector<T> need ) {
    if( have.size() != need.size() ) {
        std::cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            std::cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    std::cerr << "Case " << n << " passed." << std::endl;
}
static void eq( int n, std::string have, std::string need )
{
    if ( have == need ) {
        std::cerr << "Case " << n << " passed." << std::endl;
    } else {
        std::cerr << "Case " << n << " failed: expected ";
        print( need );
        std::cerr << " received ";
        print( have );
        std::cerr << "." << std::endl;
    }
}
// END CUT HERE

class RectangleCoveringEasy
{
  public:
    int solve(int hh, int hw, int bh, int bw)
    {
        if (hh <= bh && hw <= bw && (hh < bh || hw < bw)) return 1;
        if (hh <= bw && hw <= bh && (hh < bw || hw < bh)) return 1;
        return -1;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        RectangleCoveringEasy theObject;
        eq(0, theObject.solve(1, 1, 1, 1),-1);
    }
    {
        RectangleCoveringEasy theObject;
        eq(1, theObject.solve(3, 5, 4, 6),1);
    }
    {
        RectangleCoveringEasy theObject;
        eq(2, theObject.solve(10, 20, 25, 15),1);
    }
    {
        RectangleCoveringEasy theObject;
        eq(3, theObject.solve(3, 10, 3, 12),1);
    }
    return 0;
}
// END CUT HERE
