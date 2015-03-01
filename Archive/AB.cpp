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

class AB
{
  public:
    string createString(int N, int K)
    {
        // [#A][#(A < B)]
        auto dp = vector<vector<std::string>>(N + 1, {K + 1, ""});
        dp[0][0] = "B";
        dp[1][0] = "A";
        auto dp2(dp);
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k <= K; ++k) {
                    if (i != dp[j][k].size()) continue;
                    // cerr << "processing dp[" << j << "][" << k << "] : " << dp[j][k] << endl;
                    dp2[j + 1][k] = dp[j][k] + "A";
                    int nk = j + k;
                    if (nk <= K) {
                        dp2[j][nk] = dp[j][k] + "B";
                        // cerr << "add b = dp[" << j << "][" << nk << "] : " << dp2[j][nk] << endl;
                    }
                }
            }
            swap(dp, dp2);
        }
        for (int i = 0; i <= N; ++i) {
            if (N == dp[i][K].size()) return dp[i][K];
        }
        return "";
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        AB theObject;
        eq(0, theObject.createString(3, 2),"ABB");
    }
    {
        AB theObject;
        eq(1, theObject.createString(2, 0),"BA");
    }
    {
        AB theObject;
        eq(2, theObject.createString(5, 8),"");
    }
    {
        AB theObject;
        eq(3, theObject.createString(10, 12),"BAABBABAAB");
    }
    return 0;
}
// END CUT HERE
