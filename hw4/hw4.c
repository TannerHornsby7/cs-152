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

//find length of string
int f_len(char* s) {
    int i = 0, count = 0;
    while(s[i] != '\0') {
        i++;
        count++;
    }
    return count;
}

// return 1 if matching, 2 if not matching
int ma(char* s1, char* s2, int i) {
    int match = 1, it_len = f_len(s2);
    for(int j = 0; j < it_len; j++){
        if(s1[i + j] == '\0') {
            // printf("ma: End Reached\n");
            match = 0;
            break;
        }
        if(s2[j] == '?') continue;
        if(s1[i + j] != s2[j]){
            // printf("ma: inequal vals, %c vs %c\n", s1[i], s2[i]);
            match = 0;
            break;
        }
    }
    return match;
}

char* str_matched(char* s1, int s2_len, int i) {
    char* res = (char *)malloc(sizeof(char) * s2_len);
    for(int j = 0; j < s2_len; j++){
        res[j] = s1[i + j];
    } 
    return res;
}

char** matches(char* s, char* pat, unsigned int* nmatches) {
    int i = 0, m = 0;

    int s_len = f_len(s);
    int p_len = f_len(pat);


    for(i = 0; i < s_len; i++) {
        // printf("For the %dst element, there is %d match(es) pattern, %s\n", i+1, ma(s, pat, i), pat);
        if(ma(s, pat, i)){
            m++;
        }
    }

    char** res = (char**)malloc(sizeof(char*) * m);
    
    int k = 0; //res iterator
    for(i = 0; i < s_len; i++) {
        if(ma(s, pat, i)){
            res[k++] = str_matched(s, p_len, i);
        }
    }
    *nmatches = m;
    return res;
}