#pragma once

#include "structures.h"

struct Sentence* read_sentence();
struct Text read_text();
void words(struct Text *text);
void print_Text(struct Text *text);
void free_Text(struct Text *text);
void free_Sentence(struct Sentence *sentence);
void free_Word(struct Word *word);
wchar_t* wcsdup(const wchar_t* str);
