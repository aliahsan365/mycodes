reciclado


/*
void sorted_insert(struct node* newnode) {
	struct node* aux = head;

	if (head == NULL) {
		head = newnode;
	}
	else {
		struct node* aux = head;
		int data = newnode -> data;
		int inserted = 0;
		while (head->next != NULL && inserted == 0) {
			int cdata = head -> data;
			if ( cdata < data) {
				head = head -> next;
			}
			else {
			//insertar en medio de dos.
				
				inserted = 1;
				//en medio (justo antes del que es mas grande que el):
				struct node* primero = head;
				struct node* segundo = head->next;
				struct node* tercero = head->prev;
				struct node* auxp;
				auxp = head->prev;
				head->prev = newnode;
				aux -> next = newnode;
				newnode -> next = primero;
				newnode -> prev = tercero;


				
		}
			
		}
		if (inserted == 0) {
			head->next = newnode;
			newnode->prev = head;
			inserted = 1;
		} 
		if (inserted == 1) {
			head = aux;
		}
	}


}

*/

void sorted_insert(struct node* newnode) {
	struct node* aux = head;
	if (head == NULL) {
		head = newnode;
	}
	else {
		//1.2.3.4.5
		int nvalue = newnode->data;
		int inserted = 0;
		//el count es para contar que el primer elemento ya es mayor
		//por lo q hay q insetarlo al principio
		int count = 0;
		while (head->next != NULL && inserted == 0) {
			int cvalue = head->data;

			if (nvalue >= cvalue) {
				//insertamos antes del mayor
				inserted = 1;
				if (count == 0) {
					head = aux;
					insert_at_head(newnode);
				}
				else {
					//hay que insertarlo al final
					struct node* headprevnext;
					newnode->next = head;
					headprevnext -> next = newnode;
					head -> prev = newnode;
					head = aux;
				}
			}
			else {
			    ++count;
			    head = head -> next;
			}
		}
		if (inserted == 0) {
			//insertamos al final
			head = aux;
			insert_at_end(newnode);
		}
	}
}





