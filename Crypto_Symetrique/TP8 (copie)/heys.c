#include "heys.h"


sbox_t sbox = {0xe, 0x4, 0xd, 0x1, 0x2, 0xf, 0xb, 0x8,
	       0x3, 0xa, 0x6, 0xc, 0x5, 0x9, 0x0, 0x7};
/*            {  0,   1,   2,   3,   4,   5,   6,   7,
                 8,   9,   a,   b,   c,   d,   e,   f}
*/
sbox_t isbox = {0xe, 0x3, 0x4, 0x8, 0x1, 0xc, 0xa, 0xf, 
		0x7, 0xd, 0x9, 0x6, 0xb, 0x2, 0x0, 0x5};


block_t heys_perm(block_t b){
  block_t r;
  r = b & 0x8421;
  r ^= ((b & 0x4210) >> 3);
  r ^= ((b & 0x2100) >> 6);
  r ^= ((b & 0x0008) << 9);
  r ^= ((b & 0x1000) >> 9);
  r ^= ((b & 0x0084) << 6);
  r ^= ((b & 0x0842) << 3);
  return r;
}

block_t heys_subst(block_t b, sbox_t sbox){
  block_t r;
  r = sbox[b & 0x000f];
  r ^= sbox[(b & 0x00f0) >> 4] << 4;
  r ^= sbox[(b & 0x0f00) >> 8] << 8;
  r ^= sbox[(b & 0xf000) >> 12] << 12;
  return r;
}

int heys_key_schedule(ckey_t k, skey_t sk){
  int dec = (CIPHERKEYSIZE - ROUNDKEYSIZE)/NROUNDS;
  int i;
  for (i=0; i < NROUNDS; i++){
    sk[i] = (rkey_t)(k >> (CIPHERKEYSIZE - ROUNDKEYSIZE - i*dec)); 
    /*
    printf("decalage : %u, dec : %u, cksize : %u, rkeysize : %u\n", 
	   (CIPHERKEYSIZE - ROUNDKEYSIZE - i*dec), dec, 
	   CIPHERKEYSIZE, ROUNDKEYSIZE);
    */
  }
  sk[NROUNDS] = (rkey_t)(k & 0x0000ffff);
  /* clef de 32 bits :
     sk[0] = (rkey_t)(k >> 16);
     sk[1] = (rkey_t)((k >> 12) & 0x0000ffff);
     sk[2] = (rkey_t)((k >> 8) & 0x0000ffff);
     sk[3] = (rkey_t)((k >> 4) & 0x0000ffff);
     sk[4] = (rkey_t)(k & 0x0000ffff);
  */

  if (VERBOSE > 1){
    for (i=0; i <= NROUNDS; i++){
      fprintf(stderr, "k[%u] = %4x\n", i, sk[i]);
    }
  }
  return 1;
}

block_t heys_encrypt(block_t b, ckey_t k){
 block_t r;
 skey_t sk;
 heys_key_schedule(k, sk);
 r = sk[0] ^ b;
 if (VERBOSE){
   fprintf(stderr, "k[0] = %4x ; r = %4x\n", sk[0],r);
 }
 r = heys_subst(r,sbox);
 r = heys_perm(r);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r ^= sk[1];
 if (VERBOSE){
   fprintf(stderr, "k[1] = %4x ; r = %4x\n", sk[1],r);
 }
 r = heys_subst(r,sbox);
 r = heys_perm(r);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r ^= sk[2];
 if (VERBOSE){
   fprintf(stderr, "k[2] = %4x ; r = %4x\n", sk[2],r);
 }
 r = heys_subst(r,sbox);
 r = heys_perm(r);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r ^= sk[3];
 if (VERBOSE){
   fprintf(stderr, "k[3] = %4x ; r = %4x\n", sk[3],r);
 }
 r = heys_subst(r,sbox);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r ^= sk[4];
 if (VERBOSE){
   fprintf(stderr, "k[4] = %4x ; r = %4x\n", sk[4],r);
 }
 return r;
}

block_t heys_decrypt(block_t b, ckey_t k){
 block_t r;
 skey_t sk;
 heys_key_schedule(k, sk);
 r = sk[4] ^ b;
 if (VERBOSE){
   fprintf(stderr, "k[4] = %4x ; r = %4x\n", sk[4],r);
 }
 r = heys_subst(r,isbox);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r = sk[3] ^ r;
 if (VERBOSE){
   fprintf(stderr, "k[3] = %4x ; r = %4x\n", sk[3],r);
 }
 r = heys_perm(r);
 r = heys_subst(r,isbox);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r = sk[2] ^ r;
 if (VERBOSE){
   fprintf(stderr, "k[2] = %4x ; r = %4x\n", sk[2],r);
 }
 r = heys_perm(r);
 r = heys_subst(r,isbox);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r = sk[1] ^ r;
 if (VERBOSE){
   fprintf(stderr, "k[1] = %4x ; r = %4x\n", sk[1],r);
 }
 r = heys_perm(r);
 r = heys_subst(r,isbox);
 if (VERBOSE){
   fprintf(stderr, "              r = %4x\n",r);
 }
 r = sk[0] ^ r;
 if (VERBOSE){
   fprintf(stderr, "k[0] = %4x ; r = %4x\n", sk[0],r);
 }
 return r;
}
