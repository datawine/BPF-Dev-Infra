# Userspace Loader (datadog/ebpf-manager)

Reference: https://github.com/DataDog/ebpf-manager

This directory is for test usage and validation of eBPF program loader.

```bash
# Run script with copying files from ../../kernel/build/helloworld/main.o to ./kernel/kernel.o
sh run.sh ../../kernel/build/helloworld/main.o

# Run script directly with ./kernel/kernel.o, without copying files
sh run.sh
```