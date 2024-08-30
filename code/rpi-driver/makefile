# Implements parameter for referring to all source files.
SOURCE_FILES := source/button.cpp \
                source/gpiod_utils.c \
			    source/led.cpp \
			    source/main.cpp

# Builds and runs the application as default.
default: build run

# Builds application.
build:
	@g++ $(SOURCE_FILES) -o main -Wall -Werror -I include -lgpiod

# @brief Runs the program application.
run:
	@./main

# @brief Removes the executable.
clean:
	@rm -f main