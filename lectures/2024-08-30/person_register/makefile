# Builds and runs the application as default.
default: build run

# Builds the application.
build:
	@g++ source/main.cpp \
	     source/person.cpp \
		 source/person_register.cpp \
		 -o main -I include/ \
		 -Wall -Werror 

# Runs the application.
run:
	@./main

# Cleans the application.
clean:
	@rm -f main
