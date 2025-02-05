
#include "structures_discribe.h"
#include "actions_with_sentences.h"

struct Sentence* read_sentence(){
    wchar_t* sent = malloc(MASSIV*sizeof(wchar_t));
    wchar_t symbol_now;
    wchar_t symbol_prev;
    int size_sent=MASSIV;
    int len_sent=0;
    int already_blank=0;

    do{
        symbol_now=getwchar();
        if ((iswblank(symbol_now))&&(already_blank==1)){
            continue;
        }if ((iswblank(symbol_now))&&(already_blank==0)){
            already_blank=1;
        }if (!(iswblank(symbol_now))) {
            already_blank=0;
        }
        if (len_sent<size_sent-1){
            sent[len_sent]=symbol_now;
            sent[len_sent+1]=L'\0';
            len_sent++;
        } else{
            size_sent=size_sent+STEP;
            sent = (wchar_t*)realloc(sent, size_sent*sizeof(wchar_t));
            if ( sent== NULL) {
                wprintf(L"Error: Ошибка перераспределения памяти.\n");
                free(sent);
                exit(0);
            }
            else{
                sent[len_sent]=symbol_now;
                sent[len_sent+1]=L'\0';
                len_sent++;
            }

        } if ((symbol_now==L'.')||((symbol_now==L'\n')&&(symbol_prev==L'\n'))) break;
        symbol_prev=symbol_now;

    }while (1);
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->sentence=sent;
    return sentence;
}

struct Text read_text(){
    int size_text = MASSIV;
    int amount_of_sentence=0;
    struct Sentence **points_sentence = malloc(size_text*sizeof(struct Sentence*));
    if ( points_sentence== NULL) {
        wprintf(L"Error: Ошибка перераспределения памяти.\n");
        free(points_sentence);
        exit(0);
    } 
    struct Sentence *sentence_now;
    do{
        if (amount_of_sentence<size_text){
            sentence_now=read_sentence();
        }else{
            size_text+=STEP;
            struct Sentence **n_points_sentence = realloc(points_sentence, size_text*sizeof(struct Sentence*));
            if ( n_points_sentence== NULL) {
                wprintf(L"Error: Ошибка перераспределения памяти.\n");
                free(points_sentence);
                exit(0);
            }else{
                points_sentence=n_points_sentence;
                sentence_now=read_sentence();
            }
        }
        points_sentence[amount_of_sentence]=sentence_now;
        amount_of_sentence++;
    }while((sentence_now->sentence[wcslen(sentence_now->sentence)-1]!=L'\n')&&(sentence_now->sentence[wcslen(sentence_now->sentence)-2]!=L'\n'));
    struct Text text;
    text.pointers_sentence=points_sentence;
    text.number_of_sentence=amount_of_sentence;
    return text;

}

void words(struct Text *text){
    for (int i=0; i<text->number_of_sentence; i++){
        int size_word=MASSIV;
        int amount_of_words=0;
        struct Word** words_points= malloc(size_word*sizeof(struct Word*));
        if (words_points==NULL){
            wprintf(L"Error: Ошибка перераспределения памяти.\n");
            free(words_points);
            exit(0);
        }
        wchar_t* sentence = wcsdup(text->pointers_sentence[i]->sentence);
        wchar_t* token=wcstok(sentence, L" ,.", &sentence);
        while (token!=NULL){
            if (amount_of_words>=size_word){
                size_word+=STEP;
                struct Word** n_words_points= realloc(words_points, size_word*sizeof(struct Word*));
                if (n_words_points==NULL){
                    wprintf(L"Error: Ошибка перераспределения памяти.\n");
                    free(words_points);
                    exit(0);
                }else{
                    words_points=n_words_points;
                }
            }
            struct Word* word = malloc(sizeof(struct Word));
            word->word=wcsdup(token);
            word->len_of_word=wcslen(token);
    words_points[amount_of_words]=word;
            amount_of_words++;
            token=wcstok(NULL, L" ,.", &sentence);
        }
        text->pointers_sentence[i]->pointers_word=words_points;
        text->pointers_sentence[i]->number_of_words=amount_of_words;
        free(sentence);
    }
}

void print_Text(struct Text* text){
    for (int i=0; i<text->number_of_sentence; i++){
        wprintf(L"%ls\n", text->pointers_sentence[i]->sentence);
    }
}

void free_Word(struct Word *word) {
    free(word->word);
    free(word);
}

void free_Sentence(struct Sentence *sentence) {
    for (int i = 0; i < sentence->number_of_words; i++) {
        free_Word(sentence->pointers_word[i]);
    }
    free(sentence->pointers_word);
    free(sentence->sentence);
    free(sentence);
}

void free_Text(struct Text *text) {
    for (int i = 0; i < text->number_of_sentence; i++) {
        free_Sentence(text->pointers_sentence[i]);
    }
    free(text->pointers_sentence);
}