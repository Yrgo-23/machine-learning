# Source files used in the application.
SRC_FILES := main.cpp

# Builds and runs the application as default.
all: build run

# Builds the application.
build:
	@g++ $(SRC_FILES) -o app -Wall -Werror -std=c++17

# Runs the application.
run:
	@./app

# Cleans the application.
clean:
	@rm -f app