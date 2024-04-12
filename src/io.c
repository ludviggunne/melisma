#include <melisma/io.h>

void fprint_u16_be(FILE *f, uint16_t v)
{
    fputc((v >> 8) & 255, f);
    fputc(v & 255, f);
}

void fprint_u32_be(FILE *f, uint32_t v)
{
    fputc((v >> 24) & 255, f);
    fputc((v >> 16) & 255, f);
    fputc((v >> 8) & 255, f);
    fputc(v & 255, f);
}
