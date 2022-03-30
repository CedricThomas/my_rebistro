SRC_DIR         :=      src/

BUILD_DIR       :=      build/

INCLUDE_DIR     :=      include/

SRC             :=      $(shell find $(SRC_DIR) -name '*.c')

OBJECTS         :=      $(addprefix $(BUILD_DIR),$(SRC:$(SRC_DIR)%.c=%.o))

BINARY          :=      bistro

CFLAGS          :=      -Wall -Wextra

all: $(BINARY)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(dir $@)
		gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BINARY): $(OBJECTS)
		gcc $(OBJECTS)  $(CFLAGS) -o $(BINARY)

clean:
		rm -rf $(OBJECTS)

fclean: clean
		rm -rf $(BINARY)
		rm -rf $(BUILD_DIR)

re: fclean all
