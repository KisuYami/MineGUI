TARGET_LIB = libminegui.so

CC 		= gcc
CFLAGS 	= -Wall -Werror -pedantic -ggdb3 -fPIC

SRC_DIRS 	= ./src
BUILD_DIR 	= ./build

SRCS = $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
HEADERS = $(shell find $(SRC_DIRS) -name *.h -or -name *.hh)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

INCLUDE_DIR=/usr/local/include/minegui/
LIB_DIR=/usr/lib/

# Program binary
$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(CC) --shared $(OBJS) -o $@ $(LDFLAGS) $(CLIBS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(BUILD_DIR)/$(TARGET_LIB)
	mkdir -p $(INCLUDE_DIR)
	install -g 0 -o 0 -m 0755 build/$(TARGET_LIB) $(LIB_DIR)
	find $(SRC_DIRS)/*.h -type f -exec install -Dm 755 "{}" "$(INCLUDE_DIR)" \;

	ldconfig /usr/lib

clear:
	$(RM) -rf $(BUILD_DIR)
