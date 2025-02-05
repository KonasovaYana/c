#include "structures.h"
#include "actions_with_sentences.h"
#include "structures_discribe.h"
#include "main_functions.h"
int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.5, created by Konasova Yana.\n");
    int enter;
    struct Text text;
    wscanf(L"%d", &enter);
    if (enter==5){
        print_information_about_func();
    }
    if (enter ==8){
        text=read_text();
        trim(&text);
        words(&text);
        del_empty_sent (&text);
        del_similar_sent (&text);
        task_func(&text);
        print_Text(&text);
        free_Text(&text);

    }

    else if ((enter>=0)&&(enter<=4)){
        text=read_text();
        trim(&text);
        words(&text);
        del_empty_sent (&text);
        del_similar_sent (&text);
    }
    else{
        wprintf(L"Incorrect data.");
    }
    switch(enter){
        case 0: {
            print_Text(&text);
            free_Text(&text);
            
            break;
        }
        case 1: {
            countWords(&text);
            free_Text(&text);
            break;
        }
        case 2: {
            print_Text_for_two(&text);
                      
            free_Text(&text);
            break;
        }
        case 3: {
            sort_sentence(&text);
            print_Text(&text);
            free_Text(&text);
            break;
        }
        case 4: {
            delete_sent(&text);
            print_Text(&text);
            free_Text(&text);
            break;
        }
    }
    
    
    return 0;
}

