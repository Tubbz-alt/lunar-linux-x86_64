/* SPDX-License-Identifier: GPL-2.0 */
#ifndef ASM_X86_SERPENT_AVX_H
#define ASM_X86_SERPENT_AVX_H

#include <crypto/b128ops.h>
#include <crypto/serpent.h>
#include <linux/types.h>

struct crypto_skcipher;

#define SERPENT_PARALLEL_BLOCKS 8

struct serpent_xts_ctx {
	struct serpent_ctx tweak_ctx;
	struct serpent_ctx crypt_ctx;
};

asmlinkage void serpent_ecb_enc_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);
asmlinkage void serpent_ecb_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);

asmlinkage void serpent_cbc_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src);
asmlinkage void serpent_ctr_8way_avx(struct serpent_ctx *ctx, u8 *dst,
				     const u8 *src, le128 *iv);

asmlinkage void serpent_xts_enc_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src, le128 *iv);
asmlinkage void serpent_xts_dec_8way_avx(struct serpent_ctx *ctx, u8 *dst,
					 const u8 *src, le128 *iv);

extern void __serpent_crypt_ctr(void *ctx, u128 *dst, const u128 *src,
				le128 *iv);

extern void serpent_xts_enc(void *ctx, u128 *dst, const u128 *src, le128 *iv);
extern void serpent_xts_dec(void *ctx, u128 *dst, const u128 *src, le128 *iv);

extern int xts_serpent_setkey(struct crypto_skcipher *tfm, const u8 *key,
			      unsigned int keylen);

#endif
