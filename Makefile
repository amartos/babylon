BUILD	:= dist
EXE		:= $(BUILD)/babylon
CPP		:= gcc
COPTS	:= $(shell cat compile_flags.txt)
SRC		:= babylon.c

all: $(EXE)

$(EXE): $(SRC)
	@mkdir -p $(@D)
	@$(CPP) $(COPTS) $^ -o $@
