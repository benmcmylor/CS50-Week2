#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Program to compute the readability of given text using the Coleman-Liau formula

//Declare functions
int countlet(string a);
int countwrd(string a);
int countsnt(string a);
int gradecalc(int letters, int words, int sentences);

//Start Main
int main(void)
{
    //prompt the user to submit some text for analysis
    string text = get_string("Text: ");

    //get the grade of the text
    int letters = countlet(text);
    int words = countwrd(text);
    int sentences = countsnt(text);
    int grade = gradecalc (countlet(text), countwrd(text), countsnt(text));
    //printf ("%i letter(s)\n%i word(s)\n%i sentence(s)\n", letters, words, sentences);

    //print the analysis
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;
}

//Define function to count number of letters in a string
int countlet(string a)
{
    //work out the length of the string
    int len = strlen(a);

    //loop through the string and count any character that is either upper or lowercase
    //avoiding use of isalpha to prevent false positives
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (islower(a[i]) != 0 || isupper(a[i]) != 0)
        {
            count++;
        }
    }
    return count;
}

//Define a function to count the number of words in a string
int countwrd(string a)
{
    //determine the length of the string
    int len = strlen(a);

    //loop through the string looking for groups of characters separated by spaces.
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (isgraph(a[i]) != 0 && isspace(a[i + 1]) != 0)
        {
            count++;
        }
        else if (i == (len - 1) && isgraph(a[i]) != 0)
        {
            count++;
        }
    }
    return count;
}

//Define a function that counts the number of sentences in a string
int countsnt(string a)
{
    //determine the length of the string
    int len = strlen(a);

    //loop through the string looking for punctation to demarcate sentence boundaries
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if ((int) a[i] == 33 || (int) a[i] == 46 || (int) a[i] == 63)
        {
            count++;
        }
    }
    return count;
}

//Define a function to calculate the reading age, based on Coleman-Liau number
int gradecalc(int letters, int words, int sentences)
{
    //calculate the average number of letters per 100 words
    float l = ((float) letters / (float) words) * 100;
    //calculate the average number of sentences per 100 words
    float s = ((float) sentences / (float) words) * 100;
    //calculate the coleman-liau index
    float index = (0.0588 * l) - (0.296 * s) - 15.8;

    //round to the nearest integer
    int grade = round(index);

    return grade;
}
