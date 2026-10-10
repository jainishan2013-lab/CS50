#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// FUNCTION DECLARATION
void getting_number_of_input(string input, int *letters, int *words, int *sentences);

int main(void)
{
    // GETTING THE INPUT
    string input = get_string("Text: ");

    int total_letters = 0;
    int total_words = 1;
    int total_sentences = 0;

    // Calling function
    getting_number_of_input(input, &total_letters, &total_words, &total_sentences);

    // Coleman-Liau formula
    float L = (float) total_letters / total_words * 100;
    float S = (float) total_sentences / total_words * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = round(index);

    // Printing result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}

// DEFINING FUNCTION
void getting_number_of_input(string input, int *letters, int *words, int *sentences)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Letters
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            (*letters)++;
        }

        // Words
        if (input[i] == ' ')
        {
            (*words)++;
        }

        // Sentences
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            (*sentences)++;
        }
    }
}
