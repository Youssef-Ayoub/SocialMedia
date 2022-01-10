#include<iostream>
using namespace std ;
#include"User.h"


struct Node{
public:
    User key;
    Node *next;
};

class LinkedList{
    Node *head;
    int sz ;
public:

    LinkedList(){
        head = NULL;
        sz =0 ;
    }

    int getsz(){return sz;}

    void push(Node** head_ref, User& new_key)
    {
        /* allocate node */
        Node* new_node = new Node();

        /* put in the key */
        new_node->key = new_key;

        /* link the old list off the new node */
        new_node->next = (*head_ref);

        /* move the head to point to the new node */
        (*head_ref) = new_node;
        sz++ ;
    }

/* Checks whether the value x is present in linked list */
    string search(Node* head, string u)
    {
        Node* current = head; // Initialize current
        while (current != NULL)
        {
            if (current->key.getusername() == u) {
                return current->key.getname();
            }
            current = current->next;
        }
        return "Not Found";
    }

    User& searchLogin(Node* head, string u)
    {
        User temp ;
        Node* current = head; // Initialize current
        while (current != NULL)
        {
            if (current->key.getusername() == u) {
                return current->key;
            }
            current = current->next;
        }
        return temp;
    }




};
