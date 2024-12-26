# Name of target.
TARGET := app

# Source files used in the application.
SOURCE_FILES := source/conv_layer.cpp \
				source/main.cpp \
			    source/pooling_layer.cpp \

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