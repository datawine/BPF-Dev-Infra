# Kernel eBPF program

Folder structure

```bash
./
├── include
│   ├── all.h
│   ├── asm_goto_workaround.h
│   ├── bpf_core_read.h
│   ├── bpf_endian.h
│   ├── bpf_helper_defs.h
│   ├── bpf_helpers.h
│   ├── bpf_tracing.h
│   ├── kernel.h
│   ├── LICENSE.BSD-2-Clause
│   └── vmlinux.h
├── Makefile
├── Makefile.arch
├── Makefile.ebpf
├── README.md
├── src
│   ├── helloworld
│   │   ├── main.c
│   │   └── Makefile
│   └── map-example
│       ├── main.c
│       └── Makefile
└── update.sh
```

To add a new kernel eBPF program, create a folder with eBPF programs in `*.c` and a `Makefile` in it.
The `Makefile` should look like below:

```Makefile
# Optional: The directory to which the program will be installed
# If DIR_NAME is not specified, it will create a `build` subdir under the current directory
# DIR_NAME=xxx
include ../../Makefile.arch
include ../../Makefile.ebpf
```

Either run `make` under the newly created folder (e.g., `./src/helloworld`) to just build the new program,
or run `make` under this folder (`./`) to build all kernel programs that have been updated in `./src/`.

Note that the directory of the eBPF programs does not have to be a subdirectory of `./src`,
nor do it any position requirements. 
All you need to do is to include `Makefile.arch` and `Makefile.ebpf` in the Makefile.

`make clean` works in the same way.

## Examples

- `./src/helloworld`: An example program, attached to `tracepoint/syscalls/sys_enter_execve`
- `./src/map-example`: An example program of eBPF map usage, attached to `tracepoint/syscalls/sys_enter_execve`

## Helper commands

```bash
# Check disassembling results
llvm-objdump -s -d ./build/helloworld/main.o
```

## Update header files (Optional)

`update.sh` is for updating the header files in `./include`.
These header files should be kept up with the version of libbpf and the kernel.

If nothing is wrong, do not execute it.