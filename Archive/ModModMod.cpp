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
typedef long long    ll;

#include <assert.h>

class ModModMod
{
  public:

    ll sum(const vi& t, int x)
    {
        if (0 == x) return 0;
        assert(0 < x);
        const auto it = lower_bound(t.begin(), t.end(), x);
        if (*it == x) --x;
        if (t.begin() == it) {
            ll s = x * ll(x + 1) / 2;
            return s;
        }
        int y = *(it - 1);
        ll s1 = sum(t, y - 1);
        ll s2 = sum(t, x % y);
        return s1 * (x / y) + s2;
    }

    long long findSum(vector <int> m, int R)
    {
        vi t;
        for (int x : m)
        {
            if (t.empty() or x < t[t.size() - 1]) t.push_back(x);
        }
        reverse(t.begin(), t.end());
        return sum(t, R);
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int mARRAY[] = {10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 9999999, 9999999, 9999998, 9999998, 9999997, 9999994, 9999993, 9999992, 9999989, 9999988, 9999988, 9999986, 9999986, 9999986, 9999983, 9999983, 9999982, 9999974, 9999971, 9999964, 9999964, 9999964, 9999962, 9999959, 9999959, 9999874, 9999872, 9999860, 9999856, 9999800, 9999783, 9999769, 9999722, 9999648, 9999611, 9999441, 9999374, 9999310, 9999076, 9998897, 9998896, 9998862, 9998555, 9998519, 9998397, 9998349, 9997844, 9997705, 9997479, 9997436, 9997026, 9996393, 9996157, 9994988, 9994225, 9993781, 9993773, 9993541, 9993049, 9983997, 9981876, 9976641, 9975642, 9975182, 9973087, 9970604, 9966793, 9965514, 9963966, 9963766, 9949265, 9938622, 9930199, 9923577, 9914828, 9913139, 9908311, 9899982, 9873612, 9862712, 9861235, 9849410, 9789914, 9764760, 9759326, 9738240, 9697498, 9691075, 9674016, 9613096, 9456432, 8880810, 8813859, 8491063, 8138611, 8126273, 7886166, 7866570, 7830901, 7550460, 7527037, 7289395, 6639620, 5291389, 5286081, 5233444, 2702602, 1964016, 820862};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(7, theObject.findSum(m, 10000000),2971356079520L);
    }


    {
        int mARRAY[] = {5748988, 5728500, 7571811, 8815102, 5236307, 8014159, 9430449, 9933092, 9714515, 8998648, 6131213, 5336800, 9098515, 9031884, 6661490, 6632155, 7706784, 6028260, 5686950, 5585278, 7344838, 6373973, 7531620, 9441516, 8465201, 9658407, 6245976, 5851673, 9529727, 7713113, 5426570, 5586770, 7751937, 6376512, 7080520, 9860299, 8855021, 8993256, 8364387, 7870932, 9345398, 8904259, 8469314, 9128844, 7072268, 9086752, 5272933, 9235199, 9520325, 5663223, 7633453, 7047118, 9365801, 8214009, 9362435, 5579325, 8315306, 8700298, 9980189, 8568915, 8142380, 7332681, 5331328, 9361097, 7138490, 7904921, 8017909, 8661486, 5903168, 6953445, 8393713, 7744447, 8512271, 5600146, 6555625, 8907188, 8623827, 5089371, 9366674, 5315763, 5007732, 6839579, 9050204, 7901821, 7318505, 5295937, 6305758, 7637889, 5669635, 6992227, 6214661, 7344183, 6713514, 7008716, 9426897, 8161367, 9482724, 9447272, 9250779, 6961385, 6206461, 6635748, 7303039, 7262452, 6680128, 7520815, 6319330, 7664447, 9536627, 9111661};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(6, theObject.findSum(m, 8573793),16663914484738L);
    }

    {
        int mARRAY[] = {5,3,2};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(0, theObject.findSum(m, 5),2L);
    }

    {
        int mARRAY[] = {5,3,2};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(0, theObject.findSum(m, 10),4L);
    }

    {
        int mARRAY[] = {33, 15, 7, 10, 100, 9, 5};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(1, theObject.findSum(m, 64),92L);
    }

    {
        int mARRAY[] = {995,149,28,265,275,107,555,241,702,462,519,212,362,478,783,381,602,546,183,886,59,317,977,612,328,91,771,131};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(2, theObject.findSum(m, 992363),12792005L);
    }

    {
        int mARRAY[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(3, theObject.findSum(m, 100),4950L);
    }

    {
        int mARRAY[] = {2934};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(4, theObject.findSum(m, 10000000),14664070144L);
    }

    {
        int mARRAY[] = {3};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(5, theObject.findSum(m, 10), 10L);
    }

    {
        int mARRAY[] = {3};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(5, theObject.findSum(m, 11), 12L);
    }

    {
        int mARRAY[] = {3};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(5, theObject.findSum(m, 12), 12L);
    }

    {
        int mARRAY[] = {3};
        vector <int> m( mARRAY, mARRAY+ARRSIZE(mARRAY) );
        ModModMod theObject;
        eq<long long>(5, theObject.findSum(m, 12), 12L);
    }

    return 0;
}
// END CUT HERE
