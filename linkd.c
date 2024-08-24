#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* createNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}


void printList(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {     
        printf("%d --> ", temp->data);  
        temp = temp->next;
        
    }
    printf("NULL\n");
}


void add(Node* head, int data)
{
    Node* newNode = createNode(data);
    Node* temp = head;
 
    while (temp != NULL)
    {
	if (temp->next == NULL)
        {
            temp->next = newNode;
            return;
        }
        temp = temp->next;        
    }
}


typedef struct LinkedList {
    Node* head;
    void* tail;
} LinkedList;


LinkedList* init(int values[])
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    
    Node* head = createNode(values[0]);
    list->head = head;
    
    for (int i = 1; i < 15; i++)
    {
        add(head, values[i]); 
    }

    return list;
}


int main(void)
{
    int values[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    LinkedList* list = init(values);

    printList(list->head);

    while (list->head != NULL)
    {
        Node* temp = list->head;
        list->head = temp->next;
        free(temp); 
    
    }

    return 0;
}

