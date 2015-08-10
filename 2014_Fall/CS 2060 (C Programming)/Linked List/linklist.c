#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int number;
    struct list *next;
    struct list *prev;
} Node;

Node* insertList() {
    List *list, *root;
    for(int i = 0; i < 10; i++) {
	if(list == NULL) {
	    list = (List *)malloc(sizeof(List));
	    root = newList;
	    strcpy(list -> sentance, line);
	} else {
	    while(list -> next) {
		list = list -> next;
	    }
	    list -> next = (Node *)malloc(sizeof(Node));
	    strcpy(list -> next -> sentance, line);
	}
    }
    return l;
}

List* buildList() {
    List *l;
    l = (List *)malloc(sizeof(List));
    return l;
}

int main(int argc, char *argv[]) {
    int value[] = {42,41,43,0,12,17,33,12,1,14};
    List *root, *newList;
    
    for(int i = 0; i < 10; i++) {
	if(newList == NULL) {
	    newList = (List *)malloc(sizeof(List));
	    root = newList;
	    newList -> number = value[i];
	} else {
	    while(newList -> next) {
		newList = newList -> next;
	    }
	    newList -> next = (List *)malloc(sizeof(List));
	    newList -> next -> number = value[i];
	}
    }
    
    newList = root;
    while(newList) {
	printf("Number: %d\n", newList->number);
	newList = newList->next;
    }
    
    for(int i = 0; i < 10; i++) {
	//insertList(value[i]);
    }
    
    return 0;
}