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

        Count      count(Index index_                ) const;
        Count rangeCount(Index indexA_, Index indexB_) const;

      private:
        void         doAdd(Index index_, Count value_);
        Count   singleCount(Index index_) const;
        Count fromLeftCount(Index index_) const;
        std::vector<Index> _vector;
    };

namespace {

    Bit::Index toZeroBased(Bit::Index index_)
    {
        return index_ - 1;
    }

    Bit::Index toOneBased(Bit::Index index_)
    {
        return index_ + 1;
    }

}

    Bit::Bit(Index N)
        : _vector(N)
    {
    }

    void Bit::add(Index index_, Count value_)
    {
        doAdd(toOneBased(index_), value_);
    }

    Bit::Count Bit::count(Index index_) const
    {
        return singleCount(toOneBased(index_));
    }

    Bit::Count Bit::rangeCount(Index indexA_, Index indexB_) const
    {
        Count count = 0 < indexA_ ? fromLeftCount(toOneBased(indexA_ - 1)) : 0;
        return fromLeftCount(toOneBased(indexB_)) - count;
    }

    void Bit::doAdd(Index index_, Count value_)
    {
        while (toZeroBased(index_) < _vector.size())
        {
            _vector[toZeroBased(index_)] += value_;
            index_                       += (index_ & -index_);
        }
    }

    Bit::Count Bit::singleCount(Index index_) const
    {
        Count sum = _vector[toZeroBased(index_)];
        if (1 < index_) {
            const Index z = index_ - (index_ & -index_);
            index_--;
            while (z != index_) {
                sum    -= _vector[toZeroBased(index_)];
                index_ -= (index_ & -index_);
            }
        }
        return sum;
    }

    Bit::Count Bit::fromLeftCount(Index index_) const
    {
        Count sum = 0;
        while (0 < index_)
        {
            sum    += _vector[toZeroBased(index_)];
            index_ -= (index_ & -index_);
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
                std::size_t vectorSum = countRange(vector_, i, j);
                std::size_t bitSum = bit_.rangeCount(i, j);
                if (vectorSum != bitSum)
                {
                    issues << "Range count different for [" << i << ", " << j << "], vector = " << vectorSum << ", BIT = " << bitSum << "\n";
                }
            }
        }
        for (std::size_t i = 0; i < N; ++i)
        {
            Bit::Count bitCount = bit_.count(i);
            if (vector_[i] != bitCount)
            {
                issues << "Count different for [" << i << "], vector = " << vector_[i] << ", BIT = " << bitCount << "\n";
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

        index = 3;
        count = 2;
        bit.add(index, count);
        v[index] += count;
        BOOST_CHECK(checkBitRange(v, bit));

        index = 3;
        count = 2;
        bit.add(index, count);
        v[index] += count;
        BOOST_CHECK(checkBitRange(v, bit));

        index = 9;
        count = 5;
        bit.add(index, count);
        v[index] += count;
        BOOST_CHECK(checkBitRange(v, bit));

        index = 0;
        count = 10;
        bit.add(index, count);
        v[index] += count;
        BOOST_CHECK(checkBitRange(v, bit));

        index = 5;
        count = 1000;
        bit.add(index, count);
        v[index] += count;
        BOOST_CHECK(checkBitRange(v, bit));
    }

    BOOST_AUTO_TEST_CASE(Large)
    {
        std::size_t testSize = 100;
        std::size_t mul = 123;
        Bit bit(testSize);
        std::vector<std::size_t> v(testSize);
        for (std::size_t i = 1; i < 10 * testSize; ++i)
        {
            std::size_t index = (i * mul) % testSize;
            std::size_t count = i;
            bit.add(index, count);
            v[index] += count;
            BOOST_CHECK(checkBitRange(v, bit));
        }
    }

BOOST_AUTO_TEST_SUITE_END()

}
}
