#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int counter(string text, bool (*matches)(char));
int count_letters(string text);
bool check_if_Letter(char character);
int count_words(string text);
bool check_if_Space(char character);
int count_sentences(string text);
bool check_if_end_sentence(char character);
float Coleman_Liau_index(int lelength, int lewords, int lesentences);
void print_index(float index);

int main(void)
{
    string text = get_string("Text: ");
    float index = Coleman_Liau_index(count_letters(text), count_words(text), count_sentences(text));
    print_index(index);
}

int counter(string text, bool (*matches)(char)) // go through all elements of the string and looks for matches
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (matches(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

int count_letters(string text)
{
    return counter(text, check_if_Letter);
}

bool check_if_Letter(char character)
{
    return isalpha(character);
}

int count_words(string text)
{
    return counter(text, check_if_Space) + 1; // only counts the places between words
}

bool check_if_Space(char character)
{
    return (character == ' ');
}

int count_sentences(string text)
{
    return counter(text, check_if_end_sentence);
}

bool check_if_end_sentence(char character)
{
    return (character == '.' || character == '!' || character == '?');
}

float Coleman_Liau_index(int lelength, int lewords, int lesentences)
{
    float L = ((float) lelength * 100) / lewords;
    float S = ((float) lesentences * 100) / lewords;
    return 0.0588 * L - 0.296 * S - 15.8;
}

void print_index(float index)
{
    int grade = (int) round(index);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (15 < grade)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}