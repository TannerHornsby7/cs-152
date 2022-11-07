#include <stdlib.h>
#include <stdio.h>

char* flip_case(char* s){
    int i = 0, length = 0;
    while(s[i] != '\0') {
        i++;
        length++;
    }
    char* res = (char*)malloc(sizeof(char)* length);
    for(i = 0; i < length; i++) {
        if (97 <= s[i] && s[i] <= 122) {
            res[i] = s[i] - 32;
        }
        else if (65 <= s[i] && s[i] <= 97) {
            res[i] = s[i] + 32;
        } else {
            res[i] = s[i];
        }
    }

    return res;
}