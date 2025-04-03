#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node * node = malloc(sizeof(struct list_node));
  if(node == NULL) {
    return NULL;
  }
  node -> value = value;
  node -> next = NULL;
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * new_head = new_node(value);
  if(new_head != NULL) {
    new_head -> next = list -> head;
    list -> head = new_head;
  }
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node * new_tail = new_node(value);
  if(new_tail != NULL) {
    if(list -> head == NULL) {
      list -> head = new_tail;
    }
    else {
      struct list_node * currnode = list -> head;
      while(currnode -> next != NULL) {
        currnode = currnode -> next;
      }
      currnode -> next = new_tail;
    }
  }
}

size_t remove_from_head(struct linked_list *list) { 
  if(list -> head == NULL) {
    return 0;
  }
  else {
    size_t ret_val = list -> head -> value;
    struct list_node * new_head = list -> head -> next;
    free(list -> head);
    list -> head = new_head;
    return ret_val;
  }
}

size_t remove_from_tail(struct linked_list *list) { 
  if(list -> head == NULL) {
    return 0;
  }
  else {
    struct list_node * currnode = list -> head;
    size_t ret_val;
    if(currnode -> next == NULL) {
      ret_val = list -> head -> value;
      free(list -> head);
      list -> head = NULL;
      return ret_val;
    }
    else {
      //advance to second-to-last node
      while(currnode -> next -> next != NULL) {
        currnode = currnode -> next;
      }
      ret_val = currnode -> next -> value;
      free(currnode -> next);
      currnode -> next = NULL;
      return ret_val;
    }
  }
}

void free_list(struct linked_list list) {
  if(list.head != NULL) {
    struct list_node * currnode = list.head;
    struct list_node * nextnode = list.head;
    while(currnode != NULL) {
      nextnode = nextnode -> next;
      free(currnode);
      currnode = nextnode;
    }
    list.head = NULL;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}


