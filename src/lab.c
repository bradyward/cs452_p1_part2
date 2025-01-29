/**Update this file with the starter code**/
#include <stdio.h>
#include <stdlib.h>
#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    // Create the list
    list_t *list = (list_t *)malloc(sizeof(list_t));
        printf("allocating *list %p\n", (void*)list);

    // TODO: Did malloc return NULL?

    list->destroy_data = destroy_data;
    list->compare_to = compare_to; 
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));
        printf("allocating list->head %p\n", (void *)list->head);    

    
    // Setup the sentinel node
    list->head->data = NULL;
    list->head->next = list->head;
    list->head->prev = list->head;
    // Return the list
    return list;
}

void list_destroy(list_t **list) {

    list_t *plst = *list;
    
    // Destroy the data of each node and free them
    node_t *current = (*list)->head->next;
    // while (current != NULL) {
    while ((*list)->size > (size_t)0) {
        node_t *next = current->next;
        (*list)->destroy_data(current->data);

        printf("freeing current %p\n", (void *)current);    
        free(current);

        current = next;
        (*list)->size--;
    }
    // Free the list itself
    // ???
    // free((*list)->head->data);
    // free((*list)->head->next);
    // free((*list)->head->prev);
    
        printf("freeing current %p\n", (void *)current);    
    free(current);


    //free((*list)->head);
        printf("freeing plst %p\n", (void *)plst);    
    free(plst);


    //     printf("freeing list %d\n", &list);
    // free(list);

    current = NULL;
    plst = NULL;
    *list = 0;
}

list_t *list_add(list_t *list, void *data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
            printf("allocating new_node %p\n", (void *)new_node);    

    // TODO: Did malloc return NULL?
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
        node_t *front = list->head->next; // Pointer to "front" of the list
        // Add the new node to the front, pointing to the sentinel node
        new_node->prev = list->head;
        new_node->next = front;
        
        // Connect the sentinel node to the new node
        front->prev = new_node;
        // list->head->next->prev = new_node;
        list->head->next = new_node;

        // Return the list
        list->size++;
        return list;
    }
}

void *list_remove_index(list_t *list, size_t index) {
    // Find the node to be removed
    if ((size_t)index >= list->size) {
        return NULL;
    }
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

    void *data_copy = malloc(sizeof(int)); 
            printf("allocating data_copy %p\n", (void *)data_copy);    
 // Assuming stored data is an int
    if (data_copy == NULL) {
        printf("Data_copy was null\n");
        free(data_copy);
        return NULL;  // Memory allocation failed
    }

    *(int *)data_copy = *(int *)(current->data);
    list->destroy_data(current->data);
    free(current);
    printf("freeing %d\n", current);
    return data_copy;
}

int list_indexof(list_t *list, void *data) {
    node_t *current = list->head->next;
    // Search for the node with matching data
    for (int i = 0; (size_t)i < list->size; i++) {
        if (list->compare_to(current->data, data) == 0) {
            return i;
        }
        current = current->next;
    }
    // The node was not found
    return -1;
}