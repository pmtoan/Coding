char* replace_string(const char* string, const char* substr, const char* replacement)
{
    /*
    *	todo: Replace a sub-string in a string
    *	Example:
    *		replace_string("hello world", "hello", "hi") -> hi world
    */
    char* tok = NULL;
    char* newstr = NULL;
    char* oldstr = NULL;
    int   oldstr_len = 0;
    int   substr_len = 0;
    int   replacement_len = 0;
    newstr = strdup(string);
    substr_len = strlen(substr);
    replacement_len = strlen(replacement);

    if (substr == NULL || replacement == NULL) {
        return newstr;
    }
    while ((tok = strstr(newstr, substr))) {
        oldstr = newstr;
        oldstr_len = strlen(oldstr);
        newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));
        if (newstr == NULL) {
            free(oldstr);
            return NULL;
        }
        memcpy(newstr, oldstr, tok - oldstr);
        memcpy(newstr + (tok - oldstr), replacement, replacement_len);
        memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
        memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);
        free(oldstr);
    }
    return newstr;
}