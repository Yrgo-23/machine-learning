# Application target.
TARGET := app

# Source files used in the application.
SOURCE_FILES := source/act_func.c \
                source/dense_layer.c \
                source/main.c \
			    source/neural_network.c \
			    source/vector.c \
			    source/vector_2d.c

# Include directories.
INCLUDE_DIRS := include

# Compiler flags.
COMPILER_FLAGS := -Wall -Werror

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ $(SOURCE_FILES) -o $(TARGET) -I $(INCLUDE_DIRS) $(COMPILER_FLAGS)

# Runs the application.
run:
	@./$(TARGET)

# Cleans the application.
clean:
	@rm -f $(TARGET)