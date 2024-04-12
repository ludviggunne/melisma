#include <melisma/stream_parser.h>
#include <melisma/int.h>

uint32_t stream_read_u32_be(void **data)
{

    uint32_t v = read_u32_be(*data);
    (*(uint32_t **) data)++;
    return v;
}

uint16_t stream_read_u16_be(void **data)
{
    uint16_t v = read_u16_be(*data);
    (*(uint16_t **) data)++;
    return v;
}

uint32_t stream_read_u32_le(void **data)
{
    uint32_t v = read_u32_le(*data);
    (*(uint32_t **) data)++;
    return v;
}

uint16_t stream_read_u16_le(void **data)
{
    uint16_t v = read_u16_le(*data);
    (*(uint16_t **) data)++;
    return v;
}

char *stream_read_id(void **data)
{
    char *_data = *data;
    (*(char **) data) += 4;
    return _data;
}
