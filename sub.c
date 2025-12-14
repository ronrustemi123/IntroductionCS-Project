#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

const int KEY_SIZE = 26;

void encrypt(FILE *input, FILE *output, char *key);
void decrypt(FILE *input, FILE *output, char *key);
void reverseKey(char *reverseKeyArr, char *key);

int main(int argc, char *argv[])
{

  if(argc != 5)
  {
    printf("USAGE: ./sub KEY OUTPUT \n");
    return 1;
  }

  if(strlen(argv[1]) != KEY_SIZE)
  {
    printf("Key length must be 26 characters");
    return 3;
  }

  for (int i = 0; i < KEY_SIZE; i++) {
    if(!isalpha(argv[1][i]))
    {
      printf("Non aphabetical character in key \n");
      return 2;
    }

    for (int j = i + 1; j < KEY_SIZE; j++) {
      if(argv[1][i] == argv[1][j])
      {
        printf("Duplicate characters found in KEY\n");
        return 4;
      }
    }
  }

  int encryptFlag = 0;
  int decryptFlag = 0;

  for (int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-e") == 0)
    {
      encryptFlag++;
    }
    else if (strcmp(argv[i], "-d") == 0)
    {
      decryptFlag++;
    }
  }

  char *inputFile = argv[2];
  char *outputFile = argv[3];

  FILE *input = fopen(inputFile, "r");
  FILE *output = fopen(outputFile, "w");

  if(encryptFlag && !decryptFlag)
  {
    encrypt(input, output, argv[1]);
  } else if (!encryptFlag && decryptFlag)
  {
    decrypt(input, output, argv[1]);
  }

  remove(inputFile);
 
}

void reverseKey(char *reverseKeyArr, char *key)
{
  for (int i = 0; i < 26; i++) {
    reverseKeyArr[key[i] - 'A'] = 'A' + i;
  }
}

void decrypt(FILE *input, FILE *output, char *key)
{
  unsigned char charBuffer;
  char reversedKey[26];

  reverseKey(reversedKey, key);

  while(fread(&charBuffer, sizeof(unsigned char), 1, input) == 1)
  {
    if(isalpha(charBuffer))
    {
      int keyIndex;
      unsigned char substitutedChar;
      if(isupper(charBuffer))
      {
        keyIndex = charBuffer - 'A';
        substitutedChar = toupper(reversedKey[keyIndex]);
      }
      else 
      {
        keyIndex = charBuffer - 'a'; 
        substitutedChar = tolower(reversedKey[keyIndex]);
      }
      fwrite(&substitutedChar, sizeof(unsigned char), 1, output);
    }
    else
    {
      fwrite(&charBuffer, sizeof(unsigned char), 1, output);
    }
  }
  fclose(input);
  fclose(output);
}

void encrypt(FILE *input, FILE *output, char *key)
{
  unsigned char charBuffer;
while(fread(&charBuffer, sizeof(unsigned char), 1, input) == 1)
  {
    if (isalpha(charBuffer)) {
        int keyIndex;
        unsigned char substitutedChar;  
        if(isupper(charBuffer))
        {
          keyIndex = charBuffer - 'A';
          substitutedChar = toupper(key[keyIndex]);
        }
        else
        {
          keyIndex = charBuffer - 'a';
          substitutedChar = tolower(key[keyIndex]);
        } 
        fwrite(&substitutedChar, sizeof(unsigned char), 1, output);
    } else {
        fwrite(&charBuffer, sizeof(unsigned char), 1, output);
    }
  }

  fclose(input);
  fclose(output);
  
}
