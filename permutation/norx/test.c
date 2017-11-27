
#include "norx.h"

// norx 32-4 test vector
char tv32[]=
{ 0x6c, 0xe9, 0x4c, 0xb5, 0x48, 0xb2, 0x0f, 0xed,
  0x7b, 0x68, 0xc6, 0xac, 0x60, 0xac, 0x4c, 0xb5,
  0xeb, 0xb1, 0xf0, 0x9a, 0xec, 0x5a, 0x75, 0x0e,
  0xcf, 0x50, 0xec, 0x0e, 0x64, 0x93, 0x8b, 0xf2,
  0x40, 0x17, 0xa4, 0xff, 0x06, 0x84, 0xf8, 0x08,
  0xa6, 0x7c, 0x19, 0x6c, 0x31, 0xa0, 0xaf, 0x12,
  0x56, 0x9b, 0xe5, 0xf7, 0xc5, 0x6a, 0xd3, 0xbc,
  0xac, 0x88, 0xda, 0x36, 0x86, 0x57, 0x5f, 0x93,
  0x43, 0x96, 0x8d, 0xa2, 0x20, 0x77, 0xee, 0xcc,
  0xe7, 0xd6, 0x63, 0x17, 0x49, 0x08, 0xa3, 0xf7,
  0x3c, 0x9e, 0x9a, 0xc1, 0x49, 0xb5, 0xce, 0x6b,
  0xe6, 0x9c, 0x9e, 0x31, 0x7c, 0xd7, 0xe7, 0xe8,
  0x0c, 0x85, 0x69, 0x97, 0x74, 0x02, 0x24, 0x41,
  0x3a, 0xe0, 0x64, 0xa2, 0x5a, 0x81, 0x08, 0xb8,
  0xd3, 0xa6, 0x85, 0x92, 0x74, 0xc7, 0x65, 0x86,
  0xe2, 0x9c, 0x27, 0xed, 0x11, 0xfb, 0x71, 0x95,
  0xd5, 0x54, 0xe4, 0xbc, 0x6b, 0x5b, 0xb7, 0x89,
  0x54, 0x77, 0x59, 0xea, 0xcd, 0xff, 0xcf, 0x47 };

void norx_aead_encryptx(norx_ctx *c);  
int norx_aead_decryptx(norx_ctx *c);
  
int main(void)
{
  uint8_t  k[16], n[16], a[128], m[128], z[128], c[256], p[256];
  int      i, clen, mlen, r;
  norx_ctx ctx;
  
  for (i=0; i<16; i++) {
    k[i] = i;
    n[i] = 32+i;
  }
  
  for (i=0; i<128; i++) {
    a[i] = i;
    m[i] = i;
    z[i] = i;
  }  
  
  ctx.a = a; ctx.alen = sizeof(a);  
  ctx.c = c; ctx.clen = 0;
  ctx.m = m; ctx.mlen = sizeof(m);
  ctx.z = z; ctx.zlen = sizeof(z);
  ctx.n = n; ctx.k = k;
  
  norx_aead_encryptx(&ctx);
  
  for (i=0; i<ctx.clen; i++) {
    if ((i & 7)==0) putchar('\n');
    if ((ctx.clen - i) == NORX_T/8) putchar('\n');
    printf("0x%02x, ", c[i]);    
  }
  printf("\n\nNORX 32-4 Encryption Test %s\n",
      memcmp(c, tv32, sizeof(tv32))==0 ? "OK" : "FAILED");      
  
  ctx.m = p;
  
  r = norx_aead_decryptx(&ctx);
        
  printf("\nNORX 32-4 Decryption Test %s\n",
      r==0 && (memcmp(m, p, ctx.mlen)==0) ? "OK" : "FAILED");

      
  return 0;
}