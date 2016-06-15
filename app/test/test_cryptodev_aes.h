/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2016 Intel Corporation. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *	 * Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimer.
 *	 * Redistributions in binary form must reproduce the above copyright
 *	   notice, this list of conditions and the following disclaimer in
 *	   the documentation and/or other materials provided with the
 *	   distribution.
 *	 * Neither the name of Intel Corporation nor the names of its
 *	   contributors may be used to endorse or promote products derived
 *	   from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TEST_CRYPTODEV_AES_H_
#define TEST_CRYPTODEV_AES_H_

struct aes_test_data {
	enum rte_crypto_cipher_algorithm crypto_algo;

	struct {
		uint8_t data[64];
		unsigned len;
	} cipher_key;

	struct {
		uint8_t data[64] __rte_aligned(16);
		unsigned len;
	} iv;

	struct {
		uint8_t data[2048];
		unsigned len;
	} plaintext;

	struct {
		uint8_t data[2048];
		unsigned len;
	} ciphertext;

	enum rte_crypto_auth_algorithm auth_algo;

	struct {
		uint8_t data[128];
		unsigned len;
	} auth_key;

	struct {
		uint8_t data[128];
		unsigned len;		/* for qat */
		unsigned truncated_len;	/* for mb */
	} digest;
};

int
test_AES_all_tests(struct rte_mempool *mbuf_pool,
	struct rte_mempool *op_mpool,
	uint8_t dev_id,
	enum rte_cryptodev_type cryptodev_type);

/* test vectors */
/* AES128-CTR-SHA1 test vector */
static const struct aes_test_data aes_test_data_1 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CTR,
	.cipher_key = {
		.data = {
			0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
			0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
		},
		.len = 16
	},
	.iv = {
		.data = {
			0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
			0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
			0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
			0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
			0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
			0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11,
			0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
			0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17,
			0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10
		},
		.len = 64
	},
	.ciphertext = {
		.data = {
			0x87, 0x4D, 0x61, 0x91, 0xB6, 0x20, 0xE3, 0x26,
			0x1B, 0xEF, 0x68, 0x64, 0x99, 0x0D, 0xB6, 0xCE,
			0x98, 0x06, 0xF6, 0x6B, 0x79, 0x70, 0xFD, 0xFF,
			0x86, 0x17, 0x18, 0x7B, 0xB9, 0xFF, 0xFD, 0xFF,
			0x5A, 0xE4, 0xDF, 0x3E, 0xDB, 0xD5, 0xD3, 0x5E,
			0x5B, 0x4F, 0x09, 0x02, 0x0D, 0xB0, 0x3E, 0xAB,
			0x1E, 0x03, 0x1D, 0xDA, 0x2F, 0xBE, 0x03, 0xD1,
			0x79, 0x21, 0x70, 0xA0, 0xF3, 0x00, 0x9C, 0xEE
		},
		.len = 64
	},
	.auth_algo = RTE_CRYPTO_AUTH_SHA1_HMAC,
	.auth_key = {
		.data = {
			0xF8, 0x2A, 0xC7, 0x54, 0xDB, 0x96, 0x18, 0xAA,
			0xC3, 0xA1, 0x53, 0xF6, 0x1F, 0x17, 0x60, 0xBD,
			0xDE, 0xF4, 0xDE, 0xAD
		},
		.len = 20
	},
	.digest = {
		.data = {
			0x9B, 0x6F, 0x0C, 0x43, 0xF5, 0xC1, 0x3E, 0xB0,
			0xB1, 0x70, 0xB8, 0x2B, 0x33, 0x09, 0xD2, 0xB2,
			0x56, 0x20, 0xFB, 0xFE
		},
		.len = 20,
		.truncated_len = 12
	}
};

/** AES-192-CTR XCBC test vector */
static const struct aes_test_data aes_test_data_2 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CTR,
	.cipher_key = {
		.data = {
			0xCB, 0xC5, 0xED, 0x5B, 0xE7, 0x7C, 0xBD, 0x8C,
			0x50, 0xD9, 0x30, 0xF2, 0xB5, 0x6A, 0x0E, 0x5F,
			0xAA, 0xAE, 0xAD, 0xA2, 0x1F, 0x49, 0x52, 0xD4
		},
		.len = 24
	},
	.iv = {
		.data = {
			0x3F, 0x69, 0xA8, 0xCD, 0xE8, 0xF0, 0xEF, 0x40,
			0xB8, 0x7A, 0x4B, 0xED, 0x2B, 0xAF, 0xBF, 0x57
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			0x01, 0x0F, 0x10, 0x1F, 0x20, 0x1C, 0x0E, 0xB8,
			0xFB, 0x5C, 0xCD, 0xCC, 0x1F, 0xF9, 0xAF, 0x0B,
			0x95, 0x03, 0x74, 0x99, 0x49, 0xE7, 0x62, 0x55,
			0xDA, 0xEA, 0x13, 0x20, 0x1D, 0xC6, 0xCC, 0xCC,
			0xD1, 0x70, 0x75, 0x47, 0x02, 0x2F, 0xFB, 0x86,
			0xBB, 0x6B, 0x23, 0xD2, 0xC9, 0x74, 0xD7, 0x7B,
			0x08, 0x03, 0x3B, 0x79, 0x39, 0xBB, 0x91, 0x29,
			0xDA, 0x14, 0x39, 0x8D, 0xFF, 0x81, 0x50, 0x96,
		},
		.len = 64
	},
	.ciphertext = {
		.data = {
			0x4A, 0x6C, 0xC8, 0xCC, 0x96, 0x2A, 0x13, 0x84,
			0x1C, 0x36, 0x88, 0xE9, 0xE5, 0x94, 0x70, 0xB2,
			0x14, 0x5B, 0x13, 0x80, 0xEA, 0xD8, 0x8D, 0x37,
			0xFD, 0x70, 0xA8, 0x83, 0xE8, 0x2B, 0x88, 0x1E,
			0xBA, 0x94, 0x3F, 0xF6, 0xB3, 0x1F, 0xDE, 0x34,
			0xF3, 0x5B, 0x80, 0xE9, 0xAB, 0xF5, 0x1C, 0x29,
			0xB6, 0xD9, 0x76, 0x2B, 0x06, 0xC6, 0x74, 0xF1,
			0x59, 0x5E, 0x9E, 0xA5, 0x7B, 0x2D, 0xD7, 0xF0
		},
		.len = 64
	},
	.auth_algo = RTE_CRYPTO_AUTH_AES_XCBC_MAC,
	.auth_key = {
		.data = {
			0x87, 0x61, 0x54, 0x53, 0xC4, 0x6D, 0xDD, 0x51,
			0xE1, 0x9F, 0x86, 0x64, 0x39, 0x0A, 0xE6, 0x59
		},
		.len = 16
	},
	.digest = {
		.data = {
			0xCA, 0x33, 0xB3, 0x3B, 0x16, 0x94, 0xAA, 0x55,
			0x36, 0x6B, 0x45, 0x46
		},
		.len = 12,
		.truncated_len = 12
	}
};

/** AES-256-CTR SHA1 test vector */
static const struct aes_test_data aes_test_data_3 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CTR,
	.cipher_key = {
		.data = {
			0x60, 0x3D, 0xEB, 0x10, 0x15, 0xCA, 0x71, 0xBE,
			0x2B, 0x73, 0xAE, 0xF0, 0x85, 0x7D, 0x77, 0x81,
			0x1F, 0x35, 0x2C, 0x07, 0x3B, 0x61, 0x08, 0xD7,
			0x2D, 0x98, 0x10, 0xA3, 0x09, 0x14, 0xDF, 0xF4
		},
		.len = 32
	},
	.iv = {
		.data = {
			0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
			0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
			0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
			0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C,
			0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
			0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11,
			0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
			0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17,
			0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10
		},
		.len = 64
	},
	.ciphertext = {
		.data = {
			0x60, 0x1E, 0xC3, 0x13, 0x77, 0x57, 0x89, 0xA5,
			0xB7, 0xA7, 0xF5, 0x04, 0xBB, 0xF3, 0xD2, 0x28,
			0xF4, 0x43, 0xE3, 0xCA, 0x4D, 0x62, 0xB5, 0x9A,
			0xCA, 0x84, 0xE9, 0x90, 0xCA, 0xCA, 0xF5, 0xC5,
			0x2B, 0x09, 0x30, 0xDA, 0xA2, 0x3D, 0xE9, 0x4C,
			0xE8, 0x70, 0x17, 0xBA, 0x2D, 0x84, 0x98, 0x8D,
			0xDF, 0xC9, 0xC5, 0x8D, 0xB6, 0x7A, 0xAD, 0xA6,
			0x13, 0xC2, 0xDD, 0x08, 0x45, 0x79, 0x41, 0xA6
		},
		.len = 64
	},
	.auth_algo = RTE_CRYPTO_AUTH_SHA1_HMAC,
	.auth_key = {
		.data = {
			0xF8, 0x2A, 0xC7, 0x54, 0xDB, 0x96, 0x18, 0xAA,
			0xC3, 0xA1, 0x53, 0xF6, 0x1F, 0x17, 0x60, 0xBD,
			0xDE, 0xF4, 0xDE, 0xAD
		},
		.len = 20
	},
	.digest = {
		.data = {
			0x3B, 0x1A, 0x9D, 0x82, 0x35, 0xD5, 0xDD, 0x64,
			0xCC, 0x1B, 0xA9, 0xC0, 0xEB, 0xE9, 0x42, 0x16,
			0xE7, 0x87, 0xA3, 0xEF
		},
		.len = 20,
		.truncated_len = 12
	}
};

/** AES-128-CBC SHA1 test vector */
static const struct aes_test_data aes_test_data_4 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CBC,
	.cipher_key = {
		.data = {
			0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
			0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A
		},
		.len = 16
	},
	.iv = {
		.data = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			"What a lousy earth! He wondered how many people "
			"were destitute that same night even in his own "
			"prosperous country, how many homes were "
			"shanties, how many husbands were drunk and "
			"wives socked, and how many children were "
			"bullied, abused, or abandoned. How many "
			"families hungered for food they could not "
			"afford to buy? How many hearts were broken? How "
			"many suicides would take place that same night, "
			"how many people would go insane? How many "
			"cockroaches and landlords would triumph? How "
			"many winners were losers, successes failures, "
			"and rich men poor men? How many wise guys were "
			"stupid? How many happy endings were unhappy "
			"endings? How many honest men were liars, brave "
			"men cowards, loyal men traitors, how many "
			"sainted men were corrupt, how many people in "
			"positions of trust had sold their souls to "
			"bodyguards, how many had never had souls? How "
			"many straight-and-narrow paths were crooked "
			"paths? How many best families were worst "
			"families and how many good people were bad "
			"people? When you added them all up and then "
			"subtracted, you might be left with only the "
			"children, and perhaps with Albert Einstein and "
			"an old violinist or sculptor somewhere."
		},
		.len = 512
	},
	.ciphertext = {
		.data = {
			0x8B, 0x4D, 0xDA, 0x1B, 0xCF, 0x04, 0xA0, 0x31,
			0xB4, 0xBF, 0xBD, 0x68, 0x43, 0x20, 0x7E, 0x76,
			0xB1, 0x96, 0x8B, 0xA2, 0x7C, 0xA2, 0x83, 0x9E,
			0x39, 0x5A, 0x2F, 0x7E, 0x92, 0xB4, 0x48, 0x1A,
			0x3F, 0x6B, 0x5D, 0xDF, 0x52, 0x85, 0x5F, 0x8E,
			0x42, 0x3C, 0xFB, 0xE9, 0x1A, 0x24, 0xD6, 0x08,
			0xDD, 0xFD, 0x16, 0xFB, 0xE9, 0x55, 0xEF, 0xF0,
			0xA0, 0x8D, 0x13, 0xAB, 0x81, 0xC6, 0x90, 0x01,
			0xB5, 0x18, 0x84, 0xB3, 0xF6, 0xE6, 0x11, 0x57,
			0xD6, 0x71, 0xC6, 0x3C, 0x3F, 0x2F, 0x33, 0xEE,
			0x24, 0x42, 0x6E, 0xAC, 0x0B, 0xCA, 0xEC, 0xF9,
			0x84, 0xF8, 0x22, 0xAA, 0x60, 0xF0, 0x32, 0xA9,
			0x75, 0x75, 0x3B, 0xCB, 0x70, 0x21, 0x0A, 0x8D,
			0x0F, 0xE0, 0xC4, 0x78, 0x2B, 0xF8, 0x97, 0xE3,
			0xE4, 0x26, 0x4B, 0x29, 0xDA, 0x88, 0xCD, 0x46,
			0xEC, 0xAA, 0xF9, 0x7F, 0xF1, 0x15, 0xEA, 0xC3,
			0x87, 0xE6, 0x31, 0xF2, 0xCF, 0xDE, 0x4D, 0x80,
			0x70, 0x91, 0x7E, 0x0C, 0xF7, 0x26, 0x3A, 0x92,
			0x4F, 0x18, 0x83, 0xC0, 0x8F, 0x59, 0x01, 0xA5,
			0x88, 0xD1, 0xDB, 0x26, 0x71, 0x27, 0x16, 0xF5,
			0xEE, 0x10, 0x82, 0xAC, 0x68, 0x26, 0x9B, 0xE2,
			0x6D, 0xD8, 0x9A, 0x80, 0xDF, 0x04, 0x31, 0xD5,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x61, 0x1C, 0x42, 0x10, 0x76,
			0x73, 0x02, 0x42, 0xC9, 0x23, 0x18, 0x8E, 0xB4,
			0x6F, 0xB4, 0xA3, 0x54, 0x6E, 0x88, 0x3B, 0x62,
			0x7C, 0x02, 0x8D, 0x4C, 0x9F, 0xC8, 0x45, 0xF4,
			0xC9, 0xDE, 0x4F, 0xEB, 0x22, 0x83, 0x1B, 0xE4,
			0x49, 0x37, 0xE4, 0xAD, 0xE7, 0xCD, 0x21, 0x54,
			0xBC, 0x1C, 0xC2, 0x04, 0x97, 0xB4, 0x10, 0x61,
			0xF0, 0xE4, 0xEF, 0x27, 0x63, 0x3A, 0xDA, 0x91,
			0x41, 0x25, 0x62, 0x1C, 0x5C, 0xB6, 0x38, 0x4A,
			0x88, 0x71, 0x59, 0x5A, 0x8D, 0xA0, 0x09, 0xAF,
			0x72, 0x94, 0xD7, 0x79, 0x5C, 0x60, 0x7C, 0x8F,
			0x4C, 0xF5, 0xD9, 0xA1, 0x39, 0x6D, 0x81, 0x28,
			0xEF, 0x13, 0x28, 0xDF, 0xF5, 0x3E, 0xF7, 0x8E,
			0x09, 0x9C, 0x78, 0x18, 0x79, 0xB8, 0x68, 0xD7,
			0xA8, 0x29, 0x62, 0xAD, 0xDE, 0xE1, 0x61, 0x76,
			0x1B, 0x05, 0x16, 0xCD, 0xBF, 0x02, 0x8E, 0xA6,
			0x43, 0x6E, 0x92, 0x55, 0x4F, 0x60, 0x9C, 0x03,
			0xB8, 0x4F, 0xA3, 0x02, 0xAC, 0xA8, 0xA7, 0x0C,
			0x1E, 0xB5, 0x6B, 0xF8, 0xC8, 0x4D, 0xDE, 0xD2,
			0xB0, 0x29, 0x6E, 0x40, 0xE6, 0xD6, 0xC9, 0xE6,
			0xB9, 0x0F, 0xB6, 0x63, 0xF5, 0xAA, 0x2B, 0x96,
			0xA7, 0x16, 0xAC, 0x4E, 0x0A, 0x33, 0x1C, 0xA6,
			0xE6, 0xBD, 0x8A, 0xCF, 0x40, 0xA9, 0xB2, 0xFA,
			0x63, 0x27, 0xFD, 0x9B, 0xD9, 0xFC, 0xD5, 0x87,
			0x8D, 0x4C, 0xB6, 0xA4, 0xCB, 0xE7, 0x74, 0x55,
			0xF4, 0xFB, 0x41, 0x25, 0xB5, 0x4B, 0x0A, 0x1B,
			0xB1, 0xD6, 0xB7, 0xD9, 0x47, 0x2A, 0xC3, 0x98,
			0x6A, 0xC4, 0x03, 0x73, 0x1F, 0x93, 0x6E, 0x53,
			0x19, 0x25, 0x64, 0x15, 0x83, 0xF9, 0x73, 0x2A,
			0x74, 0xB4, 0x93, 0x69, 0xC4, 0x72, 0xFC, 0x26,
			0xA2, 0x9F, 0x43, 0x45, 0xDD, 0xB9, 0xEF, 0x36,
			0xC8, 0x3A, 0xCD, 0x99, 0x9B, 0x54, 0x1A, 0x36,
			0xC1, 0x59, 0xF8, 0x98, 0xA8, 0xCC, 0x28, 0x0D,
			0x73, 0x4C, 0xEE, 0x98, 0xCB, 0x7C, 0x58, 0x7E,
			0x20, 0x75, 0x1E, 0xB7, 0xC9, 0xF8, 0xF2, 0x0E,
			0x63, 0x9E, 0x05, 0x78, 0x1A, 0xB6, 0xA8, 0x7A,
			0xF9, 0x98, 0x6A, 0xA6, 0x46, 0x84, 0x2E, 0xF6,
			0x4B, 0xDC, 0x9B, 0x8F, 0x9B, 0x8F, 0xEE, 0xB4,
			0xAA, 0x3F, 0xEE, 0xC0, 0x37, 0x27, 0x76, 0xC7,
			0x95, 0xBB, 0x26, 0x74, 0x69, 0x12, 0x7F, 0xF1,
			0xBB, 0xFF, 0xAE, 0xB5, 0x99, 0x6E, 0xCB, 0x0C
		},
		.len = 512
	},
	.auth_algo = RTE_CRYPTO_AUTH_SHA1_HMAC,
	.auth_key = {
		.data = {
			0xF8, 0x2A, 0xC7, 0x54, 0xDB, 0x96, 0x18, 0xAA,
			0xC3, 0xA1, 0x53, 0xF6, 0x1F, 0x17, 0x60, 0xBD,
			0xDE, 0xF4, 0xDE, 0xAD
		},
		.len = 20
	},
	.digest = {
		.data = {
			0x9A, 0x4F, 0x88, 0x1B, 0xB6, 0x8F, 0xD8, 0x60,
			0x42, 0x1A, 0x7D, 0x3D, 0xF5, 0x82, 0x80, 0xF1,
			0x18, 0x8C, 0x1D, 0x32
		},
		.len = 20,
		.truncated_len = 12
	}
};

/** AES-128-CBC SHA256 test vector */
static const struct aes_test_data aes_test_data_5 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CBC,
	.cipher_key = {
		.data = {
			0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
			0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A
		},
		.len = 16
	},
	.iv = {
		.data = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			"What a lousy earth! He wondered how many people "
			"were destitute that same night even in his own "
			"prosperous country, how many homes were "
			"shanties, how many husbands were drunk and "
			"wives socked, and how many children were "
			"bullied, abused, or abandoned. How many "
			"families hungered for food they could not "
			"afford to buy? How many hearts were broken? How "
			"many suicides would take place that same night, "
			"how many people would go insane? How many "
			"cockroaches and landlords would triumph? How "
			"many winners were losers, successes failures, "
			"and rich men poor men? How many wise guys were "
			"stupid? How many happy endings were unhappy "
			"endings? How many honest men were liars, brave "
			"men cowards, loyal men traitors, how many "
			"sainted men were corrupt, how many people in "
			"positions of trust had sold their souls to "
			"bodyguards, how many had never had souls? How "
			"many straight-and-narrow paths were crooked "
			"paths? How many best families were worst "
			"families and how many good people were bad "
			"people? When you added them all up and then "
			"subtracted, you might be left with only the "
			"children, and perhaps with Albert Einstein and "
			"an old violinist or sculptor somewhere."
		},
		.len = 512
	},
	.ciphertext = {
		.data = {
			0x8B, 0x4D, 0xDA, 0x1B, 0xCF, 0x04, 0xA0, 0x31,
			0xB4, 0xBF, 0xBD, 0x68, 0x43, 0x20, 0x7E, 0x76,
			0xB1, 0x96, 0x8B, 0xA2, 0x7C, 0xA2, 0x83, 0x9E,
			0x39, 0x5A, 0x2F, 0x7E, 0x92, 0xB4, 0x48, 0x1A,
			0x3F, 0x6B, 0x5D, 0xDF, 0x52, 0x85, 0x5F, 0x8E,
			0x42, 0x3C, 0xFB, 0xE9, 0x1A, 0x24, 0xD6, 0x08,
			0xDD, 0xFD, 0x16, 0xFB, 0xE9, 0x55, 0xEF, 0xF0,
			0xA0, 0x8D, 0x13, 0xAB, 0x81, 0xC6, 0x90, 0x01,
			0xB5, 0x18, 0x84, 0xB3, 0xF6, 0xE6, 0x11, 0x57,
			0xD6, 0x71, 0xC6, 0x3C, 0x3F, 0x2F, 0x33, 0xEE,
			0x24, 0x42, 0x6E, 0xAC, 0x0B, 0xCA, 0xEC, 0xF9,
			0x84, 0xF8, 0x22, 0xAA, 0x60, 0xF0, 0x32, 0xA9,
			0x75, 0x75, 0x3B, 0xCB, 0x70, 0x21, 0x0A, 0x8D,
			0x0F, 0xE0, 0xC4, 0x78, 0x2B, 0xF8, 0x97, 0xE3,
			0xE4, 0x26, 0x4B, 0x29, 0xDA, 0x88, 0xCD, 0x46,
			0xEC, 0xAA, 0xF9, 0x7F, 0xF1, 0x15, 0xEA, 0xC3,
			0x87, 0xE6, 0x31, 0xF2, 0xCF, 0xDE, 0x4D, 0x80,
			0x70, 0x91, 0x7E, 0x0C, 0xF7, 0x26, 0x3A, 0x92,
			0x4F, 0x18, 0x83, 0xC0, 0x8F, 0x59, 0x01, 0xA5,
			0x88, 0xD1, 0xDB, 0x26, 0x71, 0x27, 0x16, 0xF5,
			0xEE, 0x10, 0x82, 0xAC, 0x68, 0x26, 0x9B, 0xE2,
			0x6D, 0xD8, 0x9A, 0x80, 0xDF, 0x04, 0x31, 0xD5,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x61, 0x1C, 0x42, 0x10, 0x76,
			0x73, 0x02, 0x42, 0xC9, 0x23, 0x18, 0x8E, 0xB4,
			0x6F, 0xB4, 0xA3, 0x54, 0x6E, 0x88, 0x3B, 0x62,
			0x7C, 0x02, 0x8D, 0x4C, 0x9F, 0xC8, 0x45, 0xF4,
			0xC9, 0xDE, 0x4F, 0xEB, 0x22, 0x83, 0x1B, 0xE4,
			0x49, 0x37, 0xE4, 0xAD, 0xE7, 0xCD, 0x21, 0x54,
			0xBC, 0x1C, 0xC2, 0x04, 0x97, 0xB4, 0x10, 0x61,
			0xF0, 0xE4, 0xEF, 0x27, 0x63, 0x3A, 0xDA, 0x91,
			0x41, 0x25, 0x62, 0x1C, 0x5C, 0xB6, 0x38, 0x4A,
			0x88, 0x71, 0x59, 0x5A, 0x8D, 0xA0, 0x09, 0xAF,
			0x72, 0x94, 0xD7, 0x79, 0x5C, 0x60, 0x7C, 0x8F,
			0x4C, 0xF5, 0xD9, 0xA1, 0x39, 0x6D, 0x81, 0x28,
			0xEF, 0x13, 0x28, 0xDF, 0xF5, 0x3E, 0xF7, 0x8E,
			0x09, 0x9C, 0x78, 0x18, 0x79, 0xB8, 0x68, 0xD7,
			0xA8, 0x29, 0x62, 0xAD, 0xDE, 0xE1, 0x61, 0x76,
			0x1B, 0x05, 0x16, 0xCD, 0xBF, 0x02, 0x8E, 0xA6,
			0x43, 0x6E, 0x92, 0x55, 0x4F, 0x60, 0x9C, 0x03,
			0xB8, 0x4F, 0xA3, 0x02, 0xAC, 0xA8, 0xA7, 0x0C,
			0x1E, 0xB5, 0x6B, 0xF8, 0xC8, 0x4D, 0xDE, 0xD2,
			0xB0, 0x29, 0x6E, 0x40, 0xE6, 0xD6, 0xC9, 0xE6,
			0xB9, 0x0F, 0xB6, 0x63, 0xF5, 0xAA, 0x2B, 0x96,
			0xA7, 0x16, 0xAC, 0x4E, 0x0A, 0x33, 0x1C, 0xA6,
			0xE6, 0xBD, 0x8A, 0xCF, 0x40, 0xA9, 0xB2, 0xFA,
			0x63, 0x27, 0xFD, 0x9B, 0xD9, 0xFC, 0xD5, 0x87,
			0x8D, 0x4C, 0xB6, 0xA4, 0xCB, 0xE7, 0x74, 0x55,
			0xF4, 0xFB, 0x41, 0x25, 0xB5, 0x4B, 0x0A, 0x1B,
			0xB1, 0xD6, 0xB7, 0xD9, 0x47, 0x2A, 0xC3, 0x98,
			0x6A, 0xC4, 0x03, 0x73, 0x1F, 0x93, 0x6E, 0x53,
			0x19, 0x25, 0x64, 0x15, 0x83, 0xF9, 0x73, 0x2A,
			0x74, 0xB4, 0x93, 0x69, 0xC4, 0x72, 0xFC, 0x26,
			0xA2, 0x9F, 0x43, 0x45, 0xDD, 0xB9, 0xEF, 0x36,
			0xC8, 0x3A, 0xCD, 0x99, 0x9B, 0x54, 0x1A, 0x36,
			0xC1, 0x59, 0xF8, 0x98, 0xA8, 0xCC, 0x28, 0x0D,
			0x73, 0x4C, 0xEE, 0x98, 0xCB, 0x7C, 0x58, 0x7E,
			0x20, 0x75, 0x1E, 0xB7, 0xC9, 0xF8, 0xF2, 0x0E,
			0x63, 0x9E, 0x05, 0x78, 0x1A, 0xB6, 0xA8, 0x7A,
			0xF9, 0x98, 0x6A, 0xA6, 0x46, 0x84, 0x2E, 0xF6,
			0x4B, 0xDC, 0x9B, 0x8F, 0x9B, 0x8F, 0xEE, 0xB4,
			0xAA, 0x3F, 0xEE, 0xC0, 0x37, 0x27, 0x76, 0xC7,
			0x95, 0xBB, 0x26, 0x74, 0x69, 0x12, 0x7F, 0xF1,
			0xBB, 0xFF, 0xAE, 0xB5, 0x99, 0x6E, 0xCB, 0x0C
		},
		.len = 512
	},
	.auth_algo = RTE_CRYPTO_AUTH_SHA256_HMAC,
	.auth_key = {
		.data = {
			0x42, 0x1A, 0x7D, 0x3D, 0xF5, 0x82, 0x80, 0xF1,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x61, 0x1C, 0x42, 0x10, 0x76,
			0x9A, 0x4F, 0x88, 0x1B, 0xB6, 0x8F, 0xD8, 0x60
		},
		.len = 32
	},
	.digest = {
		.data = {
			0xC8, 0x57, 0x57, 0x31, 0x03, 0xE0, 0x03, 0x55,
			0x07, 0xC8, 0x9E, 0x7F, 0x48, 0x9A, 0x61, 0x9A,
			0x68, 0xEE, 0x03, 0x0E, 0x71, 0x75, 0xC7, 0xF4,
			0x2E, 0x45, 0x26, 0x32, 0x7C, 0x12, 0x15, 0x15
		},
		.len = 32,
		.truncated_len = 16
	}
};

/** AES-128-CBC SHA512 test vector */
static const struct aes_test_data aes_test_data_6 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CBC,
	.cipher_key = {
		.data = {
			0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
			0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A
		},
		.len = 16
	},
	.iv = {
		.data = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			"What a lousy earth! He wondered how many people "
			"were destitute that same night even in his own "
			"prosperous country, how many homes were "
			"shanties, how many husbands were drunk and "
			"wives socked, and how many children were "
			"bullied, abused, or abandoned. How many "
			"families hungered for food they could not "
			"afford to buy? How many hearts were broken? How "
			"many suicides would take place that same night, "
			"how many people would go insane? How many "
			"cockroaches and landlords would triumph? How "
			"many winners were losers, successes failures, "
			"and rich men poor men? How many wise guys were "
			"stupid? How many happy endings were unhappy "
			"endings? How many honest men were liars, brave "
			"men cowards, loyal men traitors, how many "
			"sainted men were corrupt, how many people in "
			"positions of trust had sold their souls to "
			"bodyguards, how many had never had souls? How "
			"many straight-and-narrow paths were crooked "
			"paths? How many best families were worst "
			"families and how many good people were bad "
			"people? When you added them all up and then "
			"subtracted, you might be left with only the "
			"children, and perhaps with Albert Einstein and "
			"an old violinist or sculptor somewhere."
		},
		.len = 512
	},
	.ciphertext = {
		.data = {
			0x8B, 0x4D, 0xDA, 0x1B, 0xCF, 0x04, 0xA0, 0x31,
			0xB4, 0xBF, 0xBD, 0x68, 0x43, 0x20, 0x7E, 0x76,
			0xB1, 0x96, 0x8B, 0xA2, 0x7C, 0xA2, 0x83, 0x9E,
			0x39, 0x5A, 0x2F, 0x7E, 0x92, 0xB4, 0x48, 0x1A,
			0x3F, 0x6B, 0x5D, 0xDF, 0x52, 0x85, 0x5F, 0x8E,
			0x42, 0x3C, 0xFB, 0xE9, 0x1A, 0x24, 0xD6, 0x08,
			0xDD, 0xFD, 0x16, 0xFB, 0xE9, 0x55, 0xEF, 0xF0,
			0xA0, 0x8D, 0x13, 0xAB, 0x81, 0xC6, 0x90, 0x01,
			0xB5, 0x18, 0x84, 0xB3, 0xF6, 0xE6, 0x11, 0x57,
			0xD6, 0x71, 0xC6, 0x3C, 0x3F, 0x2F, 0x33, 0xEE,
			0x24, 0x42, 0x6E, 0xAC, 0x0B, 0xCA, 0xEC, 0xF9,
			0x84, 0xF8, 0x22, 0xAA, 0x60, 0xF0, 0x32, 0xA9,
			0x75, 0x75, 0x3B, 0xCB, 0x70, 0x21, 0x0A, 0x8D,
			0x0F, 0xE0, 0xC4, 0x78, 0x2B, 0xF8, 0x97, 0xE3,
			0xE4, 0x26, 0x4B, 0x29, 0xDA, 0x88, 0xCD, 0x46,
			0xEC, 0xAA, 0xF9, 0x7F, 0xF1, 0x15, 0xEA, 0xC3,
			0x87, 0xE6, 0x31, 0xF2, 0xCF, 0xDE, 0x4D, 0x80,
			0x70, 0x91, 0x7E, 0x0C, 0xF7, 0x26, 0x3A, 0x92,
			0x4F, 0x18, 0x83, 0xC0, 0x8F, 0x59, 0x01, 0xA5,
			0x88, 0xD1, 0xDB, 0x26, 0x71, 0x27, 0x16, 0xF5,
			0xEE, 0x10, 0x82, 0xAC, 0x68, 0x26, 0x9B, 0xE2,
			0x6D, 0xD8, 0x9A, 0x80, 0xDF, 0x04, 0x31, 0xD5,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x61, 0x1C, 0x42, 0x10, 0x76,
			0x73, 0x02, 0x42, 0xC9, 0x23, 0x18, 0x8E, 0xB4,
			0x6F, 0xB4, 0xA3, 0x54, 0x6E, 0x88, 0x3B, 0x62,
			0x7C, 0x02, 0x8D, 0x4C, 0x9F, 0xC8, 0x45, 0xF4,
			0xC9, 0xDE, 0x4F, 0xEB, 0x22, 0x83, 0x1B, 0xE4,
			0x49, 0x37, 0xE4, 0xAD, 0xE7, 0xCD, 0x21, 0x54,
			0xBC, 0x1C, 0xC2, 0x04, 0x97, 0xB4, 0x10, 0x61,
			0xF0, 0xE4, 0xEF, 0x27, 0x63, 0x3A, 0xDA, 0x91,
			0x41, 0x25, 0x62, 0x1C, 0x5C, 0xB6, 0x38, 0x4A,
			0x88, 0x71, 0x59, 0x5A, 0x8D, 0xA0, 0x09, 0xAF,
			0x72, 0x94, 0xD7, 0x79, 0x5C, 0x60, 0x7C, 0x8F,
			0x4C, 0xF5, 0xD9, 0xA1, 0x39, 0x6D, 0x81, 0x28,
			0xEF, 0x13, 0x28, 0xDF, 0xF5, 0x3E, 0xF7, 0x8E,
			0x09, 0x9C, 0x78, 0x18, 0x79, 0xB8, 0x68, 0xD7,
			0xA8, 0x29, 0x62, 0xAD, 0xDE, 0xE1, 0x61, 0x76,
			0x1B, 0x05, 0x16, 0xCD, 0xBF, 0x02, 0x8E, 0xA6,
			0x43, 0x6E, 0x92, 0x55, 0x4F, 0x60, 0x9C, 0x03,
			0xB8, 0x4F, 0xA3, 0x02, 0xAC, 0xA8, 0xA7, 0x0C,
			0x1E, 0xB5, 0x6B, 0xF8, 0xC8, 0x4D, 0xDE, 0xD2,
			0xB0, 0x29, 0x6E, 0x40, 0xE6, 0xD6, 0xC9, 0xE6,
			0xB9, 0x0F, 0xB6, 0x63, 0xF5, 0xAA, 0x2B, 0x96,
			0xA7, 0x16, 0xAC, 0x4E, 0x0A, 0x33, 0x1C, 0xA6,
			0xE6, 0xBD, 0x8A, 0xCF, 0x40, 0xA9, 0xB2, 0xFA,
			0x63, 0x27, 0xFD, 0x9B, 0xD9, 0xFC, 0xD5, 0x87,
			0x8D, 0x4C, 0xB6, 0xA4, 0xCB, 0xE7, 0x74, 0x55,
			0xF4, 0xFB, 0x41, 0x25, 0xB5, 0x4B, 0x0A, 0x1B,
			0xB1, 0xD6, 0xB7, 0xD9, 0x47, 0x2A, 0xC3, 0x98,
			0x6A, 0xC4, 0x03, 0x73, 0x1F, 0x93, 0x6E, 0x53,
			0x19, 0x25, 0x64, 0x15, 0x83, 0xF9, 0x73, 0x2A,
			0x74, 0xB4, 0x93, 0x69, 0xC4, 0x72, 0xFC, 0x26,
			0xA2, 0x9F, 0x43, 0x45, 0xDD, 0xB9, 0xEF, 0x36,
			0xC8, 0x3A, 0xCD, 0x99, 0x9B, 0x54, 0x1A, 0x36,
			0xC1, 0x59, 0xF8, 0x98, 0xA8, 0xCC, 0x28, 0x0D,
			0x73, 0x4C, 0xEE, 0x98, 0xCB, 0x7C, 0x58, 0x7E,
			0x20, 0x75, 0x1E, 0xB7, 0xC9, 0xF8, 0xF2, 0x0E,
			0x63, 0x9E, 0x05, 0x78, 0x1A, 0xB6, 0xA8, 0x7A,
			0xF9, 0x98, 0x6A, 0xA6, 0x46, 0x84, 0x2E, 0xF6,
			0x4B, 0xDC, 0x9B, 0x8F, 0x9B, 0x8F, 0xEE, 0xB4,
			0xAA, 0x3F, 0xEE, 0xC0, 0x37, 0x27, 0x76, 0xC7,
			0x95, 0xBB, 0x26, 0x74, 0x69, 0x12, 0x7F, 0xF1,
			0xBB, 0xFF, 0xAE, 0xB5, 0x99, 0x6E, 0xCB, 0x0C
		},
		.len = 512
	},
	.auth_algo = RTE_CRYPTO_AUTH_SHA512_HMAC,
	.auth_key = {
		.data = {
			0x42, 0x1A, 0x7D, 0x3D, 0xF5, 0x82, 0x80, 0xF1,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x65, 0x1C, 0x42, 0x50, 0x76,
			0x9A, 0xAF, 0x88, 0x1B, 0xB6, 0x8F, 0xF8, 0x60,
			0xA2, 0x5A, 0x7F, 0x3F, 0xF4, 0x72, 0x70, 0xF1,
			0xF5, 0x35, 0x4C, 0x3B, 0xDD, 0x90, 0x65, 0xB0,
			0x47, 0x3A, 0x75, 0x61, 0x5C, 0xA2, 0x10, 0x76,
			0x9A, 0xAF, 0x77, 0x5B, 0xB6, 0x7F, 0xF7, 0x60
		},
		.len = 64
	},
	.digest = {
		.data = {
			0x5D, 0x54, 0x66, 0xC1, 0x6E, 0xBC, 0x04, 0xB8,
			0x46, 0xB8, 0x08, 0x6E, 0xE0, 0xF0, 0x43, 0x48,
			0x37, 0x96, 0x9C, 0xC6, 0x9C, 0xC2, 0x1E, 0xE8,
			0xF2, 0x0C, 0x0B, 0xEF, 0x86, 0xA2, 0xE3, 0x70,
			0x95, 0xC8, 0xB3, 0x06, 0x47, 0xA9, 0x90, 0xE8,
			0xA0, 0xC6, 0x72, 0x69, 0x05, 0xC0, 0x0D, 0x0E,
			0x21, 0x96, 0x65, 0x93, 0x74, 0x43, 0x2A, 0x1D,
			0x2E, 0xBF, 0xC2, 0xC2, 0xEE, 0xCC, 0x2F, 0x0A
		},
		.len = 64,
		.truncated_len = 32
	}
};

/** AES-128-CBC XCBC test vector */
static const struct aes_test_data aes_test_data_7 = {
	.crypto_algo = RTE_CRYPTO_CIPHER_AES_CBC,
	.cipher_key = {
		.data = {
			0xE4, 0x23, 0x33, 0x8A, 0x35, 0x64, 0x61, 0xE2,
			0x49, 0x03, 0xDD, 0xC6, 0xB8, 0xCA, 0x55, 0x7A
		},
		.len = 16
	},
	.iv = {
		.data = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
		},
		.len = 16
	},
	.plaintext = {
		.data = {
			"What a lousy earth! He wondered how many people "
			"were destitute that same night even in his own "
			"prosperous country, how many homes were "
			"shanties, how many husbands were drunk and "
			"wives socked, and how many children were "
			"bullied, abused, or abandoned. How many "
			"families hungered for food they could not "
			"afford to buy? How many hearts were broken? How "
			"many suicides would take place that same night, "
			"how many people would go insane? How many "
			"cockroaches and landlords would triumph? How "
			"many winners were losers, successes failures, "
			"and rich men poor men? How many wise guys were "
			"stupid? How many happy endings were unhappy "
			"endings? How many honest men were liars, brave "
			"men cowards, loyal men traitors, how many "
			"sainted men were corrupt, how many people in "
			"positions of trust had sold their souls to "
			"bodyguards, how many had never had souls? How "
			"many straight-and-narrow paths were crooked "
			"paths? How many best families were worst "
			"families and how many good people were bad "
			"people? When you added them all up and then "
			"subtracted, you might be left with only the "
			"children, and perhaps with Albert Einstein and "
			"an old violinist or sculptor somewhere."
		},
		.len = 512
	},
	.ciphertext = {
		.data = {
			0x8B, 0x4D, 0xDA, 0x1B, 0xCF, 0x04, 0xA0, 0x31,
			0xB4, 0xBF, 0xBD, 0x68, 0x43, 0x20, 0x7E, 0x76,
			0xB1, 0x96, 0x8B, 0xA2, 0x7C, 0xA2, 0x83, 0x9E,
			0x39, 0x5A, 0x2F, 0x7E, 0x92, 0xB4, 0x48, 0x1A,
			0x3F, 0x6B, 0x5D, 0xDF, 0x52, 0x85, 0x5F, 0x8E,
			0x42, 0x3C, 0xFB, 0xE9, 0x1A, 0x24, 0xD6, 0x08,
			0xDD, 0xFD, 0x16, 0xFB, 0xE9, 0x55, 0xEF, 0xF0,
			0xA0, 0x8D, 0x13, 0xAB, 0x81, 0xC6, 0x90, 0x01,
			0xB5, 0x18, 0x84, 0xB3, 0xF6, 0xE6, 0x11, 0x57,
			0xD6, 0x71, 0xC6, 0x3C, 0x3F, 0x2F, 0x33, 0xEE,
			0x24, 0x42, 0x6E, 0xAC, 0x0B, 0xCA, 0xEC, 0xF9,
			0x84, 0xF8, 0x22, 0xAA, 0x60, 0xF0, 0x32, 0xA9,
			0x75, 0x75, 0x3B, 0xCB, 0x70, 0x21, 0x0A, 0x8D,
			0x0F, 0xE0, 0xC4, 0x78, 0x2B, 0xF8, 0x97, 0xE3,
			0xE4, 0x26, 0x4B, 0x29, 0xDA, 0x88, 0xCD, 0x46,
			0xEC, 0xAA, 0xF9, 0x7F, 0xF1, 0x15, 0xEA, 0xC3,
			0x87, 0xE6, 0x31, 0xF2, 0xCF, 0xDE, 0x4D, 0x80,
			0x70, 0x91, 0x7E, 0x0C, 0xF7, 0x26, 0x3A, 0x92,
			0x4F, 0x18, 0x83, 0xC0, 0x8F, 0x59, 0x01, 0xA5,
			0x88, 0xD1, 0xDB, 0x26, 0x71, 0x27, 0x16, 0xF5,
			0xEE, 0x10, 0x82, 0xAC, 0x68, 0x26, 0x9B, 0xE2,
			0x6D, 0xD8, 0x9A, 0x80, 0xDF, 0x04, 0x31, 0xD5,
			0xF1, 0x35, 0x5C, 0x3B, 0xDD, 0x9A, 0x65, 0xBA,
			0x58, 0x34, 0x85, 0x61, 0x1C, 0x42, 0x10, 0x76,
			0x73, 0x02, 0x42, 0xC9, 0x23, 0x18, 0x8E, 0xB4,
			0x6F, 0xB4, 0xA3, 0x54, 0x6E, 0x88, 0x3B, 0x62,
			0x7C, 0x02, 0x8D, 0x4C, 0x9F, 0xC8, 0x45, 0xF4,
			0xC9, 0xDE, 0x4F, 0xEB, 0x22, 0x83, 0x1B, 0xE4,
			0x49, 0x37, 0xE4, 0xAD, 0xE7, 0xCD, 0x21, 0x54,
			0xBC, 0x1C, 0xC2, 0x04, 0x97, 0xB4, 0x10, 0x61,
			0xF0, 0xE4, 0xEF, 0x27, 0x63, 0x3A, 0xDA, 0x91,
			0x41, 0x25, 0x62, 0x1C, 0x5C, 0xB6, 0x38, 0x4A,
			0x88, 0x71, 0x59, 0x5A, 0x8D, 0xA0, 0x09, 0xAF,
			0x72, 0x94, 0xD7, 0x79, 0x5C, 0x60, 0x7C, 0x8F,
			0x4C, 0xF5, 0xD9, 0xA1, 0x39, 0x6D, 0x81, 0x28,
			0xEF, 0x13, 0x28, 0xDF, 0xF5, 0x3E, 0xF7, 0x8E,
			0x09, 0x9C, 0x78, 0x18, 0x79, 0xB8, 0x68, 0xD7,
			0xA8, 0x29, 0x62, 0xAD, 0xDE, 0xE1, 0x61, 0x76,
			0x1B, 0x05, 0x16, 0xCD, 0xBF, 0x02, 0x8E, 0xA6,
			0x43, 0x6E, 0x92, 0x55, 0x4F, 0x60, 0x9C, 0x03,
			0xB8, 0x4F, 0xA3, 0x02, 0xAC, 0xA8, 0xA7, 0x0C,
			0x1E, 0xB5, 0x6B, 0xF8, 0xC8, 0x4D, 0xDE, 0xD2,
			0xB0, 0x29, 0x6E, 0x40, 0xE6, 0xD6, 0xC9, 0xE6,
			0xB9, 0x0F, 0xB6, 0x63, 0xF5, 0xAA, 0x2B, 0x96,
			0xA7, 0x16, 0xAC, 0x4E, 0x0A, 0x33, 0x1C, 0xA6,
			0xE6, 0xBD, 0x8A, 0xCF, 0x40, 0xA9, 0xB2, 0xFA,
			0x63, 0x27, 0xFD, 0x9B, 0xD9, 0xFC, 0xD5, 0x87,
			0x8D, 0x4C, 0xB6, 0xA4, 0xCB, 0xE7, 0x74, 0x55,
			0xF4, 0xFB, 0x41, 0x25, 0xB5, 0x4B, 0x0A, 0x1B,
			0xB1, 0xD6, 0xB7, 0xD9, 0x47, 0x2A, 0xC3, 0x98,
			0x6A, 0xC4, 0x03, 0x73, 0x1F, 0x93, 0x6E, 0x53,
			0x19, 0x25, 0x64, 0x15, 0x83, 0xF9, 0x73, 0x2A,
			0x74, 0xB4, 0x93, 0x69, 0xC4, 0x72, 0xFC, 0x26,
			0xA2, 0x9F, 0x43, 0x45, 0xDD, 0xB9, 0xEF, 0x36,
			0xC8, 0x3A, 0xCD, 0x99, 0x9B, 0x54, 0x1A, 0x36,
			0xC1, 0x59, 0xF8, 0x98, 0xA8, 0xCC, 0x28, 0x0D,
			0x73, 0x4C, 0xEE, 0x98, 0xCB, 0x7C, 0x58, 0x7E,
			0x20, 0x75, 0x1E, 0xB7, 0xC9, 0xF8, 0xF2, 0x0E,
			0x63, 0x9E, 0x05, 0x78, 0x1A, 0xB6, 0xA8, 0x7A,
			0xF9, 0x98, 0x6A, 0xA6, 0x46, 0x84, 0x2E, 0xF6,
			0x4B, 0xDC, 0x9B, 0x8F, 0x9B, 0x8F, 0xEE, 0xB4,
			0xAA, 0x3F, 0xEE, 0xC0, 0x37, 0x27, 0x76, 0xC7,
			0x95, 0xBB, 0x26, 0x74, 0x69, 0x12, 0x7F, 0xF1,
			0xBB, 0xFF, 0xAE, 0xB5, 0x99, 0x6E, 0xCB, 0x0C
		},
		.len = 512
	},
	.auth_algo = RTE_CRYPTO_AUTH_AES_XCBC_MAC,
	.auth_key = {
		.data = {
			0x87, 0x61, 0x54, 0x53, 0xC4, 0x6D, 0xDD, 0x51,
			0xE1, 0x9F, 0x86, 0x64, 0x39, 0x0A, 0xE6, 0x59
		},
		.len = 16
	},
	.digest = {
		.data = {
			0xE0, 0xAC, 0x9A, 0xC4, 0x22, 0x64, 0x35, 0x89,
			0x77, 0x1D, 0x8B, 0x75
		},
		.len = 12,
		.truncated_len = 12
	}
};

#endif /* TEST_CRYPTODEV_AES_H_ */