#ifndef __CBOR_DEFINE_H__
#define __CBOR_DEFINE_H__

#include "list.h"

#ifdef __FreeBSD__
#include <sys/endian.h>
#endif

#define __MBED__
#ifdef __MBED__
#define ntohs(a) ((uint16_t)(((((uint16_t)(a)) & 0xff) << 8) | (((uint16_t)(a)) & 0xff00) >> 8))
#define htons(a) ntohs(a)
#define ntohl(a)                                                                                 \
((uint32_t)(((((uint32_t)(a)) & 0x000000ff) << 24) | ((((uint32_t)(a)) & 0x0000ff00) << 8) | \
             ((((uint32_t)(a)) & 0x00ff0000) >> 8) | ((((uint32_t)(a)) & 0xff000000) >> 24)))
#define htonl(a) ntohl(a)
#define ntohll(a)                                                                                 \
((uint64_t)(((((uint64_t)(a)) & 0x00000000000000ff) << 56) | ((((uint64_t)(a)) & 0x000000000000ff00) << 40) | \
            ((((uint64_t)(a)) & 0x0000000000ff0000) << 24) | ((((uint64_t)(a)) & 0x00000000ff000000) << 8) | \
            ((((uint64_t)(a)) & 0x000000ff00000000) >> 8) | ((((uint64_t)(a)) & 0x0000ff0000000000) >> 24) | \
            ((((uint64_t)(a)) & 0x00ff000000000000) >> 40) | ((((uint64_t)(a)) & 0xff00000000000000) >> 56)))
#define htonll(a) ntohll(a)

#endif	// __MBED__

#define htobe16(x) htons(x)
#define htobe32(x) htonl(x)
#define htobe64(x) htonll(x)
#define be16toh(x) ntohs(x)
#define be32toh(x) ntohl(x)
#define be64toh(x) ntohll(x)

#ifdef _WIN32
// #include <winsock2.h>
#define strncasecmp(s, u, l) strnicmp(s, u, l)
#define strcasecmp(s, u) stricmp(s, u)
#endif


#ifdef USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param expr If expr is false, it calls assert_failed function which reports
 *         the name of the source file and the source line number of the call
 *         that failed. If expr is true, it returns no value.
 */
#define assert(expr) ((expr) ? (void)0 : _failed((const uint8_t*)#expr, (const uint8_t*)__FILE__, __LINE__))

void _failed(const uint8_t* expr, const uint8_t* file, uint32_t line);
#else
#define assert(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


/* Major Types */
typedef enum {
    CBOR_TYPE_UINT = 0,
    CBOR_TYPE_NEGINT,
    CBOR_TYPE_BYTESTRING,
    CBOR_TYPE_STRING,
    CBOR_TYPE_ARRAY,
    CBOR_TYPE_MAP,
    CBOR_TYPE_TAG,
    CBOR_TYPE_SIMPLE,

    CBOR__TYPE_PAIR,
} cbor_type;

typedef enum {
    CBOR_SIMPLE_NONE = 0,
    CBOR_SIMPLE_FALSE = 20,
    CBOR_SIMPLE_TRUE = 21,
    CBOR_SIMPLE_NULL = 22,
    CBOR_SIMPLE_UNDEF = 23,
    CBOR_SIMPLE_EXTENSION = 24,
    CBOR_SIMPLE_REAL = 25,
} cbor_simple;

#pragma anon_unions

struct _cbor_value {
    cbor_type type;
    union {
        struct {
            size_t allocated;
            size_t length;
            char *ptr;
        } blob;
        struct {
            struct _cbor_value *key;
            struct _cbor_value *value;
        } pair;
        struct {
            unsigned long long item;
            struct _cbor_value *content;
        } tag;
        struct {
            double real;
            cbor_simple ctrl;
        } simple;
        unsigned long long uint;
        list_head(_cbor_cname, _cbor_value) container;
    };
    list_entry(_cbor_value) entry;
    struct _cbor_value *parent;
};

struct _cbor_value *cbor_create(cbor_type type);
#endif  /* !__CBOR_DEFINE_H__ */
