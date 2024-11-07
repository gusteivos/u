
#ifndef UVMENDIA_H
#define UVMENDIA_H

#include <stdint.h>
#include "uvmcompi.h"

#define UVM_ENDIAN_BIG 1234
#define UVM_ENDIAN_LIL 4321

#ifndef UVMPLA_ENDIAN
    #define UVMPLA_ENDIAN UVM_ENDIAN_BIG
#endif

#ifndef PLAUVM_ENDIAN
/*  #define PLAUVM_ENDIAN UVM_ENDIAN_LIL */
#endif

UVM_LINKAG uint32_t get_uvm_pla_endian(void);

UVM_LINKAG uint32_t get_pla_uvm_endian(void);

/*---------------------------------------------------------------------------*/
/* . */

#define UVM_END2ENDNUM(endian0, endian1, size)                                \
_uvm_##endian0##2##endian1##size

#define UVM_END2ENDNUM_DEFI(endian0, endian1, size, value)                    \
void UVM_END2ENDNUM(endian0, endian1, size)(void *value)

#define UVM_END2ENDNUM_CALL(endian0, endian1, size, value)                    \
UVM_END2ENDNUM(endian0, endian1, size)(value)

UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 2, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 4, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_BIG, 8, value);

UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 2, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 4, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_BIG, UVM_ENDIAN_LIL, 8, value);

UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 2, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 4, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_LIL, 8, value);

UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 2, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 4, value);
UVM_LINKAG UVM_END2ENDNUM_DEFI(UVM_ENDIAN_LIL, UVM_ENDIAN_BIG, 8, value);

/*---------------------------------------------------------------------------*/
/* . */

#define UVM_SWAP_FROM2TONUM(from, to, size)                                   \
swap_##from##2##to##size

#define UVM_SWAP_FROM2TONUM_DEFI(from, to, size, value)                       \
void UVM_SWAP_FROM2TONUM(from, to, size)(void *value)                         \

#define UVM_SWAP_FROM2TONUM_CALL(from, to, size, value)                       \
UVM_SWAP_FROM2TONUM(from, to, size)(value)                                    \

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 2, value); /*swap_pla2uvm2*/

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 4, value); /*swap_pla2uvm4*/

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(pla, uvm, 8, value); /*swap_pla2uvm8*/

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 2, value); /*swap_uvm2pla2*/

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 4, value); /*swap_uvm2pla4*/

UVM_LINKAG UVM_SWAP_FROM2TONUM_DEFI(uvm, pla, 8, value); /*swap_uvm2pla8*/

#endif/*UVMENDIA_H*/
