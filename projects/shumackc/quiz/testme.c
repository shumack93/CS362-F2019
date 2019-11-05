/******************************************************************************
** Author:     Cris Shumack
** Date:       11/04/2019
** Assignment: Random Testing Quiz
******************************************************************************/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char randomCharacter;

	//Assigns a random character between the 'Space' and '~'
	//characters (all keyboard characters) to the randomCharacter variable.
	randomCharacter = (rand() % 95) + 32;    

	//Returns the random character generated above.
	return randomCharacter;
}

char *inputString()
{
	int i;
	char randomString[6];

	//Loops through the first 5 elements of the randomString array and
	//assigns a random lowercase letter between 'a' and 't'. I tried
	//'a' through 'z' first and it took over the 5 minute limit.
	for (i = 0; i < 5; i++)
		randomString[i] = (rand() % 20) + 97;

	//Sets the last element of the array to the null terminator character.
	randomString[5] = '\0';

	//Returns the random string generated above.
	return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
