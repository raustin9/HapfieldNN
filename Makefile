CC=g++
CFLAGS=-std=c++20
INCLUDES=-Inetwork/src -Inetwork
LDFLAGS=-pthread
OBJ_DIR := obj
ASSEMBLY := network

SRC_FILES := $(shell find $(ASSEMBLY) -name *.cc)
DIRECTORIES := $(shell find $(ASSEMBLY) -type d)
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)

# Main targets
all: scaffold bin/network
	
run: scaffold bin/network 
	./bin/network -P 50 -N 100 --num-experiments 5

clean:
	rm -rf bin/* obj/* 

scaffold:
	@echo Scaffolding folder structure
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@echo Done.

bin/network: $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.cc.o: %.cc
	@echo $<...
	@$(CC) $< $(CFLAGS) -c -o $@ $(INCLUDES) $(LDFLAGS)


# obj/%.o: src/%.cc
# 	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@ $(LDFLAGS)
