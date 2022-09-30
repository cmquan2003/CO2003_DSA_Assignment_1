// Test Linked list
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class LinkedList {
public:
    class Node {
    public:
        int data;
        Node *next;

        Node(int data=0, Node *next=nullptr) : data(data), next(next) {}
        
    };

public:
    Node *head;
    Node *tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~LinkedList() {
        this->clear();
    }
    void add(int element) {
        Node* tmp = new Node(element);
        if (this->count == 0) {
            head = tail = tmp;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
        this->count++;
    }

    void add(int index, int element) {
        if (index < 0 || index > this->count) throw std::out_of_range("Error");
        if (index == this->count) {
            this->add(element);
            return;
        }
        Node* tmp = new Node(element);
        if (this->count == 0) {
            head = tail = tmp;
        }
        else {
            if (index == 0) {
                tmp->next = head;
                head = tmp;
            }
            else
            {
                Node* p = head;
                for (int i = 0; i < index-1; i++) p = p->next; // p at index-1
                tmp->next = p->next;
                p->next = tmp;
            }
        }
        this->count++;
    }

    int removeAt(int index) {
        if (index < 0 || index >= this->count) throw std::out_of_range("Error");
        int tmp_num;
        if (this->count == 1) {
            tmp_num = head->data;
            delete head;
            head = tail = NULL;
        }
        else if (index == 0) {
            Node* p = head->next;
            delete head;
            head = p;
        }
        else {
            Node* p = head;//p at 0
            for (int i = 0; i < index-1; i++) p = p->next;//p at index-1
            Node* tmp = p->next;//tmp at index
            tmp_num = tmp->data;

            p->next = tmp->next;
            if (index == this->count-1) {
                tail = p;
            }
            delete tmp;
        }
        this->count--;
        return tmp_num;
    }

    bool removeItem(int item) {
        int idx = indexOf(item);
        if (idx == -1) return false;
        else
        {
            removeAt(idx);
            return true;
        }
    }

    bool empty() {
        return (this->count == 0);
    }

    int size() {
        return this->count;
    }
    
    int get(int index) {
        if (index < 0 || index >= this->count) throw std::out_of_range("Error");
        Node* p = head;
        for (int i = 0; i < index; i++) p = p->next;
        return p->data;
    }

    void set(int index, int element) {
        if (index < 0 || index >= this->count) throw std::out_of_range("Error");
        Node* p = head;
        for (int i = 0; i < index; i++) p = p->next;
        p->data = element;
    }

    int indexOf(int item) {
        Node* p = head;
        int cnt = 0;
        while (p != NULL) {
            if (p->data == item) return cnt;
            p = p->next;
            cnt++;
        }
        return -1;
    }

    bool contains(int item) {
        Node* p = head;
        while (p != NULL) {
            if (p->data == item) return true;
            p = p->next;
        }
        return false;
    }
    void clear() {
        if (this->empty()) return;
        Node* p;
        while (head!=NULL)
        {
            p = head;
            head = head->next;
            delete p;
        }
        head = tail = NULL;
        this->count = 0;
    }
    string toString() {
        string s = "[";
        Node *p = head;
        while (p != NULL) {
            if (p != head) s+=',';
            s += to_string(p->data);
            p = p->next;
        }
        s += ']';
        return s;
    }
    void split(Node * head, Node *& a, Node *& b) {
        Node *fast = head->next;
        Node *slow = head;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                fast = fast->next;
                slow = slow->next;
            }
        }

        a = head;
        b = slow->next;

        slow->next = NULL;
    }
    Node *mergeList(Node *& a, Node *& b) {
        Node *res;

        Node *a_ptr = a;
        Node *b_ptr = b;

        if (a->data < b->data) {
            res = a_ptr;
            a_ptr = a_ptr->next;
        }
        else {
            res = b_ptr;
            b_ptr = b_ptr->next;
        }

        Node *p = res;

        while (a_ptr != nullptr && b_ptr != nullptr) {
            if (a_ptr->data <= b_ptr->data) {
                p->next = a_ptr;
                a_ptr = a_ptr->next;
                p = p->next;
            }
            else {
                p->next = b_ptr;
                b_ptr = b_ptr->next;
                p = p->next;
            }
        }
        while (a_ptr != nullptr) {
            p->next = a_ptr;
            a_ptr = a_ptr->next;
            p = p->next;
        }
        while (b_ptr != nullptr) {
            p->next = b_ptr;
            b_ptr = b_ptr->next;
            p = p->next;
        }

        return res;
    }
    void mergesort(Node *& head) {
        if (head == NULL || head->next == NULL) return;

        Node *a;
        Node *b;

        split(head, a, b);
        mergesort(a);
        mergesort(b);
        head = mergeList(a, b);//head changed here
    }
    void sort() {
        mergesort(this->head);
        this->tail = head;
        for (int i = 0; i < this->count-1; i++) this->tail = this->tail->next; // tail at count-1
        // Sorting list completed

        // This part is for BTL1 of DSA
        /*
        0-> 0 ->  32->...
                  p
            pre
        */
        Node *p = head;
        while (p != NULL && p->data == 0) p = p->next;
        if (p == head || p == NULL) return;
        Node *pre = head;
        while (pre->next != p) pre = pre->next;
        pre->next = nullptr;
        tail->next = head;
        head = p;
        tail = pre;
    }
};

int main()
{
    LinkedList list;
    // int values[]   = {10, 15, 2,  6,  0,  7,  40,  8, 0};
    // int index[]    = {0,  0,  1,  3,  2,  3,  5,   0, 1};
    int values[] = {0,10};
    int index[] = {0,0,0};
    for (int idx = 0; idx < 2; idx++) {
        list.add(index[idx], values[idx]);
    }
    cout << list.toString() << endl;//[8,0,15,2,0,7,10,40,6]
    list.sort();
    cout << list.toString() << endl;//[2,6,7,8,10,15,40,0,0]
    cout << list.head->data << " " << list.tail->data;
    list.clear();
    cout << list.toString();//[]
}
// g++ test.cpp -o test ; if ($?) { .\test }

// // Test string and char*
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     const char a[] = "ABCDEFGH";
//     string s(a);
//     string sr(s.rbegin(), s.rend());
//     cout << a << " " << s << " " << sr << endl;//ABCDEFGH ABCDEFGH HGFEDCBA
//     cout << s.substr(4, 1111);//EFGH
// }

// Copy elision
// #include <bits/stdc++.h>
// using namespace std;
// class Test {
// public:
//     int x;
//     Test(int x) : x(x) {
//         cout << "Constructor called" << endl;
//     }
//     Test(const Test &obj) {
//         x = obj.x;
//         cout << "Constructor called" << endl;
//     }
//     ~Test() {
//         cout << "Destructor called" << endl;
//     }
//     Test bar(int x) {
//         Test res(x);
//         cout << &res << endl;
//         return res;
//     }
//     // Test(Test&& obj) : x{obj.x} {
//     //     cout << "Move Constructor called" << endl;
//     // }
// };
// Test foo(int x) {
//     Test res(x);
//     cout << &res << endl;
//     return res;
// }
// int main() {
//     Test objA = foo(10);
//     cout << &objA << endl;
//     cout << "End of main\n";
// }

// // g++ test.cpp -o test -std=c++11 -fno-elide-constructors ; if ($?) { .\test }