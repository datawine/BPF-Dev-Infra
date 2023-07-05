PROGRAMS := $(wildcard src/*)

.PHONY: all clean $(PROGRAMS)

all: $(PROGRAMS)

clean: 
	-$(RM) -r ./build

$(PROGRAMS):
	$(MAKE) --directory=$@
