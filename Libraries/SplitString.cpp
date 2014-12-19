#define BOOST_TEST_MODULE String

#include "Test.h"

#include <string>
#include <sstream>
#include <vector>

#include <boost/test/unit_test.hpp>

namespace Libraries { namespace String {

// BEGIN CUT HERE

    std::vector<std::string> split(const std::string& s_, char delim_ = ' ')
    {
        std::stringstream ss(s_);
        std::vector<std::string> elems;
        std::string item;
        while (std::getline(ss, item, delim_))
        {
            elems.push_back(item);
        }
        return elems;
    }

// END CUT HERE

    BOOST_AUTO_TEST_SUITE(StringTest)

    BOOST_AUTO_TEST_CASE(BasicDefault)
    {
        const std::vector<std::string> vs = split(std::string("a b c d e"));
        BOOST_CHECK(vs[0] == std::string("a"));
        BOOST_CHECK(vs[1] == std::string("b"));
        BOOST_CHECK(vs[2] == std::string("c"));
        BOOST_CHECK(vs[3] == std::string("d"));
        BOOST_CHECK(vs[4] == std::string("e"));
    }

    BOOST_AUTO_TEST_CASE(BasicColon)
    {
        const std::vector<std::string> vs = split(std::string("a:b:c:d:e"), ':');
        BOOST_CHECK(vs[0] == std::string("a"));
        BOOST_CHECK(vs[1] == std::string("b"));
        BOOST_CHECK(vs[2] == std::string("c"));
        BOOST_CHECK(vs[3] == std::string("d"));
        BOOST_CHECK(vs[4] == std::string("e"));
    }

    BOOST_AUTO_TEST_SUITE_END()

}
}
