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

class BuildingTowersEasy
{
  public:
    int maxHeight(int N, vector <int> x, vector <int> t)
    {
        int M = x.size();
        vi v(N, -1);
        for (int i = 0; i < M; ++i) {
            v[x[i] - 1] = t[i];
        }
        v[0] = 0;
        for (int i = 1; i < N; ++i) {
            if (v[i] < 0 || v[i - 1] + 1 <= v[i]) {
                v[i] = v[i - 1] + 1;
            }
            else {
                for (int j = i - 1; 0 <= j; --j) {
                    if (v[j + 1] + 1 < v[j]) {
                        v[j] = v[j + 1] + 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return *max_element(v.begin(), v.end());
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int xARRAY[] = {1,30,400,1300,2500};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int tARRAY[] = {100000,100000,100000,100000,100000};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        BuildingTowersEasy theObject;
        eq(2, theObject.maxHeight(2718, x, t),2717);
    }

    {
        int xARRAY[] = {3,8};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int tARRAY[] = {1,1};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        BuildingTowersEasy theObject;
        eq(0, theObject.maxHeight(10, x, t),3);
    }
    {
        BuildingTowersEasy theObject;
        eq(1, theObject.maxHeight(100000, vector <int>(), vector <int>()),99999);
    }
    {
        int xARRAY[] = {4,7,13,15,18};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int tARRAY[] = {3,8,1,17,16};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        BuildingTowersEasy theObject;
        eq(3, theObject.maxHeight(20, x, t),8);
    }
    {
        int xARRAY[] = {32,35,55,60,61,88,91,97,128,151,181,186,192,196,198,237,259,268,291,314,341,367,389,390,391,428,435};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int tARRAY[] = {81,221,172,641,25,953,330,141,123,440,692,394,200,649,78,726,50,810,501,4,216,407,2,172,0,29,14};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        BuildingTowersEasy theObject;
        eq(4, theObject.maxHeight(447, x, t),120);
    }
    {
        int xARRAY[] = {8,1749,4550,5388,6752,7089,9737,14891,16671,16821,17691,19753,24589,
           25348,30114,32213,34376,36467,37699,41490,44784,44893,57316,58275,58567,
           61122,61489,63195,64776,65905,68788,69908,72853,78152,78784,82779,84488,
           86277,88611,92793,93214,97583};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int tARRAY[] = {16610,6,497,14,42892,31,79,1203,518,31147,597,7846,1396,8309,12,14,1148,
           433,23693,13,1939,244,19,46,27,611,412,10,27023,19141,34,15667,588,10,229,
           83,390,14,38441,16021,4,39386};
        vector <int> t( tARRAY, tARRAY+ARRSIZE(tARRAY) );
        BuildingTowersEasy theObject;
        eq(5, theObject.maxHeight(97638, x, t),6343);
    }

    return 0;
}
// END CUT HERE
