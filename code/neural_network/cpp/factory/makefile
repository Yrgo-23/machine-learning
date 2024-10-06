# Name of target.
TARGET := app

# Source files used in the application.
SOURCE_FILES := source/act_func_calc.cpp \
                source/dense_layer.cpp \
				source/factory.cpp \
                source/main.cpp \
			    source/neural_network.cpp \

# Include directories.
INCLUDE_DIRS := include

# Additional compiler flags.
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