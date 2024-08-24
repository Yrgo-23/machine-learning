################################################################################
# @brief Implements parameter for referring to source files.
################################################################################
SOURCE_FILES := source/button.cpp \
                source/gpiod_utils.c \
			    source/led.cpp \
			    source/main.cpp

################################################################################
# @brief Builds the project and runs the program as default.
################################################################################
default: build run

################################################################################
# @brief Builds the project and creates an executable called main.
################################################################################
build:
	@g++ $(SOURCE_FILES) -o main -Wall -Werror -I include -lgpiod

################################################################################
# @brief Runs the program (by running the main executable).
################################################################################
run:
	@./main

################################################################################
# @brief Removes compiled files (by deleting the main executable).
################################################################################
clean:
	@rm -f main