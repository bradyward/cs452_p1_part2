/**Update this file with the starter code**/
#include <stdio.h>
#include <stdlib.h>
#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    // Create the list
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->destroy_data = destroy_data;
    list->compare_to = compare_to; 
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));
    // Setup the sentinel node
    list->head->data = NULL;
    list->head->next = NULL;
    list->head->prev = NULL;
    // Return the list
    return list;
}

void list_destroy(list_t **list) {
    // Destroy the data of each node and free them
    node_t *current = (*list)->head->next;
    // while (current != NULL) {
    while ((*list)->size > (size_t)0) {
        node_t *next = current->next;
        (*list)->destroy_data(current->data);
        free(current);
        current = next;
        (*list)->size--;
    }
    // Free the list itself
    // ???
    // free((*list)->head->data);
    // free((*list)->head->next);
    // free((*list)->head->prev);
    
    free(current);
    //free((*list)->head);
    free(*list);
}

list_t *list_add(list_t *list, void *data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    // List is empty
    if (list->size == (size_t)0) {
        list->head->next = new_node;
        list->head->prev = new_node;
        new_node->next = list->head;
        new_node->prev = list->head;
        list->size++;
        return list;
    }
    else {
        node_t *front = list->head->prev; // Pointer to "front" of the list
        // Add the new node to the front, pointing to the sentinel node
        new_node->prev = front;
        new_node->next = list->head;
        front->next = new_node;
        // Connect the sentinel node to the new node
        list->head->prev = new_node;
        // Return the list
        list->size++;
        return list;
    }
}

void *list_remove_index(list_t *list, size_t index) {
    // Find the node to be removed
    node_t *current = list->head->next;
    for (int i = 0; (size_t)i < index; i++) {
        if (current == NULL) {
            return NULL;
        }
        current = current->next;
    }
    // Current now points to node to remove
    // Disconnect current from the list
    current->prev->next = current->next;
    current->next->prev = current->prev;
    // Destroy current
    list->size--;
    list->destroy_data(current->data);
    free(current);
}

int list_indexof(list_t *list, void *data) {
    int index = -1;
    node_t *current = list->head->next;
    // Search for the node with matching data
    for (int i = 0; (size_t)i < list->size; i++) {
        if (list->compare_to(current->data, data) == 0) {
            return index;
        }
        index++;
    }
    // The node was not found
    return -1;
}