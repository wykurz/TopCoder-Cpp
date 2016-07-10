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
        int n = costV.size();
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
        int costVARRAY[] = {9984, 8708, 8276, 9922, 9994, 8938, 9991, 9984, 9609, 9973, 9998, 9833, 9592, 9813, 9978, 9977, 9836, 9998, 9998, 9591, 9794, 9995, 9673, 9917, 9980, 9159, 9951, 9960, 9062, 9998, 9463, 9992, 9992, 9962, 9784, 9998, 9702, 7611, 7666, 9991, 9672, 9888, 8763, 9994, 9994, 9431, 9998, 9814, 7878, 9833, 9871, 9809, 9978, 9894, 9709, 9996, 8468, 9819, 9975, 9968, 9383, 9983, 9998, 9987, 9985, 8360, 8618, 9677, 9936, 9998, 9743, 9998, 9927, 9799, 9985, 9998, 9176, 9996, 9986, 9088, 9997, 9996, 9972, 9981, 9554, 9957, 9993, 9998, 9998, 9997, 9965, 9314, 9994, 9983, 9976, 9996, 7092, 9998, 9997};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0, 1, 0, 2, 3, 5, 5, 3, 8, 9, 2, 5, 0, 5, 12, 9, 16, 2, 0, 1, 12, 6, 17, 16, 6, 22, 5, 6, 2, 23, 22, 20, 25, 29, 26, 11, 24, 7, 21, 9, 27, 2, 4, 37, 28, 8, 21, 36, 10, 41, 34, 16, 50, 29, 50, 16, 14, 13, 14, 40, 41, 56, 6, 42, 20, 6, 7, 37, 49, 42, 22, 69, 23, 12, 8, 67, 41, 44, 20, 71, 31, 5, 20, 75, 35, 47, 29, 58, 73, 6, 53, 12, 21, 31, 55, 27, 28, 91};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {1, 15, 4, 10, 1, 99, 9, 197, 2, 87, 1, 59, 118, 4, 3, 1, 170, 3, 13, 1, 209, 162, 78, 3, 1, 69, 2, 12, 1, 5, 3, 6, 17, 68, 3, 107, 33, 1, 259, 55, 31, 112, 2, 18, 15, 84, 1, 1, 63, 151, 36, 71, 2, 2, 1, 3, 4, 17, 1, 1, 2, 43, 5, 154, 2, 13, 214, 272, 6, 6, 2, 14, 6, 277, 23, 3, 13, 1, 5, 1, 1, 13, 6, 36, 1, 1, 9, 1, 11, 2, 30, 203, 1, 254, 45, 98, 1, 2};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(0, theObject.minimize(costV, pre, costE),634253);
    }
    {
        int costVARRAY[] = {1, 12, 143, 4906, 4, 8, 4951, 106, 9950, 5098, 1, 3, 8, 5014, 5090, 5038, 5068, 9981, 80, 207, 96, 168, 9084, 9436, 131, 8315, 26, 83, 41, 4911, 3, 4937, 16, 26, 5000, 9, 4961, 5047, 18, 5072, 4963, 2357, 4930, 13, 9624, 96, 1, 196, 25, 4979, 417, 250, 122, 1, 547, 13, 4965, 9934, 4978, 5017, 77, 4941, 1410, 3, 92, 4975, 1, 16, 9990, 3, 767, 5048, 9952, 4976, 2, 403, 1, 5065, 11, 4806, 8, 9496, 9992, 877, 230, 1, 5011, 1, 5096, 99, 4924, 9814, 151, 1, 6011, 6, 7, 225, 4967, 4};
        vector <int> costV( costVARRAY, costVARRAY+ARRSIZE(costVARRAY) );
        int preARRAY[] = {0, 0, 2, 1, 0, 2, 6, 3, 3, 1, 6, 6, 2, 1, 4, 1, 4, 15, 4, 14, 10, 14, 10, 22, 5, 13, 7, 0, 21, 18, 2, 0, 2, 30, 16, 33, 7, 12, 17, 12, 2, 1, 13, 22, 4, 2, 40, 32, 34, 3, 23, 38, 51, 25, 14, 42, 8, 6, 1, 45, 36, 12, 54, 62, 1, 6, 33, 6, 50, 11, 7, 60, 1, 11, 48, 14, 27, 34, 58, 72, 49, 55, 16, 67, 27, 38, 58, 0, 13, 59, 69, 70, 19, 21, 79, 9, 44, 4, 13};
        vector <int> pre( preARRAY, preARRAY+ARRSIZE(preARRAY) );
        int costEARRAY[] = {159, 241, 58, 2, 2, 198, 162, 5, 12, 32, 81, 23, 41, 231, 43, 215, 10, 38, 1, 179, 106, 178, 16, 12, 176, 69, 82, 1, 5, 34, 2, 8, 1, 18, 66, 2, 199, 17, 52, 8, 31, 7, 5, 5, 1, 27, 36, 9, 20, 57, 8, 140, 80, 20, 86, 5, 3, 15, 15, 1, 149, 1, 159, 74, 23, 13, 2, 242, 283, 4, 77, 47, 29, 8, 1, 125, 5, 5, 21, 11, 66, 49, 40, 273, 7, 4, 2, 10, 16, 1, 4, 4, 35, 8, 176, 28, 4, 1, 1};
        vector <int> costE( costEARRAY, costEARRAY+ARRSIZE(costEARRAY) );
        TreeAndCycle theObject;
        eq(0, theObject.minimize(costV, pre, costE),147956);
    }
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
