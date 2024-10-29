
# uvm (unnamed virtual machine)

Implementation of a stack-based virtual machine written in c.

A small example in assembly:
```asm

bypush   0x80       # push the value 0x80 (128 in decimal) onto the stack (A)
bypush   0x3F       # push the value 0x3F (63 in decimal) onto the stack (B)

bysub
@#
pop A and B, subtract B from A (128 - 63),
and push the result (65) onto the stack
#@

byoutimm 0x00
@#
pop the result (65) from the stack and
write it in port 0x00
#@

```
