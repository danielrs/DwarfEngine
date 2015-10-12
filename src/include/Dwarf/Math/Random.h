/*
* The Mersenne Twister pseudo-random number generator (PRNG)
*
* This is an implementation of fast PRNG called MT19937,
* meaning it has a period of 2^19937-1, which is a Mersenne
* prime.
*
* This PRNG is fast and suitable for non-cryptographic code.
* For instance, it would be perfect for Monte Carlo simulations,
* etc.
*
* This code has been designed as a drop-in replacement for libc rand and
* srand().  If you need to mix them, you should encapsulate this code in a
* namespace.
*
* Written by Christian Stigen Larsen
* 2012-01-11 -- http://csl.sublevel3.org
*
* Distributed under the modified BSD license.
*/

#ifndef DWARF_MATH_RANDOM_H
#define DWARF_MATH_RANDOM_H

#include <stdint.h>

#include "../DwarfSetup.h"

namespace Dwarf
{
	namespace Math
	{
		namespace NRandom
		{
			/*
			* Maximum number you can get from rand().
			*/
			// #define RAND_MAX INT32_MAX

			#define M32(x) (0x80000000 & x) // 32nd Most Significant Bit
			#define L31(x) (0x7FFFFFFF & x) // 31 Least Significant Bits
			#define ODD(x) (x & 1) // Check if number is odd

			/*
			* Initialize the number generator with given seed.
			* (LIBC REPLACEMENT FUNCTION)
			*/
			void DWARFAPI srand(unsigned seed_value);

			/*
			* Extract a pseudo-random integer in the range 0 ... RAND_MAX.
			* (LIBC REPLACEMENT FUNCTION)
			*/
			int DWARFAPI rand();

			/*
			* Extract a pseudo-random unsigned 32-bit integer in the range 0 ... UINT32_MAX
			*/
			uint32_t DWARFAPI rand_u32();

			/*
			* Combine two unsigned 32-bit pseudo-random numbers into one 64-bit
			*/
			uint64_t DWARFAPI rand_u64();

			/*
			* Initialize Mersenne Twister with given seed value.
			*/
			void DWARFAPI seed(uint32_t seed_value);

			/*
			* Return a random float in the CLOSED range [0, 1]
			* Mnemonic: randf_co = random float 0=closed 1=closed
			*/
			float DWARFAPI randf_cc();

			/*
			* Return a random float in the OPEN range [0, 1>
			* Mnemonic: randf_co = random float 0=closed 1=open
			*/
			float DWARFAPI randf_co();

			/*
			* Return a random float in the OPEN range <0, 1>
			* Mnemonic: randf_oo = random float 0=open 1=open
			*/
			float DWARFAPI randf_oo();

			/*
			* Return a random double in the CLOSED range [0, 1]
			* Mnemonic: randd_co = random double 0=closed 1=closed
			*/
			double DWARFAPI randd_cc();

			/*
			* Return a random double in the OPEN range [0, 1>
			* Mnemonic: randd_co = random double 0=closed 1=open
			*/
			double DWARFAPI randd_co();

			/*
			* Return a random double in the OPEN range <0, 1>
			* Mnemonic: randd_oo = random double 0=open 1=open
			*/
			double DWARFAPI randd_oo();

		} // end of namespace NRandom

		// Template for swaping values
		template <typename TYPENAME>
		void Swap(TYPENAME &a, TYPENAME &b)
		{
			TYPENAME temp = a;
			a = b;
			b = temp;
		}

		class DWARFAPI Random
		{
		private:
			static bool initialized;
		public:
			Random();

			// The following functions generates a number in the range:
			// start-end (inclusive)
			// 0-end (inclusive)

			int nextInt(const int &end) const;
			int nextInt(int start, int end) const;

			float nextFloat(const float &end) const;
			float nextFloat(float start, float end) const;

			double nextDouble(const double &end) const;
			double nextDouble(double start, double end) const;
		};

	} // end of namespace Math
} // end of namespace Dwarf

#endif // DWARF_MATH_RANDOM_H
