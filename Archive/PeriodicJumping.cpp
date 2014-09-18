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

typedef unsigned long long ull;

class PeriodicJumping
{
  public:
    int minimalTime(int x, vector<int> v)
    {
        if (0 == x) return 0;
        int N = v.size();
        x = abs(x);
        ull sum = x;
        vector<int>  w;
        w.push_back(x);
        for (int i = 0; i < 2 * N; ++i) {
            sum += v[i % N];
            w.push_back(v[i % N]);
            bool ok = true;
            for (int j = 0; j < w.size(); ++j) {
                if (sum < 2 * w[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return i + 1;
            }
        }
        if (sum < 2 * x) {
            ull msum = sum - x;
            int ret = 2 * N * (x / msum);
            x %= msum;
            int i = 0;
            while (0 < x) {
                x -= v[i % N];
                ++i;
            }
            return ret + i;
        }
        return -1;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int jumpLengthsARRAY[] = {1,2,3,4,5,6,7,8,9,10};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(0, theObject.minimalTime(15, jumpLengths),5);
    }

    {
        int jumpLengthsARRAY[] = {5};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(1, theObject.minimalTime(5, jumpLengths),1);
    }

    {
        int jumpLengthsARRAY[] = {10};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(2, theObject.minimalTime(1, jumpLengths),2);
    }

    {
        int jumpLengthsARRAY[] = {2,3,4,500,6,7,8};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(3, theObject.minimalTime(-10, jumpLengths),11);
    }

    {
        int jumpLengthsARRAY[] = {1};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(4, theObject.minimalTime(-1000000000, jumpLengths),1000000000);
    }

    {
        int jumpLengthsARRAY[] = {19911120};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(5, theObject.minimalTime(0, jumpLengths),0);
    }

    {
        int jumpLengthsARRAY[] = {99};
        vector <int> jumpLengths( jumpLengthsARRAY, jumpLengthsARRAY+ARRSIZE(jumpLengthsARRAY) );
        PeriodicJumping theObject;
        eq(6, theObject.minimalTime(653528017, jumpLengths),6601294);
    }

    return 0;
}
// END CUT HERE
