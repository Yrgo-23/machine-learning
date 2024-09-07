from lin_reg import LinReg

def main() -> None:
    """Trains a linear regression model to predict the pattern y = 2x + 2.
       is trained until the accuracy is above 99.9 %, then the results are printed.
    """
    input  = [0, 1, 2, 3, 4]
    output = [2, 4, 6, 8, 10]
    linReg = LinReg(input, output)
    while linReg.train(200) < 0.999:
        pass
    linReg.print_results()

# Calls the main function is this is the startup script of the application.
if __name__ == "__main__":
    main()