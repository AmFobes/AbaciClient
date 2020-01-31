#pragma once

#include <thread>
#include <vector>
#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <cstring> //memst
#ifndef WIN32
#define _aligned_malloc(size,alignment) aligned_alloc(alignment,size)
#define _aligned_free(ptr) free(ptr)
#endif

namespace AbaciHelpers
{
	/*
	 *
	 *									Trial division prime class
	 * The method of finding prime numbers for this class is called trial division
	 * A prime number does not have a factor but itself and 1 so we do
	 * f % 2
	 * f % 3
	 * f % 4 etc
	 *
	 *									__m256d
	 * The type __m256d is just an array of doubles aligned by 32 bits
	 * Why I used this type is due to the fact that processors are able to
	 * do math on 4 numbers at a time using vectorized operations.
	 * I can either
	 * 1. Rely on the compiler to vectorize my subroutine (The chances of this are very low)
	 * 2. Create an external assembly function to call
	 * 3. Use the intrinsic functions provided by intel
	 *
	 * I chose option 3 because the compiler can actually optimize the intrinsic functions
	 * When writing assembly (and inline assembly) the compiler does not change it at all,
	 * any inefficient practices in my assembly will effect the release version of the library 
	 *
	 *									_aligned_malloc
	 * It's usually stated that when you need to allocate memory in C++, _use_ the keyword 'new'
	 * and that C style allocations is _bad_. In this case I use _aligned_malloc because I need to
	 * There is no cross-platform implementation of an aligned new.
	 *
	 *									Alignment (False sharing or Cache Line Bouncing)
	 * When creating a multi threaded application there are problems where when two threads share the same
	 * part of CPU cache, it'll slow down the process because no matter what, the CPU re-fetches the data from
	 * memory. I avoid this by aligning my arrays by 64 bits (The size of each cache line). This ensures that
	 * the CPU does not have to re-fetch the cache and that each thread stays in its own cache line.
	 *
	 *									PrimeRange class
	 * This class just makes it easier to convert different container types to one universal type, instead of
	 * having many findPrimeInRange functions with different arguments.
	 *
	 *
	 *									isPrime argument logic
	 * One downside of implementing the class with __m256d objects is that we have to calculate the factors up to
	 * the square root of the largest number in the __m256d, we calculate more factors than we have to for the smaller
	 * numbers. With this we have to be careful to not do `num % num`, the logic is that the sqrt of the largest number
	 * in the set of 4 doubles _cannot_ be greater than or equal to the value of the smallest number in the set of 4 doubles.
	 *
	 *									_hmin_pd and _hmax_pd
	 * There is no vectorized function for max and min, these functions solve that by comparing the vector by 2 indexes at a time
	 * compare
	 * flip
	 * compare
	 * compare the two comparisons
	 * 
	 *									Notes
	 * The primality test function is tested, and profiles with Intel VTune Amplifier
	 * The bottleneck is the fmod function, which is to be expected; division is the slowest operation on all CPUs
	 * There is thread creation overhead but that is happening when threads are working, therefore it is negligible
	 * If memory was a bottleneck that would be a problem to solve
	 */
	class TDPrime
	{
	private:
		std::vector<std::thread> _wrkThreads;
		unsigned int _threadCount;
		static inline bool _isPrime(__m256d in, bool primes[]);
		static inline __m256d _hmin_pd(__m256d m256d);
		static  inline __m256d _hmax_pd(__m256d m256d);
		
		static void threadWorker(double* alignedIn, int iterations, bool* res);
		
	public:
		TDPrime(const unsigned int threads = std::thread::hardware_concurrency()) : _threadCount(threads + 1)
		{
			 // Allocate space for the threads
			_wrkThreads.resize(threads+1);
		}

		std::vector<double> findPrimesInRange(double* work, size_t count);
		bool isPrime(double prime);

	};
}
