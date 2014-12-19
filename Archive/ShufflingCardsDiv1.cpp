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

class ShufflingCardsDiv1
{
  public:
    int n;
    vi  m;
    const int max = INT_MAX;

    int f(int x)
    {
        if (x == n) return 0;

        const int y = n - x;

        const int x1 = min((n + 1) / 2,     x);
        const int x2 = min(      n / 2, n - x);

        const int y1 = min((n + 1) / 2,     y);
        const int y2 = min(      n / 2, n - y);

        const int xh = x1 + x2;
        const int xl = n - (y1 + y2);

        if (-1 != m[x]) return m[x];

        int ret = max;
        m[x] = max;
        for (int xi = xl; xi <= xh; ++xi)
            ret = min(ret, f(xi));
        if (max == ret) return max;
        m[x] = ret + 1;
        // cerr << "f(" << x << ") = " << m[x] << endl;
        return m[x];
    }
    int shuffle(vector <int> p)
    {
        n = p.size() / 2;
        m = vi(n, -1);
        bool sorted = true;
        for (int i = 0; i < 2 * n; ++i) {
            sorted &= p[i] == i + 1;
        }
        if (sorted) return 0;
        int x = 0;
        for (int i = 0; i < n; ++i) {
            x += p[2 * i] <=  n;
        }
        return 1 + f(x);
    }
};

// BEGIN CUT HERE
int main( int argc, char* argv[] )
{
    {
        int permutationARRAY[] = {1,2,3,4};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(0, theObject.shuffle(permutation),0);
    }
    {
        int permutationARRAY[] = {1,4,3,2};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(1, theObject.shuffle(permutation),2);
    }
    {
        int permutationARRAY[] = {6,3,5,2,4,1};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(2, theObject.shuffle(permutation),4);
    }
    {
        int permutationARRAY[] = {8,5,4,9,1,7,6,10,3,2};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(3, theObject.shuffle(permutation),2);
    }
    {
        int permutationARRAY[] = {9,1,7,2,10,3,6,4,8,5};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(4, theObject.shuffle(permutation),4);
    }
    {
        int permutationARRAY[] = {1, 2, 5, 3, 7, 4, 8, 10, 6, 9};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(5, theObject.shuffle(permutation),3);
    }
    {
        int permutationARRAY[] = {179, 567, 119, 485, 299, 535, 146, 752, 205, 698, 123, 651, 349, 823, 41, 786, 247, 475, 400, 798, 390, 542, 79, 576, 245, 657, 240, 477, 242, 432, 151, 644, 281, 769, 88, 512, 9, 450, 319, 809, 8, 460, 236, 753, 129, 745, 73, 610, 152, 685, 147, 517, 124, 750, 368, 720, 221, 588, 303, 479, 10, 442, 309, 614, 216, 488, 411, 808, 7, 523, 367, 428, 248, 817, 62, 725, 91, 629, 60, 762, 392, 500, 369, 422, 382, 486, 210, 819, 212, 620, 56, 744, 110, 759, 193, 820, 320, 464, 84, 483, 260, 470, 82, 764, 375, 815, 406, 701, 157, 441, 377, 502, 345, 622, 99, 604, 118, 458, 264, 520, 101, 524, 5, 573, 50, 615, 158, 549, 74, 444, 203, 739, 58, 647, 97, 478, 106, 807, 77, 564, 191, 551, 145, 438, 304, 445, 387, 765, 59, 459, 257, 507, 312, 579, 208, 598, 353, 499, 354, 522, 199, 586, 20, 557, 43, 684, 96, 688, 115, 665, 332, 803, 335, 538, 321, 527, 113, 616, 252, 718, 330, 481, 384, 484, 317, 793, 220, 756, 296, 525, 262, 554, 126, 673, 202, 758, 185, 528, 265, 504, 356, 590, 316, 667, 133, 476, 109, 779, 19, 501, 401, 491, 33, 634, 37, 467, 57, 426, 292, 627, 258, 519, 295, 565, 181, 733, 40, 696, 336, 580, 244, 824, 171, 568, 107, 671, 329, 795, 3, 637, 1, 716, 188, 709, 215, 640, 197, 650, 409, 746, 63, 490, 386, 609, 372, 774, 241, 738, 187, 466, 194, 510, 267, 789, 34, 778, 105, 465, 31, 468, 224, 563, 313, 642, 404, 741, 120, 462, 81, 730, 103, 754, 223, 571, 288, 536, 251, 556, 69, 482, 298, 766, 104, 771, 311, 611, 128, 506, 165, 695, 49, 414, 27, 742, 388, 552, 249, 543, 314, 448, 176, 694, 381, 677, 4, 413, 6, 509, 66, 632, 229, 605, 92, 562, 134, 608, 55, 689, 277, 589, 155, 780, 339, 451, 239, 461, 337, 755, 254, 633, 228, 675, 211, 814, 201, 788, 300, 537, 238, 679, 227, 649, 273, 544, 234, 572, 196, 669, 246, 760, 102, 618, 138, 643, 389, 592, 340, 453, 168, 787, 279, 496, 131, 812, 22, 802, 100, 692, 378, 656, 282, 641, 156, 785, 204, 816, 261, 583, 182, 747, 278, 505, 361, 648, 183, 569, 342, 704, 140, 594, 344, 480, 137, 561, 127, 724, 13, 811, 45, 596, 159, 804, 366, 597, 11, 800, 125, 683, 175, 435, 301, 595, 206, 430, 178, 447, 207, 521, 190, 775, 263, 497, 130, 418, 209, 639, 15, 621, 371, 511, 291, 797, 51, 761, 70, 676, 393, 700, 189, 727, 285, 516, 44, 693, 174, 587, 166, 546, 78, 645, 362, 799, 357, 767, 396, 526, 38, 717, 21, 599, 359, 822, 95, 772, 222, 631, 28, 636, 343, 777, 230, 602, 395, 452, 235, 680, 36, 473, 338, 581, 14, 735, 305, 726, 23, 570, 385, 550, 86, 431, 274, 690, 64, 821, 122, 711, 214, 606, 53, 732, 318, 472, 373, 541, 380, 612, 192, 416, 35, 714, 376, 530, 26, 584, 412, 574, 308, 686, 348, 558, 85, 492, 29, 463, 243, 559, 30, 801, 195, 670, 112, 672, 325, 702, 307, 734, 144, 601, 407, 545, 324, 630, 184, 721, 164, 697, 253, 662, 347, 540, 280, 660, 48, 625, 76, 723, 170, 429, 32, 791, 333, 661, 163, 534, 341, 434, 80, 495, 132, 446, 218, 655, 276, 449, 233, 663, 25, 749, 346, 668, 173, 728, 108, 593, 121, 471, 294, 575, 358, 706, 383, 743, 167, 813, 177, 705, 270, 703, 61, 427, 403, 531, 364, 628, 302, 585, 370, 810, 47, 578, 259, 498, 363, 607, 161, 439, 402, 456, 232, 419, 186, 433, 52, 617, 162, 654, 98, 600, 297, 768, 255, 638, 410, 457, 350, 751, 286, 773, 148, 792, 75, 646, 2, 420, 322, 712, 54, 529, 334, 566, 24, 678, 331, 805, 67, 659, 293, 666, 89, 794, 150, 731, 399, 489, 198, 729, 323, 763, 226, 437, 136, 494, 172, 710, 310, 806, 114, 708, 250, 635, 17, 582, 143, 784, 374, 423, 352, 474, 398, 514, 351, 577, 328, 722, 16, 782, 287, 487, 87, 415, 269, 503, 154, 455, 256, 440, 142, 421, 284, 796, 12, 736, 68, 533, 141, 603, 93, 560, 200, 707, 405, 719, 94, 699, 65, 591, 275, 513, 391, 425, 283, 757, 327, 626, 213, 539, 169, 553, 139, 781, 272, 508, 326, 737, 266, 555, 355, 547, 153, 424, 315, 783, 268, 715, 39, 687, 180, 681, 117, 674, 394, 518, 289, 652, 237, 548, 46, 653, 225, 623, 71, 740, 217, 713, 116, 619, 408, 682, 379, 613, 72, 748, 83, 664, 397, 493, 18, 515, 290, 776, 42, 532, 271, 454, 365, 818, 90, 770, 306, 624, 231, 790, 160, 691, 135, 436, 219, 469, 360, 658, 149, 417, 111, 443};
        vector <int> permutation( permutationARRAY, permutationARRAY+ARRSIZE(permutationARRAY) );
        ShufflingCardsDiv1 theObject;
        eq(6, theObject.shuffle(permutation),1);
    }

    return 0;
}
// END CUT HERE
