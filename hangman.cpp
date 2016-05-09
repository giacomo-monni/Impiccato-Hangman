/* STILL TESTING */

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

#define JOLLY_CHARACTER '_'
#define MAX 27

using namespace std;

int CountLines (char filename [])
{
  ifstream fin;
  int lines;
  int c;

  lines=0;
  fin.open (filename);
  if (fin.is_open())
  {
    while ((c=fin.get ()) != EOF)
    {
      if (c=='\n')
        lines++;
    }
    fin.close();
  }
  else
    cerr<<"It isn't possible to open the file '"<<filename<<"'"<<endl;

  return lines;
}

void ReadWord (char filename[], int indexWord, char word [])
{
  ifstream fin;
  int i;
  int c;
  char s[101];

  fin.open (filename);
  if (fin.is_open())
  {
      for (i=1;i<=indexWord;i++)
        fin.getline(s,sizeof(s));
      fin.close();
      strcpy(word,s);
  }
  else
  {
    cerr<<"It isn't possible to open the file '"<<filename<<"'"<<endl;
    strcpy(word,"");
  }
}

void ChoosesSecretWord(char secretWord[])
{
  int i;

  srand(time(NULL));
  i=rand()%CountLines("dizionario.txt");
  ReadWord ("dizionario.txt", i+1, secretWord);

}

void ShowsWord (char word [])
{
  int i;
  for (i=0;i<strlen (word);i++)
    cout<<word[i]<<" ";
  cout<<endl;
}

void SetShowedWord (char secretWord [], char word [])
{
  int i;
  strcpy(word,secretWord);
  for (i=0;i<strlen(secretWord);i++)
  {
    word[i]=JOLLY_CHARACTER;
  }

}

int CharacterInWord (char c, char secretWord[])
{
  int i, cont;
  cont=0;
  for (i=0;i<strlen(secretWord);i++)
    if(secretWord[i]==c)
      cont++;
  return cont;
}

int JollyStillPresent (char word[])
{
  return (CharacterInWord(JOLLY_CHARACTER,word));
}

void SubstituteCharacterInWord (char c, char word[], char secretWord[])
{
  int i;
  for (i=0;i<strlen(word);i++)
    if (secretWord[i]==c)
      word[i]=secretWord[i];
}

int main ()
{
  bool letters[MAX];
  char word [MAX],secretWord [MAX];
  char c;
  int attempts;

  ChoosesSecretWord (secretWord);
  SetShowedWord (secretWord,word);

  attempts=10;

  while ((attempts>0)&&(JollyStillPresent(word)))
  {
    cout<<"The word to guess is: ";
    ShowsWord(word);
    cout<<"Choose a letter: ";
    cin>>c;
    c=toupper(c);
    if (CharacterInWord(c,secretWord))
      SubstituteCharacterInWord(c, word, secretWord);
    else
      attempts--;
    cout<<"You have "<<attempts<<" attempts"<<endl;
  }

  if (attempts==0){
    cout<<"Game Over! The word was "<<secretWord<<endl;
  }
  else
  {
    cout<<"Congratulations! You have guessed the word: "<<word<<endl;
    cout<<"Your score is:"<<attempts*10<<" points"<<endl;
  }
  return 0;
}
