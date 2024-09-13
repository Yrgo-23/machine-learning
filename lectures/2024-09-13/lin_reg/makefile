# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ src/lin_reg.cpp src/main.cpp -o lin_reg -I inc -Wall -Werror

# Runs the application.
run:
	@./lin_reg
	
# Cleans the application.
clean:
	@rm -f lin_reg