#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void initialize_alphabet(char alphabet[]);
bool test_length_26(string key);
bool test_only_alphabetic_character(string key);
bool test_whole_alphabet_in_key(string key);
bool test_character_more_than_once_in_key(char character, string key);
bool is_key_valid();
string encode(string key, string text);

int const length_alphabet = 26, length_ASCII = 128;

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argv[2] != NULL)
    {
        return 1;
    }
    if (!is_key_valid(key))
    {
        return 1;
    }
    char alphabet[length_alphabet];
    initialize_alphabet(alphabet);
    string text = get_string("plaintext : ");
    text = encode(key, text);
    printf("ciphertext: %s\n", text);
}

void initialize_alphabet(char alphabet[length_alphabet])
{
    int j = 0;
    for (char i = 'A'; i <= 'Z'; i++)
    {
        alphabet[j] = i;
        j++;
    }
}

bool test_length_26(string key)
{
    return (strlen(key) == length_alphabet);
}

bool test_only_alphabetic_character(string key)
{
    for (int i = 0; i < length_alphabet; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}

bool test_whole_alphabet_in_key(string key)
{
    for (int i = 0; i < length_alphabet; i++)
    {
        if (test_character_more_than_once_in_key(key[i], key))
        {
            return false;
        }
    }
    return true;
}

bool test_character_more_than_once_in_key(char character, string key)
{
    int j = 0;
    for (int i = 0; i < length_alphabet; i++)
    {
        if (tolower(character) == tolower(key[i]))
        {
            j++;
        }
    }
    return (j != 1);
}

bool is_key_valid(string key)
{
    bool valid = true;
    if (key == NULL || !test_length_26(key))
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    if (!test_only_alphabetic_character(key))
    {
        printf("Key must only contain alphabetic characters.\n");
        return false;
    }
    if (!test_whole_alphabet_in_key(key))
    {
        printf("Key must not contain repeated character.\n");
        return false;
    }
    return true;
}

string encode(string key, string text)
{
    int ASCII[128];
    for (int i = 0; i < length_ASCII; i++)
    {
        ASCII[i] = i;
    }
    for (int i = 0; i < length_alphabet; i++)
    {
        ASCII[i + ((int) 'a')] = (int) tolower(key[i]);
        ASCII[i + ((int) 'A')] = (int) toupper(key[i]);
    }
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = ASCII[(int) text[i]];
    }
    return text;
}