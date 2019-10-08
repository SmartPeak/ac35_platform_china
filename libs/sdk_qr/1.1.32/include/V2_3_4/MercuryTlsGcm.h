#ifndef __MERCURY_TLS_GCM_H__
#define __MERCURY_TLS_GCM_H__

/**
 * \file gcm.h
 *
 * \brief Galois/Counter mode for 128-bit block ciphers
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#define MBEDTLS_GCM_ENCRYPT     1
#define MBEDTLS_GCM_DECRYPT     0

#define MBEDTLS_ERR_GCM_AUTH_FAILED                       -0x0012  /**< Authenticated decryption failed. */
#define MBEDTLS_ERR_GCM_BAD_INPUT                         -0x0014  /**< Bad input parameters to function. */

/** Maximum length of any IV, in bytes */
#define MBEDTLS_MAX_IV_LENGTH      16
/** Maximum block size of any cipher, in bytes */
#define MBEDTLS_MAX_BLOCK_LENGTH   16

typedef enum {
    MBEDTLS_OPERATION_NONE = -1,
    MBEDTLS_DECRYPT = 0,
    MBEDTLS_ENCRYPT,
    MBEDTLS_OPERATION_MAX = 0x7fffffff
} mercury_operation_t;

typedef enum {
    MBEDTLS_CIPHER_ID_NONE = 0,
    MBEDTLS_CIPHER_ID_NULL,
    MBEDTLS_CIPHER_ID_AES,
    MBEDTLS_CIPHER_ID_DES,
    MBEDTLS_CIPHER_ID_3DES,
    MBEDTLS_CIPHER_ID_CAMELLIA,
    MBEDTLS_CIPHER_ID_BLOWFISH,
    MBEDTLS_CIPHER_ID_ARC4,
    MBEDTLS_CIPHER_ID_MAX = 0x7fffffff
} mercury_cipher_id_t;

typedef enum {
    MBEDTLS_CIPHER_NONE = 0,
    MBEDTLS_CIPHER_NULL,
    MBEDTLS_CIPHER_AES_128_ECB,
    MBEDTLS_CIPHER_AES_192_ECB,
    MBEDTLS_CIPHER_AES_256_ECB,
    MBEDTLS_CIPHER_AES_128_CBC,
    MBEDTLS_CIPHER_AES_192_CBC,
    MBEDTLS_CIPHER_AES_256_CBC,
    MBEDTLS_CIPHER_AES_128_CFB128,
    MBEDTLS_CIPHER_AES_192_CFB128,
    MBEDTLS_CIPHER_AES_256_CFB128,
    MBEDTLS_CIPHER_AES_128_CTR,
    MBEDTLS_CIPHER_AES_192_CTR,
    MBEDTLS_CIPHER_AES_256_CTR,
    MBEDTLS_CIPHER_AES_128_GCM,
    MBEDTLS_CIPHER_AES_192_GCM,
    MBEDTLS_CIPHER_AES_256_GCM,
    MBEDTLS_CIPHER_CAMELLIA_128_ECB,
    MBEDTLS_CIPHER_CAMELLIA_192_ECB,
    MBEDTLS_CIPHER_CAMELLIA_256_ECB,
    MBEDTLS_CIPHER_CAMELLIA_128_CBC,
    MBEDTLS_CIPHER_CAMELLIA_192_CBC,
    MBEDTLS_CIPHER_CAMELLIA_256_CBC,
    MBEDTLS_CIPHER_CAMELLIA_128_CFB128,
    MBEDTLS_CIPHER_CAMELLIA_192_CFB128,
    MBEDTLS_CIPHER_CAMELLIA_256_CFB128,
    MBEDTLS_CIPHER_CAMELLIA_128_CTR,
    MBEDTLS_CIPHER_CAMELLIA_192_CTR,
    MBEDTLS_CIPHER_CAMELLIA_256_CTR,
    MBEDTLS_CIPHER_CAMELLIA_128_GCM,
    MBEDTLS_CIPHER_CAMELLIA_192_GCM,
    MBEDTLS_CIPHER_CAMELLIA_256_GCM,
    MBEDTLS_CIPHER_DES_ECB,
    MBEDTLS_CIPHER_DES_CBC,
    MBEDTLS_CIPHER_DES_EDE_ECB,
    MBEDTLS_CIPHER_DES_EDE_CBC,
    MBEDTLS_CIPHER_DES_EDE3_ECB,
    MBEDTLS_CIPHER_DES_EDE3_CBC,
    MBEDTLS_CIPHER_BLOWFISH_ECB,
    MBEDTLS_CIPHER_BLOWFISH_CBC,
    MBEDTLS_CIPHER_BLOWFISH_CFB64,
    MBEDTLS_CIPHER_BLOWFISH_CTR,
    MBEDTLS_CIPHER_ARC4_128,
    MBEDTLS_CIPHER_AES_128_CCM,
    MBEDTLS_CIPHER_AES_192_CCM,
    MBEDTLS_CIPHER_AES_256_CCM,
    MBEDTLS_CIPHER_CAMELLIA_128_CCM,
    MBEDTLS_CIPHER_CAMELLIA_192_CCM,
    MBEDTLS_CIPHER_CAMELLIA_256_CCM,
    MBEDTLS_CIPHER_MAX = 0x7fffffff

} mercury_cipher_type_t;
typedef enum {
    MBEDTLS_MODE_NONE = 0,
    MBEDTLS_MODE_ECB,
    MBEDTLS_MODE_CBC,
    MBEDTLS_MODE_CFB,
    MBEDTLS_MODE_OFB, /* Unused! */
    MBEDTLS_MODE_CTR,
    MBEDTLS_MODE_GCM,
    MBEDTLS_MODE_STREAM,
    MBEDTLS_MODE_CCM,
    MBEDTLS_MODE_MAX = 0x7fffffff
} mercury_cipher_mode_t;

#define MBEDTLS_AES_BLOCK_SIZE          16
#define MBEDTLS_DES3_BLOCK_SIZE         8

//#if defined(MBEDTLS_AES_C)
#define MBEDTLS_CIPHER_BLKSIZE_MAX      16  /* longest used by CMAC is AES */
//#else
//#define MBEDTLS_CIPHER_BLKSIZE_MAX      8   /* longest used by CMAC is 3DES */
//#endif

/**
 * CMAC context structure - Contains internal state information only
 */
typedef struct
{
    /** Internal state of the CMAC algorithm  */
    unsigned char       state[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /** Unprocessed data - either data that was not block aligned and is still
     *  pending to be processed, or the final block */
    unsigned char       unprocessed_block[MBEDTLS_CIPHER_BLKSIZE_MAX];

    /** Length of data pending to be processed */
    size_t              unprocessed_len;
}mercury_cmac_context_t;

typedef struct
{
    /** Base Cipher type (e.g. MBEDTLS_CIPHER_ID_AES) */
    mercury_cipher_id_t cipher;

    /** Encrypt using ECB */
    int (*ecb_func)( void *ctx, mercury_operation_t mode,
                     const unsigned char *input, unsigned char *output );

    /** Encrypt using CBC */
    int (*cbc_func)( void *ctx, mercury_operation_t mode, size_t length,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );

    /** Encrypt using CFB (Full length) */
    int (*cfb_func)( void *ctx, mercury_operation_t mode, size_t length, size_t *iv_off,
                     unsigned char *iv, const unsigned char *input,
                     unsigned char *output );

    /** Encrypt using CTR */
    int (*ctr_func)( void *ctx, size_t length, size_t *nc_off,
                     unsigned char *nonce_counter, unsigned char *stream_block,
                     const unsigned char *input, unsigned char *output );

    /** Encrypt using STREAM */
    int (*stream_func)( void *ctx, size_t length,
                        const unsigned char *input, unsigned char *output );

    /** Set key for encryption purposes */
    int (*setkey_enc_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen );

    /** Set key for decryption purposes */
    int (*setkey_dec_func)( void *ctx, const unsigned char *key,
                            unsigned int key_bitlen);

    /** Allocate a new context */
    void * (*ctx_alloc_func)( void );

    /** Free the given context */
    void (*ctx_free_func)( void *ctx );

}mercury_cipher_base_t;

typedef struct {
    /** Full cipher identifier (e.g. MBEDTLS_CIPHER_AES_256_CBC) */
    mercury_cipher_type_t type;

    /** Cipher mode (e.g. MBEDTLS_MODE_CBC) */
    mercury_cipher_mode_t mode;

    /** Cipher key length, in bits (default length for variable sized ciphers)
     *  (Includes parity bits for ciphers like DES) */
    unsigned int key_bitlen;

    /** Name of the cipher */
    const char * name;

    /** IV/NONCE size, in bytes.
     *  For cipher that accept many sizes: recommended size */
    unsigned int iv_size;

    /** Flags for variable IV size, variable key size, etc. */
    int flags;

    /** block size, in bytes */
    unsigned int block_size;

    /** Base cipher information and functions */
    const mercury_cipher_base_t *base;

} mercury_cipher_info_t;

typedef struct {
    /** Information about the associated cipher */
    const mercury_cipher_info_t *cipher_info;

    /** Key length to use */
    int key_bitlen;

    /** Operation that the context's key has been initialised for */
    mercury_operation_t operation;

    /** Padding functions to use, if relevant for cipher mode */
    void (*add_padding)( unsigned char *output, size_t olen, size_t data_len );
    int (*get_padding)( unsigned char *input, size_t ilen, size_t *data_len );

    /** Buffer for data that hasn't been encrypted yet */
    unsigned char unprocessed_data[MBEDTLS_MAX_BLOCK_LENGTH];

    /** Number of bytes that still need processing */
    size_t unprocessed_len;

    /** Current IV or NONCE_COUNTER for CTR-mode */
    unsigned char iv[MBEDTLS_MAX_IV_LENGTH];

    /** IV size in bytes (for ciphers with variable-length IVs) */
    size_t iv_size;

    /** Cipher-specific context */
    void *cipher_ctx;

    /** CMAC Specific context */
    mercury_cmac_context_t *cmac_ctx;
} mercury_cipher_context_t;

/**
 * \brief          GCM context structure
 */
typedef struct {
    mercury_cipher_context_t cipher_ctx;/*!< cipher context used */
    unsigned long long HL[16];            /*!< Precalculated HTable */
    unsigned long long HH[16];            /*!< Precalculated HTable */
    unsigned long long len;               /*!< Total data length */
    unsigned long long add_len;           /*!< Total add length */
    unsigned char base_ectr[16];/*!< First ECTR for tag */
    unsigned char y[16];        /*!< Y working value */
    unsigned char buf[16];      /*!< buf working value */
    int mode;                   /*!< Encrypt or Decrypt */
}mercury_gcm_context;

/**
 * \brief           Initialize GCM context (just makes references valid)
 *                  Makes the context ready for mercury_gcm_setkey() or
 *                  mercury_gcm_free().
 *
 * \param ctx       GCM context to initialize
 */
void mercury_gcm_init( mercury_gcm_context *ctx );

/**
 * \brief           GCM initialization (encryption)
 *
 * \param ctx       GCM context to be initialized
 * \param cipher    cipher to use (a 128-bit block cipher)
 * \param key       encryption key
 * \param keybits   must be 128, 192 or 256
 *
 * \return          0 if successful, or a cipher specific error code
 */
int mercury_gcm_setkey( mercury_gcm_context *ctx,
                        mercury_cipher_id_t cipher,
                        const unsigned char *key,
                        unsigned int keybits );

/**
 * \brief           GCM buffer encryption/decryption using a block cipher
 *
 * \note On encryption, the output buffer can be the same as the input buffer.
 *       On decryption, the output buffer cannot be the same as input buffer.
 *       If buffers overlap, the output buffer must trail at least 8 bytes
 *       behind the input buffer.
 *
 * \param ctx       GCM context
 * \param mode      MBEDTLS_GCM_ENCRYPT or MBEDTLS_GCM_DECRYPT
 * \param length    length of the input data
 * \param iv        initialization vector
 * \param iv_len    length of IV
 * \param add       additional data
 * \param add_len   length of additional data
 * \param input     buffer holding the input data
 * \param output    buffer for holding the output data
 * \param tag_len   length of the tag to generate
 * \param tag       buffer for holding the tag
 *
 * \return         0 if successful
 */
int mercury_gcm_crypt_and_tag( mercury_gcm_context *ctx,
                       int mode,
                       size_t length,
                       const unsigned char *iv,
                       size_t iv_len,
                       const unsigned char *add,
                       size_t add_len,
                       const unsigned char *input,
                       unsigned char *output,
                       size_t tag_len,
                       unsigned char *tag );

/**
 * \brief           GCM buffer authenticated decryption using a block cipher
 *
 * \note On decryption, the output buffer cannot be the same as input buffer.
 *       If buffers overlap, the output buffer must trail at least 8 bytes
 *       behind the input buffer.
 *
 * \param ctx       GCM context
 * \param length    length of the input data
 * \param iv        initialization vector
 * \param iv_len    length of IV
 * \param add       additional data
 * \param add_len   length of additional data
 * \param tag       buffer holding the tag
 * \param tag_len   length of the tag
 * \param input     buffer holding the input data
 * \param output    buffer for holding the output data
 *
 * \return         0 if successful and authenticated,
 *                 MBEDTLS_ERR_GCM_AUTH_FAILED if tag does not match
 */
int mercury_gcm_auth_decrypt( mercury_gcm_context *ctx,
                      size_t length,
                      const unsigned char *iv,
                      size_t iv_len,
                      const unsigned char *add,
                      size_t add_len,
                      const unsigned char *tag,
                      size_t tag_len,
                      const unsigned char *input,
                      unsigned char *output );

/**
 * \brief           Generic GCM stream start function
 *
 * \param ctx       GCM context
 * \param mode      MBEDTLS_GCM_ENCRYPT or MBEDTLS_GCM_DECRYPT
 * \param iv        initialization vector
 * \param iv_len    length of IV
 * \param add       additional data (or NULL if length is 0)
 * \param add_len   length of additional data
 *
 * \return         0 if successful
 */
int mercury_gcm_starts( mercury_gcm_context *ctx,
                int mode,
                const unsigned char *iv,
                size_t iv_len,
                const unsigned char *add,
                size_t add_len );

/**
 * \brief           Generic GCM update function. Encrypts/decrypts using the
 *                  given GCM context. Expects input to be a multiple of 16
 *                  bytes! Only the last call before mercury_gcm_finish() can be less
 *                  than 16 bytes!
 *
 * \note On decryption, the output buffer cannot be the same as input buffer.
 *       If buffers overlap, the output buffer must trail at least 8 bytes
 *       behind the input buffer.
 *
 * \param ctx       GCM context
 * \param length    length of the input data
 * \param input     buffer holding the input data
 * \param output    buffer for holding the output data
 *
 * \return         0 if successful or MBEDTLS_ERR_GCM_BAD_INPUT
 */
int mercury_gcm_update( mercury_gcm_context *ctx,
                size_t length,
                const unsigned char *input,
                unsigned char *output );

/**
 * \brief           Generic GCM finalisation function. Wraps up the GCM stream
 *                  and generates the tag. The tag can have a maximum length of
 *                  16 bytes.
 *
 * \param ctx       GCM context
 * \param tag       buffer for holding the tag
 * \param tag_len   length of the tag to generate (must be at least 4)
 *
 * \return          0 if successful or MBEDTLS_ERR_GCM_BAD_INPUT
 */
int mercury_gcm_finish( mercury_gcm_context *ctx,
                unsigned char *tag,
                size_t tag_len );

/**
 * \brief           Free a GCM context and underlying cipher sub-context
 *
 * \param ctx       GCM context to free
 */
void mercury_gcm_free( mercury_gcm_context *ctx );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */

#endif
