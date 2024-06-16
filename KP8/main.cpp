#include <iostream>

using namespace std;

class Node {
public:
    int data;

private:
    Node* next;

public:
    Node() :data(0), next(NULL) {};
    Node(int d) : data(d), next(NULL) {};
    Node(Node& nod) : data(nod.data), next(NULL) {};
    ~Node() { data = 0; next = NULL; }
    friend class List;

    void printNode() {
        cout << data << '\n';
    }
};

class List {
    Node* head;
    int len;

public:
    List() : head(NULL) {};
    List(int l, int val) : head(NULL), len(l) {
        head = new Node(val);
        Node* a = new Node(val);
        head->next = a;
        for (int i = 0; i < l - 1; ++i) {
            a->next = new Node(val);
            a = a->next;
        }
    };

    ~List() { len = 0, head = NULL; }

    int& operator[](int i) {
        Node* a = head;
        if (len <= i) {
            throw - 1;
        }
        while (i > 0) {
            a = a->next;
            --i;
        }
        return a->data;
    }

    int length() {
        return len;
    }

    void appEnd(int vak) {
        Node* a = head;
        while (a->next != NULL) {
            a = a->next;
        }
        a->next = new Node(vak);
        len += 1;
    }

    bool isEmpty() {
        return head == NULL;
    }

    void printList() {
        Node* a = head;
        for (int i = 0; i < len; ++i) {
            a->printNode();
            a = a->next;
        }
        cout << '\n';
    }

    void deleteList() {
        head = NULL;
        delete[] & len;
    }

    void dobav(int val, int k) {
        if (len >= k) {
            return;
        }
        while (len != k) {
            appEnd(val);
        }
    }
};

int main() {
    int k;
    cout << "Enter k ";
    cin >> k;
    List a(10, 4);
    a.dobav(10, k);
    for (int i = 0; i < a.length(); ++i) {
        cout << a[i] << ' ';
    }
}
