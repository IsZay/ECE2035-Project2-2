//=================================================================
// Implementation for DLL module.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {

    // Your code here
    // Okay so this is to create just a brand new llnode with this data
    // Basically the llnode's constructor

    LLNode* node = (LLNode*) malloc(sizeof(LLNode)); 
    node->data = data; // TODO Changed this
    node->prev = NULL;
    node->next = NULL;
    return node; // replace this
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*) malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

// TODO should I do error checking? Like make sure that the linkedList passed in isn't null?
// Post this on Ed Discussion after the break!

int getSize(DLinkedList* dLinkedList){

  // Your code here
  // int theSize = dLinkedList->size;
  return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){

  // Your code here

  return dLinkedList->head; // replace this
}

LLNode* getTail(DLinkedList* dLinkedList){

  // Your code here

  return dLinkedList->tail; // replace this
}

LLNode* getNext(LLNode* node){

  // Your code here

  return node->next; // replace this
}

LLNode* getPrev(LLNode* node){

  // Your code here

  return node->prev; // replace this
}

void* getData(LLNode* node){

  // Your code here

  return node->data; // replace this
}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }

  // Your code here
  // Idea
  // Create a new node
  // Then set its next to the current prev_node's next
  // Then set its previous to current prev_node's spot
  // Then go to the prev_node's next and set its previous to the current node
  // Then go to that prev_node and set its next to the added node you just passed in
  // alr bet this is O(1)

  LLNode* newNode = create_llnode(data); // Should this be &data or data
  newNode->next = prev_node->next;
  newNode->prev = prev_node;
  if (prev_node->next != NULL) { // If the node that prev_node was pointing to as next is not null
    // Then we want it to point to newNode
    prev_node->next->prev = newNode; // TODO this will give an error if the next is null. Unless we are assuming that if there is a node, only its data can be null
  }
  prev_node->next = newNode; // should this be &newNode
  // lowkey I think thats it
  
  // if (dLinkedList->size == 1) {
  //   // update the tail
  //   dLinkedList->tail = next;
  // }
  if (dLinkedList->tail == prev_node) {
    // update tail this way instead
    dLinkedList->tail = newNode;
  } 

  dLinkedList->size++;
  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }

  // Your code here
  // Idea
  // Create a new node
  // Then set its next to the current next_node
  // Then set its previous to current next_node's prev
  // Then go to the next_node->prev's  and set its next to the newNode
  // Then go to that next_node and set its prev to the added node you just passed in
  // alr bet this is O(1)

  LLNode* newNode = create_llnode(data);
  newNode->next = next_node;
  newNode->prev = next_node->prev;
  if (next_node->prev != NULL) {
    next_node->prev->next = newNode;
  }
  next_node->prev = newNode;
  dLinkedList->size++;

  if (dLinkedList->head == next_node) {
    // update head then
    dLinkedList->head = newNode;
  }

  return;
}

void insertHead(DLinkedList* dLinkedList, void* data){

  // Please ask a TA how this void* data is giving us the address of m[0] even though you are inputting m[0] and not &m[0]
  // printf("This is insertHead\n");
  // printf("The head pointer is currently %x \n", dLinkedList->head);
  // printf("The tail pointer is currently %x \n", dLinkedList->tail);
  // printf("%x: data \n", data);
  // printf("%x:  &data \n", &data);



  if(dLinkedList->head == NULL){
    // If there are no nodes in the list
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode; // TODO  changed this to &newNode
    dLinkedList->tail = newNode; // TODO did same thing
    dLinkedList->size++;


    // printf("This is after adding to an empty list with insertHead\n");
    // printf("The head pointer is currently %x \n", dLinkedList->head);
    // printf("The tail pointer is currently %x \n", dLinkedList->tail);
    // printf("%x: data \n", data);
    // printf("%x:  &data", &data);

  }else{

    insertBefore(dLinkedList, dLinkedList->head, data); // TODO insertBefore(dLinkedList, dLinkedList->head, &data) WITH AMPERSTAND &??????
    // dLinkedList->size++; Do NOT Increment, InsertAFter already does
    return; // can you call a different method here instead? Do you need a return statement here?
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){

  // Your code here


  // printf("This is insertTail\n");
  // printf("The head pointer is currently %x \n", dLinkedList->head);
  // printf("The tail pointer is currently %x \n", dLinkedList->tail);
  // printf("%x: data \n", data);
  // printf("%x:  &data", &data);






  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  } else if (dLinkedList->tail == NULL) {
    // this should never occur!
  } else {

    insertAfter(dLinkedList, dLinkedList->tail, data); // why not &dLinkedList? insertAfter(dLinkedList, dLinkedList->tail, &data) ?????
    // dLinkedList->size++; Do not incremenet anymore you already did in insertBefore/After
    return; // can you call a different method here instead? Do you need a return statement here?
  }
}

// TOOD Alright after all that, I did no edge checking. For the adding, if the size was 1, then that you gotta update tail. And you know do all the things
// I mean if you update Tail everytime though correctly though by going to InsertAfter

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){

  // Your code here
  // okay assume that Node is defined
  // I don't think this method works as expected. I'm still getting leaks!
  if (dLinkedList->size == 0) {
    printf("You can't delete something if nothing is there!");
    return;
  } else if (dLinkedList->size == 1) {
    // printf("You are trying to destroy the only node in the list, which is %x\n", Node);
    dLinkedList->head = NULL;
    dLinkedList->tail = NULL;
    // free(Node); // I really hope this works it should per slide 14 of Heap introduction

  } else if (Node == dLinkedList->head) {
    // printf("You are trying to destroy the head of this list, which is %x\n", Node);
    // if we are destroying the head
    // make sure the next node is not pointing to NULL now
    // make sure that we destroy this node
    // and set head pointer to nextNode
    // LLNode* nextNode = getNext(Node);
    dLinkedList->head = Node->next;
    Node->next->prev = NULL;
    // free(Node);

  } else if (Node == dLinkedList->tail) {
    // printf("You are trying to destroy the tail of this list, which is %x\n", Node);
    dLinkedList->tail = Node->prev;
    Node->prev->next = NULL;
    // free(Node);
  } else {
    // printf("You are trying to a Node in this list, which is %x\n", Node);
    // Node's previous' next should be Node's next
    // Node's next' previous should be Node's previous!
    Node->prev->next = Node->next;
    Node->next->prev = Node->prev;
    // free(Node); // I think that's it??
  }
  dLinkedList->size--;
  free(Node->data); // free Node's data
  free(Node); // as well as Node!

}

void destroyList(DLinkedList* dLinkedList){

  // Your code here
  // make sure you go through each node or else you wil get memory leaks.
  // maybe do a for loop??
  int sizeList = dLinkedList->size; // this will update if you delete a node
  for (int i = 0; i < sizeList; i++) {
    deleteNode(dLinkedList, dLinkedList->head); // This frees and decreases size of list
  }
  // now that the list is indeed empty (everything freed), you got to do that to the list too
  free(dLinkedList); // I really hope this is right
} 

DLinkedList* split(DLinkedList* dLinkedList, LLNode* Node)
{
  if (Node == dLinkedList->tail) {
    return NULL;
  }

  // Your code here
  // Okay, so we need to make a new list by allocating space on the heap
  DLinkedList* newList = create_dlinkedlist();
  // Now that you have a newList, set its head and tail
  newList->head = Node->next; // defined since we know NOde is not the tail
  newList->head->prev = NULL; // make sure you are not pointing behind you!
  newList->tail = dLinkedList->tail;


  dLinkedList->tail = Node;
  dLinkedList->tail->next = NULL;
  // head stays the same
  
  
  // Okay after much trying we have to do a for loop to see how big the newList is
  LLNode* current = newList->head;
  int count = 0;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  newList->size = count;
  // printf("New newList size is %d\n", newList->size);

  dLinkedList->size = dLinkedList->size - newList->size;
  // printf("New dLinkedList size is %d\n", dLinkedList->size);

  return newList; // replace this
}
