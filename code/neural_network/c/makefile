# Name of target.
TARGET := app

# Source files used in the application.
SRC_FILES := src/act_func.c \
             src/dense_layer.c \
             src/main.c \
			 src/neural_network.c \
			 src/vector.c \
			 src/vector_2d.c

# Include directories.
INC_DIRS := inc

# Compiler flags.
COMPILER_FLAGS := -Wall -Werror

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ $(SRC_FILES) -o $(TARGET) -I $(INC_DIRS) $(COMPILER_FLAGS)

# Runs the application.
run:
	@./$(TARGET)

# Cleans the application.
clean:
	@rm -f $(TARGET)