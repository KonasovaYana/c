#pragma once

#include "structures.h"
int wcscasecmp(const wchar_t* s1, const wchar_t* s2);
wchar_t* wcsdup(const wchar_t* str);
void del_sent(struct Text *text, int numb_of_sent);
void del_empty_sent (struct Text *text);
void del_similar_sent (struct Text *text);
int check_registr(struct Sentence *sentence);
void count_lat(struct Text *text);
void trim(struct Text *text);
