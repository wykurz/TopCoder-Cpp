#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <typeinfo>
#include <functional>

using namespace std;
// BEGIN CUT HERE
vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( size_t i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}
vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( size_t i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}
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
    for ( size_t i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
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
    for( size_t i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
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

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) begin(c), end(c)
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c, x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

int gg[100][100];
int hh[100];

class TreeAndCycle {
public:
    int minimize(vector <int> costV, vector <int> pre, vector <int> costE)
    {
        ZERO(gg);
        ZERO(hh);
        int n = costV.size() + 1;
        vector<tuple<int, int> > el;
        REP(i, n - 1) {
            int u = i + 1, v = pre[i];
            gg[u][v] = costE[i];
            gg[v][u] = costE[i];
            ++hh[u];
            ++hh[v];
            el.push_back(make_tuple(u, v));
        }
        int res = 0;
        // In a loop:
        // 1) for any vertex with more than 2 edges, find cheapest edge to remove
        // 2) remove, update costs for adjecent edges
        while (2 < *max_element(ALL(hh))) {
            vector<tuple<int, int, int> > vv;
            for (auto& p : el) {
                int u, v;
                tie(u, v) = p;
                if (hh[u] < 3 && hh[v] < 3) continue;
                int addCost = 0;
                if (hh[u] < 3) addCost += costV[u];
                if (hh[v] < 3) addCost += costV[v];
                vv.push_back(make_tuple(gg[u][v] + addCost, u, v));
            }
            assert(vv.size());
            sort(ALL(vv));
            int cost, u, v;
            tie(cost, u, v) = vv[0];
            res += gg[u][v];
            --hh[u];
            --hh[v];
            assert(0 <= hh[u]);
            assert(0 <= hh[v]);
            auto it = find(ALL(el), make_tuple(u, v));
            if (it == el.end()) it = find(ALL(el), make_tuple(v, u));
            assert(it != el.end());
            el.erase(it);
        }
        REP(i, n) if(hh[i] < 2) res += (2 - hh[i]) * costV[i];
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int costVARRAY[] = {7,2,5,8};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,1,2};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {6,4,3};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(0, theObject.minimize(costV, pre, costE),15);
    }
    {
        int costVARRAY[] = {100,5,9,8};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,0,0};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {6,2,2};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(1, theObject.minimize(costV, pre, costE),32);
    }
    {
        int costVARRAY[] = {10,20,30,40,50,60,70,80,90};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0,1,2,2,3,4,5,7};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {5,15,25,35,45,55,65,75};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(2, theObject.minimize(costV, pre, costE),205);
    }
    return 0;
}
// END CUT HERE
