# TestSuite

## Building

From the `TestSuite` directory:

```bash
mkdir build
cd build
cmake ..
make
```

## Running tests

```bash
cd build
./tests
```

## What does it test

The test suite validates the Core Wars game logic:

- **Parser** - parsing warrior instructions and arithmetic operations
- **Operators** - all warlock operators (add, sub, mul, div, mod, cmp, mov, jmp, jmz, jmn, djn, slt, dat)
- **Code loading** - loading warrior code into the core
- **Instruction copying** - deep copying of instructions
- **Parameter copying** - deep copying of instruction parameters
- **Default modifiers** - setting default modifier flags on instructions
