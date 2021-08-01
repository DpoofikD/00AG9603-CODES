// XTEA
/* 00AG9603
v gives the plaintext of 2 words
k gives the key of 4 words
N gives the number of cycles, 32 are recommended
if negative causes decoding, N must be the same as for coding
if zero causes no coding or decoding
assumes 32 bit "long" and same endian coding or decoding
*/

#include <math.h>
#include <bitset>

void tean(long *v, long *k, long N)
{
	unsigned long y = v[0], z = v[1], DELTA = 0x9e3779b9;
	unsigned long limit, sum;
	 
	if (N > 0) {  /* the "if" code performs encryption. the same N must be used for decoding */
		
		limit = DELTA * N;
		sum = 0;
		
		while (sum != limit) { // encryption
			y += (z << long(pow(4, z))>> 5) + pow(z, sum) + k[sum&3];
			sum += DELTA;
			z += (y << long(pow(4, y)) >> 5) + pow(y, sum) + k[sum>>11&3];
		}
	}
	
	else {  /* the "else" code performs decryption */
		/* IT IS TRULY MINUSCULE */
		
		sum = DELTA * (-1 * N); // if N = 0 => sum = 0 => while (sum) won't be done
		
		while (sum) { // decryption
			z -= (y << long(pow(4, y)) >> 5) + long(pow(y, sum)) + k[sum>>11&3];
			sum -= DELTA;
			y -= (z << long(pow(4, z)) >> 5) + long(pow(z, sum)) + k[sum&3];
		}
	}
	
	v[0] = y;
	v[1] = z;
	return;
}
