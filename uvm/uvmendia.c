#include "uvmendia.h"

uint32_t get_uvm_pla_endian()
{

    return UVMPLA_ENDIAN;

}

uint32_t get_pla_uvm_endian()
{

#ifndef PLAUVM_ENDIAN

    /* Based on: https://github.com/cpredef/predef/blob/master/Endianness.md */

    union
    {

        uint32_t u_int_32;

        uint8_t  u_int_08[sizeof(uint32_t)];

    } u_int_3208;

    u_int_3208.u_int_08[0] = 0x00;
	u_int_3208.u_int_08[1] = 0x01;
	u_int_3208.u_int_08[2] = 0x02;
	u_int_3208.u_int_08[3] = 0x03;

    switch (u_int_3208.u_int_32)
    {

    case UINT32_C(0x00010203):
        return UVM_ENDIAN_BIG;
	case UINT32_C(0x03020100):
        return UVM_ENDIAN_LIL;

    default:
        return 0;

    }

#else

    return PLAUVM_ENDIAN;

#endif

}

/*---------------------------------------------------------------------------*/
/* . */

static uint16_t invert_uint16(uint16_t u)
{
    return ((u >> 8) & 0x00FF) |
           ((u << 8) & 0xFF00);
}

static uint32_t invert_uint32(uint32_t u)
{
    return ((u >> 24) & 0x000000FF) |
           ((u >> 8)  & 0x0000FF00) |
           ((u << 8)  & 0x00FF0000) |
           ((u << 24) & 0xFF000000);
}

static uint64_t invert_uint64(uint64_t u)
{
    return ((u >> 56) & 0x00000000000000FF) |
           ((u >> 40) & 0x000000000000FF00) |
           ((u >> 24) & 0x0000000000FF0000) |
           ((u >> 8)  & 0x00000000FF000000) |
           ((u << 8)  & 0x000000FF00000000) |
           ((u << 24) & 0x0000FF0000000000) |
           ((u << 40) & 0x00FF000000000000) |
           ((u << 56) & 0xFF00000000000000);
}

UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 2, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 4, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 8, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 2, value)
{
    *(uint16_t *)value = invert_uint16(*(uint16_t *)value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 4, value)
{
    *(uint32_t *)value = invert_uint32(*(uint32_t *)value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 8, value)
{
    *(uint64_t *)value = invert_uint64(*(uint64_t *)value);
}

UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 2, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 4, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 8, value)
{
    UVM_UNUSED(value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 2, value)
{
    *(uint16_t *)value = invert_uint16(*(uint16_t *)value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 4, value)
{
    *(uint32_t *)value = invert_uint32(*(uint32_t *)value);
}
UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 8, value)
{
    *(uint64_t *)value = invert_uint64(*(uint64_t *)value);
}

/*---------------------------------------------------------------------------*/
/* . */

#define PLA2UVM_ENDIAN(size, value)                                           \
do                                                                            \
{                                                                             \
switch (get_pla_uvm_endian())                                                 \
{                                                                             \
case UVM_ENDIAN_BIG:                                                          \
    UVM_END2ENDNUM_CALL(UVM_ENDIAN_BIG, UVMPLA_ENDIAN, size, value);          \
    break;                                                                    \
case UVM_ENDIAN_LIL:                                                          \
    UVM_END2ENDNUM_CALL(UVM_ENDIAN_LIL, UVMPLA_ENDIAN, size, value);          \
    break;                                                                    \
}                                                                             \
} while (0)                                                                   \

UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 2, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(PLAUVM_ENDIAN, UVMPLA_ENDIAN, 2, value);
#else
    PLA2UVM_ENDIAN(2, value);
#endif
}

UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 4, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(PLAUVM_ENDIAN, UVMPLA_ENDIAN, 4, value);
#else
    PLA2UVM_ENDIAN(4, value);
#endif
}

UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 8, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(PLAUVM_ENDIAN, UVMPLA_ENDIAN, 8, value);
#else
    PLA2UVM_ENDIAN(8, value);
#endif
}

#define UVM2PLA_ENDIAN(size, value)                                           \
do                                                                            \
{                                                                             \
switch (get_pla_uvm_endian())                                                 \
{                                                                             \
case UVM_ENDIAN_BIG:                                                          \
    UVM_END2ENDNUM_CALL(UVMPLA_ENDIAN, UVM_ENDIAN_BIG, size, value);          \
    break;                                                                    \
case UVM_ENDIAN_LIL:                                                          \
    UVM_END2ENDNUM_CALL(UVMPLA_ENDIAN, UVM_ENDIAN_LIL, size, value);          \
    break;                                                                    \
}                                                                             \
} while (0)                                                                   \

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 2, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(UVMPLA_ENDIAN, PLAUVM_ENDIAN, 2, value);
#else
    UVM2PLA_ENDIAN(2, value);
#endif
}

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 4, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(UVMPLA_ENDIAN, PLAUVM_ENDIAN, 4, value);
#else
    UVM2PLA_ENDIAN(4, value);
#endif
}

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 8, value)
{
#if defined(PLAUVM_ENDIAN)
    UVM_END2ENDNUM_CALL(UVMPLA_ENDIAN, PLAUVM_ENDIAN, 8, value);
#else
    UVM2PLA_ENDIAN(8, value);
#endif
}
