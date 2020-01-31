#include "PrimeClass.h"

using namespace AbaciHelpers;

inline __m256d TDPrime::_hmax_pd(__m256d m256d)
{
	__m256d m256dPermute = _mm256_permute2f128_pd(m256d, m256d, 1);
	__m256d m1 = _mm256_max_pd(m256d, m256dPermute);
	__m256d m2 = _mm256_permute_pd(m1, 5);
	__m256d m = _mm256_max_pd(m1, m2);
	return m;
}
inline __m256d TDPrime::_hmin_pd(__m256d m256d)
{
	__m256d m256dPermute = _mm256_permute2f128_pd(m256d, m256d, 1);
	__m256d m1 = _mm256_min_pd(m256d, m256dPermute);
	__m256d m2 = _mm256_permute_pd(m1, 5);
	__m256d m = _mm256_min_pd(m1, m2);
	return m;
}

bool TDPrime::_isPrime(__m256d in, bool primes[])
{

	__m256d maxFactor = _mm256_sqrt_pd(in);
	maxFactor = _mm256_floor_pd(maxFactor);
	__m256d curFactor = _mm256_set_pd(2, 2, 2, 2);

	__m256d highFactor = _hmax_pd(maxFactor);
	__m256d minPrime = _hmin_pd(in);

	if (highFactor[0] >= minPrime[0])
		return false;
	
	__m256d ones = _mm256_set_pd(1,1,1,1);
	
	for (__m256d factor = _mm256_set1_pd(2); factor[0] <= highFactor[0]; factor = _mm256_add_pd(factor, ones))
	{
		
		#ifdef WIN32
		auto res = __mm256d_fmod_pd(in,factor);
		#else
		__m256d res = _mm256_div_pd(in,factor);
		res = _mm256_round_pd(res,_MM_FROUND_TRUNC);
		res = _mm256_mul_pd(res,factor);
		res = _mm256_sub_pd(in,res);
		#endif

		if (res[0] == 0.0)
			primes[3] = false;
		if (res[1] == 0.0)
			primes[2] = false;
		if (res[2] == 0.0)
			primes[1] = false;
		if (res[3] == 0.0)
			primes[0] = false;
	}
	return true;
}

void TDPrime::threadWorker(double* alignedIn, int iterations, bool* res)
{
	for (int curIteration = 0; curIteration < iterations; curIteration += 4)
	{
		__m256d primes = _mm256_set_pd(alignedIn[curIteration],
			alignedIn[curIteration + 1],
			alignedIn[curIteration + 2],
			alignedIn[curIteration + 3]);

		_isPrime(primes, res + curIteration);
	}
	
}

std::vector<double> TDPrime::findPrimesInRange(double* work,size_t count)
{
	bool* primeRes = (bool*)_aligned_malloc(count, 64); // Create aligned boolean array
	memset(primeRes, 1, count);

	const int iterPerThread = count / (this->_threadCount);
	for(unsigned int threadIteration = 0; threadIteration < this->_threadCount; threadIteration++){
		
		_wrkThreads[threadIteration] = std::thread(&TDPrime::threadWorker,
			&work[0] + (iterPerThread * threadIteration),iterPerThread,
			primeRes + (iterPerThread * threadIteration));
	}

	for(unsigned int threadIteration = 0; threadIteration < this->_threadCount; threadIteration++)
	{
		// Wait for threads to finish
		_wrkThreads[threadIteration].join();
	}
	
	std::vector<double> primesFound;
	for(unsigned int iteration = 0; iteration < count - 4; iteration += 4)
	{
		if (primeRes[iteration])
			primesFound.push_back(work[iteration]);
		if (primeRes[iteration + 1])
			primesFound.push_back(work[iteration + 1]);
		if (primeRes[iteration + 2])
			primesFound.push_back(work[iteration + 2]);
		if (primeRes[iteration + 3])
			primesFound.push_back(work[iteration + 3]);
	}
	_aligned_free(primeRes);
	return primesFound;
}

bool TDPrime::isPrime(double num)
{
	const __m256d prime = _mm256_set1_pd(num);
	
	bool res[4] = {true,true,true,true};
	
	_isPrime(prime, res);

	return res[0];
}