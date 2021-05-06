// include & typedefs
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//#define _FORCE_MEM_ERROR

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


// function declaration
int getListLength(Node list);
bool isListSorted(Node list);
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code);






// internal helper functions

void printList (Node list)
{
    while (list)
    {
        printf("%d, ", list->x);
        list = list->next;
    }
    printf("\n");
}

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
        else
        {
            list = list->next;
        }
    }

    // Reached NULL, the list is sorted
    return true;
}




// Frees the entire list
void freeFullList(Node list)
{
    while(list)
    {
        Node next_node = list->next;
        free(list);
        list = next_node;
    }
}

// Allocate next node
Node allocateNextNode (Node list_start)
{
    #ifdef _FORCE_MEM_ERROR
    if (list_start != NULL)
    {
        freeFullList(list_start);
        return NULL;
    }
    
    #endif
    Node next_node = malloc(sizeof(*next_node));

    // If the allocation failed, free everything we allocated so far
    if (next_node == NULL)
    {
        freeFullList(list_start);
        return NULL;
    }

    // Return new node
    next_node->next = NULL;
    return next_node;
}

// Adds all elements from old_list to new_list in their order. Returns true if process succeded
bool addAllElementsToNewList(Node old_list, Node new_list, ErrorCode *error_code)
{
    while (old_list)
    {
        new_list->x = old_list->x;

        // Finished scanning the list
        if (old_list->next == NULL)
        {
            break;
        }

        // Allocate next node
        Node next_node = allocateNextNode(new_list);
        if (next_node == NULL)
        {
            *error_code = MEMORY_ERROR;
            return false;
        }

        // Moving current_node forward
        new_list->next = next_node;
        new_list       = next_node;
        old_list       = old_list->next;
    }
    return true;
}

// Verify the user has supplied valid input
bool verifyValidInput (Node list1, Node list2, ErrorCode* error_code)
{
    // Verify error_code is a valid pointer
    if (error_code == NULL)
    {
        // can't update error_code :(
        return false;
    }

    // Verify the lists aren't empty
    int list1_length = getListLength(list1);    
    int list2_length = getListLength(list2);
    
    if (list1_length == 0 || list2_length == 0)
    {
        *error_code = NULL_ARGUMENT;
        return false;
    }

    // Verify the lists are sorted
    if (isListSorted(list1) != true || isListSorted(list2) != true)
    {
        *error_code = UNSORTED_LIST;
        return false;
    }

    // Input is valid
    return true;
}

// Merges two sorted lists into a new one, returning it. Error codes will be provided through the ErrorCode variable 
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code)
{
    
    // Verifies the input is valid. If it's invalid, the error_code will be updated
    if (verifyValidInput(list1, list2, error_code) == false)
    {
        return NULL;
    }
    

    // Memory allocation for new list - allocate 1 node at a time
    Node new_list = allocateNextNode(NULL);
    if (new_list == NULL)
    {
        *error_code = MEMORY_ERROR;
        return NULL;
    }

    Node current_node = new_list; // For iteration purposes

    // While both lists still have elements    
    while (list1 && list2)
    {
        // If current list1 value is bigger than the current list2 value
        if (list1->x > list2->x)
        {
            // Put the value in the current node and move list1 to
            current_node->x = list2->x;
            list2           = list2->next;
        }
        else
        {
            // Put the value in the current node and move list2 to 
            current_node->x = list1->x;
            list1           = list1->next;
        }

        // Allocate next node
        Node next_node = allocateNextNode(new_list);
        if (next_node == NULL)
        {
            *error_code = MEMORY_ERROR;
            return NULL;
        }
        
        // Moving current_node forward
        current_node->next = next_node;
        current_node       = next_node;
    }

    // 1 list still has elements
    Node list_remainer = list1 == NULL ? list2 : list1;
    bool add_elements_result = addAllElementsToNewList(list_remainer, current_node, error_code);
    if (add_elements_result == false)
    {
        return NULL;
    }

    *error_code = SUCCESS;
    return new_list;

}   //// EDGE CASE






int main()
{
    Node list1 = allocateNextNode(NULL);
    Node list2 = allocateNextNode(NULL);

    list1->x = -9999;
    list2->x = 0;
    
    int current_list = 1;
    Node iter = list1;
    while (current_list <= 2)
    {
        int input = -1;
        printf("Enter number for list%d. To move on press -1\n", current_list);
        scanf("%d", &input);
        if(input == -1)
        {
            current_list++;
            iter = list2;
        }
        else
        {
            if (input == -2)
            {
                current_list++;
                if (current_list == 2)
                {
                    freeFullList(list1);
                    list1 = NULL;
                    iter = list2;
                }
                else
                {
                    freeFullList(list2);
                    list2 = NULL;
                    iter = NULL;
                }
            }
            else
            {
                Node next_node  = allocateNextNode(list1);
                iter->next = next_node;
                next_node->x    = input;
                iter = next_node;
            }
        }

    }

    printf("lists:\n");
    printList(list1);
    printList(list2);
    ErrorCode err;
    printf("\n");

    Node merged = mergeSortedLists(list1, list2, &err);
    if (merged == NULL)
    {
        printf("err is %d", err);
    }
    else
    {
        printList(merged);

    }
    
    freeFullList(list1);
    freeFullList(list2);
    freeFullList(merged);
    list1 = list2 = merged = NULL;

    return 0;
}