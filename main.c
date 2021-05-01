#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;


typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;


int getListLength(Node list);
bool isListSorted(Node list);
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code);


// TODO
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

// TODO
bool isListSorted(Node list)
{
    // Check if current node & next node aren't NULL
    while (list != NULL && list->next != NULL)
    {
        // If the current value is BIGGER than the next one, the list isn't sorted
        if (list->x > list->next)
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

    /* ??? WHAT IF ERROR_CODE IS NULL ??? */

    // Check if lists are empty
    int list1_lenght = getListLength(list1);    
    int list2_lenght = getListLength(list2);
    if (list1_lenght == 0 || list2_lenght == 0)
    {
        *error_code = EMPTY_LIST;
        /// return NULL; ????
    }

    // Check if lists are sorted
    if (isListSorted(list1) != true || isListSorted(list1) != true)
    {
        return 
    }
    // check lists lenght

    // memory allocation for new list

    // if the memory alocation failed , return MEMORY_ERROR

    // merge the two list

    // 

    // assert();
    

}   //// EDGE CASE