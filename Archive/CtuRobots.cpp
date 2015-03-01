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

class CtuRobots
{
  public:
    struct Robot
    {
        int cost;
        int cap;
    };

    double maxDist(int B, vector <int> cost, vector <int> cap)
    {
        int N = cost.size();
        vector<Robot> robots;
        for (int i = 0; i < N; ++i) {
            robots.emplace_back(Robot{cost[i], cap[i]});
        }
        sort(robots.begin(), robots.end(), [](const Robot& l, const Robot& r) { return l.cap < r.cap; });
        vector<double> curr(B + 1, 0);
        vector<double> prev(B + 1, 0);
        for (const Robot& r : robots) {
            for (int i = 0; i <= B; ++i) {
                curr[i] = prev[i];
            }
            for (int i = 0; i + r.cost <= B; ++i) {
                curr[i + r.cost] = max(curr[i + r.cost], prev[i] / 3.0 + r.cap);
            }
            swap(curr, prev);
        }
        return *max_element(prev.begin(), prev.end()) / 2.0;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int costARRAY[] = {50,25};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {1,1};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(0, theObject.maxDist(100, cost, cap),0.6666666666666666);
    }
    {
        int costARRAY[] = {23,5,8,20,15};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {108,30,42,100,94};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(1, theObject.maxDist(25, cost, cap),55.0);
    }
    {
        int costARRAY[] = {0,0,0,1000,1000,0,1000,0};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {2039,4819,5923,1577,8749,9182,3652,4918};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(2, theObject.maxDist(1382, cost, cap),6503.238683127572);
    }
    {
        int costARRAY[] = {185,130,109,1,45,117,127,13,2,37,6,1,2};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {93,5,278,4,20,54,93,213,103,5,225,32,5};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(3, theObject.maxDist(209, cost, cap),190.48376771833563);
    }
    {
        int costARRAY[] = {3229,736,1325,2680,410,1227,1378,499,1525,1722,1262,2080,2581,1505,1019,
           480,3155,836,2697,616,136,2032,2345,3154,1953,1654,344,3079,1426,199,2857,
           1714,2952,996,1567,2674,2054,2110,949,2412,2148,1016,234,1932,1554,1943,
           1625,1266,258,2924,49,1693,3140,309,557,12,2760,227,2497,330,646,1935,3032,
           2671,2433,164,1472,3080,717,221,2483,1309,1174,12,917,2335,3086,148,64,189,
           2628,1660,2983,109,1920,2470};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {934850,214,15807606,2426,176520,1900009,1184867,40550,1774843,2953,77834310,
           7276,3139890,695,213862217,13,193864,189,557664,1206555,85133,381662,4887,
           115027,2186890,218075,1,2024,9,95244962,7,906,3485642,52962078,58645759,785706,
           303,18,189,819600,17528041,11616471,92719012,82351,12752,634,26122233,215485,
           58,5506810,101874,130429471,2,1,68966,76303,321766922,463,26,225,207,52,1739,
           246841,496,228,4749453,191,79,10560,1414194,7529,13,521935,1,2,11590618,4020,
           105,3,28,3,2855,189909573,1,295052};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(4, theObject.maxDist(9956, cost, cap),2.1034261053998655E8);
    }
    {
        int costARRAY[] = {2547,912,2592,1085,296,523,2257,2347,1822,261,334,2159,528,2739,201,964,427,
           2038,26,2361,234,2063,2885,2178,2708,730,2902,326,306,2794,1725,13,137,2169,
           388,1124,1464,2120,2357,1544,2794,2260,185,650,2852,124,1767,453,1331,1397,
           1991,1166,413,1428,2862,1194,1139,571,1299,1232,267,2027,746,1971,2695,2586,
           185,1319,1088,2818,2604,1798,475,1252,1767,2277,545,601,2160,325,2749,1161,
           1172,1075,1925,2468,1596,1116,1558,2226,1302,796,775,1105,418,334,2872,1921,
           2830,2448,2914,2634,1386,2516,492,1029,1134,2934,2017,1741,1675,2593,2233,
           2401,68,683,2053,155,183,923,2276,1823,65,2290,2448,92,2468,819,837,303,1440,
           705,291,2348,2562,765,1926,14,2514,2403,2671,1143,1358,121,376,2874,2447,1769,
           1686,967,967,2492,2472,2014,1686,2291,1093,1801,818};
        vector <int> cost( costARRAY, costARRAY+ARRSIZE(costARRAY) );
        int capARRAY[] = {263268,256181,476791,365614,265352,19307,243180,84909,98175,367524,241474,479623,
           277638,111229,155356,415525,234382,97870,451466,58375,268277,404582,484789,458230,
           529286,449840,103208,199505,319373,294746,78005,326456,14418,257144,135669,238651,
           411723,99122,20421,298154,278407,153564,24778,73065,110408,392693,510192,362399,
           333830,125893,130946,345134,261418,230632,306751,451242,175675,459988,150787,349338,
           134594,255227,263645,180770,436965,502871,242085,318340,220576,189202,395789,390659,
           101649,337117,440471,466547,513054,316694,30382,38826,472506,67698,223953,397305,
           325564,57949,194651,443500,443188,431386,220061,400640,286085,189461,324214,171813,
           420711,260549,426526,208052,83343,429483,366076,52443,224742,333286,544259,335276,
           93282,326772,82841,225256,270357,547610,397526,193336,182374,439866,255860,111363,
           509167,228847,218257,39438,212242,378338,88972,127544,59230,428847,155553,116333,
           255176,396356,223463,226360,38283,6238,173455,447707,332111,60485,398523,462205,
           55397,148417,529738,460063,177715,404809,336155,50750,24165,530386,394811,512481,
           230296,45797,370008};
        vector <int> cap( capARRAY, capARRAY+ARRSIZE(capARRAY) );
        CtuRobots theObject;
        eq(5, theObject.maxDist(8852, cost, cap),408339.73124862404);
    }
    return 0;
}
// END CUT HERE
