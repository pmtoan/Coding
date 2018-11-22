int count_substring_in_string(const char* sub_str, const char* str)
{
    int count = 0;
    const char *tmp = str;
    while(tmp = strstr(tmp, sub_str))
    {
        count++;
        tmp++;
    }
    return count;
}