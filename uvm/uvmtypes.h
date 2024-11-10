
#ifndef UVM_TYPES_H
#define UVM_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include "uvmcompi.h"
#include "uvmendia.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UVM_BYTE
#define UVM_BYTE uint8_t
typedef UVM_BYTE uvm_byte;
#define UVM_BYTE_SZ 1
#define UVM_BYTE_MIN 0
#define UVM_BYTE_MAX UINT8_MAX
#endif

UVM_LINKAG uvm_byte pla2uvmbyte(uvm_byte);

UVM_LINKAG uvm_byte uvm2plabyte(uvm_byte);

#ifndef UVM_SBYTE
#define UVM_SBYTE int8_t
typedef UVM_BYTE uvm_sbyte;
#define UVM_SBYTE_SZ 1
#define UVM_SBYTE_MIN INT8_MIN
#define UVM_SBYTE_MAX INT8_MAX
#endif

UVM_LINKAG uvm_sbyte pla2uvmsbyte(uvm_sbyte);

UVM_LINKAG uvm_sbyte uvm2plasbyte(uvm_sbyte);

#ifndef UVM_SHORT
#define UVM_SHORT int16_t
typedef UVM_SHORT uvm_short;
#define UVM_SHORT_SZ 2
#define UVM_SHORT_MIN INT16_MIN
#define UVM_SHORT_MAX INT16_MAX
#endif

UVM_LINKAG uvm_short pla2uvmshort(uvm_short);

UVM_LINKAG uvm_short uvm2plashort(uvm_short);

#ifndef UVM_USHORT
#define UVM_USHORT uint16_t
typedef UVM_USHORT uvm_ushort;
#define UVM_USHORT_SZ 2
#define UVM_USHORT_MIN 0
#define UVM_USHORT_MAX UINT16_MAX
#endif

UVM_LINKAG uvm_ushort pla2uvmushort(uvm_ushort);

UVM_LINKAG uvm_ushort uvm2plaushort(uvm_ushort);

#ifndef UVM_INT
#define UVM_INT int32_t
typedef UVM_INT uvm_int;
#define UVM_INT_SZ 4
#define UVM_INT_MIN INT32_MIN
#define UVM_INT_MAX INT32_MAX
#endif

UVM_LINKAG uvm_int pla2uvmint(uvm_int);

UVM_LINKAG uvm_int uvm2plaint(uvm_int);

#ifndef UVM_UINT
#define UVM_UINT uint32_t
typedef UVM_UINT uvm_uint;
#define UVM_UINT_SZ 4
#define UVM_UINT_MIN 0
#define UVM_UINT_MAX UINT32_MAX
#endif

UVM_LINKAG uvm_uint pla2uvmuint(uvm_uint);

UVM_LINKAG uvm_uint uvm2plauint(uvm_uint);

#ifndef UVM_SIZE
#define UVM_SIZE uint64_t
typedef UVM_SIZE uvm_size;
#define UVM_SIZE_SZ 8
#define UVM_SIZE_MIN 0
#define UVM_SIZE_MAX UINT64_MAX
#endif

UVM_LINKAG uvm_size pla2uvmsize(uvm_size);

UVM_LINKAG uvm_size uvm2plasize(uvm_size);

UVM_LINKAG uvm_size plasz2uvmsz(size_t);

UVM_LINKAG size_t uvmsz2plasz(uvm_size);

#ifndef UVM_SSIZE
#define UVM_SSIZE int64_t
typedef UVM_SSIZE uvm_ssize;
#define UVM_SSIZE_SZ 8
#define UVM_SSIZE_MIN INT64_MIN
#define UVM_SSIZE_MAX INT64_MAX
#endif

UVM_LINKAG uvm_ssize pla2uvmssize(uvm_ssize);

UVM_LINKAG uvm_ssize uvm2plassize(uvm_ssize);

#ifdef __cplusplus
}
#endif

#endif/*UVM_TYPES_H*/
