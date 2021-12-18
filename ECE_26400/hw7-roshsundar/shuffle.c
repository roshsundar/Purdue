// ***
// *** You must modify this file
// ***

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// do not modify this function
static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

#ifdef TEST_DIVIDE
// leftDeck and rightDeck are arrays of CardDeck
// This function creates pairs of left and right decks
// Each pair divides the original deck into two non-overlapping decks and
// together they form the original deck.
//
// You can think of the left deck held by the left hand taking some
// cards (at least one) from the top of the original deck.
//
// The right deck is held by the right hand taking some (at least one)
// cards from the bottom of the original deck.
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
#endif

#ifdef TEST_INTERLEAVE

// Interleave two decks to generate all possible results.
//
// If the leftDeck is {'A'} and the right deck is {'2', '3'}, this
// function prints
// A 2 3
// 2 A 3
// 2 3 A
//
// If the leftDeck is {'A', '2'} and the right deck is {'3', '4'}, this
// function prints 
// 3 4 A 2
// 3 A 4 2
// A 3 4 2 
// 3 A 2 4 
// A 3 2 4 
// A 2 3 4 
//
// Please notice the space does not matter because grading will use
// diff -w
//
// How to generate all possible interleaves?

// Understand that a card at a particular position can come from
// either left or right (two options). The following uses left for
// explanation but it is equally applicable to the right.
//
// After taking one card from the left deck, the left deck has one
// fewer card. Now, the problem is the same as the earlier problem
// (thus, this problem can be solved by using recursion), excecpt one
// left card has been taken. Again, the next card can come from left
// or right.
//
// This process continues until either the left deck or the right deck
// runs out of cards. The remaining cards are added to the result.
// 
// It is very likely that you want to create a "helper" function that
// can keep track of some more arguments.  If you create a helper
// function, please keep it inside #ifdef TEST_INTERLEAVE and #endif
// so that the function can be removed for grading other parts of the
// program.

void interleaveHelper(CardDeck ShuffledDeck, CardDeck leftDeck, CardDeck rightDeck);

void interleaveHelper(CardDeck ShuffledDeck, CardDeck leftDeck, CardDeck rightDeck)
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

		printDeck(ShuffledDeck);
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

    printDeck(ShuffledDeck);
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
	interleaveHelper(leftShuffledDeck, new_leftDeck, rightDeck);
 		
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
  interleaveHelper(rightShuffledDeck, leftDeck, new_rightDeck);
}

void interleave(CardDeck leftDeck, CardDeck rightDeck)
{
  CardDeck ShuffledDeck;
  ShuffledDeck.size = 0;
  
  interleaveHelper(ShuffledDeck, leftDeck, rightDeck);
}
#endif

#ifdef TEST_SHUFFLE
// The shuffle function has the following steps:

// 1. calculate the number of possible left and right decks. It is
// the number of cards - 1 because the left deck may have 1, 2,...,
// #cards - 1 cards.
//
// 2. allocate memory to store these possible pairs of left and right
// decks.
//
// 3. send each pair to the interleave function
//
// 4. release allocated memory
//
void shuffle(CardDeck origDeck)
{
  int pair_count = origDeck.size - 1;

  
  CardDeck * leftDeck = (CardDeck *) malloc(pair_count * sizeof(CardDeck));
  CardDeck * rightDeck = (CardDeck *) malloc(pair_count * sizeof(CardDeck));

  divide(origDeck, leftDeck, rightDeck);

  for (int i = 0; i < pair_count; i++)
  {
    interleave(leftDeck[i], rightDeck[i]);
  }

  free(leftDeck);
  free(rightDeck);
}
#endif
