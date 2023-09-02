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
    double overdraft;
    const double AUTHORIZED_OVERDRAFT;
};

int main()
{
    struct Client currentUser = { "Hammilton", 16 };
    struct Account currentAccount = { currentUser, 5000.00, 1000.00, 1000.00 };

    const char LOCAL_CURRENCY[4] = "GBR";
    int option;
    double withdrawal, deposit, transfer;

    do {
        printf("Hello, Mr. %s\n", currentUser.name);
        printf("[ 1 ] Balance\n");
        printf("[ 2 ] Withdrawal\n");
        printf("[ 3 ] Deposit\n");
        printf("[ 4 ] Transfer\n");
        printf("[ 0 ] Exit\n\n");
        printf(">");
        scanf_s("%d", &option);

        switch (option) {
        case 1:
            printf("\n\n| Current balance: %s %.2f | Avaliable overdraft: %s %.2f |\n\n", LOCAL_CURRENCY, currentAccount.balance, LOCAL_CURRENCY, currentAccount.overdraft);
            break;
        case 2:
            printf("\n\nWithdrawal\n");
            printf("| Balance: %s %.2f | Overdraft: %s %.2f |\n", LOCAL_CURRENCY, currentAccount.balance, LOCAL_CURRENCY, currentAccount.overdraft);
            printf("Value: %s ", LOCAL_CURRENCY);
            scanf_s("%lf", &withdrawal);
            getchar();

            // Verify if withdrawal is avaliable
            if (withdrawal <= currentAccount.balance + currentAccount.overdraft) {
                
                // Uses overdraft
                if (withdrawal <= currentAccount.balance) {
                    currentAccount.balance -= withdrawal;
                }
                else {
                    currentAccount.overdraft -= (withdrawal - currentAccount.balance);
                    currentAccount.balance = 0.0;
                }
                printf("Successful withdrawal!\n\n");
            }
            else {
                printf("Unauthorized withdrawal. Amount exceeds your balance.\n\n");
            }

            break;
        case 3:
            printf("\n\nDeposit\n");
            printf("Value: %s ", LOCAL_CURRENCY);
            scanf_s("%lf", &deposit);
            getchar();

            // Used overdraft
            if (currentAccount.overdraft < currentAccount.AUTHORIZED_OVERDRAFT) {
                currentAccount.overdraft += deposit;
                double overflow = currentAccount.overdraft - currentAccount.AUTHORIZED_OVERDRAFT;
                if (overflow > 0) {
                    currentAccount.balance += overflow;
                    currentAccount.overdraft -= overflow;
                }
            }
            else {
                currentAccount.balance += deposit;
            }

            printf("Successful deposit!\n\n");
            break;
        case 4:
            puts("Transfer money");
            printf("Value %s", LOCAL_CURRENCY);
            scanf_s("%lf", &transfer);
            getchar();

            // Verify if transfer is possible
            if (transfer <= currentAccount.balance + currentAccount.overdraft) {
                int reciver_account;
                printf("Account of reciver: ");
                scanf_s("%d", &reciver_account);

                // Uses overdraft
                if (transfer <= currentAccount.balance) {
                    currentAccount.balance -= transfer;
                }
                else {
                    currentAccount.overdraft -= (transfer - currentAccount.balance);
                    currentAccount.balance = 0.0;
                }
                printf("Successful transfer!\n\n");
            }
            else {
                printf("Unauthorized transfer. Amount exceeds your balance.\n\n");
            }

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
