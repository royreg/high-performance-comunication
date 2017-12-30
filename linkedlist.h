#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



typedef struct Link {
	char* key;
	char* value;
	struct Link *next;
} Link;

typedef struct list {
	int size; /* the size of the table */
	Link* first;
	
} list;

list *createList(){
	list* newList;
	if( (newList = malloc(sizeof(list))) < 0)
		return 0;

	newList->size=0;

	if((newList->first = malloc(sizeof(Link))) < 0)
		return 0;

	return newList;
}

//get linke with key Key , null if key does not exist in lst
Link* getLinkWithKey(char* key , list* lst){
	Link* curr = lst->first;

	while(curr != NULL){
		if(strcmp(curr->key,key) == 0)
			return curr;
		curr = curr->next;

	}

	return NULL;

}

int addKeyValue(char* key , char* value , list* lst){
	Link* curr = lst->first;
	Link* exist;
	
	if(lst->size == 0){
		curr->key = key;
		curr->value = value;
		lst->size++;

	}

	//case it exist , change the exisiting value of key
	if((exist = getLinkWithKey(key , lst))!=NULL){
		exist->value = value;
		return 1;
	}

	//case it doesn;t exist
	while(curr->next != NULL){
		curr = curr->next;

	}
	Link* add =malloc(sizeof(Link));

	//case malloc failed
	if(add < 0){
		return -1;
	}

	add->key = key;
	add->value = value;
	add->next = NULL;
	curr->next = add;
	lst->size++;

	return 1;

}

void printList(list* lst){
	Link* curr = lst-> first;
	while(curr != NULL){
		printf("key is:%s   val is:%s\n",curr->key,curr->value);
		curr=curr->next;
	}
}






// int main(int argc , char** argv){
// 	list* lst = createList();
// 	char* key = strdup("roy");
// 	char* val = strdup("king");

// 	addKeyValue(key,val,lst);

// 	//printList(lst);

// 	char* nkey = strdup("zz");
// 	char* nval = strdup("yy");

// 	addKeyValue(nkey,nval,lst);

// 	printList(lst);
// 	char* tempStr = "roy";

// 	addKeyValue(nkey,tempStr,lst);
// 	printList(lst);

	
// 	return 0;
// }

