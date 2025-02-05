#include "main_functions.h"
#include "actions_with_sentences.h"
void countWords(struct Text* text){
    struct WordCount* word_counts = NULL;
    int size_word_counts = 0;
    for (int i = 0; i < text->number_of_sentence; i++) {
        for (int j = 0; j < text->pointers_sentence[i]->number_of_words; j++) {
            wchar_t* current_word = text->pointers_sentence[i]->pointers_word[j]->word;
            int word_index = -1;
            for (int k = 0; k < size_word_counts; k++) {
                if (wcscmp(current_word, word_counts[k].word) == 0) {
                    word_index = k;
                    break;
                }
            }
            if (word_index == -1) {
                if (size_word_counts == 0) {
                    word_counts = malloc(sizeof(struct WordCount));
                } else {
                    word_counts = realloc(word_counts, (size_word_counts + 1) * sizeof(struct WordCount));
                }
                if (word_counts == NULL) {
                    wprintf(L"Error: Ошибка перераспределения памяти.\n");
                    exit(1);
                }
                word_counts[size_word_counts].word = wcsdup(current_word);
                word_counts[size_word_counts].count = 1;
                size_word_counts++;
            } else {
                word_counts[word_index].count++;
            }
        }
    }

    for (int i = 0; i < size_word_counts; i++) {
        wprintf(L"%ls: %d\n", word_counts[i].word, word_counts[i].count);
        free(word_counts[i].word);
    }

    free(word_counts);
}

void delete_sent(struct Text* text){
    for (int i =0; i<text->number_of_sentence; i++){
        int flag=0;
        if (check_registr(text->pointers_sentence[i])){
            for (int j =0; j<text->pointers_sentence[i]->number_of_words; j++){
                for (int l =0; l<text->pointers_sentence[i]->pointers_word[j]->len_of_word; l++){
                    wchar_t a=text->pointers_sentence[i]->pointers_word[j]->word[l];
                    if ((a==L'#')||(a==L'$')||(a==L'^')|| (a==L'%') || (a==L'@')){
                        flag++;
                    }
                }
            }
        }
        if (flag!=0){
            del_sent(text, i);
            i--;
        }
    }
}

void print_Text_for_two(struct Text* text){
    for (int i=0; i<text->number_of_sentence; i++){
        for (int j=0; j<wcslen(text->pointers_sentence[i]->sentence); j++){
            wchar_t a = text->pointers_sentence[i]->sentence[j];
            if ((iswalpha(a))||(a >= L'\u0400' && a <= L'\u04FF')){
                wprintf(L"%c", a);
            }else if(a==L'.'){
                wprintf(L"%c\n", a);
            }else if(a==L' '){
                wprintf(L" ", a);
            }else if(a==L'\n'){
                wprintf(L"\n", a);
            }else {
                wprintf(L"%d", a);
            }
        }
    }
}


void sort_sentence(struct Text* text){
    count_lat(text);
    for (int i = 0; i < text->number_of_sentence; i++) {

        for (int j = 0; j < text->number_of_sentence-i-1; j++) {
            if (text->pointers_sentence[j]->amount_of_lat > text->pointers_sentence[j+1]->amount_of_lat) {
                
                struct Sentence* temp = text->pointers_sentence[j];
                text->pointers_sentence[j] = text->pointers_sentence[j+1];
                text->pointers_sentence[j+1]= temp;
            }
        }
    }
}
void task_func(struct Text* text){
    for (int i=0; i<text->number_of_sentence; i++){
        wchar_t* sentence = text->pointers_sentence[i]->sentence;
        wchar_t* result = malloc((wcslen(sentence)*2 +1)* sizeof(wchar_t));
        wchar_t * res_ptr = result;
        int len = wcslen(sentence);
        for (int j=0; j<len;){
            wchar_t curr_sent = sentence[j];
            int count = 1;
            while (j+ count < len && towlower (sentence[j+count])== towlower(curr_sent)){
                count++;
            }
            if (count >1){
                *res_ptr++ =towupper(curr_sent);
                res_ptr += swprintf(res_ptr, 10, L"%d", count);

            }else{
                *res_ptr++ = curr_sent;
            }
            j+=count;
        }
        *res_ptr=L'\0';
        text->pointers_sentence[i]->sentence=result;
    }

}
void print_information_about_func(){
    wprintf(L"1. Prints each word case-sensitive and the number of its repetitions in the text.\n 2. Replaces each character that is not a letter with its code.\n 3. sort sentences by the number of Latin letters in the sentence.\n 4. delete all sentences that contain special characters and do not contain capital letters.");
}
