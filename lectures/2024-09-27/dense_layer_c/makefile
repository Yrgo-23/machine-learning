# Source files.
SOURCE_FILES := source/act_func.c \
                source/dense_layer.c \
                source/main.c

# Include directories.
INCLUDE_DIRS := include

# Additional compiler flags.
COMPILER_FLAGS := -Wall -Werror

# Linked libraries.
LINK_LIBS := -lm

# Application target.
TARGET := app

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@gcc $(SOURCE_FILES) -o $(TARGET) -I $(INCLUDE_DIRS) $(COMPILER_FLAGS) $(LINK_LIBS)

# Runs the application.
run:
	@./$(TARGET)

# Cleans the application.
clean:
	@rm -f $(TARGET)
