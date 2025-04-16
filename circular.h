#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"
using namespace std;

// TODO: Implement all methods
template <typename T>
class CircularList : public List<T> {  
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node(){ 
                next = this;
                prev = this;
            }

            Node(T value) {
                data = value;
                next = nullptr;
                prev = nullptr;
            }

            void killSelf(){
                if (next != nullptr) {
                    next->prev = prev;
                }   
                if (prev != nullptr) {
                    prev->next = next;
                }
                delete this;
            }    
        };

    private:
        Node* head;//sentinel
        int nodes; 

    public:
        CircularList() : List<T>() { }

        ~CircularList(){
           clear();
           delete head;
        }       

        T front(){
            if (is_empty()){
                throw out_of_range("Lista vacia");
            }
            return head->next->data;
        }

        T back(){
            if (is_empty()){
                throw out_of_range("Lista vacia");
            }
            return head->prev->data;
        }

        void push_front(T data){
            Node* node = new Node(data);
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
            nodes++;
        }

        void push_back(T data){
            Node* node = new Node(data);
            node->prev = head->prev;
            node->next = head;
            head->prev->next = node;
            head->prev = node;
            nodes++;
        }

        T pop_front(){
            if (is_empty()) {
            throw out_of_range("Lista vacia");
            }
            Node* borrar = head->next;
            T value = borrar->data;
            head->next = borrar->next;
            borrar->next->prev = head;
            delete borrar;
            nodes--;
            return value;
        }

        T pop_back(){
            if (is_empty()) {
                throw out_of_range("Lista vacia");
            }
            Node* borrar = head->prev;
            T value = borrar->data;
            head->prev = borrar->prev;
            borrar->prev->next = head;
            delete borrar;
            nodes--;
            return value;
        }

        T insert(T data, int pos){
            if (pos < 0 || pos > nodes) {
                return false;
            }
            Node* temp = head;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            Node* node = new Node(data);
            node->next = temp->next;
            node->prev = temp;
            temp->next->prev = node;
            temp->next = node;
            nodes++;
            return true;
        }

        bool remove(int pos){
            if (pos < 0 || pos >= nodes) {
                return false;
            }
            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            temp->killSelf();
            nodes--;
            return true;
        }

        T& operator[](int pos){
            if (pos < 0 || pos >= nodes) {
                throw out_of_range("Fuera de rango");
            }
            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            return temp->data;
        }

        bool is_empty(){
            return nodes == 0;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (!is_empty()) {
                pop_front();
            }
        }
        
        void sort(){
            if (nodes < 2) {
                return;
            }
            bool swapped;
            do {
                swapped = false;
                Node* current = head->next;
                while (current->next != head) {
                    if (current->data > current->next->data) {
                        swap(current->data, current->next->data);
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }

        bool is_sorted(){
            if (nodes < 2) {
                return true;
            }
            Node* current = head->next;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    return false;
                }
                current = current->next;
            }
            return true;
        }

        void reverse(){
            if (nodes < 2) {
                return;
            }
            Node* current = head;
            do {
                swap(current->next, current->prev);
                current = current->prev;
            } while (current != head);
        }

        std::string name(){
            return "CircularList";
        }
};

#endif