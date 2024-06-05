/*
 * A singly linked list program
 * With different functions for list manipulation
 * And access of elements.
 */



#include <assert.h>
#include <stdio.h>
#include <malloc.h>

struct node {
    int data; //data
    struct node* next; //address of the next node
};

struct node* start_node;
static void createNodeList(int, struct node**); //create a linked list with specified number of elements
static void displayNodes(struct node**); // display linked list
static int computeSum(struct node**); // compute the sum of elements in linked list
static int findElement(int, struct node**); // find an element with its value
static void freeMem(struct node**); // free allocated memory by the linked list
static void addBack(int, struct node**); // add at the end of the list a new node
static void addFront(int, struct node**); // add at the front of the list a new node
static void addAfterIndex(int, int, struct node**); //add a new node after the specified index
static void addBeforeIndex(int, int, struct node**); //add a new node before the specified index
static int listLength(struct node**); //returns the length of the list
static int getElement(int, struct node**); //get a node with its index
static struct node* map(int (*g)(int), struct node**); //returns a new list mapped by a function
static void map_mut(int (*g)(int), struct node**); //mapps the same list by a function
static struct node* foldf(int, int (*g)(int,int), struct node**); //returns a new list mapped by a function

int f (int x) {
    return x + 1;
}
int m(int x, int a) {
    return x * a;
}

int main(void) {
    int numberOfNodes;
    printf("Input the number of nodes\n");
    scanf("%d",&numberOfNodes);
    createNodeList(numberOfNodes, &start_node);
    displayNodes(&start_node);
    puts("\n");
    struct node* mappedNode = foldf(5, &m, &start_node);
    displayNodes(&mappedNode);
    return 0;
}

static void createNodeList(int totalNodes, struct node** start_node) {
    struct node* newNode;
    struct node* nodeBuffer;
    int nodeData;
    int nodeCounter;

    //allocate memory of start node
    *start_node = (struct node*)malloc(sizeof(struct node));

    printf("Input data for node 1\n");
    scanf("%d", &nodeData);

    (*start_node)->data = nodeData;
    (*start_node)->next = NULL;
    nodeBuffer = *start_node;

    for(nodeCounter = 1; nodeCounter < totalNodes; nodeCounter++) {

        newNode = (struct node*)malloc(sizeof(struct node));

        if(newNode == NULL) {
            printf("Memory cannot be allocated");
            break;
        }
            scanf("%d",&nodeData);
            newNode->data = nodeData;
            newNode->next = NULL;

            nodeBuffer->next = newNode;
            nodeBuffer = nodeBuffer->next;

    }
}

static void displayNodes(struct node** start_node) {

        struct node* nodeBuffer;
        nodeBuffer = *start_node;

        if(nodeBuffer == NULL) {
            printf("list is empty");
        }
        else {
            while(nodeBuffer != NULL) {
                printf("%d\n",nodeBuffer->data);
                nodeBuffer = nodeBuffer->next;
            }
        }
}

static int computeSum(struct node** start_node) {
    struct node* nodeBuffer;
    int sum = 0;

    nodeBuffer = *start_node;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
    }else {

        while(nodeBuffer != NULL) {
            sum += nodeBuffer->data;
            nodeBuffer = nodeBuffer->next;
        }
    }
    return sum;
}

static int findElement(int element, struct node** start_node) {
    struct node* nodeBuffer;
    int count = 0;
    nodeBuffer = *start_node;

    if(nodeBuffer == NULL)
            printf("the list is empty");
    else {
        while (nodeBuffer != NULL) {
            if(count == element) {
                return (nodeBuffer->data);
            }
            count++;
            nodeBuffer = nodeBuffer->next;
        }
    }
    assert(0);
}

static void freeMem(struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    free(nodeBuffer);
}
static void addBack(int data,struct node** start_node) {
    struct node* nodeBuffer;
    struct node* new_node;

    nodeBuffer = *start_node;
    new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = data;

    if(nodeBuffer == NULL) {
        nodeBuffer = new_node;
    }

    while (nodeBuffer->next != NULL) {
            nodeBuffer = nodeBuffer->next;
    }

    nodeBuffer->next = new_node;
}
static void addFront(int data, struct node** start_node) {
    struct node* nodeBuffer;
    struct node* new_node;

    nodeBuffer = *start_node;
    new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = data;
    new_node->next = nodeBuffer;
    *start_node = new_node;

}
static void addAfterIndex(int index, int data, struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* tmp;
    int count = 0;

    new_node->data = data;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
    }

    while (nodeBuffer != NULL) {
        if(count == index) {
            tmp = nodeBuffer->next;
            nodeBuffer->next = new_node;
            nodeBuffer = tmp;
            new_node->next = nodeBuffer;
            break;
        }
        count++;
        nodeBuffer = nodeBuffer->next;
    }

}
static void addBeforeIndex(int index, int data, struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* tmp;
    int count = 0;

    new_node->data = data;

    while (nodeBuffer != NULL) {
        if(count == index - 1) {
            tmp = nodeBuffer->next;
            nodeBuffer->next = new_node;
            nodeBuffer = tmp;
            new_node->next = nodeBuffer;
            break;
        }
        count++;
        nodeBuffer = nodeBuffer->next;
    }
}
static int listLength(struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    int length = 0;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
        return length;
    }
    while (nodeBuffer != NULL) {
        length++;
        nodeBuffer =  nodeBuffer->next;
    }

    return length;
}
static int getElement(int index, struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    int data;
    int count = 0;

    while (nodeBuffer != NULL) {
        if(count == index) {
            return nodeBuffer->data;
        }
        count++;
        nodeBuffer = nodeBuffer->next;
    }

    return -1;
}
static struct node* map(int (*g)(int), struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    struct node* head_ref;
    struct node* newBuffer;
    struct node* new_node;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
        assert(0);
    }

    head_ref = (struct node*)malloc(sizeof(struct node));
    head_ref->data = g(nodeBuffer->data);
    head_ref->next = NULL;
    newBuffer = head_ref;
    nodeBuffer = nodeBuffer->next;

    while (nodeBuffer != NULL) {
        new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = g(nodeBuffer->data);
        new_node->next = NULL;
        newBuffer->next = new_node;
        newBuffer = newBuffer->next;
        nodeBuffer = nodeBuffer->next;
    }
    return head_ref;
}
static void map_mut(int (*g)(int), struct node** start_node) {
    struct node* nodeBuffer = *start_node;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
        assert(0);
    }

    while (nodeBuffer != NULL) {
        nodeBuffer->data = g(nodeBuffer->data);
        nodeBuffer = nodeBuffer->next;
    }
}
static struct node* foldf(int a, int (*g)(int x, int y), struct node** start_node) {
    struct node* nodeBuffer = *start_node;
    struct node* head_ref = (struct node*)malloc(sizeof(struct node));
    struct node* new_node;
    struct node* newBuffer;

    if(nodeBuffer == NULL) {
        printf("the list is empty");
        assert(0);
    }

    head_ref->data = g(a, nodeBuffer->data);
    head_ref->next = NULL;
    newBuffer = head_ref;
    nodeBuffer = nodeBuffer->next;

    while (nodeBuffer != NULL) {
        new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = g(a, nodeBuffer->data);
        new_node->next = NULL;
        newBuffer->next = new_node;
        newBuffer = newBuffer->next;
        nodeBuffer = nodeBuffer->next;
    }
    return head_ref;

}