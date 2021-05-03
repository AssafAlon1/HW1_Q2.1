#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;


typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;


int getListLength(Node list);
bool isListSorted(Node list);
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code);


// helper
int getListLength(Node list)
{
    int list_length = 0;
    while (list != NULL)
    {
        list_length++;
        list = list->next;
    }
    return list_length;
}

// helper
bool isListSorted(Node list)
{
    // Check if current node & next node aren't NULL
    while (list != NULL && list->next != NULL)
    {
        // If the current value is BIGGER than the next one, the list isn't sorted
        if (list->x > list->next->x)
        {
            return false;
        }
    }

    // Reached NULL, the list is sorted
    return true;
}



// TO PUBLISH
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code)
{

    // error_code cannot be NULL, otherwise we can't alert the user if something's wrong
    if (error_code == NULL)
    {
        // can't update error_code :(
        return NULL;
    }
    
    // Check if lists are empty
    int list1_length = getListLength(list1);    
    int list2_length = getListLength(list2);
    
    if (list1_length == 0 || list2_length == 0)
    {
        *error_code = NULL_ARGUMENT;
        return NULL;
    }
    
    // Check if lists are sorted
    if (isListSorted(list1) != true || isListSorted(list1) != true)
    {
        *error_code = UNSORTED_LIST;
        return NULL;
    }

    // Memory allocation for new list - allocate all
    int total_length = list1_length + list2_length;
    Node new_list = (Node)malloc(sizeof(Node)*total_length);
    if (new_list == NULL)
    {
        *error_code = MEMORY_ERROR;
        return NULL;
    }

    // Merge the two list
    //Node first_node   = new_list; // Will be returned

    Node current_node = new_list; // For iteration purposes

    for (int i = 0; i < total_length; i++)
    {
        // If we finished adding a list to our new list, exit the loop
        if (list1 == NULL || list2 == NULL)
        {
            break;
        }

        // If current list1 value is bigger than the current list2 value
        if (list1->x > list2->x)
        {
            // Put the value in the current node and move list1 to 
            current_node->x = list2->x;
            list2 = list2->next;

            // current_node
            current_node->next = current_node++;
            
        }
        else
        {
            // put other val
            // 2 = 2->next
        }

        // update current_node
    }

    // PUT LEFTOVERS

    // 

    // assert();
    
    //*error_code = SUCCESS
    return NULL; // return the real

}   //// EDGE CASE





// // helper function to handle this
//         if (list1 == NULL)
//         {
//             current_node->x = list2->x;
//             list2 = list2->next;
//             continue;
//         }

//         if (list2 == NULL)
//         {
//             current_node->x = list1->x;
//             list1 = list1->next;
//             continue;
//         }
//         //