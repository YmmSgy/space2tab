# subdirectory paths
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# targets and prerequisites
EXE := $(BIN_DIR)/space2tab
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# compiler flags
CPPFLAGS := -I$(SRC_DIR) -MMD -MP
CFLAGS := -Wall -Werror
LDFLAGS :=
LDLIBS :=

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SRC_DIR)/vers.c -o $(OBJ_DIR)/vers.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
