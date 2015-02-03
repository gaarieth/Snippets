
#import "memget.h"

uint8_t memget8(const uint8_t** p)
{
    uint8_t value = **p;
    (*p) += sizeof(value);
    return value;
}

uint16_t memget16(const uint8_t** p)
{
    uint16_t value = ntohs(*((uint16_t*) *p));
    (*p) += sizeof(value);
    return value;
}

uint32_t memget32(const uint8_t** p)
{
    uint32_t value = ntohl(*((uint32_t*) *p));
    (*p) += sizeof(value);
    return value;
}

const char* memgetNTS(const uint8_t** p)
{
    uint8_t length = **p;
    (*p) += sizeof(length);
    const char* value = (char*) *p;
    (*p) += length;
    return value;
}
