#ifndef __MERCURY_TLS_AES_H__
#define __MERCURY_TLS_AES_H__


#define MBEDTLS_AES_ENCRYPT     1
#define MBEDTLS_AES_DECRYPT     0

#define MBEDTLS_ERR_AES_INVALID_KEY_LENGTH                -0x0020  /**< Invalid key length. */
#define MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH              -0x0022  /**< Invalid data input length. */

/**
 * \brief          AES context structure
 *
 * \note           buf is able to hold 32 extra bytes, which can be used:
 *                 - for alignment purposes if VIA padlock is used, and/or
 *                 - to simplify key expansion in the 256-bit case by
 *                 generating an extra round key
 */
typedef struct
{
    int nr;                     /*!<  number of rounds  */
    unsigned int *rk;               /*!<  AES round keys    */
    unsigned int buf[68];           /*!<  unaligned data    */
}mercury_aes_context;

/**
 * \brief          Initialize AES context
 *
 * \param ctx      AES context to be initialized
 */
void mercury_aes_init( mercury_aes_context *ctx );

/**
 * \brief          Clear AES context
 *
 * \param ctx      AES context to be cleared
 */
void mercury_aes_free( mercury_aes_context *ctx );

/**
 * \brief          AES key schedule (encryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      encryption key
 * \param keybits  must be 128, 192 or 256
 *
 * \return         0 if successful, or MBEDTLS_ERR_AES_INVALID_KEY_LENGTH
 */
int mercury_aes_setkey_enc( mercury_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );

/**
 * \brief          AES key schedule (decryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      decryption key
 * \param keybits  must be 128, 192 or 256
 *
 * \return         0 if successful, or MBEDTLS_ERR_AES_INVALID_KEY_LENGTH
 */
int mercury_aes_setkey_dec( mercury_aes_context *ctx, const unsigned char *key,unsigned int keybits );

/**
 * \brief          AES-ECB block encryption/decryption
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 *
 * \return         0 if successful
 */
int mercury_aes_crypt_ecb( mercury_aes_context *ctx,int mode,const unsigned char input[16],unsigned char output[16] );

/**
 * \brief          AES-CBC buffer encryption/decryption
 *                 Length should be a multiple of the block
 *                 size (16 bytes)
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful, or MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH
 */
int mercury_aes_crypt_cbc( mercury_aes_context *ctx,int mode,size_t length,unsigned char iv[16],
                                                                const unsigned char *input,unsigned char *output );

/**
 * \brief          AES-CFB128 buffer encryption/decryption.
 *
 * Note: Due to the nature of CFB you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * mercury_aes_setkey_enc() for both MBEDTLS_AES_ENCRYPT and MBEDTLS_AES_DECRYPT.
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param length   length of the input data
 * \param iv_off   offset in IV (updated after use)
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful
 */
int mercury_aes_crypt_cfb128( mercury_aes_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief          AES-CFB8 buffer encryption/decryption.
 *
 * Note: Due to the nature of CFB you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * mercury_aes_setkey_enc() for both MBEDTLS_AES_ENCRYPT and MBEDTLS_AES_DECRYPT.
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     MBEDTLS_AES_ENCRYPT or MBEDTLS_AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful
 */
int mercury_aes_crypt_cfb8( mercury_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );

/**
 * \brief               AES-CTR buffer encryption/decryption
 *
 * Warning: You have to keep the maximum use of your counter in mind!
 *
 * Note: Due to the nature of CTR you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * mercury_aes_setkey_enc() for both MBEDTLS_AES_ENCRYPT and MBEDTLS_AES_DECRYPT.
 *
 * \param ctx           AES context
 * \param length        The length of the data
 * \param nc_off        The offset in the current stream_block (for resuming
 *                      within current cipher stream). The offset pointer to
 *                      should be 0 at the start of a stream.
 * \param nonce_counter The 128-bit nonce and counter.
 * \param stream_block  The saved stream-block for resuming. Is overwritten
 *                      by the function.
 * \param input         The input data stream
 * \param output        The output data stream
 *
 * \return         0 if successful
 */
int mercury_aes_crypt_ctr( mercury_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief           Deprecated internal AES block encryption function
 *                  without return value.
 *
 * \deprecated      Superseded by mercury_aes_encrypt_ext() in 2.5.0
 *
 * \param ctx       AES context
 * \param input     Plaintext block
 * \param output    Output (ciphertext) block
 */
void mercury_aes_encrypt( mercury_aes_context *ctx,const unsigned char input[16],unsigned char output[16] );

/**
 * \brief           Deprecated internal AES block decryption function
 *                  without return value.
 *
 * \deprecated      Superseded by mercury_aes_decrypt_ext() in 2.5.0
 *
 * \param ctx       AES context
 * \param input     Ciphertext block
 * \param output    Output (plaintext) block
 */
void mercury_aes_decrypt( mercury_aes_context *ctx,const unsigned char input[16],unsigned char output[16] );

#endif //__MERCURY_TLS_AES_H__
