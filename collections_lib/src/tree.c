#include "collections/tree.h"


static int tree_insert_recurse(Node* head, void* data, Hash hash);
static void tree_traverse_inorder_recurse(Node* head, Hash hash, IteratorFunction func, void* accumulator);

void tree_init(Tree* tree, Hash hash) {
  tree->hash = hash;
  tree->head = NULL;
}

int tree_clear(Tree* tree) {
  #if CHECK_OK == 1
  if (tree_ok(tree) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

int tree_insert(Tree* tree, void* data) {
  if (tree->head == NULL) {
    tree->head = node_new(data);
  } else {
    int tree_insert_result = tree_insert_recurse(tree->head, data, tree->hash);
    if (tree_insert_result != OK) {
      return tree_insert_result;
    }
  }

  #if CHECK_OK == 1
  if (tree_ok(tree) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

void* tree_find(Tree* tree, int key) {
  #if CHECK_OK == 1
  if (tree_ok(tree) == DATASTRUCT_ERROR) {
    return EDATOKFAIL;
  }
  #endif
  return OK;
}

void tree_traverse_inorder(Tree* tree, IteratorFunction func, void* accumulator) {
  Node* head = tree->head;
  tree_traverse_inorder_recurse(head, tree->hash, func, accumulator);
}

int tree_ok(Tree* tree) {

  return DATASTRUCT_OK;
}

/**
 * @brief Recursive helper function for inserting into the tree.
 *        Does not ballance the tree
 *
 * @param head
 * @param data
 * @param hash
 * @return int OK => ok
 *             EDATAFOUND => Attempting to insert a value that already exists
 *             EDATAOKFAIL => some part of this operation left a portion of the state unrecognizable
 */
static int tree_insert_recurse(Node* head, void* data, Hash hash) {
  int data_hash = hash(data);
  void* head_data = node_get_data(head);
  int head_hash = hash(head_data);
  size_t num_children = node_num_children(head);
  if (data_hash == head_hash) return EDATAFOUND;

  if (data_hash < head_hash) {
    if ( num_children == 2) {
      return tree_insert_recurse(node_get_child(head, 0), data, hash);
    } else if (num_children == 1) {
      Node* child = node_get_child(head, 0);
      int child_hash = hash(node_get_data(child));
      if (child_hash == data_hash)
        return EDATAFOUND;
      else if (child_hash < head_hash)
        return tree_insert_recurse(node_get_child(head, 0), data, hash);
    }
    return node_push_child_front(head, node_new(data));
  }

  if ( num_children == 2) {
      return tree_insert_recurse(node_get_child(head, 1), data, hash);
    } else if (num_children == 1) {
      Node* child = node_get_child(head, 0);
      int child_hash = hash(node_get_data(child));
      if (child_hash == data_hash)
        return EDATAFOUND;
      else if (child_hash > head_hash) // child is right child
        return tree_insert_recurse(node_get_child(head, 0), data, hash);
    }
    // no children or child is left child
    return node_push_child_back(head, node_new(data));
}

/**
 * @brief traverse the tree in order calling func on each node
 *
 */
static void tree_traverse_inorder_recurse(Node* head, Hash hash, IteratorFunction func, void* accumulator) {
  if (head == NULL) return;
  size_t num_children = node_num_children(head);
  int head_hash = hash(node_get_data(head));

  if (num_children == 0) {
    func(node_get_data(head), accumulator);
    return;
  }

  if (num_children == 1) {
    Node* child = node_get_child(head, 0);
    int child_hash = hash(node_get_data(child));
    if (child_hash < head_hash) {
      tree_traverse_inorder_recurse(child, hash, func, accumulator);
      func(node_get_data(head), accumulator);
      return;
    } else {
      func(node_get_data(head), accumulator);
      tree_traverse_inorder_recurse(child, hash, func, accumulator);
      return;
    }
  }

  Node* left_child = node_get_child(head, 0);
  Node* right_child = node_get_child(head, 1);
  tree_traverse_inorder_recurse(left_child, hash, func, accumulator);
  func(node_get_data(head), accumulator);
  tree_traverse_inorder_recurse(right_child, hash, func, accumulator);
}
