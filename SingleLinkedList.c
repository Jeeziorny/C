#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

struct Node
{
    int key;
    struct Node *next;
};

///inserting on tail of the list.
void insert(struct Node** head, const int key);
///deleting first node which contains key = key;
void delete(struct Node** head, const int key);
///tell if list is empty;
bool isEmpty(struct Node** head);
///findMTF search key on list. If found it puts
///node one element earlier;
bool findMTF(struct Node** head, const int key);
///findTRANS search key on list. If key has found
///it puts it on the head of the list.
bool findTRANS(struct Node** head, const int key);
///debugging
void print(struct Node *head);

int globalCounter = 0;

int main(void)
{
    srand(time(NULL));
    struct Node* list = NULL;
    struct Node* list2= NULL;

    //array initialization
    int tempArray[100];
    for(int i = 0; i < 100; i++)
        tempArray[i] = i;
    //permutation
    for (int i = 99; i >= 0; --i)
    {
        int j = rand() % (i+1);

        int temp = tempArray[i];
        tempArray[i] = tempArray[j];
        tempArray[j] = temp;
    }
    //inserting
    for(int i = 0; i < 100; i++)
    {
        insert(&list, tempArray[i]);
        insert(&list2,tempArray[i]);
    }

    int max = 0;
    int sum = 0;

    while(!isEmpty(&list))
    {
        for(int i = 0; i < 101; i++)
        {
            if(findMTF(&list, i))
            {
                max = i;
            }
        }
        delete(&list, max);
        max = 0;
        sum += globalCounter;
        globalCounter = 0;
    }
    printf("Comparisons in findMTF: %d\n", sum);
    sum = 0;
    max = 0;
    while(!isEmpty(&list2))
    {
        for(int i = 0; i < 101; i++)
        {
            if(findTRANS(&list2, i))
            {
                max = i;
            }
        }
        delete(&list2, max);
        max = 0;
        sum += globalCounter;
        globalCounter = 0;
    }

    printf("Comparisons in findTRANS: %d", sum);
    return 0;
}

bool findTRANS(struct Node** head, const int key)
{
    struct Node* thirdNode = NULL;
    struct Node* secondNode = *head;
    struct Node* currNode = *head;

    while(currNode != NULL && currNode->key != key)
    {
        thirdNode = secondNode;
        secondNode = currNode;
        currNode = currNode->next;
        globalCounter += 2;
    }
    //currNode == NULL xor currNode->key == key.
    if(currNode != NULL) //currNode->key == key, list is not empty.
    {
        if(secondNode == *head) //list has one xor two nodes.
        {
            if(thirdNode != NULL) //list has two nodes.
            {
                secondNode->next = currNode->next;
                *head = currNode;
                currNode->next = secondNode;

                globalCounter += 3;

                return true;
            }
            else //list has one node that is searched key.
            {
                globalCounter += 3;
                return true;
            }
        }
        else //list has three xor more nodes.
        {
            thirdNode->next = currNode;
            secondNode->next = currNode->next;
            currNode->next = secondNode;

            globalCounter += 2;
            return true;
        }
    }
    globalCounter += 1;
    return false;
}

bool findMTF(struct Node** head, const int key)
{
    struct Node* lastNode = *head;
    struct Node* currNode = *head;

    while(currNode != NULL && currNode->key != key)
    {
        lastNode = currNode;
        currNode = currNode->next;

        globalCounter += 2;
    }

    if(currNode != NULL) //currNode->key == key.
    {
        if(currNode != lastNode) //currNode is not the head of list.
        //if condition is not met searching key is in head of list, so nothing to do.
        {
            lastNode->next = currNode->next;
            currNode->next = *head;
            *head = currNode;
        }
        globalCounter += 2;
        return true;
    } //list does not contain searching key.
    globalCounter += 1;
    return false;
}

bool isEmpty(struct Node** head)
{
    globalCounter++;
    return *head == NULL;
    /*
    if(*head == NULL)
        return true;
    return false;*/
}

void delete(struct Node ** head, const int key)
{
    struct Node* lastNode = *head;
    struct Node* currNode = *head;

    while(currNode != NULL && currNode->key != key)
    {
        lastNode = currNode;
        currNode = currNode->next;

        globalCounter += 2;
    }
    //currNode == NULL xor currNode->key == key;
    if(currNode != NULL) //currNode->key == key;
    {
        if(currNode != lastNode) // searching key is not on first position.
        {
            lastNode->next = currNode->next;
            free(currNode);
        }
        else //searching key is in head of the list.
        {
            *head = (*head)->next;
            free(currNode);
        }
        globalCounter++;
    }
    else // list does not contain searching key.
    {
        return;
    }
}

void print(struct Node *head)
{
    struct Node *n =  head;
    while(n != NULL)
    {
        printf("%d  ", n->key);
        n = n->next;
    }
    printf("\n");
}

void insert(struct Node** head, const int key)
{
    //constructing node newTail with new key.
    struct Node* newTail = (struct Node*)malloc(sizeof(struct Node));
    newTail->key = key;
    newTail->next = NULL;

    if(*head == NULL) //list is empty.
    {
        *head = newTail;
        return;
    }
    //list has one xor more elements.
    struct Node* tempNode = *head;
    while(tempNode->next != NULL)
    {
        tempNode = tempNode->next;
    }
    tempNode->next = newTail;
}
