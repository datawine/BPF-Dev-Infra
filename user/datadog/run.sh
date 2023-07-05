#!/bin/sh

if [ -z "$1" ]; then
    echo "Directly loading ./kernel/kernel.o"
else
    # Copy file to ./kernel/kernel.o
    echo "Copying " $1 " to ./kernel/kernel.o"
    cp $1 ./kernel/kernel.o
fi

# if [ ! -f "go.sum" ]; then
#     echo "Generating go module"
#     go mod tidy
# else
#     echo "go.sum exists"
# fi
go mod tidy

echo "Building ebpf-manager with embeded ./kernel/kernel.o"
go build

echo "Loading eBPF program ./kernel/kernel.o into the kernel"
sudo ./ebpf-manager