#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>

#define MASSIV 100
#define STEP 20

struct Word{
    wchar_t* word;
    int len_of_word;
    int amount_in_text;
};

struct Sentence{
    wchar_t* sentence;
    struct Word ** pointers_word;
    int number_of_words;
    int amount_of_lat;
};
 
struct Text{
    struct Sentence ** pointers_sentence;
    int number_of_sentence;
};

struct WordCount {
    wchar_t* word;
    int count;
};