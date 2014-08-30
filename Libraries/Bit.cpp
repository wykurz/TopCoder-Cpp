#define BOOST_TEST_MODULE Bit

#include "Test.h"

#include <cstdint>
#include <vector>

#include <boost/test/unit_test.hpp>

namespace Libraries { namespace Bit {

    class Bit
    {
      public:
        typedef std::size_t Index;
        typedef std::size_t Count;

        Bit(Index N);
        void add(Index index_, Count value_);
        Count rangeCount(Index indexA_, Index indexB_) const;

      private:
        Count leftCount(Index index_) const;
        std::vector<Index> _vector;
    };

    Bit::Bit(Index N)
        : _vector(N)
    {
    }

    void Bit::add(Index index_, Count value_)
    {
        while (index_ < _vector.size())
        {
            _vector[index_] += value_;
            index_ += (index_ & -index_);
        }
    }

    Bit::Count Bit::rangeCount(Index indexA_, Index indexB_) const
    {
        Count leftSum = 0 < indexA_ ? leftCount(indexA_ - 1) : 0;
        return leftCount(indexB_) - leftSum;
    }

    Bit::Count Bit::leftCount(Index index_) const
    {
        Count sum = _vector[index_];
        if (0 < index_)
        {
            Index z = index_ - (index_ & -index_);
            --index_;
            while (index_ != z)
            {
                sum -= _vector[index_];
                index_ -= (index_ & -index_);
            }
        }
        return sum;
    }

    BOOST_AUTO_TEST_SUITE(BitTest)

    std::size_t countRange(std::vector<std::size_t> vector_, std::size_t indexA_, std::size_t indexB_)
    {
        std::size_t sum = 0;
        for (std::size_t i = indexA_; i <= indexB_; ++i)
        {
            sum += vector_[i];
        }
        return sum;
    }

    Test::Predicate checkBitRange(const std::vector<std::size_t>& vector_, const Bit& bit_)
    {
        Test::TestIssues issues;
        std::size_t N = vector_.size();
        for (std::size_t i = 0; i < N; ++i)
        {
            for (std::size_t j = i; j < N; ++j)
            {
                std::size_t vectorSum = 0;
                for (std::size_t k = i; k <= j; ++k)
                {
                    vectorSum += vector_[k];
                }
                std::size_t bitSum = bit_.rangeCount(i, j);
                if (vectorSum != bitSum)
                {
                    issues << "Range count different for [" << i << ", " << j << "], vector = " << vectorSum << ", BIT = " << bitSum << "\n";
                }
            }
        }
        return issues.predicate;
    }

    BOOST_AUTO_TEST_CASE(Small)
    {
        std::size_t testSize = 10;
        Bit bit(testSize);
        std::vector<std::size_t> v(testSize);
        std::size_t index, count;

        index = 5;
        count = 1;
        bit.add(index, count);
        v[index] += count;

        BOOST_CHECK(checkBitRange(v, bit));
    }

    BOOST_AUTO_TEST_CASE(Large)
    {
        std::size_t testSize = 1000;
        std::size_t mul = 123;
        Bit bit(testSize);
        std::vector<std::size_t> v(testSize);
        for (std::size_t i = 1; i < 100 * testSize; ++i)
        {
            std::size_t indexA = (i * mul) % testSize;
            std::size_t indexB = std::min((i + 2 * i), testSize - 1);
            std::size_t count = i;
            bit.add(indexA, count);
            v[indexA] += count;
            BOOST_CHECK_EQUAL(bit.rangeCount(indexA, indexB), countRange(v, indexA, indexB));
        }
    }

BOOST_AUTO_TEST_SUITE_END()

}
}
