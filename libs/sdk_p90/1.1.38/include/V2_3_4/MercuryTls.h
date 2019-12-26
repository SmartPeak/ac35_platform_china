#ifndef __MERCURY_TLS_H__
#define __MERCURY_TLS_H__


/**
 * @brief Establish a SSL connection.
 *
 * @param [in] host: @n Specify the hostname(IP) of the SSL server
 * @param [in] port: @n Specify the SSL port of SSL server
 * @param [in] ca_crt @n Specify the root certificate which is PEM format.
 * @param [in] ca_crt_len @n Length of root certificate, in bytes.
 * @return SSL handle.
 * @see None.
 * @note None.
 */
unsigned int* mercury_ssl_establish(
            const char *host,
            unsigned short port,
            const char *ca_crt,
            size_t ca_crt_len);


/**
 * @brief Destroy the specific SSL connection.
 *
 * @param[in] handle: @n Handle of the specific connection.
 *
 * @return < 0, fail; 0, success.
 */
int mercury_ssl_destroy(unsigned int* handle);


/**
 * @brief Write data into the specific SSL connection.
 *        The API will return immediately if @len be written into the specific SSL connection.
 *
 * @param [in] fd @n A descriptor identifying a connection.
 * @param [in] buf @n A pointer to a buffer containing the data to be transmitted.
 * @param [in] len @n The length, in bytes, of the data pointed to by the @buf parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block @timeout_ms millisecond maximumly.
 * @return
   @verbatim
        < 0 : SSL connection error occur..
          0 : No any data be write into the SSL connection in @timeout_ms timeout period.
   (0, len] : The total number of bytes be written in @timeout_ms timeout period.
   @endverbatim
 * @see None.
 */
int mercury_ssl_write(unsigned int* handle, const char *buf, int len, int timeout_ms);


/**
 * @brief Read data from the specific SSL connection with timeout parameter.
 *        The API will return immediately if @len be received from the specific SSL connection.
 *
 * @param [in] fd @n A descriptor identifying a SSL connection.
 * @param [in] buf @n A pointer to a buffer to receive incoming data.
 * @param [in] len @n The length, in bytes, of the data pointed to by the @buf parameter.
 * @param [in] timeout_ms @n Specify the timeout value in millisecond. In other words, the API block @timeout_ms millisecond maximumly.
 * @return
   @verbatim
         -2 : SSL connection error occur.
         -1 : SSL connection be closed by remote server.
          0 : No any data be received in @timeout_ms timeout period.
   (0, len] : The total number of bytes be received in @timeout_ms timeout period.
   @endverbatim
 * @see None.
 */
int mercury_ssl_read(unsigned int* handle, char *buf, int len, int timeout_ms);


#endif //__MERCURY_TLS_H__
