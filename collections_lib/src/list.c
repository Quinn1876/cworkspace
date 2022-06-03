#include "collections/list.h"
#include "collections/common.h"

void list_init(List* list) {
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
}


int list_insert_element_front(List* list, void* data) {
  list->length++;
  ListNode* new_node = malloc(sizeof(ListNode));
  new_node->data = data;
  new_node->next = list->head;
  new_node->previous = NULL;

  if (list->length == 1) {
    list->head = new_node;
    list->tail = new_node;
    return OK;
  }

  list->head->previous = new_node;
  list->head = list->head->previous;
  #if CHECK_OK == 1
  if (list_ok(list) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

int list_insert_element_back(List* list, void* data) {
  list->length++;
  ListNode* new_node = malloc(sizeof(ListNode));
  new_node->data = data;
  new_node->next = NULL;
  new_node->previous = list->tail;

  if (list->length == 1) {
    list->head = new_node;
    list->tail = new_node;
    return OK;
  }

  list->tail->next = new_node;
  list->tail = list->tail->next;
  #if CHECK_OK == 1
  if (list_ok(list) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

int list_remove_index(List* list, size_t index) {
  if (index >= list->length) {
    return EOUTOFRANGE;
  }
  ListNode* runner = list->head;
  for (size_t i = 1; i <= index; i++) {
    runner = runner->next;
  }
  if (runner == list->head)
    list->head = runner->next;
  if (runner == list->tail)
    list->tail = runner->previous;

  if (runner->next != NULL)
    runner->next->previous = runner->previous;
  if (runner->previous != NULL)
    runner->previous->next = runner->next;

  free(runner);
  --list->length;
  #if CHECK_OK == 1
  if (list_ok(list) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

int list_clear(List* list) {
  while(list->head != NULL) {
    ListNode* runner = list->head;
    list->head = list->head->next;
    free(runner);
    --list->length;
  }
  #if CHECK_OK == 1
  if (list_ok(list) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

void list_for_each_forward(List* list, IteratorFunction action, void* accumulator) {
  ListNode* runner = list->head;
  int result = 1;
  while (runner != NULL && result) {
    result = action(runner->data, accumulator);
    runner = runner->next;
  }
}

void list_for_each_backward(List* list, IteratorFunction action, void* accumulator) {
  ListNode* runner = list->tail;
  int result = 1;
  while (runner != NULL && result) {
    result = action(runner->data, accumulator);
    runner = runner->previous;
  }
}

size_t list_length(List* list) {
  return list->length;
}

int list_ok(List* list) {
  if (list->length < 0) return DATASTRUCT_ERROR;

  if (list->length == 0) {
    int ok = list->head == NULL && list->tail == NULL;
    return ok;
  }
  if (list->length == 1) {
    int ok = list->head != NULL && list->head == list->tail;
  }

  int counter = 0;
  ListNode* runner = list->head;
  while (runner != NULL) {
    counter++;
    runner = runner->next;
  }
  if (list->length != counter) return DATASTRUCT_ERROR;

  counter = 0;
  runner = list->tail;
  while (runner != NULL) {
    counter++;
    runner = runner->previous;
  }
  if (list->length != counter) return DATASTRUCT_ERROR;

  return DATASTRUCT_OK;
}
