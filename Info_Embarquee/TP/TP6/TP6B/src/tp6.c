#include <stdio.h>
#include <stdlib.h>

/* init an element */
#define INIT_LIST_HEAD(head){\
head->next = head;\
head->prev = head;\
head->val = malloc(sizeof(struct my_object));}

#define container_of(ptr, type, member) ({ \
const typeof( ((type *)0)->member ) *__mptr = (ptr); \
(type *)( (char *)__mptr - offsetof(type, member) );})

/* iterate over a list starting at head */
#define list_for_each_entry(cur, head, member) \
for (cur = container_of((head)->next, typeof(*cur), member); \
&cur->member !=(head); \
cur = container_of(cur->member.next, typeof(*cur), member))


struct list_head{
	struct list_head *prev;
	struct my_object *val;
	struct list_head *next;
};


struct my_object {
	struct list_head my_object_listA;
	struct list_head my_object_listB;
};


/* add “node” element after “head”*/ 
void list_add(struct list_head *node, struct list_head *head){
	struct list_head *tmp1=head->next;
	head->next = node;
	node->next = tmp1;
	tmp1->prev = node;
}


/* remove element “node” from a list */
void list_del(struct list_head *node){
	node->prev->next = node->next;
	node->next->prev = node->prev;
}



int main(){
	
}