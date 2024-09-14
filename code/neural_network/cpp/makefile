# Name of target.
TARGET := app

# Source files used in the application.
SRC_FILES := src/dense_layer.cpp \
             src/main.cpp \
			 src/neural_network.cpp

# Include directories.
INC_DIRS := inc

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ $(SRC_FILES) -o $(TARGET) -Wall -Werror -I $(INC_DIRS)

# Runs the application.
run:
	@./$(TARGET)

# Cleans the application.
clean:
	@rm -f $(TARGET)