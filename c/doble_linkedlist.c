#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct  node* next;
	struct node* prev;
};

struct node* head = NULL;

struct node* create_node(int data) {
	
	struct node* newnode = malloc(sizeof(struct node));
	newnode -> data = data;
    newnode -> next = NULL;
    newnode -> prev = NULL;
    return newnode;
}


void print_node(struct node* node) {
	printf("data %d\n", node-> data);
	printf("prev pointer %p\n",node->prev);
	printf("next pointer %p\n",node->next);
}


void forward_print() 
{ 
	printf("\nTraversal in forward direction \n"); 
    int i = 1;
    struct node* aux=  head;
    while (aux != NULL) { 
    	
        printf("itr %d, valor %d\n", i, aux->data); 
        ++i;
        aux = aux->next; 
    } 
}


void reverse_print() {
	printf("\nTraversal in reverse direction \n");
	//se usa el puntero aux para no perder la referncia de head
	//ya que nos movemos usando el head y este no es const.
	struct node *aux = head; 
	struct node *began;
	while (aux != NULL) {
		began = aux;
		aux  = aux -> next;

	}
    int i = 1;
    while (began != NULL) {
        printf("itr %d, valor %d\n", i, began->data); 
        ++i;

		began = began -> prev;
	}
}



//funciona correctamente
void insert_at_head(struct node* newnode) {
	if (head ==  NULL) {
		head = newnode;
	}
	else  {

	    //antes que nada, el previo de lo que apunta head esa newnode ahora.
	    //pk lo queremos insertar al principio
		head-> prev = newnode;
		//le newnode next apunta a lo que apunta head en se momento pk es va antes ahora.
		newnode -> next = head;
		//actualizamos el puntero head a la dir del newnode.
		head = newnode;
	}
}

void insert_at_end(struct node* newnode) {
	if (head == NULL) {
		head = newnode;
	}

	else {
		//insert  with more than one element.
		//es muy necesario el aux para no perder la ref de head.
		struct node* aux = head;
		//hay que pararlo justo antes que sea null, exactamente una antes.
		//por eso head->next null y NO head != null.
		while (head->next != NULL) {
			printf("%p\n",head);
			head = head->next;
		}
		//computo de punteros.
		head->next = newnode;
		newnode->prev = head;
		//dejamos la ref de head como antes.
		head = aux;
	}
}






int main(void) 
{
	//struct Node* node1 = (struct )

	int data3 = 3;
	struct node* n3 = create_node(data3);
	int data1 = 1;
	struct node* n1 = create_node(data1);
	int data2 = 2;
	struct node* n2 = create_node(data2);
	insert_at_end(n3);
    insert_at_end(n2);
    insert_at_end(n1);
    forward_print();
	reverse_print();
    forward_print();
	reverse_print();
	return 0;
}