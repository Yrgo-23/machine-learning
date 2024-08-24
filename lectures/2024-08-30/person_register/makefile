################################################################################
# @brief Builds the project and runs the program as default.
################################################################################
default: build run

################################################################################
# @brief Builds the project and creates an executable called main.
################################################################################
build:
	@g++ source/main.cpp \
	     source/person.cpp \
		 source/person_register.cpp \
		 -o main -I include/ \
		 -Wall -Werror 

################################################################################
# @brief Runs the program (by running the main executable)
################################################################################
run:
	@./main

################################################################################
# @brief Removes compiled files (by deleting the main executable).
################################################################################
clean:
	@rm -f main
