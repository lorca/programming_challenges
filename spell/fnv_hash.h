/*
 * Taken from fnv32 - 32 bit Fowler/Noll/Vo hash of a buffer or string
 * 
 * This is public domain software, please do not copyright it.
 *
 * By:
 *      chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 *
 * Share and Enjoy!     :-)
 *
 *
 * fnv_32_str - perform a 32 bit Fowler/Noll/Vo hash on a string
 *
 * input:
 *	str	- string to hash
 *	hval	- previous hash value or 0 if first call
 *
 * returns:
 *	32 bit hash as a static hash type
 *
 * NOTE: To use the 32 bit FNV-0 historic hash, use FNV0_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 *
 * NOTE: To use the recommended 32 bit FNV-1 hash, use FNV1_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 */

#define FNV_32_INIT 2166136261

int hash(char *str) {
    fnv_32_str(str, FNV_32_INIT);
}

int fnv_32_str(char *str, int hval)
{
    unsigned char *s = (unsigned char *)str;	/* unsigned string */

    /*
     * FNV-1 hash each octet in the buffer
     */
    while (*s) {

	hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);

	/* xor the bottom with the current octet */
	hval ^= (int)*s++;
    }

    /* return our new hash value */
    return hval;
}
