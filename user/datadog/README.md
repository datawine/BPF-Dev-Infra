# Userspace Loader (datadog/ebpf-manager)

Reference: https://github.com/DataDog/ebpf-manager

This directory is for test usage and validation of eBPF program loader.

## Basic Requirements

- golang

## Usage

Run script with copying files from `../../kernel/src/helloworld/build/main.o` to `./kernel/kernel.o`.

```bash
mkdir
sh run.sh ../../kernel/src/helloworld/build/main.o
```

Run script directly with `./kernel/kernel.o`, without copying files.
```bash
sh run.sh
```