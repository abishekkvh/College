#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_STATES 20

char alphabets[MAX];
char inputString[MAX];
int isFinal[MAX_STATES];

int getSymbolIndex(char symbol, int numOfAlphabets)
{
  for (int i = 0; i < numOfAlphabets; i++)
  {
    if (alphabets[i] == symbol)
    {
      return i;
    }
  }

  return -1;
}

int main()
{
  int numOfStates, startState, numOfAcceptingStates, numOfAlphabets,
      currentState;

  printf("Enter no. of states : ");
  scanf("%d", &numOfStates);

  int statesList[MAX_STATES];
  printf("Enter the %d states (separated by space, e.g., 2 3 4 5): ",
         numOfStates);
  for (int i = 0; i < numOfStates; i++)
  {
    scanf("%d", &statesList[i]);
  }

  printf("Enter Starting state : ");
  scanf("%d", &startState);

  for (int i = 0; i < MAX_STATES; i++)
  {
    isFinal[i] = 0;
  }

  printf("Enter no. of accepting states : ");
  scanf("%d", &numOfAcceptingStates);

  if (numOfAcceptingStates > 0)
  {
    printf("Enter the %d accepting states: ", numOfAcceptingStates);
    for (int i = 0; i < numOfAcceptingStates; i++)
    {
      int finalState;
      scanf("%d", &finalState);

      if (finalState >= 0 && finalState < MAX_STATES)
      {
        isFinal[finalState] = 1;
      }
    }
  }

  printf("Enter no. of Alphabets : ");
  scanf("%d", &numOfAlphabets);

  if (numOfAlphabets > 0)
  {
    printf("Enter the %d alphabets (separated by space): ", numOfAlphabets);
    for (int i = 0; i < numOfAlphabets; i++)
    {
      scanf(" %c", &alphabets[i]);
    }
  }

  printf(
      "Enter the transition table (states as rows, alphabets as columns):\n");
  int transitionTable[MAX_STATES][MAX];

  for (int i = 0; i < MAX_STATES; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      transitionTable[i][j] = -1;
    }
  }

  for (int i = 0; i < numOfStates; i++)
  {
    for (int j = 0; j < numOfAlphabets; j++)
    {
      scanf("%d", &transitionTable[statesList[i]][j]);
    }
  }

  while (1)
  {
    printf("Enter the string to check: ");
    scanf("%s", inputString);

    currentState = startState;
    int isValid = 1;

    for (int i = 0; i < strlen(inputString); i++)
    {
      int symbolIndex = getSymbolIndex(inputString[i], numOfAlphabets);

      if (symbolIndex == -1)
      {
        printf("String not accepted (Invalid symbol '%c')\n", inputString[i]);
        isValid = 0;
        break;
      }

      if (transitionTable[currentState][symbolIndex] == -1)
      {
        isValid = 0;
        break;
      }

      currentState = transitionTable[currentState][symbolIndex];
    }

    if (isValid && isFinal[currentState])
    {
      printf("String \"%s\" Accepted\n", inputString);
    }
    else if (isValid)
    {
      printf("String \"%s\" Rejected\n", inputString);
    }
  }

  return 0;
}
