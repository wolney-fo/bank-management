#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Client {
    char name[30];
    int age;
};

struct Account {
    struct Client holder;
    double balance;
};

int main()
{
    struct Client currentUser = { "Hammilton", 16 };
    struct Account currentAccount = { currentUser, 5000.00 };

    const char LOCAL_CURRENCY[4] = "GBR";
    int option;
    double withdrawal, deposit;

    do {
        printf("Hello, Mr. %s\n", currentUser.name);
        printf("[ 1 ] Balance\n");
        printf("[ 2 ] Withdrawal\n");
        printf("[ 3 ] Deposit\n");
        printf("[ 0 ] Exit\n\n");
        printf(">");
        scanf_s("%d", &option);

        switch (option) {
        case 1:
            printf("\n\nYour current balance is: %s %.2f\n\n", LOCAL_CURRENCY, currentAccount.balance);
            break;
        case 2:
            printf("\n\nWithdrawal\n");
            printf("| Balance: %s %.2f |\n", LOCAL_CURRENCY, currentAccount.balance);
            printf("Value: %s ", LOCAL_CURRENCY);
            scanf_s("%lf", &withdrawal);
            getchar();

            if (withdrawal <= currentAccount.balance) {
                currentAccount.balance -= withdrawal;
                printf("Successful withdrawal!\n\n");
            }
            else {
                printf("Unauthorized withdrawal. Amount exceeds your balance.\n\n");
            }

            break;
        case 3:
            printf("\n\Deposit\n");
            printf("Value: %s ", LOCAL_CURRENCY);
            scanf_s("%lf", &deposit);
            getchar();

            currentAccount.balance += deposit;

            printf("Successful deposit!\n\n");
            break;
        case 0:
            printf("Have a great week!");
            return 0;
        default:
            printf("\n\nOops! Invalid option. Choose again:\n\n");
        }

    } while (option != 0);

    return 0;
}
