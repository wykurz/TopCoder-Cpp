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

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[ ";
    for (const T& x : v) {
        os << x << " ";
    }
    os << "]";
    return os;
}

class TheKingsRoadsDiv1
{
  public:
    const string yes{  "Correct"};
    const string  no{"Incorrect"};
    int v;
    int e;
    vvb g;
    vi  c;
    vi  d;

    pair<bool, bool> findCycle(int prev, int curr, vb& visited, vi& cycle, int depth)
    {
        // cerr << "findCycle(" << prev << ", " << curr << ", " << visited << ", " << cycle << ")" << endl;
        if (visited[curr]) {
            cycle.push_back(curr);
            return make_pair(true, false);
        }
        visited[curr] = true;
        if (6 * 10 + 3 < depth) {
            return make_pair(false, false);
        }
        for (int next = 0; next < v; ++next) {
            if (!g[curr][next] || next == prev) continue;
            auto result = findCycle(curr, next, visited, cycle, depth + 1);
            if (result.first) {
                if (!result.second) {
                    cycle.push_back(curr);
                }
                return make_pair(true, result.second || (1 < cycle.size() && curr == cycle[0]));
            }
        }
        return make_pair(false, false);
    }

    int checkGraph(int prev, int curr, vb& visited)
    {
        // cerr << "checkGraph(" << prev << ", " << curr << ", " << visited << ")" << endl;
        if (visited[curr]) {
            // cerr << "Found a cycle!" << endl;
            return -1;
        }
        visited[curr] = true;
        vi numVisited(2);
        int numSons = 0;
        for (int next = 0; next < v; ++next) {
            if (!g[curr][next] || next == prev) continue;
            ++numSons;
            if (2 < numSons) {
                // cerr << "Too many sons" << endl;
                return -1;
            }
            numVisited[numSons -1] = checkGraph(curr, next, visited);
        }
        if (numVisited[0] != numVisited[1]) {
            // cerr << "Imbalanced num sons: " << numVisited[0] << " != " << numVisited[1] << endl;
            return -1;
        }
        int totalVisited = 1 + numVisited[0] + numVisited[1];
        // cerr << "OK, returning " << totalVisited << endl;
        return totalVisited;
    }

    bool checkGraph()
    {
        // cerr << "checkGraph()" << endl;
        if (1 == v) return true;
        if (d[2] != 1) {
            // cerr << "Too many roots" << endl;
            return false;
        }
        if (d[1] != (v + 1) / 2) {
            // cerr << "Invalid # leaves(" << d[0] << ") != " << (v + 1) / 2 << endl;
            return false;
        }
        if (d[1] + d[2] + d[3] != v) {
            // cerr << "Invalid total nodes..." << endl;
            return false;
        }
        int root = -1;
        for (int i = 0; i < v; ++i) {
            if (2 == c[i]) {
                if (root < 0) {
                        root = i;
                }
                else {
                    // cerr << "Wrong root " << root << endl;
                    return false;
                }
            }
        }
        if (root < 0) {
            // cerr << "No root" << endl;
            return false;
        }
        vb visited(v);
        return v == checkGraph(-1, root, visited);
    }

    bool check(int edges)
    {
        // cerr << "check(" << edges << ")" << endl;
        if (0 == edges) {
            return checkGraph();
        }
        vi cycle;
        {
            vb visited(v);
            cycle.reserve(30);
            if (!findCycle(-1, 0, visited, cycle, 0).first) {
                return false;
            }
        }
        if (20 < cycle.size()) {
            cerr << "Long cycle " << cycle.size() << endl;
        }
        for (int i = 0; i < cycle.size() - 1; ++i) {
            int x = cycle[i];
            int y = cycle[i + 1];
            // cerr << "Remove edge: [" << x << ", " << y << "]" << endl;
            g[x][y] = false;
            --c[x];
            ++d[c[x]];
            --d[c[x] + 1];
            g[y][x] = false;
            --c[y];
            ++d[c[y]];
            --d[c[y] + 1];
            if (check(edges - 1)) return true;
            g[x][y] = true;
            ++c[x];
            ++d[c[x]];
            --d[c[x] - 1];
            g[y][x] = true;
            ++c[y];
            ++d[c[y]];
            --d[c[y] - 1];
        }
        return false;
    }

    string getAnswer(int h, vector <int> a, vector <int> b)
    {
        // cerr << "getAnswer(" << h << ", " << a << ", " << b << ")" << endl;
        v = (1 << h) - 1;
        e = a.size();
        if (e != v - 1 + 3 ) {
            // cerr << "e(" << e << ") != v(" << v << ") - 1 + 3" << endl;
            return no;
        }
        for (int i : a) {
            if (v < i) {
                return no;
            }
        }
        for (int i : b) {
            if (v < i) {
                return no;
            }
        }
        g = vvb(v, vb(v));
        c = vi(v);
        d = vi(v + 1);
        int extra = 3;
        for (int i = 0; i < e; ++i) {
            int x = a[i] - 1;
            int y = b[i] - 1;
            if (x == y || g[x][y]) {
                --extra;
                continue;
            }
            g[x][y] = true;
            c[x]++;
            g[y][x] = true;
            c[y]++;
        }
        for (int x : c) {
            ++d[x];
        }
        if (0 < d[0]) {
            return no;
        }
        int obvious = max(0, d[2] - 1);
        for (int i = 4; i < v + 1; ++i) {
            obvious += d[i];
        }
        obvious /= 2;
        if (extra < obvious) {
            // cerr << "Obvious: " << obvious << ", extra: " << extra << endl;
            return no;
        }
        return check(extra) ? yes : no;
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{

    {
        int aARRAY[] = {1, 3, 2, 2, 3, 7, 1, 5, 4};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {6, 5, 4, 7, 4, 3, 3, 1, 7};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(0, theObject.getAnswer(3, a, b),"Correct");
    }

    {
        int aARRAY[] = {1, 2, 1, 3, 3};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2, 1, 2, 3, 3};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(1, theObject.getAnswer(2, a, b),"Incorrect");
    }

    {
        int aARRAY[] = {1, 3, 2, 2, 6, 6, 4, 4, 7};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2, 1, 4, 5, 4, 4, 7, 7, 6};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(2, theObject.getAnswer(3, a, b),"Incorrect");
    }

    {
        int aARRAY[] = {1, 2, 2, 1, 1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {1, 2, 2, 1, 2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(3, theObject.getAnswer(2, a, b),"Incorrect");
    }

    {
        int aARRAY[] = {6, 15, 29, 28, 7, 13, 13, 23, 28, 13, 30, 27, 14, 4, 14, 19, 27, 20, 20, 19, 10, 15, 7, 7, 19, 29, 4, 24, 10, 23, 30, 6, 24};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {9, 22, 30, 20, 26, 25, 8, 7, 24, 21, 27, 31, 4, 28, 29, 6, 16, 1, 17, 10, 3, 12, 30, 18, 14, 23, 19, 21, 5, 13, 15, 2, 11};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(4, theObject.getAnswer(5, a, b),"Correct");
    }

    {
        int aARRAY[] = {1,1,1,2,1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2,3,1,2,2};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(5, theObject.getAnswer(2, a, b),"Correct");
    }

    {
        int aARRAY[] = {5, 6, 3, 3, 1, 3, 1, 3, 6};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {5, 3, 4, 1, 7, 6, 2, 5, 1};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(6, theObject.getAnswer(3, a, b),"Correct");
    }

    {
        int aARRAY[] = {1, 1, 1, 2, 2, 2, 3, 3, 4};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {2, 2, 3, 3, 4, 5, 5, 7, 5};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(7, theObject.getAnswer(3, a, b),"Incorrect");
    }

    {
        int aARRAY[] = {204, 555, 419, 313, 426, 7, 809, 635, 846, 191, 280, 441, 847, 944, 176, 683, 371, 549, 392, 278, 641, 961, 645, 609, 621, 597, 796, 65, 729, 835, 751, 9, 24, 524, 165, 262, 407, 231, 77, 511, 279, 801, 2, 75, 237, 12, 135, 350, 948, 1020, 638, 509, 658, 271, 427, 866, 849, 852, 684, 788, 912, 320, 79, 818, 308, 648, 386, 653, 47, 393, 917, 959, 197, 177, 596, 914, 840, 588, 286, 911, 800, 334, 153, 780, 383, 403, 494, 931, 622, 45, 504, 591, 894, 905, 440, 305, 379, 28, 424, 1022, 909, 867, 241, 889, 481, 785, 273, 74, 637, 200, 25, 97, 6, 678, 17, 763, 290, 400, 257, 461, 149, 771, 150, 992, 36, 23, 620, 126, 491, 330, 798, 964, 568, 339, 743, 85, 230, 900, 508, 579, 487, 98, 1014, 807, 799, 21, 682, 939, 254, 626, 624, 545, 960, 202, 830, 753, 493, 816, 908, 963, 206, 275, 512, 559, 902, 506, 731, 710, 990, 590, 482, 843, 978, 535, 1023, 132, 433, 428, 328, 501, 581, 878, 244, 274, 317, 594, 62, 585, 375, 755, 53, 1007, 155, 362, 100, 314, 159, 367, 91, 893, 930, 415, 903, 240, 981, 140, 18, 346, 411, 395, 516, 806, 467, 68, 41, 713, 372, 923, 11, 942, 429, 58, 644, 744, 937, 22, 233, 777, 999, 618, 122, 76, 602, 106, 979, 540, 996, 432, 1009, 536, 997, 107, 185, 662, 276, 172, 315, 752, 93, 767, 586, 915, 431, 560, 968, 668, 929, 259, 222, 282, 550, 397, 285, 528, 478, 820, 760, 151, 61, 951, 631, 437, 373, 521, 48, 67, 295, 606, 327, 529, 417, 111, 691, 685, 114, 520, 72, 762, 456, 318, 348, 721, 827, 561, 698, 1005, 1010, 537, 906, 205, 20, 872, 224, 439, 670, 495, 566, 619, 175, 42, 582, 975, 554, 404, 808, 390, 735, 892, 255, 322, 272, 129, 469, 82, 37, 1003, 947, 1011, 309, 130, 13, 634, 144, 572, 715, 46, 357, 995, 164, 89, 484, 1000, 186, 855, 899, 518, 643, 875, 727, 1006, 822, 958, 873, 871, 326, 360, 547, 193, 102, 131, 584, 118, 438, 333, 625, 378, 43, 972, 880, 158, 201, 264, 630, 576, 649, 522, 123, 675, 425, 639, 416, 510, 256, 773, 650, 1018, 861, 887, 54, 388, 557, 722, 347, 283, 234, 733, 896, 312, 577, 523, 589, 712, 858, 459, 718, 232, 688, 270, 267, 805, 33, 869, 565, 418, 615, 455, 719, 895, 983, 335, 714, 604, 689, 527, 227, 174, 901, 366, 147, 336, 332, 627, 63, 745, 410, 613, 221, 355, 742, 865, 374, 734, 934, 757, 558, 764, 775, 99, 941, 759, 19, 70, 874, 485, 16, 632, 924, 553, 188, 886, 971, 389, 289, 697, 538, 56, 38, 784, 127, 80, 611, 768, 986, 564, 170, 125, 182, 976, 552, 138, 229, 916, 281, 116, 15, 748, 488, 10, 8, 841, 882, 716, 349, 462, 636, 814, 468, 361, 642, 652, 546, 323, 27, 595, 700, 163, 897, 956, 692, 211, 681, 88, 341, 672, 499, 422, 101, 704, 542, 475, 195, 319, 57, 699, 725, 452, 502, 774, 833, 693, 345, 883, 207, 216, 498, 1012, 778, 530, 965, 90, 492, 34, 71, 598, 179, 59, 81, 198, 473, 112, 444, 398, 181, 1001, 133, 447, 173, 369, 782, 474, 819, 578, 143, 756, 324, 292, 483, 513, 687, 723, 750, 252, 740, 574, 376, 208, 105, 646, 953, 110, 870, 226, 142, 694, 434, 266, 556, 728, 885, 412, 316, 695, 141, 754, 4, 311, 307, 623, 950, 288, 294, 223, 825, 137, 783, 277, 607, 380, 196, 385, 184, 500, 445, 732, 420, 246, 730, 803, 1013, 797, 890, 881, 531, 448, 945, 616, 1008, 569, 936, 977, 946, 610, 733, 66, 449, 293, 854, 769, 575, 160, 377, 199, 868, 970, 828, 845, 733, 436, 539, 235, 746, 562, 599, 157, 739, 982, 651, 86, 161, 95, 253, 1019, 243, 29, 525, 832, 505, 1004, 194, 405, 477, 162, 453, 709, 214, 640, 300, 605, 823, 864, 458, 472, 40, 705, 985, 647, 171, 391, 115, 708, 952, 409, 789, 370, 824, 442, 251, 954, 368, 676, 663, 32, 910, 203, 514, 702, 401, 888, 435, 148, 250, 657, 399, 306, 26, 245, 503, 733, 507, 50, 673, 213, 465, 677, 55, 517, 519, 928, 980, 1, 268, 791, 219, 891, 904, 659, 49, 660, 94, 168, 414, 117, 356, 121, 96, 358, 337, 476, 907, 629, 617, 533, 850, 87, 249, 932, 792, 450, 862, 302, 92, 842, 109, 532, 225, 287, 674, 993, 236, 423, 136, 451, 238, 489, 766, 31, 83, 879, 51, 724, 413, 815, 884, 146, 787, 583, 967, 1015, 962, 813, 384, 856, 966, 128, 220, 919, 765, 183, 918, 776, 381, 614, 859, 212, 671, 666, 935, 365, 913, 166, 258, 1002, 655, 877, 831, 430, 5, 844, 573, 737, 664, 466, 480, 701, 310, 446, 263, 860, 998, 44, 940, 248, 486, 848, 543, 187, 321, 526, 654, 656, 707, 344, 736, 69, 863, 829, 795, 949, 838, 853, 592, 726, 988, 52, 359, 541, 113, 421, 761, 156, 479, 457, 612, 920, 857, 686, 284, 210, 304, 242, 680, 926, 178, 749, 3, 35, 1017, 747, 955, 812, 969, 471, 209, 601, 343, 974, 103, 720, 793, 876, 587, 340, 265, 758, 991, 628, 973, 706, 215, 325, 363, 351, 269, 826, 921, 134, 669, 933, 78, 301, 661, 925, 696, 571, 534, 989, 239, 667, 790, 169, 608, 839, 217, 108, 580, 497, 60, 460, 331, 394, 567, 548, 39, 741, 338, 804, 770, 189, 603, 470, 14, 786, 353, 406, 851, 593, 943, 298, 382, 352, 291, 794, 811, 84, 190, 690, 64, 261, 228, 984, 738, 544, 781, 247, 354, 154, 898, 810, 396, 515, 139, 703, 600, 260, 463, 563, 836, 711, 329, 218, 837, 299, 938, 124, 152, 927, 821, 717, 443, 180, 303, 817, 120, 1021, 408, 957, 402, 342, 496, 167, 779, 994, 145, 1016, 490, 802, 834, 119, 387, 73, 987, 922, 296, 104, 772, 633, 464, 192, 551, 665, 454, 364, 30, 679, 297};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {715, 134, 689, 769, 798, 153, 461, 65, 273, 397, 911, 857, 758, 730, 888, 853, 800, 778, 64, 510, 336, 340, 176, 925, 649, 93, 393, 88, 618, 59, 356, 557, 212, 419, 718, 252, 582, 372, 286, 962, 581, 378, 326, 404, 152, 178, 315, 938, 61, 338, 856, 537, 766, 172, 899, 521, 214, 1022, 721, 468, 637, 1017, 967, 654, 16, 126, 535, 291, 267, 260, 66, 310, 868, 199, 1002, 487, 254, 567, 357, 865, 669, 127, 24, 426, 926, 312, 736, 242, 329, 339, 248, 163, 805, 723, 499, 821, 399, 48, 1009, 591, 420, 978, 136, 815, 425, 406, 1016, 21, 864, 169, 875, 991, 642, 743, 102, 413, 952, 762, 753, 677, 51, 552, 844, 1, 345, 479, 476, 916, 358, 47, 35, 379, 3, 631, 202, 945, 616, 171, 832, 1021, 306, 283, 513, 764, 268, 1018, 319, 168, 763, 611, 17, 507, 368, 441, 568, 540, 673, 808, 860, 503, 773, 103, 541, 292, 826, 1008, 650, 460, 571, 423, 156, 148, 211, 711, 243, 659, 739, 196, 518, 27, 955, 307, 633, 225, 609, 355, 598, 790, 107, 480, 902, 932, 735, 389, 498, 116, 713, 752, 277, 942, 135, 366, 1012, 272, 584, 684, 780, 239, 119, 180, 437, 161, 912, 678, 852, 251, 886, 855, 837, 427, 200, 434, 477, 761, 39, 539, 1010, 108, 165, 512, 746, 80, 905, 187, 960, 876, 644, 181, 974, 851, 50, 867, 314, 524, 999, 891, 40, 223, 998, 976, 849, 738, 147, 767, 664, 415, 686, 194, 940, 52, 922, 98, 728, 745, 830, 33, 84, 698, 75, 36, 667, 74, 132, 12, 528, 85, 605, 1015, 387, 244, 579, 501, 62, 984, 688, 900, 994, 681, 705, 32, 213, 218, 317, 858, 467, 332, 346, 831, 265, 34, 471, 701, 60, 547, 459, 370, 117, 99, 972, 993, 679, 462, 463, 569, 490, 776, 440, 478, 980, 138, 722, 656, 431, 410, 374, 386, 401, 897, 100, 538, 298, 323, 285, 941, 245, 229, 270, 432, 155, 668, 131, 627, 519, 953, 744, 731, 493, 236, 587, 281, 704, 294, 115, 617, 81, 504, 247, 594, 612, 433, 118, 324, 572, 271, 675, 625, 13, 206, 141, 850, 580, 25, 383, 222, 130, 693, 634, 388, 597, 944, 923, 144, 874, 369, 927, 817, 777, 542, 197, 716, 1006, 599, 646, 219, 464, 634, 841, 819, 804, 380, 683, 506, 23, 770, 452, 11, 10, 835, 929, 87, 365, 877, 295, 347, 741, 42, 146, 322, 884, 494, 895, 546, 333, 919, 621, 422, 544, 149, 221, 697, 957, 533, 725, 641, 342, 86, 192, 305, 576, 63, 290, 812, 786, 416, 367, 643, 511, 671, 947, 920, 435, 299, 619, 787, 526, 205, 352, 215, 38, 982, 558, 58, 190, 924, 691, 258, 729, 647, 908, 371, 903, 818, 188, 31, 363, 327, 297, 232, 20, 917, 624, 408, 799, 276, 289, 589, 22, 750, 760, 275, 184, 124, 935, 779, 623, 759, 651, 803, 954, 882, 771, 570, 834, 1013, 816, 264, 985, 890, 485, 55, 405, 517, 968, 230, 516, 217, 971, 996, 296, 879, 845, 907, 71, 447, 724, 833, 796, 274, 465, 508, 457, 645, 250, 626, 246, 79, 360, 6, 783, 482, 54, 96, 179, 174, 69, 111, 46, 443, 209, 963, 784, 939, 595, 529, 421, 489, 483, 933, 137, 450, 201, 543, 402, 78, 1000, 563, 708, 562, 795, 881, 391, 308, 979, 94, 727, 385, 473, 610, 456, 515, 381, 658, 228, 551, 966, 424, 880, 145, 661, 548, 564, 253, 19, 77, 1001, 414, 417, 227, 824, 685, 351, 73, 4, 396, 887, 596, 703, 220, 737, 751, 839, 775, 436, 682, 470, 620, 348, 585, 702, 583, 469, 862, 173, 514, 956, 765, 635, 989, 847, 241, 140, 811, 570, 288, 359, 375, 364, 820, 234, 101, 565, 843, 235, 1007, 931, 191, 311, 301, 497, 237, 700, 961, 263, 573, 592, 774, 574, 334, 304, 949, 781, 186, 475, 509, 754, 792, 164, 602, 904, 240, 300, 204, 403, 407, 455, 898, 29, 710, 344, 712, 278, 559, 182, 797, 951, 133, 977, 1004, 106, 836, 921, 948, 829, 395, 279, 608, 121, 914, 451, 256, 747, 76, 788, 975, 981, 534, 878, 26, 706, 446, 45, 162, 143, 492, 556, 331, 262, 634, 1005, 603, 491, 150, 714, 934, 520, 112, 672, 120, 160, 448, 226, 937, 500, 622, 590, 125, 854, 350, 791, 1003, 545, 842, 757, 484, 505, 203, 481, 986, 789, 676, 928, 636, 910, 231, 208, 918, 665, 863, 282, 794, 97, 674, 692, 210, 628, 578, 593, 530, 377, 807, 175, 361, 439, 655, 606, 872, 969, 694, 709, 607, 341, 313, 909, 663, 362, 525, 666, 83, 123, 973, 838, 614, 657, 259, 825, 418, 154, 170, 159, 871, 652, 695, 453, 613, 95, 586, 810, 37, 384, 92, 964, 531, 889, 438, 8, 943, 44, 284, 15, 806, 122, 930, 732, 216, 749, 89, 720, 717, 318, 183, 601, 444, 707, 997, 827, 257, 748, 1014, 43, 376, 536, 189, 699, 638, 198, 690, 639, 53, 302, 449, 995, 321, 249, 325, 873, 109, 1019, 782, 894, 400, 600, 207, 632, 555, 802, 630, 105, 915, 553, 495, 892, 67, 936, 1023, 354, 320, 454, 167, 287, 328, 869, 687, 82, 56, 330, 2, 883, 577, 733, 870, 428, 7, 293, 349, 445, 280, 398, 987, 813, 670, 823, 965, 185, 959, 382, 430, 394, 488, 885, 466, 861, 442, 158, 946, 129, 970, 740, 742, 392, 523, 640, 353, 988, 5, 28, 648, 113, 166, 906, 1011, 72, 195, 653, 337, 554, 157, 696, 848, 680, 496, 224, 560, 719, 866, 901, 151, 950, 142, 309, 128, 68, 859, 458, 893, 522, 41, 49, 472, 561, 14, 809, 177, 70, 266, 412, 91, 726, 343, 983, 755, 828, 604, 373, 335, 30, 992, 104, 566, 90, 814, 316, 615, 990, 840, 660, 411, 768, 1020, 9, 474, 114, 550, 958, 303, 846, 269, 502, 756, 193, 390, 57, 238, 486, 409, 527, 772, 662, 549, 233, 429, 255, 18, 139, 261, 110, 785, 822, 588, 801, 734, 629, 896, 532, 913, 575};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(8, theObject.getAnswer(10, a, b),"Incorrect");
    }

    {
        int aARRAY[] = {220, 220, 904, 904, 102, 102, 16, 16, 839, 839, 998, 998, 454, 454, 826, 826, 79, 79, 154, 154, 551, 551, 9, 9, 838, 838, 311, 311, 315, 315, 201, 201, 211, 211, 402, 402, 857, 857, 352, 352, 43, 43, 381, 381, 837, 837, 195, 195, 129, 129, 242, 242, 615, 615, 470, 470, 634, 634, 264, 264, 484, 484, 557, 557, 504, 504, 743, 743, 937, 937, 786, 786, 117, 117, 966, 966, 347, 347, 465, 465, 778, 778, 977, 977, 962, 962, 585, 585, 652, 652, 835, 835, 1008, 1008, 569, 569, 39, 39, 374, 374, 446, 446, 605, 605, 29, 29, 598, 598, 455, 455, 114, 114, 255, 255, 879, 879, 165, 165, 447, 447, 106, 106, 443, 443, 542, 542, 260, 260, 590, 590, 301, 301, 438, 438, 340, 340, 1010, 1010, 423, 423, 350, 350, 287, 287, 302, 302, 692, 692, 172, 172, 740, 740, 630, 630, 214, 214, 698, 698, 645, 645, 961, 961, 607, 607, 925, 925, 358, 358, 981, 981, 183, 183, 66, 66, 55, 55, 1016, 1016, 59, 59, 932, 932, 488, 488, 367, 367, 493, 493, 421, 421, 141, 141, 415, 415, 978, 978, 370, 370, 372, 372, 205, 205, 592, 592, 534, 534, 890, 890, 526, 526, 704, 704, 212, 212, 150, 150, 622, 622, 767, 767, 924, 924, 208, 208, 363, 363, 779, 779, 619, 619, 690, 690, 584, 584, 952, 952, 19, 19, 747, 747, 76, 76, 171, 171, 799, 799, 836, 836, 22, 22, 803, 803, 848, 848, 84, 84, 516, 516, 344, 344, 544, 544, 100, 100, 765, 765, 193, 193, 716, 716, 28, 28, 709, 709, 861, 861, 669, 669, 31, 31, 449, 449, 700, 700, 138, 138, 107, 107, 899, 899, 752, 752, 883, 883, 944, 944, 393, 393, 376, 376, 661, 661, 822, 822, 947, 947, 309, 309, 912, 912, 229, 229, 643, 643, 238, 238, 81, 81, 503, 503, 33, 33, 249, 249, 127, 127, 646, 646, 17, 17, 476, 476, 305, 305, 843, 843, 671, 671, 2, 2, 802, 802, 510, 510, 823, 823, 559, 559, 259, 259, 524, 524, 636, 636, 1018, 1018, 876, 876, 380, 380, 353, 353, 159, 159, 787, 787, 167, 167, 467, 467, 222, 222, 123, 123, 128, 128, 184, 184, 950, 950, 364, 364, 558, 558, 286, 286, 278, 278, 511, 511, 922, 922, 705, 705, 62, 62, 501, 501, 723, 723, 581, 581, 856, 856, 489, 489, 258, 258, 518, 518, 75, 75, 332, 332, 384, 384, 95, 95, 294, 294, 960, 960, 604, 604, 48, 48, 61, 61, 734, 734, 614, 614, 729, 729, 496, 496, 519, 519, 563, 563, 600, 600, 116, 116, 67, 67, 582, 582, 703, 703, 312, 312, 859, 859, 810, 810, 181, 181, 122, 122, 699, 699, 120, 120, 914, 914, 965, 965, 399, 399, 580, 580, 668, 668, 959, 959, 745, 745, 994, 994, 1014, 1014, 86, 86, 251, 251, 547, 547, 50, 50, 130, 130, 245, 245, 884, 884, 354, 354, 60, 60, 554, 554, 520, 520, 942, 942, 814, 814, 811, 811, 145, 145, 609, 609, 555, 555, 478, 478, 1019, 1019, 160, 160, 285, 285, 1009, 1009, 35, 35, 915, 915, 834, 834, 396, 396, 599, 599, 675, 675, 539, 539, 677, 677, 26, 26, 687, 687, 853, 853, 241, 241, 98, 98, 224, 224, 963, 963, 610, 610, 388, 388, 528, 528, 586, 586, 357, 357, 642, 642, 549, 549, 983, 983, 398, 398, 237, 237, 284, 284, 338, 338, 174, 174, 307, 307, 94, 94, 663, 663, 531, 531, 1007, 1007, 442, 442, 411, 411, 775, 775, 458, 458, 386, 386, 252, 252, 842, 842, 292, 292, 44, 44, 896, 896, 660, 660, 289, 289, 759, 759, 83, 83, 325, 325, 612, 612, 597, 597, 845, 845, 12, 12, 712, 712, 696, 696, 378, 378, 277, 277, 38, 38, 124, 124, 749, 749, 770, 770, 327, 327, 771, 771, 682, 682, 596, 596, 995, 995, 427, 427, 681, 681, 377, 377, 948, 948, 266, 266, 659, 659, 841, 841, 741, 741, 365, 365, 424, 424, 109, 109, 186, 186, 788, 788, 46, 46, 532, 532, 613, 613, 371, 371, 288, 288, 830, 830, 575, 575, 746, 746, 1023, 1023, 409, 409, 105, 105, 507, 507, 564, 564, 936, 936, 88, 88, 953, 953, 833, 833, 827, 827, 32, 32, 907, 907, 418, 418, 134, 134, 462, 462, 540, 540, 468, 468, 215, 215, 748, 748, 368, 368, 513, 513, 982, 982, 403, 403, 262, 262, 945, 945, 232, 232, 206, 206, 781, 781, 881, 881, 546, 546, 809, 809, 139, 139, 373, 373, 589, 589, 806, 806, 588, 588, 517, 517, 964, 964, 628, 628, 568, 568, 541, 541, 560, 560, 225, 225, 218, 218, 713, 713, 989, 989, 414, 414, 545, 545, 917, 917, 303, 303, 691, 691, 657, 657, 794, 794, 349, 349, 984, 984, 758, 758, 672, 672, 293, 293, 512, 512, 63, 63, 463, 463, 946, 946, 753, 753, 620, 620, 444, 444, 996, 996, 24, 24, 36, 36, 654, 654, 271, 271, 684, 684, 858, 858, 567, 567, 397, 397, 820, 820, 23, 23, 270, 270, 275, 275, 239, 239, 261, 261, 717, 717, 151, 151, 149, 149, 893, 893, 113, 113, 943, 943, 601, 601, 851, 851, 738, 738, 321, 321, 361, 361, 210, 210, 419, 419, 556, 556, 1017, 1017, 162, 162, 133, 133, 182, 182, 1015, 1015, 639, 639, 369, 369, 776, 776, 934, 934, 144, 144, 572, 572, 400, 400, 189, 189, 790, 790, 310, 310, 457, 457, 345, 345, 807, 807, 621, 621, 306, 306, 308, 308, 736, 736, 999, 999, 888, 888, 295, 295, 1000, 1000, 407, 407, 346, 346, 792, 792, 505, 505, 191, 191, 852, 852, 913, 913, 773, 773, 68, 68, 429, 429, 230, 230, 854, 854, 432, 432, 719, 719, 801, 801, 471, 471, 706, 706, 13, 13, 702, 702, 99, 99, 85, 85, 626, 626, 21, 21, 606, 606, 334, 334, 929, 929, 710, 710, 246, 246, 64, 64, 453, 453, 550, 550, 739, 739, 137, 137, 451, 451, 997, 997, 115, 115, 440, 440, 147, 147, 972, 972, 247, 247, 185, 185, 720, 720, 1, 1, 1};
        vector <int> a( aARRAY, aARRAY+ARRSIZE(aARRAY) );
        int bARRAY[] = {904, 102, 16, 839, 998, 454, 826, 79, 154, 551, 9, 838, 311, 315, 201, 211, 402, 857, 352, 43, 381, 837, 195, 129, 242, 615, 470, 634, 264, 484, 557, 504, 743, 937, 786, 117, 966, 347, 465, 778, 977, 962, 585, 652, 835, 1008, 569, 39, 374, 446, 605, 29, 598, 455, 114, 255, 879, 165, 447, 106, 443, 542, 260, 590, 301, 438, 340, 1010, 423, 350, 287, 302, 692, 172, 740, 630, 214, 698, 645, 961, 607, 925, 358, 981, 183, 66, 55, 1016, 59, 932, 488, 367, 493, 421, 141, 415, 978, 370, 372, 205, 592, 534, 890, 526, 704, 212, 150, 622, 767, 924, 208, 363, 779, 619, 690, 584, 952, 19, 747, 76, 171, 799, 836, 22, 803, 848, 84, 516, 344, 544, 100, 765, 193, 716, 28, 709, 861, 669, 31, 449, 700, 138, 107, 899, 752, 883, 944, 393, 376, 661, 822, 947, 309, 912, 229, 643, 238, 81, 503, 33, 249, 127, 646, 17, 476, 305, 843, 671, 2, 802, 510, 823, 559, 259, 524, 636, 1018, 876, 380, 353, 159, 787, 167, 467, 222, 123, 128, 184, 950, 364, 558, 286, 278, 511, 922, 705, 62, 501, 723, 581, 856, 489, 258, 518, 75, 332, 384, 95, 294, 960, 604, 48, 61, 734, 614, 729, 496, 519, 563, 600, 116, 67, 582, 703, 312, 859, 810, 181, 122, 699, 120, 914, 965, 399, 580, 668, 959, 745, 994, 1014, 86, 251, 547, 50, 130, 245, 884, 354, 60, 554, 520, 942, 814, 811, 145, 609, 555, 478, 1019, 160, 285, 1009, 35, 915, 834, 396, 599, 675, 539, 677, 26, 687, 853, 241, 98, 224, 963, 610, 388, 528, 586, 357, 642, 549, 983, 398, 237, 284, 338, 174, 307, 94, 663, 531, 1007, 442, 411, 775, 458, 386, 252, 842, 292, 44, 896, 660, 289, 759, 83, 325, 612, 597, 845, 12, 712, 696, 378, 277, 38, 124, 749, 770, 327, 771, 682, 596, 995, 427, 681, 377, 948, 266, 659, 841, 741, 365, 424, 109, 186, 788, 46, 532, 613, 371, 288, 830, 575, 746, 1023, 409, 105, 507, 564, 936, 88, 953, 833, 827, 32, 907, 418, 134, 462, 540, 468, 215, 748, 368, 513, 982, 403, 262, 945, 232, 206, 781, 881, 546, 809, 139, 373, 589, 806, 588, 517, 964, 628, 568, 541, 560, 225, 218, 713, 989, 414, 545, 917, 303, 691, 657, 794, 349, 984, 758, 672, 293, 512, 63, 463, 946, 753, 620, 444, 996, 24, 36, 654, 271, 684, 858, 567, 397, 820, 23, 270, 275, 239, 261, 717, 151, 149, 893, 113, 943, 601, 851, 738, 321, 361, 210, 419, 556, 1017, 162, 133, 182, 1015, 639, 369, 776, 934, 144, 572, 400, 189, 790, 310, 457, 345, 807, 621, 306, 308, 736, 999, 888, 295, 1000, 407, 346, 792, 505, 191, 852, 913, 773, 68, 429, 230, 854, 432, 719, 801, 471, 706, 13, 702, 99, 85, 626, 21, 606, 334, 929, 710, 246, 64, 453, 550, 739, 137, 451, 997, 115, 440, 147, 972, 247, 185, 720, 158, 808, 406, 676, 813, 49, 939, 1001, 404, 143, 821, 179, 637, 908, 603, 970, 227, 37, 986, 537, 623, 624, 573, 40, 648, 291, 825, 895, 330, 862, 313, 735, 805, 855, 456, 324, 257, 664, 632, 724, 968, 426, 629, 387, 104, 494, 234, 990, 5, 1013, 553, 250, 1004, 656, 869, 757, 764, 1006, 392, 135, 47, 15, 831, 514, 751, 283, 223, 949, 761, 331, 951, 42, 483, 509, 536, 213, 866, 431, 732, 783, 649, 436, 594, 1020, 631, 341, 647, 11, 548, 530, 985, 979, 57, 316, 718, 1003, 919, 337, 992, 469, 356, 6, 938, 490, 54, 336, 576, 931, 527, 898, 221, 157, 375, 941, 268, 816, 355, 180, 231, 265, 299, 824, 479, 163, 323, 685, 570, 474, 319, 956, 168, 725, 874, 815, 461, 847, 608, 1012, 170, 362, 832, 72, 971, 595, 491, 485, 976, 437, 466, 903, 173, 920, 74, 900, 318, 322, 865, 666, 689, 905, 868, 894, 65, 974, 487, 935, 290, 1022, 56, 940, 425, 280, 27, 420, 481, 812, 533, 108, 263, 726, 683, 413, 428, 818, 797, 772, 993, 566, 618, 714, 728, 933, 737, 188, 401, 3, 161, 701, 864, 916, 51, 730, 192, 164, 756, 492, 389, 819, 89, 780, 552, 34, 774, 670, 795, 243, 611, 777, 744, 439, 282, 877, 71, 880, 175, 475, 422, 279, 433, 125, 782, 25, 328, 708, 791, 870, 958, 793, 77, 10, 579, 789, 339, 7, 140, 784, 885, 348, 673, 667, 574, 499, 91, 304, 902, 240, 253, 405, 281, 187, 686, 360, 711, 486, 731, 766, 269, 274, 329, 873, 571, 132, 644, 522, 910, 680, 750, 103, 627, 1021, 111, 987, 521, 497, 525, 236, 317, 448, 20, 529, 297, 653, 674, 897, 923, 906, 954, 565, 146, 256, 52, 502, 209, 928, 119, 196, 382, 1005, 918, 473, 233, 707, 207, 235, 391, 911, 878, 314, 112, 506, 333, 156, 678, 640, 267, 342, 901, 500, 980, 872, 219, 87, 41, 53, 416, 4, 176, 633, 785, 887, 216, 849, 169, 121, 148, 198, 379, 844, 394, 561, 662, 796, 679, 410, 577, 651, 804, 320, 228, 754, 635, 69, 190, 97, 742, 200, 562, 199, 273, 248, 695, 988, 203, 412, 957, 828, 90, 452, 973, 194, 126, 495, 272, 1, 991, 166, 118, 80, 197, 755, 482, 395, 727, 366, 975, 78, 276, 587, 593, 226, 658, 886, 889, 45, 464, 335, 926, 817, 70, 131, 875, 82, 93, 110, 693, 155, 688, 602, 863, 955, 871, 498, 694, 343, 254, 472, 434, 655, 96, 385, 715, 459, 891, 326, 178, 829, 1011, 617, 846, 417, 441, 583, 625, 882, 73, 244, 508, 14, 578, 768, 969, 722, 445, 58, 92, 543, 591, 8, 177, 351, 650, 850, 136, 430, 204, 638, 408, 142, 762, 921, 460, 18, 390, 296, 477, 298, 515, 909, 383, 300, 202, 760, 359, 538, 153, 927, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 930, 2, 3, 4};
        vector <int> b( bARRAY, bARRAY+ARRSIZE(bARRAY) );
        TheKingsRoadsDiv1 theObject;
        eq(9, theObject.getAnswer(10, a, b),"Incorrect");
    }

    return 0;
}
// END CUT HERE
