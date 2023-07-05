CLANG := clang

TARGET = main
SRC = main.c

ELFSO = -lelf
BPFSO = -lbpf

LD_PATH = $(ELFSO) $(BPFSO)
LIBRARY_PATH = -Wl,-rpath,/usr/lib64

.PHONY: default

default: $(SRC)
	$(CLANG) $^ $(LD_PATH) $(LIBRARY_PATH) -o $(TARGET)