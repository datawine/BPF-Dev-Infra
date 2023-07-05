# BPF-Dev-Infra v1.0

This is the eBPF development infrastructure.

## Basic Requirements

- common libraries: libelf1 libelf-dev zlib1g-dev gcc-multilib 
- compiler, linker, etc.: clang, llc, opt, llvm-dis, llvm-objdump
- manually installed library: libbpf
- manually installed tools: bpftool

## Installation

### Dependencies

Installation of dependencies.

```bash
sudo apt install libelf1 libelf-dev zlib1g-dev

# For error: /usr/include/linux/types.h:5:10: fatal error: 'asm/types.h' file not found
sudo apt install gcc-multilib 
```

Install clang-14, llc-14, opt-14, llvm-dis-14, llvm-objdump-14

```bash
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" -- 14
```


### Manual Installation for libbpf and bpftool

Installation for `libbpf`(v1.2.0) and `bpftool`(v7.2.0).

```bash
# Note: Update w/o recursive option
git submodule update --init

# Create symbolic link instead of download submodule again
rm -r ./bpftool/libbpf/ && ln -s $(realpath ./libbpf) $(realpath ./bpftool)

# Install libbpf
cd ./libbpf/src && make && sudo make install && cd -

# Instal bpftool
cd ./bpftool/src && make && sudo make install && cd -
```

Which should install the following:

```bash
# >>>>>>>>>>>>>> for libbpf
  ...
  INSTALL  bpf.h libbpf.h btf.h libbpf_common.h libbpf_legacy.h bpf_helpers.h bpf_helper_defs.h bpf_tracing.h bpf_endian.h bpf_core_read.h skel_internal.h libbpf_version.h usdt.bpf.h
  INSTALL  ./libbpf.pc
  INSTALL  ./libbpf.a ./libbpf.so ./libbpf.so.1 ./libbpf.so.1.2.0

# >>>>>>>>>>>>>> for bpftool
  ...
  INSTALL  bpftool
```

### Generate vmlinux.h (Optional)

```bash
bpftool btf dump file /sys/kernel/btf/vmlinux format c > ./kernel/include/vmlinux.h
```

## Usage

- [Kernel eBPF compilation](./kernel/README.md)
- [User space eBPF loader](./user/README.md)