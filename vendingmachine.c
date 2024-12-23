#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POPNAME "Pop"
#define UPPERLIMITPRICE 115
#define LOWERLIMITPRICE 30
#define LOWESTDENOMINATOR 5
#define COIN1NAME "Pente"
#define COIN2NAME "Dime"
#define COIN3NAME "Nickel"
#define COIN1VALUE 20
#define COIN2VALUE 10
#define COIN3VALUE 5
#define COIN1INPUTUPPERCASE 'P'
#define COIN1INPUTLOWERCASE 'p'
#define COIN2INPUTUPPERCASE 'D'
#define COIN2INPUTLOWERCASE 'd'
#define COIN3INPUTUPPERCASE 'N'
#define COIN3INPUTLOWERCASE 'n'
#define CHANGEINPUTUPPERCASE 'R'
#define CHANGEINPUTLOWERCASE 'r'
#define EXITINPUTUPPERCASE 'K'
#define EXITINPUTLOWERCASE 'k'
#define CURRENCYNAME "centimes"
#define WELCOMECOIN1 "Pentes"
#define WELCOMECOIN2 "Dimes"
#define WELCOMECOIN3 "Nickels"

// Function to calculate and print change
void calculateAndPrintChange(int change, const char *currencyName, const char *dimeName, const char *nickelName) {
    int numberOfDimes = change / COIN2VALUE;
    int numberOfNickels = (change % COIN2VALUE) / COIN3VALUE;

    printf("Change given: %d %s as %d %s(s) and %d %s(s).\n",
           change, currencyName, numberOfDimes, dimeName, numberOfNickels, nickelName);
}

int main(int argc, char *argv[]) {
    int sodaPrice = 0;

    if (argc == 2) {
        sodaPrice = atoi(argv[1]);
    }

    /* Check for errors in command-line arguments */
    if (argc < 2) {
        printf("Please specify the selling price as a command line argument.\nUsage: %s [price]\n", argv[0]);
        return 0;
    } else if (argc > 2) {
        printf("Please only enter one argument.\n");
        return 0;
    } else if (sodaPrice > UPPERLIMITPRICE || sodaPrice < LOWERLIMITPRICE) {
        printf("Price must be from %d to %d %s inclusive.\n", LOWERLIMITPRICE, UPPERLIMITPRICE, CURRENCYNAME);
        return 0;
    } else if (sodaPrice % LOWESTDENOMINATOR != 0) {
        printf("Price must be a multiple of %d.\n", LOWESTDENOMINATOR);
        return 0;
    }

    /* Machine in service */
    char coinChoice;
    int balance;
    int change;

    printf("Welcome to my C Pop Machine!\n");

    while (true) {
        /* Reset variables for each new transaction */
        balance = 0;
        change = 0;
        bool resetTransaction = false;  // New flag for resetting transaction

        printf("\n%s is %d %s. Please insert any combination of %s [%c or %c], %s [%c or %c] or %s [%c or %c]. You can also press %c or %c for coin return.",
               POPNAME, sodaPrice, CURRENCYNAME, WELCOMECOIN3, COIN3INPUTUPPERCASE, COIN3INPUTLOWERCASE,
               WELCOMECOIN2, COIN2INPUTUPPERCASE, COIN2INPUTLOWERCASE, WELCOMECOIN1, COIN1INPUTUPPERCASE, COIN1INPUTLOWERCASE,
               CHANGEINPUTUPPERCASE, CHANGEINPUTLOWERCASE);

        /* Loop for inserting coins */
        while (balance < sodaPrice) {
            printf("\nEnter coin (%c%c%c%c): ", COIN3INPUTUPPERCASE, COIN2INPUTUPPERCASE, COIN1INPUTUPPERCASE, CHANGEINPUTUPPERCASE);
            scanf(" %c", &coinChoice);

            /* Process coin input */
            if (coinChoice == COIN3INPUTUPPERCASE || coinChoice == COIN3INPUTLOWERCASE) {
                balance += COIN3VALUE;
                printf("  %s detected.", COIN3NAME);
            } else if (coinChoice == COIN2INPUTUPPERCASE || coinChoice == COIN2INPUTLOWERCASE) {
                balance += COIN2VALUE;
                printf("  %s detected.", COIN2NAME);
            } else if (coinChoice == COIN1INPUTUPPERCASE || coinChoice == COIN1INPUTLOWERCASE) {
                balance += COIN1VALUE;
                printf("  %s detected.", COIN1NAME);
            } else if (coinChoice == CHANGEINPUTUPPERCASE || coinChoice == CHANGEINPUTLOWERCASE) {
                if (balance <= 0) {
                    calculateAndPrintChange(0, CURRENCYNAME, COIN2NAME, COIN3NAME);
                } else {
                    /* Calculate and display correct change breakdown */
                    calculateAndPrintChange(balance, CURRENCYNAME, COIN2NAME, COIN3NAME);
                }
                resetTransaction = true;  // Set the flag to reset the transaction
                break;  // Exit the transaction loop after returning coins
            } else if (coinChoice == EXITINPUTUPPERCASE || coinChoice == EXITINPUTLOWERCASE) {
                /* Exit the program with final message */
                calculateAndPrintChange(balance, CURRENCYNAME, COIN2NAME, COIN3NAME);
                printf("Shutting down. Goodbye.\n");
                return 0;
            } else {
                printf("Unknown coin rejected.");
            }

            printf("\nYou have inserted a total of %d %s.", balance, CURRENCYNAME);
            if (balance < sodaPrice) {
                printf("\nPlease insert %d more %s", sodaPrice - balance, CURRENCYNAME);
            } else {
                printf("\n%s is dispensed. Thank you for your business! Please come again.\n", POPNAME);
                change = balance - sodaPrice;
                break;
            }
        }

        /* Final change calculation if overpaid */
        if (change > 0) {
            calculateAndPrintChange(change, CURRENCYNAME, COIN2NAME, COIN3NAME);
        }

        /* Check if we need to reset the transaction loop */
        if (resetTransaction) {
            continue;
        }
    }

    return 0;
}
