#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void printDeck(CardDeck deck);
static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}



void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck);
void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
  for (int i = 0; i < origDeck.size - 1; i++)
  {
    strncpy(leftDeck[i].cards, &origDeck.cards[0], i + 1);
    strncpy(rightDeck[i].cards, &origDeck.cards[i+1], origDeck.size - (i + 1));

    leftDeck[i].size = i + 1;
    rightDeck[i].size = origDeck.size - (i + 1);
  }
}



void interleaveHelper(CardDeck ShuffledDeck, CardDeck leftDeck, CardDeck rightDeck, int round);
void interleaveHelper(CardDeck ShuffledDeck, CardDeck leftDeck, CardDeck rightDeck, int round)
{
  // If leftDeck is empty, copy rightDeck to ShuffledDeck
  if (leftDeck.size == 0)
  {
    // If empty, add remaining rightDeck cards
    for(int i=0; i < (rightDeck.size); i++)
    {
      //copy card
      strncpy(&ShuffledDeck.cards[ShuffledDeck.size], &rightDeck.cards[i], 1);

      //copy size
      ShuffledDeck.size = ShuffledDeck.size + 1;
    }

	shuffle(ShuffledDeck, round - 1);
    return;
  }
    
  // If rightDeck is empty, copy leftDeck to ShuffledDeck
  if (rightDeck.size == 0)
  {
    // Add remaining leftDeck cards
    for(int i=0; i < (leftDeck.size); i++)
    {
      //copy card
			strncpy(&ShuffledDeck.cards[ShuffledDeck.size], &leftDeck.cards[i], 1);

      //copy size
      ShuffledDeck.size = ShuffledDeck.size + 1;
    }

    shuffle(ShuffledDeck, round - 1);
    return;
  }

	// For recursive operation, create new left and right deck
  CardDeck new_leftDeck;
  new_leftDeck.size = 0;
	
	CardDeck new_rightDeck;
  new_rightDeck.size = 0;
	
	// Create new schuffled deck for left and right
	CardDeck leftShuffledDeck;
  leftShuffledDeck.size = ShuffledDeck.size;

  CardDeck rightShuffledDeck;
  rightShuffledDeck.size = ShuffledDeck.size;

	// Handle left Deck	
  for(int i=0; i < (ShuffledDeck.size); i++) strncpy(&leftShuffledDeck.cards[i], &ShuffledDeck.cards[i], 1);  
		
  // Add to left Shuffled Deck from left deck
	strncpy(&leftShuffledDeck.cards[leftShuffledDeck.size], leftDeck.cards, 1);
  leftShuffledDeck.size += 1;

	// Fill new left Deck
  for(int i=1; i < (leftDeck.size); i++)
  {
    strncpy(&new_leftDeck.cards[i-1], &leftDeck.cards[i], 1);
      new_leftDeck.size += 1;
  }

	// Recursion
	interleaveHelper(leftShuffledDeck, new_leftDeck, rightDeck, round);
 		
  // Handle right Deck
  for(int i=0; i < (ShuffledDeck.size); i++) strncpy(&rightShuffledDeck.cards[i], &ShuffledDeck.cards[i], 1);  

  // Add to right Shuffled Deck from right deck
	strncpy(&rightShuffledDeck.cards[rightShuffledDeck.size], rightDeck.cards, 1);
  rightShuffledDeck.size += 1;

  // Fill new right Deck 
  for(int i=1; i < (rightDeck.size); i++)
  {
    strncpy(&new_rightDeck.cards[i-1], &rightDeck.cards[i], 1);
    new_rightDeck.size += 1;  
  }
		
  // Recursion
  interleaveHelper(rightShuffledDeck, leftDeck, new_rightDeck, round);
}



void interleave(CardDeck leftDeck, CardDeck rightDeck, int round);
void interleave(CardDeck leftDeck, CardDeck rightDeck, int round)
{
  CardDeck ShuffledDeck;
  ShuffledDeck.size = 0;
  
  interleaveHelper(ShuffledDeck, leftDeck, rightDeck, round);
}



void ActualShuffle(CardDeck origDeck, int round);
void ActualShuffle(CardDeck origDeck, int round)
{
    int pair_count = origDeck.size - 1;
    CardDeck * leftDeck = (CardDeck *) malloc(pair_count * sizeof(CardDeck));
    CardDeck * rightDeck = (CardDeck *) malloc(pair_count * sizeof(CardDeck));

    divide(origDeck, leftDeck, rightDeck);

    for (int j = 0; j < pair_count; j++)
    {
        interleave(leftDeck[j], rightDeck[j], round);
    }

    free(leftDeck);
    free(rightDeck);
}



void shuffle(CardDeck origDeck, int round)
{
  if (round <= 0)
  {
      printDeck(origDeck);
      return;
  }

  ActualShuffle(origDeck, round);

  return;
}