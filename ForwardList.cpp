#include <iostream>
#include <queue>
using namespace std;

template <typename t>
struct Node {

    // Atributos
    t data;
    Node* next;

    // Constructores
    Node() : data(0), next(nullptr) {}
    Node(t d) : data(d), next(nullptr) {}
    Node(t d, Node* n) : data(d), next(n) {}

};

template <typename T>
class forward_list {

    // Atributos
    Node<T> * head;

    // Metodos privados
    void divide(Node<T>* current, Node<T>** front, Node<T>** back) {
        Node<T>* slow = current;
        Node<T>* fast = current->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *front = current;
        *back = slow->next;
        slow->next = nullptr;
    }
    Node<T>* merge(Node<T>* ptr1, Node<T>* ptr2) {
        if (!ptr1) return ptr2;
        if (!ptr2) return ptr1;

        Node<T>* result = nullptr;

        if (ptr1->data <= ptr2->data) {
            result = ptr1;
            result->next = merge(ptr1->next, ptr2);
        } else {
            result = ptr2;
            result->next = merge(ptr1, ptr2->next);
        }

        return result;
    }
    void sort_recursive(Node<T>** headRef) {
        Node<T>* h = *headRef;
        if (!h || !h->next) return;

        Node<T>* a = nullptr;
        Node<T>* b = nullptr;

        split(h, &a, &b);
        merge_sort_rec(&a);
        merge_sort_rec(&b);

        *headRef = merge(a, b);
    }

    public:
    // Constructores
    forward_list() : head(nullptr) {}
    forward_list(Node<T>* n) : head(n) {}

    // Metodos
    T front() const { return head->data; }
    T back() const {
        auto* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }
    void push_front(const T& n) {
        auto* newNode = new Node<T>(n);
        newNode->next = head;
        head = newNode;
    }
    void push_back(const T& n) {
        if (head == nullptr) {
            head = new Node<T>(n);
        }
        else {
            auto* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new Node<T>(n);
        }
    }
    void pop_front() {
        auto temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back() {
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        }
        else {
            auto* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }
    T operator[](const int index) {
        auto* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    bool empty() const { return head == nullptr; }
    int size() const {
        auto* temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    void clear() {
        while (head != nullptr) {
            auto* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void sort() {
        sort_recursive(&head);
    }
    void reverse() {
            Node<T>* prev = nullptr;
            Node<T>* curr = head;
            Node<T>* next = nullptr;

            while (curr != nullptr) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            head = prev;
    }
};


int main() {



    return 0;
}
