#include "ECReverseLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

/* Reverse the given linked list */
/* pHead: head node pointer to the linked list */
/* return the head of the reversed linked list */
/* note: don't allocate any new space using malloc; you should be able to reverse the linked list by just changing the pointers */
struct ECLinkedListNode* ECReverseLinkedList( struct ECLinkedListNode *pHead )
{
  /* Your code goes here */
  struct ECLinkedListNode *prevP = NULL;
  struct ECLinkedListNode *currP = pHead;
  struct ECLinkedListNode *nextP = NULL;

  while (currP != NULL){
    // store the next node
    nextP = currP->pNext;

    // reverse the nodes
    currP->pNext = prevP;

    // Move the pointers to the next position
    prevP = currP;
    currP = nextP;
  }
  // return the prevP b/c this is now the new head
  return prevP;
}

