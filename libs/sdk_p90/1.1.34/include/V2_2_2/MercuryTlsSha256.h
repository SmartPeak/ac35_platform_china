/**
 * \file sha256.h
 *
 * \brief SHA-224 and SHA-256 cryptographic hash function
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
#ifndef __MERCURY_TLS_SHA256_H__
#define __MERCURY_TLS_SHA256_H__

/**
 * \brief          SHA-256 context structure
 */
typedef struct
{
    unsigned int total[2];          /*!< number of bytes processed  */
    unsigned int state[8];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
    int is224;                  /*!< 0 => SHA-256, else SHA-224 */
}mercury_sha256_context;

/**
 * \brief          Initialize SHA-256 context
 *
 * \param ctx      SHA-256 context to be initialized
 */
void mercury_sha256_init( mercury_sha256_context *ctx );

/**
 * \brief          Clear SHA-256 context
 *
 * \param ctx      SHA-256 context to be cleared
 */
void mercury_sha256_free( mercury_sha256_context *ctx );

/**
 * \brief          Clone (the state of) a SHA-256 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void mercury_sha256_clone( mercury_sha256_context *dst,const mercury_sha256_context *src );

/**
 * \brief          SHA-256 context setup
 *
 * \param ctx      context to be initialized
 * \param is224    0 = use SHA256, 1 = use SHA224
 */
void mercury_sha256_starts( mercury_sha256_context *ctx, int is224 );

/**
 * \brief          SHA-256 process buffer
 *
 * \param ctx      SHA-256 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void mercury_sha256_update( mercury_sha256_context *ctx, const unsigned char *input,size_t ilen );

/**
 * \brief          SHA-256 final digest
 *
 * \param ctx      SHA-256 context
 * \param output   SHA-224/256 checksum result
 */
void mercury_sha256_finish( mercury_sha256_context *ctx, unsigned char output[32] );


/**
 * \brief          Output = SHA-256( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-224/256 checksum result
 * \param is224    0 = use SHA256, 1 = use SHA224
 */
void mercury_sha256( const unsigned char *input, size_t ilen,unsigned char output[32], int is224 );

#endif /* __MERCURY_TLS_SHA256_H__ */

