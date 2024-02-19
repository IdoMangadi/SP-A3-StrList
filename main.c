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
    printf("enter your choice: ");
    scanf(" %d", &choice);

    while(choice != 0){ // Checks whether the scaf worked and if the user input was 0:

        if (choice == 1){  // Means the user wants to input strings to the StrList:
            printf("\nenter A: ");
            char a;
            scanf(" %c", &a);
            if (a == 'A'){
                printf("\nenter how many strings you want to insert: ");
                int amount;  // How many strings the user wants to enter.
                scanf(" %d", &amount);
                while (getchar() != '\n');  // Consumong all scanf's leftovers.
                printf("\nenter the strings: ");
                for(int i=0; i<amount; i++){  // Getting the strings:
                    char* str = get_string_from_user();
                    if(str == NULL){
                        StrList_free(strlist);
                        return 1;
                    }
                    StrList_insertLast(strlist, str);  // Inserting to the list
                    printf("\nthe %d string added to the list.", i+1);
                }
            }
        }

        if (choice == 2){  // Means the user wants to input a string in a specific index in the StrList:
            int index;
            if(scanf(" %d", &index) == 0){
                continue;
            }
            //add a condition what happend if user wants to enter index out of boundreis
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
            printf("%zu\n", size);
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
            printf("%d", StrList_count(strlist, str));
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
            size_t size = StrList_size(strlist);
            for(size_t i=0; i<size; i++){
                StrList_removeAt(strlist, 0);
	        }
        }

        if(choice == 12){  // Means the user wants to sort the list by lexicographic order:
            StrList_sort(strlist);
        }

        if(choice == 13){  // Means the user wants to remove all nodes from the list:
            printf("%d",StrList_isSorted(strlist));
        }

        scanf(" %d", &choice);
    }
    StrList_free(strlist);
    return 0;
}