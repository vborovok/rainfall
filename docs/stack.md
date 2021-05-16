# Stack in x86

**ESP** - _extended stack pointer_ - holds the top of stack

**EBP** - _extended base pointer_ - moved by programmer to a particular place on the stack, so that data can on the 
stack can be read from and written to using base index addressing

**EAX** - _extended AX_ -  a 32-bit general-purpose register with two common uses: to store the return value of a 
function and as a special register for certain calculations. Therefore, if you see the EAX register used immediately
after a function call, you are probably seeing the code manipulate the return value.

**EIP** - _extended instruction pointer/program counter_ -  is a register that contains the memory address of the next
instruction to be executed for a program. EIP’s only purpose is to tell the processor what to do next.


  ```
                   +-----+ 
  high address     |_____|   <- Bottom (origin) of the stack
                   |_____|
                   |_____|
                   |_____|
                   |_____|  <- Top of the stack (ESP)
                   |     |
                   |     | 
  low address      |  |  |
                   |  V  |
                      
                  stack grows
                                                               Stack figure 
  ```

### FLAGS

**ZF** - The zero flag is set when the result of an operation is equal to zero; otherwise, it is cleared.

**CF** - The carry flag is set when the result of an operation is too large or too small for the destination operand; 
otherwise, it is cleared.

**SF** - The sign flag is set when the result of an operation is negative or cleared when the result is positive. 
This flag is also set when the most sig-nificant bit is set after an arithmetic operation.

**TF** - The trap flag is used for debugging. 
The x86 processor will execute only one instruction at a time if this flag is set.


### SIMPLE INSTRUCTIONS

**mov** - move data from one location to another.  In other words, it’s the instruction for reading and writing 
to memory. The mov instruction can move data into registers or RAM. The format is mov _**destination, source**_
(Intel syntax) or _**source, destination**_ (AT&T syntax)

|Instruction | Description|
|---|---|
| mov ebx, eax | Copies the contents of EBX into the EAX register
| mov 0x42, eax | Copies the value 0x42 in the EAX
| mov [0x4037C4], eax | Copies the 4 bytes at the memory location 0x4037C4 into the EAX register
| mov [ebx], eax | Copies the 4 bytes at the memory location specified by the EBX register into the EAX register
| mov [ebx+esi*4], eax | Copies the 4 bytes at the memory location specified by the result of the equation `ebx+esi*4` into the EAX register


**lea** - "load effective address" - instruction is used to put a memory address into the destination

_EBX register used to access memory:_

|Registers|Addresses|Memory
|---|---|---|
| EAX = 0x00000000 | - | -
| EBX = 0x00B30040 | 0x00B30040 | 0x00000000
|-|0x00B30044| 0x63676862
|-|0x00B30048| 0x00000020
|-|0x00B3004C| 0x41414141

`lea eax, [ebx+8]` places the value 0xB30048 into EAX

`mov eax, [ebx+8]` places the value 0x20 (obtained from memory) into EAX

The lea instruction is not used exclusively to refer to memory addresses.
`lea ebx, [eax*5+5]`, where eax is a number, rather than a memory address. This instruction is the functional equivalent of ebx = (eax+1)*5

#### Arithmetic

Addition and subtraction:

The format of the addition instruction is _**add destination, value.**_

The format of the subtraction instruction is _**sub destination, value.**_
The sub instruction modifies two important flags: **the zero flag (ZF)** and **carry flag (CF)**. The ZF is set if the result is zero, and CF is set if the destination is less than the value subtracted.

_Addition and Subtraction instruction examples:_

|Instruction | Description|
|---|---|
| sub eax, 0x10 | Subtracts 0x10 from EAX
| add eax, ebx | Adds EBX to EAX and store the result into EAX
| inc edx | Increments EDX by 1 
| dec ecx | Decrements ECX by 1

Multiplication and division:

Multiplication and division both act on a predefined register (EAX and EDX). The assignment of the register on which a mul or div instruction acts can occur many instructions earlier.

Format of the mul and div instructions: _**mul value**_

The _**mul value**_ instruction always multiplies EAX by value. Therefore, EAX must be set up appropriately before the multiplication occurs. The result is stored as a 64-bit value across two registers: EDX and EAX. EDX stores the most significant 32 bits of the operations, and EAX stores the least significant 32 bits.

The _**div value**_ instruction does the same thing as mul, except in the oppo-site direction: It divides the 64 bits across EDX and EAX by value. There-fore, the EDX and EAX registers must be set up appropriately before the divi-sion occurs. The result of the division operation is stored in EAX, and the remainder is stored in EDX.

|Instruction | Description|
|---|---|
| mul 0x50 | Multiplies EAX by 0x50 and stores the result in EDX:EAX
| div 0x75 | Divides EDX:EAX by 0x75 and stores the result in EAX and the remainder in EDX

#### Common Logical and Shifting Arithmetic Instructions

|Instruction | Description|
|---|---|
| xor eax, eax | Clears the EAX register
| or eax, 0x7575 | Performs the logical or operation on EAX with 0x7575
| mov eax, 0xA <br> shl eax, 2| Shifts the EAX register to the left 2 bits; these two instructions result in EAX = 0x28, because 1010 (0xA in binary) shifted 2 bits left is 101000 (0x28)
| mov bl, 0xA <br> ror bl, 2 | Rotates the BL register to the right 2 bits; these two instructions result in BL = 10000010, because 1010 rotated 2 bits right is 10000010

#### NOP

Does nothing. When it’s issued, execution simply proceeds to the next instruction.