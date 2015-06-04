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

class ApplesAndOrangesEasy
{
  public:
    int maximumApples(int N, int K, vector <int> info)
    {
        vb q(N, false);
        for (auto x : info) {
            q[x - 1] = true;
        }
        const int max = K / 2;
        vb t(N);
        int count = 0;
        for (int i = 0; i < N; ++i) {
            ++count;
            t[i] = true;
            const int s = std::max(0, i - K + 1);
            if (0 < s and t[s - 1]) --count;
            for (int j = i; s <= i; --j) {
                if (count <= max) break;
                if (not q[j] and t[j]) {
                    --count;
                    t[j] = false;
                }
            }
        }
        int ret = 0;
        for (auto x : t) ret += x ? 1 : 0;
        return ret;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        ApplesAndOrangesEasy theObject;
        eq(0, theObject.maximumApples(3, 2, vector <int>()),2);
    }
    {
        int infoARRAY[] = {3, 8};
        vector <int> info( infoARRAY, infoARRAY+ARRSIZE(infoARRAY) );
        ApplesAndOrangesEasy theObject;
        eq(1, theObject.maximumApples(10, 3, info),2);
    }
    {
        int infoARRAY[] = {1, 4};
        vector <int> info( infoARRAY, infoARRAY+ARRSIZE(infoARRAY) );
        ApplesAndOrangesEasy theObject;
        eq(2, theObject.maximumApples(9, 4, info),5);
    }
    {
        int infoARRAY[] = {2, 4};
        vector <int> info( infoARRAY, infoARRAY+ARRSIZE(infoARRAY) );
        ApplesAndOrangesEasy theObject;
        eq(3, theObject.maximumApples(9, 4, info),4);
    }
    {
        int infoARRAY[] = {3, 2, 9, 1, 15, 23, 20, 19};
        vector <int> info( infoARRAY, infoARRAY+ARRSIZE(infoARRAY) );
        ApplesAndOrangesEasy theObject;
        eq(4, theObject.maximumApples(23, 7, info),10);
    }
    return 0;
}
// END CUT HERE
