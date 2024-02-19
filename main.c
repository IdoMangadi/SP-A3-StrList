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

        if (choice == 2){
            
        }

    }
    strlist_free(strlist);
    return 0;
}