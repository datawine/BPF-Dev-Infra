# kernel eBPF program

Folder structure

```bash
├── build
│   └── helloworld
│       └── main.o
├── include
│   ├── all.h
│   ├── asm_goto_workaround.h
│   ├── bpf_endian.h
│   ├── bpf_helper_defs.h
│   ├── bpf_helpers.h
│   ├── bpf_tracing.h
│   └── kernel.h
├── Makefile
├── Makefile.arch
├── Makefile.ebpf
├── README.md
└── src
    └── helloworld
        ├── main.c
        └── Makefile
```

To add a new kernel eBPF program, add a folder under `./src/` with `*.c` and a `Makefile` in it, like `./src/helloworld`
The `Makefile` should look like below:

```Makefile
# The dir to which the program will be installed
include ../../Makefile.arch
include ../../Makefile.ebpf
```

Either run `make` under the newly created folder (e.g., `./src/helloworld`) to just build the new program,
or run `make` under this folder (`./`) to build all kernel programs that have been updated.

Set install directory with BUILD_DIR variable.

`make clean` works in the same way.

## Helper commands

```bash
# Check disassembling results
llvm-objdump -s -d ./build/helloworld/main.o
```
