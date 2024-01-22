#include <stdexcept>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <gmpxx.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Haven't quite figured out how malloc/calloc limits works under the hood yet
// e.g., apparently SIZE_MAX should work in theory but doesn't, neither does PTRDIFF_MAX...
// So just going with UINT_MAX for page_size
// NOTE: malloc will break depending on how many pages we need
class BMPZMAP
{
private:
    mpz_class size;
    size_t page_size = UINT_MAX;
    size_t max_pages = SIZE_MAX;

    bool **page_array;
    size_t n_pages;

public:
    BMPZMAP(mpz_class limit)
    {
        if (limit <= 0)
        {
            throw std::invalid_argument("Limit must be greater than zero");
        }

        size = limit;
        mpz_class pages = 1 + (limit / page_size);

        if (pages > max_pages)
        {
            throw std::invalid_argument("Number of pages cannot exceed SIZE_MAX");
        }

        n_pages = pages.get_ui();

        page_array = (bool **)malloc(sizeof(bool *) * n_pages);

        if (page_array == NULL)
        {
            throw std::runtime_error("Failed to create page array for BMPZMAP");
        }

        mpz_class total_limit = limit;
        for (size_t i = 0; total_limit > 0 && i < n_pages; i++)
        {
            size_t max_page_size = page_size > total_limit ? total_limit.get_ui() : page_size;

            bool *page = (bool *)calloc(max_page_size, sizeof(bool));

            if (page == NULL)
            {
                throw std::runtime_error("Failed to create page for BMPZMAP page array");
            }

            page_array[i] = page;

            total_limit -= max_page_size;
        }
    }

    void set_from_i(mpz_class i, bool value)
    {
        if (i < 0 || i > size)
        {
            throw std::invalid_argument("Index out of range, cannot exceed size");
        }

        mpz_class page = i / page_size;
        mpz_class index = i - (page * page_size);

        size_t page_t = page.get_ui();
        size_t index_t = index.get_ui();

        page_array[page_t][index_t] = value;
    }

    bool get_from_i(mpz_class i)
    {
        if (i < 0 || i > size)
        {
            throw std::invalid_argument("Index out of range, cannot exceed size");
        }

        mpz_class page = i / page_size;
        mpz_class index = i - (page * page_size);

        size_t page_t = page.get_ui();
        size_t index_t = index.get_ui();

        return page_array[page_t][index_t];
    }

    mpz_class get_size()
    {
        return size;
    }

    ~BMPZMAP()
    {
        for (size_t i = 0; i < n_pages; i++)
        {
            free(page_array[i]);
        }
        free(page_array);
        page_array = NULL;
    }
};

// Tweaked implementation of
// https://www.geeksforgeeks.org/sieve-of-atkin/
// https://github.com/mccricardo/sieve_of_atkin/blob/master/sieve_of_atkin.py#L31
vector<mpz_class> sieveOfAtkin(BMPZMAP &map, mpz_class limit)
{
    vector<mpz_class> primes;

    mpz_class testingLimit;
    mpz_class testingLimitRem;
    mpz_sqrtrem(testingLimit.get_mpz_t(), testingLimitRem.get_mpz_t(), limit.get_mpz_t());

    map.set_from_i(2, true);
    map.set_from_i(3, true);

    for (mpz_class x = 0; x < testingLimit; x++)
    {
        for (mpz_class y = 0; y < testingLimit; y++)
        {
            mpz_class n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
            {
                map.set_from_i(n, !map.get_from_i(n));
            }

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
            {
                map.set_from_i(n, !map.get_from_i(n));
            }

            n = (3 * x * x) - (y * y);
            if (n <= limit && x > y && n % 12 == 11)
            {
                map.set_from_i(n, !map.get_from_i(n));
            }
        }
    }

    for (mpz_class i = 5; i < testingLimit; i++) {
        if (map.get_from_i(i)) {
            mpz_class k = i * i;
            for (mpz_class j = k; j < limit; j += k) {
                map.set_from_i(j, false);
            }
        }
    }

    for (mpz_class i = 2; i < map.get_size(); i++) {
        if (map.get_from_i(i)) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main(void)
{
    mpz_class limit;
    mpz_pow_ui(limit.get_mpz_t(), ((mpz_class)2).get_mpz_t(), 10);

    BMPZMAP map(limit);

    cout << "Calculating primes up to " << limit << endl;

    vector<mpz_class> primes = sieveOfAtkin(map, limit);

    cout << "Got " << primes.size() << " prime numbers" << endl;

    // for (mpz_class &prime : primes)
    // {
    //     cout << prime << endl;
    // }

    return 0;
}
