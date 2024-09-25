# Application target.
TARGET = app

# Source files used in the application.
SOURCE_FILES := source/lin_reg.c \
                source/main.c

# Include directories.
INCLUDE_DIRS := include

# Additional compiler flags.
COMPILER_FLAGS := -Wall -Werror

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@gcc $(SOURCE_FILES) -o $(TARGET) -I $(INCLUDE_DIRS) $(COMPILER_FLAGS)

# Runs the application.
run:
	@./$(TARGET)

# Cleans the application.
clean:
	@rm -f $(TARGET)
