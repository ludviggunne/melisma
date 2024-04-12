#include <melisma/int.h>

uint32_t read_u32_be(void *ptr)
{
    unsigned char *_ptr = ptr;
    return ((_ptr[0] & 255) << 24) | ((_ptr[1] & 255) << 16) |
        ((_ptr[2] & 255) << 8) | (_ptr[3] & 255);
}

uint16_t read_u16_be(void *ptr)
{
    unsigned char *_ptr = ptr;
    return ((_ptr[0] & 255) << 8) | (_ptr[1] & 255);
}

uint32_t read_u32_le(void *ptr)
{
    unsigned char *_ptr = ptr;
    return ((_ptr[3] & 255) << 24) | ((_ptr[2] & 255) << 16) |
        ((_ptr[1] & 255) << 8) | (_ptr[0] & 255);
}

uint16_t read_u16_le(void *ptr)
{
    unsigned char *_ptr = ptr;
    return ((_ptr[1] & 255) << 8) | (_ptr[0] & 255);
}
