#include <stdio.h>
#include "StrList.h"

int main(){
    StrList* strlist = StrList_alloc();
    int choice = 0;
    while(scanf(" %d", &choice) == 0){}

    while(choice != 0){

        if (choice == 1){
            char a;
            scanf(" %c", &a);
            if (a == 'A'){


                int amount;  // How many strings the user wants to enter.
                scanf(" %d", &amount);
                
                for(int i=0; i<amount; i++){  // Getting he strings:
                    int cap = 5;
                    char* str = (char*)malloc(sizeof(char)*cap);
                    char input;
                    int index = 0;
                    while((input = getchar()) != ' ' && input != '\n'){
                        str[index++] = input;

                        if(index == cap){ // Means we ran out of place in allocated memory
                            cap = cap * 2;
                            char* tmp = realloc(str, sizeof(char)*cap);
                            if(tmp == NULL){
                                free(str);
                                StrList_free(strlist);
                                return 1;
                            }
                            str = tmp;
                        }
                    }
                    // Adding '\0':
                    if(index == cap){
                        char* tmp = realloc(str, sizeof(char)*(cap+1));
                            if(tmp == NULL){
                                free(str);
                                StrList_free(strlist);
                                return 1;
                            }
                            str = tmp;
                    }
                    str[index] = '\0';
                    StrList_insertLast(strlist, str);
                }
            }
        }

    }
    strlist_free(strlist);
    return 0;
}