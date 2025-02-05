#include "actions_with_sentences.h"

void del_sent(struct Text *text, int numb_of_sent){
    struct Sentence *del_sentence = text->pointers_sentence[numb_of_sent];
    memmove(&text->pointers_sentence[numb_of_sent], &text->pointers_sentence[numb_of_sent+1], sizeof(struct Sentence*)*(text->number_of_sentence-numb_of_sent-1));
    free(del_sentence);
    text->number_of_sentence=text->number_of_sentence-1;
}

void del_empty_sent (struct Text *text){
    for (int i=0; i<text->number_of_sentence; i++){
        if (text->pointers_sentence[i]->number_of_words==0){
            del_sent(text, i);
        }
    }
}

void del_similar_sent (struct Text *text){
    for (int i =0; i<text->number_of_sentence-1; i++){
        int j=i+1;
        while(j<text->number_of_sentence){
            if (wcscasecmp(text->pointers_sentence[i]->sentence, text->pointers_sentence[j]->sentence)==0){
                del_sent(text, j);
            }else{
                j+=1;
            }
        }
    }
}

int check_registr(struct Sentence *sentence){
    int flag=0;
    for (int j =0; j<sentence->number_of_words; j++){
        for (int l =0; l<sentence->pointers_word[j]->len_of_word; l++){
            wchar_t a=sentence->pointers_word[j]->word[l];
            if (iswupper(a)){
                flag++;
            }
        }
    }
    if (flag==0){
        return 1;
    }else{
        return 0;
    }
}

void count_lat(struct Text *text){
    for (int i =0; i<text->number_of_sentence; i++){
        int amount_lat=0;
        for (int j =0; j<text->pointers_sentence[i]->number_of_words; j++){
            for (int l =0; l<text->pointers_sentence[i]->pointers_word[j]->len_of_word; l++){
                wchar_t a=text->pointers_sentence[i]->pointers_word[j]->word[l];
                if (((a>=L'a')&&(a<=L'z'))||((a>=L'A')&&(a<=L'Z'))){
                    amount_lat++;
                }
            }
        }
        text->pointers_sentence[i]->amount_of_lat=amount_lat;
    }
}
void trim(struct Text *text){
    for (int i = 0; i<text->number_of_sentence; i++){
        int begin=0;
        int end = wcslen(text->pointers_sentence[i]->sentence)-1;
        while(iswspace(text->pointers_sentence[i]->sentence[begin])){
            begin++;
        }
        while(end>=begin && iswspace(text->pointers_sentence[i]->sentence[end])){
            end--;
        }
        int j=0;
        for (j; j<=end - begin; j++){
            text->pointers_sentence[i]->sentence[j]=text->pointers_sentence[i]->sentence[begin+j];
        }
        text->pointers_sentence[i]->sentence[j]=L'\0';
    }
}
