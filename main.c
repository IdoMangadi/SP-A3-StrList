#include <stdio.h>
#include "StrList.h"

/**
 * This function gets the user input into a string and return it.
 * Note: if something went wrong it will return NULL pointer.
*/
char* get_string_from_user(){
    int cap = 5;
    char* str = (char*)malloc(sizeof(char)*cap);
    char input;
    int index = 0;
    while((input = getchar()) != ' ' && input != '\n'){
        str[index++] = input;  // Adding the char to the end of the current chars.
        if(index == cap){ // Means we ran out of space in allocated memory
            cap += 5;
            char* tmp = (char*)realloc(str, sizeof(char)*cap);
            if(tmp == NULL){
                free(str);
                return NULL;
            }
            str = tmp;
        }
    }
    // Adding '\0':
    if(index == cap){  // Means we have no room for the 0 indicator.
        char* tmp = (char*)realloc(str, sizeof(char)*(cap+1));
        if(tmp == NULL){
            free(str);
            return NULL;
        }
        str = tmp;
    }
    str[index] = '\0';
    return str;

}

int main(){
    StrList* strlist = StrList_alloc();
    int choice = 0;

    while(scanf(" %d", &choice) > 0 && choice != 0){ // Checks whether the scaf worked and if the user input was 0:

        if (choice == 1){  // Means the user wants to input strings to the StrList:
            char a;
            scanf(" %c", &a);
            if (a == 'A'){

                int amount;  // How many strings the user wants to enter.
                scanf(" %d", &amount);
                
                for(int i=0; i<amount; i++){  // Getting the strings:
                    char* str = get_string_from_user();
                    if(str == NULL){
                        StrList_free(strlist);
                        return 1;
                    }
                    StrList_insertLast(strlist, str);  // Inserting to the list
                }
            }
        }

        if (choice == 2){  // Means the user wants to input a string in a specific index in the StrList:
            int index;
            if(scanf(" %d", &index) == 0){
                continue;
            }
            char* str = get_string_from_user();
            if(str == NULL){
                continue;
            }
            StrList_insertAt(strlist, str, index);
        }

        if(choice == 3){  // Means the user wants to print the StrList:
            StrList_print(strlist);
        }

        if(choice == 4){  // Means the user wants to print the StrList's length:
            size_t size = StrList_size(strlist);
            printf("%zu", size);
        }

        if(choice == 5){  // Means the user wants to print the string in index:
            int index;
            if(scanf(" %d", &index) == 0){
                continue;
            }
            StrList_printAt(strlist, index);
        }

        if(choice == 6){  // Means the user wants to print the chars amount of all the list:
            printf("%d", StrList_printLen(strlist));
        }

        if (choice == 7){  // Means the user wants to print how many times given string is in the list:
            char* str = get_string_from_user();
            if(str == NULL){
                continue;
            }
            printf("d", StrList_count(strlist, str));
        }

        if(choice == 8){  // Means the user wants to remove all the appearences of the given string from the list:
            char* str = get_string_from_user();
            if(str == NULL){
                continue;
            }
            StrList_remove(strlist, str);
        }

        if(choice == 9){  // Means the user wants to remove the string in the given index:
            int index;
            if(scanf(" %d", &index) == 0){
                continue;
            }
            StrList_removeAt(strlist, index);
        }

        if(choice == 10){  // Means the user wants to reverse the list:
            StrList_reverse(strlist);
        }

        if(choice == 11){  // Means the user wants to remove all nodes from the list:
            StrList_clear(strlist);
        }

        if(choice == 12){  // Means the user wants to sort the list by lexicographic order:
            StrList_sort(strlist);
        }

        if(choice == 13){  // Means the user wants to remove all nodes from the list:
            printf("%d",StrList_isSorted(strlist));
        }

    }
    StrList_free(strlist);
    return 0;
}