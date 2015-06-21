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

template<typename T, typename U> void print( vector<pair<T, U>> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        cerr << "[";
        print( a[i].first );
        cerr << ", ";
        print( a[i].second );
        cerr << "]";
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
typedef vector<pair<int,int>> vpi;
typedef vector<vpi>  vvpi;

class Coversta
{
  public:
    int place(vector <string> a, vector <int> x, vector <int> y)
    {
        const int N = a.size();
        const int M = a[0].size();
        const int K = x.size();

        vvi t;
        for (auto s : a) {
            vi r;
            for (auto c : s) {
                r.push_back(c - '0');
            }
            t.push_back(r);
        }

        int mr = 0;
        auto p = make_pair(0, 0);
        for (int ix = 0; ix < N; ++ix) {
            for (int iy = 0; iy < M; ++iy) {
                int r = 0;
                for (int i = 0; i < K; ++i) {
                    int cx = ix + x[i];
                    int cy = iy + y[i];
                    if (cx < 0 || N <= cx || cy < 0 || M <= cy) continue;
                    r += t[cx][cy];
                }
                if (mr < r) {
                    mr = r;
                    p = {ix, iy};
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < K; ++j) {
                int dx = p.first  + x[i] - x[j];
                int dy = p.second + y[i] - y[j];
                if (dx < 0 || N <= dx || dy < 0 || M <= dy) continue;
                int r = 0;
                for (int k = 0; k < K; ++k) {
                    int kx = x[k] + dx;
                    int ky = y[k] + dy;
                    if (kx < 0 || N <= kx || ky < 0 || M <= ky) continue;
                    r += t[kx][ky];
                    t[kx][ky] = 0;
                }

                int mr2 = 0;
                for (int ix = 0; ix < N; ++ix) {
                    for (int iy = 0; iy < M; ++iy) {
                        int r = 0;
                        for (int i = 0; i < K; ++i) {
                            int cx = ix + x[i];
                            int cy = iy + y[i];
                            if (cx < 0 || N <= cx || cy < 0 || M <= cy) continue;
                            r += t[cx][cy];
                        }
                        if (mr2 < r) {
                            mr2 = r;
                        }
                    }
                }

                for (int k = 0; k < K; ++k) {
                    int kx = x[k] + dx;
                    int ky = y[k] + dy;
                    if (kx < 0 || N <= kx || ky < 0 || M <= ky) continue;
                    t[kx][ky] = a[kx][ky] - '0';
                }

                ret = max(ret, r + mr2);
            }
        }

        return ret;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        string aARRAY[] = {"404433240012110221142322113021134224043", "123341133242224314310023102431004001133", "434410111344132332413043402131104204232", "210110204120014102122223304431321103301", "200442330120114011343499993303223333210", "234410104413343444200399993303301314342", "223234023103112420312199994113211421240", "200341314032020312222441414320044120033", "434124421430211032044111133003232031131", "214124100314424344004134233203120244444", "243022323033202032242034321132030122214", "020340003101200040440143211331434420201", "020012334421022402433022312100402101111", "230043301240333022034302423321003340014", "012030111212214112222101344042103244422", "423231023033241104010140303413424131023", "103100221243231303023022204103002400341", "043042041340322411221403412033241240324", "013022431313014042431432000432324314300", "213424044000330132222031332040033233243", "413230134310430032130103344334214031100", "141404203213211344012030111441213200101", "012100243312323434313423430033001431342", "143234023143434130142033423201431430424", "301420000423240044001104033322143310333", "430104132303014034310142344101111121401", "121440234102311332221210444103124033121", "443240244333143112332122023223020342320", "002212323110403400022002143141343300100", "340042214440303002123314414002423403310", "232411124044311440001004413440034123313", "102440221044420042122240040341224322230", "334441430110222214213211333231012100412", "434233113321122323030323310310424410233", "422012220241032340422023120313303120234", "133203120433131234000113003323010042223", "244432220342340140233143104024031402403", "323210402040012043412330211023434444203", "232302142141103312214321004410322402101", "243301011334320241031344033234430132311", "412241414213104202112120340200313330120", "004043042221222011204131231144211034032", "331120212111102430144343203332201301140"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(8, theObject.place(a, x, y),126);
    }

    {
        string aARRAY[] = {"68473", "98008", "80514", "36392", "19823", "40231"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {1, -5, -3, -5, 0, -1, 5, 1, 2, -4};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-4, -2, 2, 3, 4, 1, -4, 3, -2, 2};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(7, theObject.place(a, x, y),43);
    }

    {
        string aARRAY[] = {"11",
            "11"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {0,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {0,1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(0, theObject.place(a, x, y),4);
    }

    {
        string aARRAY[] = {"11",
            "11"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {0,1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {0,1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(1, theObject.place(a, x, y),3);
    }

    {
        string aARRAY[] = {"15",
            "61"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {0};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(2, theObject.place(a, x, y),11);
    }
    {
        string aARRAY[] = {"151",
            "655",
            "661"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {0,0,-1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {0,1,0};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(3, theObject.place(a, x, y),33);
    }
    {
        string aARRAY[] = {"303",
            "333",
            "000"};
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {-1,-1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-1,1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(4, theObject.place(a, x, y),12);
    }
    {
        string aARRAY[] = {"0000000",
            "1010101"}
           ;
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {-1,-1};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-1,1};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(5, theObject.place(a, x, y),0);
    }

    {
        string aARRAY[] = {"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                           "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"}
        ;
        vector <string> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int xARRAY[] = {-1,-1,0,0,0,0,0,0,0,0};
        vector <int> x( xARRAY, xARRAY+ARRSIZE(xARRAY) );
        int yARRAY[] = {-1,1,0,0,0,0,0,0,0,0};
        vector <int> y( yARRAY, yARRAY+ARRSIZE(yARRAY) );
        Coversta theObject;
        eq(6, theObject.place(a, x, y),0);
    }

    return 0;
}
// END CUT HERE
