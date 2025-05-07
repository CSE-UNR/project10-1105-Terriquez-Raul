//Author: Raul Terriquez
//Purpose: Project 10
//Date: 05/01/2025

#include <stdio.h>
#define GUESSWORD 25 //length limit of guess word
#define MASTERWORDLENGTH 25 //Master word length
#define MAXWORDS 100
#define MASTERWORDFILE "mystery.txt"
void grabGuess(int *guessCount, char guessArray[6][GUESSWORD]);
void grabMasterWordList(char wordList[MAXWORDS][MASTERWORDLENGTH], int *wordCount);
void makeLowerCase(char str[]);
void compareAndDisplayGuess(char guess[], char master[]);
int isValidLength(char str[]);
int isMatch(char str1[], char str2[]); 
int main(){
	int guessCounter = 0, wordCount = 0;
	char allGuesses[6][GUESSWORD];
	char wordList[MAXWORDS][MASTERWORDLENGTH];
	grabMasterWordList(wordList, &wordCount);
	char masterWord[MASTERWORDLENGTH];
	int i = 0;
	while (wordList[0][i] != '\0') {
    		masterWord[i] = wordList[0][i];
    		i++;
	}
	masterWord[i] = '\0';
	makeLowerCase(masterWord); 

	do{
	
		grabGuess(&guessCounter, allGuesses);
		compareAndDisplayGuess(allGuesses[guessCounter], masterWord);
		if (isMatch(allGuesses[guessCounter], masterWord)) {
    			printf("Congratulations! You guessed the word!\n");
    			break;
		}
		guessCounter++;
	}while(guessCounter < 6);
	if (guessCounter == 6 && !isMatch(allGuesses[guessCounter - 1], masterWord)) {
		printf("Game Over! The correct word was: %s\n", masterWord);
	}
	return 0;
}
int isMatch(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // Not a match
        }
        i++;
    }
    // Return 1 only if both strings ended at the same length
    return str1[i] == '\0' && str2[i] == '\0';
}
void compareAndDisplayGuess(char guess[], char master[]) {
    char display[GUESSWORD];
    char indicator[GUESSWORD];
    int usedInMaster[GUESSWORD] = {0};  

    int i;
    for (i = 0; guess[i] != '\0'; i++) {
        if (guess[i] == master[i]) {
            display[i] = guess[i] - 'a' + 'A';  
            indicator[i] = ' ';
            usedInMaster[i] = 1;  
        } else {
            display[i] = guess[i]; 
            indicator[i] = ' ';
        }
    }

    display[i] = '\0';
    indicator[i] = '\0';
    for (i = 0; guess[i] != '\0'; i++) {
        if (guess[i] != master[i]) {
            int j;
            for (j = 0; master[j] != '\0'; j++) {
                if (!usedInMaster[j] && guess[i] == master[j]) {
                    indicator[i] = '^';
                    usedInMaster[j] = 1;
                    break;
                }
            }
        }
    }

    printf("%s\n", display);
    printf("%s\n", indicator);
}
int isValidLength(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    return length == 5;
}
void grabGuess(int *guessCount, char guessArray[6][GUESSWORD]){
	do {
        printf("GUESS %d! Enter your guess: ", *guessCount + 1);
        scanf("%s", guessArray[*guessCount]);
        makeLowerCase(guessArray[*guessCount]);

        if (!isValidLength(guessArray[*guessCount])) {
            printf("Invalid guess length. Please enter a five-letter word.\n");
        }
    } while (!isValidLength(guessArray[*guessCount]));
}
void makeLowerCase(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += 'a' - 'A';
		}
	}
}
void grabMasterWordList(char wordList[MAXWORDS][MASTERWORDLENGTH], int *wordCount){
	FILE *masterWordFile;
	masterWordFile = fopen(MASTERWORDFILE, "r");
	if(masterWordFile == NULL){
		printf("Failed to open %s file stream.\n", MASTERWORDFILE);
		return;
	}
	int i = 0;
	while(i < MAXWORDS && fscanf(masterWordFile, "%s", wordList[i])==1){
		i++;
	}
	*wordCount = i;
	fclose(masterWordFile);
}
