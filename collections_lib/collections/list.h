#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

/**
 * @brief ListNode
 * Container for locating the next and previous items in a list
 * as well as storing data at a given point in the list. The data
 * IS NOT OWNED by the ListNode so the ListNode will not free the
 * node on cleanup.
 *
 */
typedef struct list_node_t {
  struct list_node_t* next;
  struct list_node_t* previous;
  void* data;
} ListNode;

/**
 * @brief List
 * Stores a linked list of ListNodes. The List owns the ListNodes
 * so it will free the memory needed for them on cleanup.
 *
 */
typedef struct {
  ListNode* head;
  ListNode* tail;
  size_t length;
} List;

#define ITER_CONTINUE 1
#define ITER_BREAK 0
/**
 * @brief Function which is called while iterating a list
 *
 * Note that this function can only cause side effects on the data. It's return
 * value is tied solely to whether or not to continue iterating
 *
 * @returns ITER_CONTINUE => continue iteration
 *          ITER_BREAK => break early
 *
 */
typedef int (*IteratorFunction)(void* data, void* accumulator);

/**
 * @brief list_init
 * Given a valid memory address which points to a location which
 * stores a list, set the list to initial values.
 *
 * @note: Calling this on a list that is already initialized can lead to
 * a memory leak if nodes existed in the list before. This should only be
 * called after the user has allocated the memory for the List.
 *
 * @param list
 */
void list_init(List* list);

/**
 * @brief Add an element to the front of the list
 *
 * @param list
 * @param data
 */
int list_insert_element_front(List* list, void* data);


/**
 * @brief Add an element to the back of the list
 *
 * @param list
 * @param data
 */
int list_insert_element_back(List* list, void* data);


/**
 * @brief removes a ListNode from the list and cleans up the memory
 *        which it was using.
 *
 * @param list
 * @param index
 * @return int  OK => was able to remove index
 *              EOUTOFRANGE => The index was not valid
 */
int list_remove_index(List* list, size_t index);

/**
 * @brief Removes all elements from the list. Cleans up any memory used by
 *        the list nodes.
 *
 * @param list
 */
int list_clear(List* list);

/**
 * @brief Calls the action on each node, passing in the data stored in the
 *        list node as the argument to the action.
 *        Iterates from head to tail.
 *
 *        breaks the iteration if action returns ITER_BREAK
 *
 * @param list
 * @param action
 */
void list_for_each_forward(List* list, IteratorFunction action, void* accumulator);


/**
 * @brief Calls the action on each node, passing in the data stored in the
 *        list node as the argument to the action.
 *        Iterates from tail to head
 *
 *        breaks the iteration if action returns ITER_BREAK
 *
 * @param list
 * @param action
 */
void list_for_each_backward(List* list, IteratorFunction action, void* accumulator);

/**
 * @brief Returns the number of elements in the list;
 *
 * @param list
 * @return size_t
 */
size_t list_length(List* list);

/**
 * @brief Checks that the list is structured properly.
 *        Should be called during tests. Optionally,
 *        if CHECK_OK is set to 1, this function will be called at the end of
 *        every operation.
 *
 * @param node
 * @return int 1 => ok
 *             0 => Error
 */
int list_ok(List* list);
#endif
