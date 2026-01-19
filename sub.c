
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define KEY_SIZE 26 // numri i shkronjave ne alfabetin anglez

// prototipet e funksioneve
void encrypt(FILE *input, FILE *output, char *key);
void decrypt(FILE *input, FILE *output, char *key);
void reverseKey(char *reverseKeyArr, char *key);

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    printf("USAGE: ./sub KEY (-e | -d) INPUT OUTPUT\n");
    return 1;
  }

  char key[KEY_SIZE + 1];

  // bejme nje kopje te celsit qe te mund ta modifikiojm
  for (int i = 0; i < KEY_SIZE; i++)
    key[i] = argv[1][i];
  key[KEY_SIZE] = '\0';

  // bejme celsin ne uppercase
  for (int i = 0; i < KEY_SIZE; i++)
    key[i] = toupper(key[i]);


  if (strlen(key) != KEY_SIZE)
  {
    printf("Key length must be 26 characters\n");
    return 2;
  }

  for (int i = 0; i < KEY_SIZE; i++)
  {
    if (!isalpha(key[i]))
    {
      printf("Key must contain only letters\n");
      return 3;
    }

    for (int j = i + 1; j < KEY_SIZE; j++)
    {
      if (key[i] == key[j])
      {
        printf("Duplicate characters in key\n");
        return 4;
      }
    }
  }

  // shohim se a duhet te bejm decrypt apo encrypt ne baze se cilin ka shtypur useri
  int encryptFlag = 0, decryptFlag = 0;

  if (strcmp(argv[2], "-e") == 0)
    encryptFlag = 1;
  else if (strcmp(argv[2], "-d") == 0)
    decryptFlag = 1;
  else
  {
    printf("Must specify -e or -d\n");
    return 5;
  }

  // hapim filesat qe do nevoiten
  FILE *input = fopen(argv[3], "rb");
  FILE *output = fopen(argv[4], "wb");

  if (!input || !output)
  {
    printf("Error opening file(s)\n");
    return 6;
  }

  if (encryptFlag)
    encrypt(input, output, key);
  else
    decrypt(input, output, key);

  // fshim file-in qe nuk na duhet me
  remove(argv[3]);

  return 0;
}

// shkruajm funksionin reverse key qe do nevoitet per logjiken a decryptit
void reverseKey(char *reverseKeyArr, char *key)
{
  for (int i = 0; i < KEY_SIZE; i++)
    reverseKeyArr[key[i] - 'A'] = 'A' + i;
}

void encrypt(FILE *input, FILE *output, char *key)
{
  // shkruajm logjiken e substitution cipher si ne CS50
  unsigned char c;

  while (fread(&c, 1, 1, input) == 1)
  {
    if (isalpha(c))
    {
      if (isupper(c))
        c = key[c - 'A'];
      else
        c = tolower(key[c - 'a']);
    }
    fwrite(&c, 1, 1, output);
  }

  fclose(input);
  fclose(output);
}

void decrypt(FILE *input, FILE *output, char *key)
{
  // shkruajm logjiken e substitution cipher por me celsin e modifikuar
  unsigned char c;
  char reversedKey[KEY_SIZE];

  reverseKey(reversedKey, key);

  while (fread(&c, 1, 1, input) == 1)
  {
    if (isalpha(c))
    {
      if (isupper(c))
        c = reversedKey[c - 'A'];
      else
        c = tolower(reversedKey[c - 'a']);
    }
    fwrite(&c, 1, 1, output);
  }

  fclose(input);
  fclose(output);
}

