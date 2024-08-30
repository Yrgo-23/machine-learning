################################################################################
# @brief Parameter referring to all source files.
################################################################################
SOURCE_FILES := source/lin_reg.cpp \
                source/main.cpp

# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ $(SOURCE_FILES) -o main -I include -Wall -Werror 

# Runs the application.
run:
	@./main

# Cleans the application.
clean:
	@rm -f main
