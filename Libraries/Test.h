#ifndef TOPCODER_TEST
#define TOPCODER_TEST

#include <boost/test/unit_test.hpp>

namespace Libraries { namespace Test {

    typedef boost::test_tools::predicate_result Predicate;

    struct TestIssues
    {
      public:
        TestIssues()
          : predicate(true)
        {
        }

        Predicate predicate;
    };

    template <typename T> TestIssues& operator<<(TestIssues& testIssues_, const T& value_)
    {
        testIssues_.predicate = false;
        testIssues_.predicate.message() << value_;
        return testIssues_;
    }

}
}

#endif
