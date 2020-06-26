# Tiny Assembly Interpreter

Davide Peressoni (dp.d-@live.it)

A simple Tiny Assembler Interpreter written in C.

## Build
```
./configure
cd build
make TinyAssemblyInterpreter
```

## Usage
```
build/bin/TinyAssemblyInterpreter <file>.tas
```
If no file is passed it will read from `stdin`.

## Documentation
```
./configure
cd build
make doc
```
The documentation can be found under `build/doc`.  
The last version documentation can be consulted at [dpdmancul.gitlab.io/tiny-assembly-interpreter](https://dpdmancul.gitlab.io/tiny-assembly-interpreter)

## Test
```
./configure
cd build
make all
make test_memcheck
```

## Tiny Assembly

Examples can be found in [`examples/`](examples/).

### Comments
Comments start by a semicolon and end with new line:
```asm
; this is a comment
```

### Sections
`.data` starts the section where is defined the allocation (and possible initialization) of data.  
`.text` starts the section of instructions to be executed.

### Labels
A label is defined with its name followed by a colon:
```asm
example_label:
  add 1
```

### Instruction set
Used inside `.text`

| Mnemonic | Meaning |
|-|-|
| `get`   | Reads an integer from keyboard and stores it in memory. |
| `put`   | Prints an integer from operand. |
| `load`  | Loads the operand in the accumulator. |
| `store` | Stores accumulator in memory. |
| `add`   | Adds the operand to accumulator. |
| `sub`   | Subtracts the operand from the accumulator. |
| `mul`   | Multiplies the accumulator by the operand. |
| `div`   | Divides the accumulator by the operand. |
| `jmp`   | Jumps to operand. |
| `jne`   | Jumps to operand if accumulator is negative. |
| `jze`   | Jumps to operand if accumulator is zero. |
| `jpo`   | Jumps to operand if accumulator is positive. |
| `alt`   | Stops the execution. |
| `getC`  | Reads a char from keyboard and store it in memory. |
| `putC`  | Prints a char from operand. |
| `putS`  | Prints a string from memory. |

All instructions accepts a label as operand:
```asm
jmp end ; jumps to end label
```

`put`, `load`, `add`, `sub`, `mul`, `div`, `putc` can accept a literal as operand:
```asm
load 100
add 0x20
sub 'a'
```

### Integer sizes
When a label pointing to an integer is specified as operand, you must append the integer size to the mnemonic.

| Symbol | Size |
|-|-|
| `B` | Byte. |
| `H` | Half word. |
| `W` | Word. |
| `L` | Long word. |

```asm
getW n
loadW n
```

### Declare data
Inside `.data` you can allocate with:

| Mnemonic | Meaning |
|-|-|
| `new`  | Allocate an integer. |
| `newC` | Allocate a char. |
| `newS` | Allocate a string. |

To allocate an integer you must specify the size.

After allocation mnemonic you can insert the initial value.  
Strings must be initialized.

```asm
newH    ; new Half word integer
newB 12 ; new Byte initialized at 12

newC     ; new char
newC 'a' ; new char initialized at 'a'

newS "example" ; new string
```
