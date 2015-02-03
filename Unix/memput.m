
#import "memput.h"

uint8_t* memput8(uint8_t* buffer, uint8_t value)
{
    memcpy(buffer, &value, sizeof(value));
    return buffer + sizeof(value);
}

uint8_t* memput16(uint8_t* buffer, uint16_t value)
{
    value = htons(value);
    memcpy(buffer, &value, sizeof(value));
    return buffer + sizeof(value);
}

uint8_t* memput32(uint8_t* buffer, uint32_t value)
{
    value = htonl(value);
    memcpy(buffer, &value, sizeof(value));
    return buffer + sizeof(value);
}

uint8_t* memputNTS(uint8_t* buffer, const char* value)
{
    if (value == 0)
        value = "";
    uint8_t length = strlen(value) + 1;
    memcpy(buffer, &length, sizeof(length));
    buffer += sizeof(length);
    memcpy(buffer, value, length - 1);
    buffer[length - 1] = 0;
    return buffer + length;
}
