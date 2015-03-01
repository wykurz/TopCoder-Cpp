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

class TaroFillingAStringDiv1
{
  public:
    typedef long long int lli;
    static constexpr lli mod = 1e9 + 7;
    int getNumber(int N, vector <int> pos, string val)
    {
        int n = val.size();
        vector<pair<int, char>> v;
        for (int i = 0; i < n; ++i) {
            v.push_back(make_pair(pos[i], val[i]));
        }
        sort(v.begin(), v.end());
        lli ret = 1;
        pair<int, char> prev = make_pair(-1, 'A');
        for (auto curr : v) {
            if (0 < prev.first && ((prev.first - curr.first) & 1) != ((prev.second - curr.second) & 1)) {
                ret *= curr.first - prev.first;
                ret %= mod;
            }
            prev = curr;
        }
        return ret;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int positionARRAY[] = {1, 3};
        vector <int> position( positionARRAY, positionARRAY+ARRSIZE(positionARRAY) );
        TaroFillingAStringDiv1 theObject;
        eq(0, theObject.getNumber(3, position, "AB"),2);
    }
    {
        int positionARRAY[] = {2, 1, 3, 4};
        vector <int> position( positionARRAY, positionARRAY+ARRSIZE(positionARRAY) );
        TaroFillingAStringDiv1 theObject;
        eq(1, theObject.getNumber(4, position, "ABBA"),1);
    }
    {
        int positionARRAY[] = {23, 4, 8, 1, 24, 9, 16, 17, 6, 2, 25, 15, 14, 7, 13};
        vector <int> position( positionARRAY, positionARRAY+ARRSIZE(positionARRAY) );
        TaroFillingAStringDiv1 theObject;
        eq(2, theObject.getNumber(25, position, "ABBBBABABBAAABA"),1);
    }
    {
        int positionARRAY[] = {183, 115, 250, 1, 188, 193, 163, 221, 144, 191, 92, 192, 58, 215, 157, 187, 227, 177, 206, 15, 272, 232, 49, 11, 178, 59, 189, 246};
        vector <int> position( positionARRAY, positionARRAY+ARRSIZE(positionARRAY) );
        TaroFillingAStringDiv1 theObject;
        eq(3, theObject.getNumber(305, position, "ABAABBABBAABABBBBAAAABBABBBA"),43068480);
    }
    return 0;
}
// END CUT HERE
