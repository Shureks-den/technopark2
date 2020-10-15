#include "write.h"
#include "main_module.h"
#include "utils.h"

int main(void) {
    int choice = 0;
    test_write_to_file();
    FILE *Ptr, *Ptr_2, *blackrecord;
    Data client_data = {}, transfer = {};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n\n");
    while (scanf("%5d", &choice) != -1) {
        switch (choice) {
            case 1:
                Ptr = fopen("record.dat", "r+");
                    if (Ptr == NULL) {
                        puts("Not acess");
                        } else {
                            masterWrite(Ptr, client_data);
                            fclose(Ptr);
                        }
                break;
            case 2:
                Ptr = fopen("transaction.dat", "r+");
                    if ( Ptr == NULL ) {
                        puts("Not acess");
                    } else {
                        transactionWrite(Ptr, transfer);
                        fclose(Ptr);
                    }
                break;
            case 3:
                Ptr = fopen("record.dat", "r");
                Ptr_2 = fopen("transaction.dat", "r");
                blackrecord = fopen("blackrecord.dat", "w");
                    if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
                    puts("exit");
                    } else {
                        blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
                        fclose(Ptr);
                        fclose(Ptr_2);
                        fclose(blackrecord);
                    }
                break;
            default:
                puts("error");
                printf("%d\n", choice);
                break;
            }
        printf("%s%s", "please enter action\n1 enter data client:\n",
        "2 enter data transaction:\n3 update base\n\n");
    }
    return 0;
}
