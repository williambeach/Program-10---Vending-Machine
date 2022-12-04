/* William Beach
 * COP2220 Intro to Programming in C
 * user defined struct implementing functions from program 8 and knowledge applied from program 9 - November 15, 2022
 */

#define _CRT_SECURE_NO_WARNINGS //for Visual Studio compiler
#pragma warning(disable:6031) //ignore scanf warnings for Visual Studio compiler

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define SIZE 30

typedef struct {
	char word[SIZE];
	char upperCase[SIZE];
	char reverse[SIZE];
	int length, numVowels;
}wordInfo;

void Greeting(char name[]); //greets user and stores their name
void GetWord(char input[], char copy[]); //gets word from user and stores a copy of the word
void UppercaseWord(char upper[]); //takes in a word and uppercases all of its letters
int CountVowels(char upper[]); //displays number of each vowel and its index location, returns total number of vowels
void ReverseTheWord(char upper[], char reverse[]); //reverses word
void SaveToFile(FILE *outPtr, wordInfo wordList[], int num);

int main() {
    char firstName[30], word[30], copyOfWord[30], upperCase[30], reversed[30], sentinel;
    wordInfo wordList[SIZE];
    int count = 0;
    FILE outPtr;
    Greeting(firstName);
    printf("%s, Would you like to enter a word? 'y' (YES) 'n' (NO) ", firstName);
    scanf(" %c", &sentinel);
    while (sentinel != 'n') {
        GetWord(word, copyOfWord);
        UppercaseWord(copyOfWord);
        strcpy(upperCase, copyOfWord);
        ReverseTheWord(upperCase, reversed);
        printf("Printing the words in the main function:\n");
        printf("original word: %s\n", word);
        printf("uppercase: %s\n", upperCase);
        printf("reverse: %s\n", reversed);
        int totalVowels = CountVowels(upperCase);
        printf("The total number of vowels is %d\n", totalVowels);
        printf("----------------------------------------------\n");
        strcpy(wordList[count].word, word); //copies word of type string into struct at index of count (from 0 index till user ends)
        strcpy(wordList[count].upperCase, upperCase); //copies Uppercase word of type string into struct at index of count (from 0 index till user ends)
        strcpy(wordList[count].reverse, reversed); //copies reversed word of type string into struct at index of count (from 0 index till user ends)
        wordList[count].length = strlen(word); // initializes the string length of word in struct using dot access 
        wordList[count].numVowels = totalVowels;
        count++; // counter that keeps track of which index of struct array user is 
        printf("%s, Would you like to enter a word? 'y' (YES) 'n' (NO) ", firstName);
        scanf(" %c", &sentinel);
    }
    SaveToFile(&outPtr, wordList, count); //saves struct array to output file
    printf("Thank you, %s, have a great day!", firstName);
    return 0;
};


void Greeting(char name[]) { //greets user
    printf("Hello there, please enter your first name: \n");
    scanf(" %s", name);
    printf("***  Welcome to the character array practice program  ***\n");
    printf("---------------------------------------------------------\n");
};

void GetWord(char input[], char copy[]) { //gets word from user and copies it to copy of word string
    printf("Please enter a word: ");
    scanf(" %s", input);
    strcpy(copy, input);
};

void UppercaseWord(char upper[]) { //uppercases word and stores it in string upper
    int i;
    int length = strlen(upper);
    for (i = 0; i < length; i++) {
        upper[i] = toupper(upper[i]);
    }
};

int CountVowels(char upper[]) { //counts how many vowels there are in the word using switch block and returns value
    int j;
    int a = 0, e = 0, i = 0, o = 0, u = 0;
    int length = strlen(upper);
    for (j = 0; j < length; j++) {
        switch (upper[j]) {
            case 'A':
                printf("There is an 'A' located at index %d\n", j);
                a += 1;
                break;
            case 'E':
                printf("There is an 'E' located at index %d\n", j);
                e += 1;
                break;
            case 'I':
                printf("There is an 'I' located at index %d\n", j);
                i += 1;
                break;
            case 'O':
                printf("There is an 'O' located at index %d\n", j);
                o += 1;
                break;
            case 'U':
                printf("There is an 'U' located at index %d\n", j);
                u += 1;
                break;
        }
    }
    printf("The total number of A's is %d\n", a);
    printf("The total number of E's is %d\n", e);
    printf("The total number of I's is %d\n", i);
    printf("The total number of O's is %d\n", o);
    printf("The total number of U's is %d\n", u);
    printf("Printing the total number of vowels in the main function: \n");
    return a + e + i + o + u;
};

void ReverseTheWord(char upper[], char reverse[]) { //reverse user word
    int i, count = 0;
    int length = strlen(upper);
    for (i = length - 1; i >= 0; i--) {
        reverse[count] = upper[i];
        count++;
    }
    reverse[length] = '\0';
};

void SaveToFile(FILE *outPtr, wordInfo wordList[], int num) { //save each struct in struct array to output file
    int i;
    printf("Saving all the information in the word list to the output file\n");
    outPtr = fopen("wordsProg10.txt", "w");
    for (i = 0; i < num; i++) {
        fprintf(outPtr, "Struct %d\n\n", i + 1);
        fprintf(outPtr, "The input word was: %s\n", wordList[i].word);
        fprintf(outPtr, "The input word has %d letters\n", wordList[i].length);
        fprintf(outPtr, "The uppercase version is: %s\n", wordList[i].upperCase);
        fprintf(outPtr, "The reverse is: %s\n", wordList[i].reverse);
        fprintf(outPtr, "The total number of vowels is: %d\n\n", wordList[i].numVowels);
    }
    fclose(outPtr);
};