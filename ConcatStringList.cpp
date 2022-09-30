#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

// Implementation of CharALNode
ConcatStringList::CharALNode::CharALNode(const char * data) : next(NULL)
{
    length = 0;
    while (data[length] != '\0') length++;

    CharArrayList = new char[length + 1];
    for (int i = 0; i < length; i++) CharArrayList[i] = data[i];
    CharArrayList[length] = '\0';
}
ConcatStringList::CharALNode::CharALNode(string data) : next(NULL)
{
    length = data.size();

    CharArrayList = new char[length + 1];
    for (int i = 0; i < length; i++) CharArrayList[i] = data[i];
    CharArrayList[length] = '\0';
}
ConcatStringList::CharALNode::CharALNode(const CharALNode & objChar) : next(NULL)
{
    length = objChar.length;

    CharArrayList = new char[length + 1];
    for (int i = 0; i < length; i++) CharArrayList[i] = objChar.CharArrayList[i];
    CharArrayList[length] = '\0';
}
ConcatStringList::CharALNode::~CharALNode()
{
    delete[] this->CharArrayList;
}

// Implementation of RefNode
ConcatStringList::RefNode::RefNode() : data(NULL), refCount(0), next(NULL) {}
ConcatStringList::RefNode::RefNode(CharALNode *data, int refCount, RefNode *next)
        : data(data), refCount(refCount), next(next) {}

// Implementation of DelNode
ConcatStringList::DelNode::DelNode() : head_deleted(NULL), tail_deleted(NULL), refCountHead(NULL), refCountTail(NULL), checkConcat(false), next(NULL) {}
ConcatStringList::DelNode::DelNode(CharALNode *head_deleted, CharALNode *tail_deleted, int *refCountHead, int *refCountTail, bool checkConcat, DelNode *next)
        : head_deleted(head_deleted), tail_deleted(tail_deleted), refCountHead(refCountHead), refCountTail(refCountTail), checkConcat(checkConcat), next(next) {}

// Implementation of class ConcatStringList
// 3.2.1
ConcatStringList::ConcatStringList(const char * s) : count_node(1), checkConcat(false)
{
    // Create 1 Node with the CharArrayList <-- s
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s);
    head = pNew;
    tail = pNew;
    count_char = pNew->length;

    refList.insertNode(head, tail);
}
// Private Stuff =))
ConcatStringList::ConcatStringList() : head(NULL), tail(NULL), count_node(0), count_char(0), checkConcat(false) {}
void ConcatStringList::appendNode(string s)
{
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s);
    if (count_node == 0) {
        head = pNew;
        tail = pNew;
    }
    else {
        tail->next = pNew;
        tail = pNew;
    }
    count_node++;
    count_char += pNew->length;
}
void ConcatStringList::appendNode(const char *s)
{
    string tmp_string(s);
    appendNode(tmp_string);
}
// 3.2.2
int ConcatStringList::length() const
{
    return this->count_char;
}
// 3.2.3
char ConcatStringList::get(int index) const
{
    if (index < 0 || index > this->count_char-1) throw out_of_range("Index of string is invalid!");
    ConcatStringList::CharALNode *p = head;
    char res_c;
    while (index >= 0 && p != tail->next) {
        if (index < p->length) {
            res_c = p->CharArrayList[index];
            break;
        }
        else index -= p->length;
        p = p->next;
    }
    return res_c;
}//O(count_node)
// 3.2.4
int ConcatStringList::indexOf(char c) const
{
    ConcatStringList::CharALNode *p = head;
    int cnt = 0;
    for (int i = 0; i < this->count_char; i++) {
        if (i == cnt + p->length) {
            cnt += p->length;
            p = p->next;
        }
        if (p != NULL && p->CharArrayList[i-cnt] == c) return i;
    }
    return -1;
}//O(count_char)
// 3.2.5
std::string ConcatStringList::toString() const
{
    string res = "";

    ConcatStringList::CharALNode *p = head;
    int cnt = 0;
    for (int i = 0; i < this->count_char; i++) {
        if (i == cnt + p->length) {
            cnt += p->length;
            p = p->next;
        }
        res += p->CharArrayList[i-cnt];
    }
    return res;
}//O(count_char)
// 3.2.6
ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const
{
    ConcatStringList res_S;

    this->tail->next = otherS.head;
    res_S.head = this->head;
    res_S.tail = otherS.tail;
    res_S.count_node = this->count_node + otherS.count_node;
    res_S.count_char = this->count_char + otherS.count_char;
    res_S.checkConcat = true;

    refList.updateConcat(res_S.head, res_S.tail);
    return res_S;
}
// 3.2.7
ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if (from < 0 || from > this->count_char-1) throw out_of_range("Index of string is invalid");
    if (to   < 0 || to   > this->count_char)   throw out_of_range("Index of string is invalid");
    if (from >= to) throw logic_error("Invalid range");

    ConcatStringList res_S;
    
    ConcatStringList::CharALNode *p = this->head;
    int cnt = 0;
    for (int i = 0; i <= from; i++) {
        if (i == cnt + p->length) {
            cnt += p->length;
            p = p->next;
        }
    }
    // p is at Node that contain char at index "from"
    // cnt is the number of characters of previous Nodes
    // from >= cnt (all cases)

    // length of new string list should be to - from
    // to <= cnt + p->length: new list has only 1 node (cnt <= from < to <= cnt+p->length)
    // to >  cnt + p->length: more than 1 node

    if (to <= cnt + p->length) {
        string tmp_str(p->CharArrayList);
        string tmp_sub_str = tmp_str.substr(from-cnt, to-from);
        res_S.appendNode(tmp_sub_str);
    }
    else {
        int i = from;
        while (p != this->tail->next) {
            int length_of_new_word = min(p->length + cnt, to) - i;
            string tmp_str(p->CharArrayList);
            string tmp_sub_str = tmp_str.substr(i - cnt, length_of_new_word);
            
            res_S.appendNode(tmp_sub_str);

            cnt = cnt + p->length;
            p = p->next;
            i = cnt;
            if (i >= to) break;
        }
    }

    refList.insertNode(res_S.head, res_S.tail);
    if (res_S.head != res_S.tail)
        refList.insertNode(res_S.tail);
    return res_S;
}
// 3.2.8
ConcatStringList ConcatStringList::reverse() const
{
    ConcatStringList res_S;
    ConcatStringList::CharALNode *p_curr = this->head;
    // Reverse the string
    while (p_curr != this->tail->next) {
        string tmp_str(p_curr->CharArrayList);
        string tmp_str_reversed(tmp_str.rbegin(), tmp_str.rend());
        res_S.appendNode(tmp_str_reversed);
        p_curr = p_curr->next;
    }
    // Reverse the list
    /*
    Before:
    NULL      N1     -> N2     -> N3    -> N4    -> NULL
    p_prev    p_curr    p_next
    After:
    NULL   <- N1     <- N2     <- N3    <- N4       NULL
                                           p_prev   p_curr = p_next
    */
    res_S.tail = res_S.head;
    p_curr = res_S.head;
    ConcatStringList::CharALNode *p_prev = NULL;
    ConcatStringList::CharALNode *p_next;
    while (p_curr != NULL) {
        p_next = p_curr->next;
        p_curr->next = p_prev;
        p_prev = p_curr;
        p_curr = p_next;
    }
    res_S.head = p_prev;
    
    refList.insertNode(res_S.head, res_S.tail);
    if (res_S.head != res_S.tail)
        refList.insertNode(res_S.tail);
    return res_S;
}
// 3.2.9
ConcatStringList::~ConcatStringList()
{
    if (count_node==0) return;
    int *ref1, *ref2;
    refList.reduceRef(head, tail, ref1, ref2);
    delStrList.appendNode(head, tail, ref1, ref2, this->checkConcat);
    delStrList.updateDel();// Noi xoa cac DelNodes
    refList.recheckRef();// Noi xoa moi RefNodes khi moi refCounts = 0
}

// Implementation of class ReferencesList
ConcatStringList::ReferencesList::ReferencesList() : head(NULL), tail(NULL), count_ref_node(0) {}
void ConcatStringList::ReferencesList::insertNode(CharALNode * char_node_1, CharALNode * char_node_2)
{
    ConcatStringList::RefNode *pNew = new ConcatStringList::RefNode(char_node_1, 1, NULL);
    if (char_node_2 != NULL && char_node_1 == char_node_2) pNew->refCount++;
    if (count_ref_node == 0) {
        head = pNew;
        tail = pNew;
    }
    else {
        ConcatStringList::RefNode *p_curr = head;
        int idx = 0;
        while (p_curr != NULL && pNew->refCount > p_curr->refCount && p_curr->refCount > 0) {
            idx++;
            p_curr = p_curr->next;
        }// idx is where we need to insert pNew
        if (idx == 0) {
            pNew->next = head;
            head = pNew;
        }
        else if (idx == count_ref_node) {
            tail->next = pNew;
            tail = pNew;
        }
        else {
            p_curr = head;
            for (int i = 0; i < idx-1; i++) p_curr = p_curr->next; // p at index-1
            pNew->next = p_curr->next;
            p_curr->next = pNew;
        }
    }
    count_ref_node++;
}
void ConcatStringList::ReferencesList::updateConcat(CharALNode * char_node_1, CharALNode * char_node_2)
{
    ConcatStringList::RefNode *p = this->head;
    while (p != NULL) {
        if (p->data == char_node_1) {
            p->refCount++;
        }
        if (p->data == char_node_2) {
            p->refCount++;
        }
        p = p->next;
    }
    this->sort();
}
void ConcatStringList::ReferencesList::sort()
{
    mergeSort(this->head);
    this->tail = head;
    for (int i = 0; i < count_ref_node-1; i++) this->tail = this->tail->next; // tail at count-1
    // Sorting list completed

    // Bring 0s to the end of the list
    /*
    0 -> 0 -> 32 -> ...
              p
         pre
    */
    ConcatStringList::RefNode *p = head;
    while (p != NULL && p->refCount == 0) p = p->next;
    if (p == head || p == NULL) return;
    ConcatStringList::RefNode *pre = head;
    while (pre->next != p) pre = pre->next;
    pre->next = NULL;
    tail->next = head;
    head = p;
    tail = pre;
}
void ConcatStringList::ReferencesList::mergeSort(RefNode *& head)
{
    if (head == NULL || head->next == NULL) return;

    ConcatStringList::RefNode *a;
    ConcatStringList::RefNode *b;

    split(head, a, b);
    mergeSort(a);
    mergeSort(b);
    head = mergeList(a, b);//head changed here
}
void ConcatStringList::ReferencesList::split(RefNode * head, RefNode *& a, RefNode *& b) {
    // split the head list into 2 sub list a and b
    ConcatStringList::RefNode *fast = head->next;
    ConcatStringList::RefNode *slow = head;

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
ConcatStringList::RefNode *ConcatStringList::ReferencesList::mergeList(RefNode *& a, RefNode *& b)
{
    // merge 2 sorted list into 1 list
    ConcatStringList::RefNode *res;

    ConcatStringList::RefNode *a_ptr = a;
    ConcatStringList::RefNode *b_ptr = b;
    if (a->refCount < b->refCount) {
        res = a_ptr;
        a_ptr = a_ptr->next;
    }
    else {
        res = b_ptr;
        b_ptr = b_ptr->next;
    }

    ConcatStringList::RefNode *p = res;
    while (a_ptr != nullptr && b_ptr != nullptr) {
        if (a_ptr->refCount <= b_ptr->refCount) {
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
void ConcatStringList::ReferencesList::reduceRef(CharALNode *&char_node_1, CharALNode *&char_node_2, int *& ref1, int *& ref2)
{
    ConcatStringList::RefNode *p = this->head;
    while (p != NULL) {
        if (p->data == char_node_1) {
            p->refCount--;
            ref1 = &(p->refCount);
        }
        if (p->data == char_node_2) {
            p->refCount--;
            ref2 = &(p->refCount);
        }
        p = p->next;
    }
    this->sort();
}
void ConcatStringList::ReferencesList::recheckRef()
{
    if (head == NULL || head->refCount != 0) return;
    ConcatStringList::RefNode *p = head;
    while (p != NULL) {
        ConcatStringList::CharALNode *p_char = p->data;
        delete p_char;
        ConcatStringList::RefNode *p_ref_next = p->next;
        delete p;
        p = p_ref_next;
    }
    head = NULL;
    tail = NULL;
    count_ref_node = 0;
}
// 3.3.1
int ConcatStringList::ReferencesList::size() const
{
    return this->count_ref_node;
}
// 3.3.2
int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0 || index >= this->count_ref_node) throw out_of_range("Index of references list is invalid!");
    ConcatStringList::RefNode *p = this->head;
    int i = 0;
    while (p != NULL) {
        if (i == index) return p->refCount;
        p = p->next;
        i++;
    }
    return -1;
}
// 3.3.3
std::string ConcatStringList::ReferencesList::refCountsString() const
{
    string res_string = "RefCounts[";
    ConcatStringList::RefNode *p = this->head;
    while (p != NULL) {
        if (p != this->head) res_string += ',';
        res_string += to_string(p->refCount);
        p = p->next;
    }
    res_string += ']';
    return res_string;
}
// Implementation of class DeleteStringList
ConcatStringList::DeleteStringList::DeleteStringList() : head(NULL), tail(NULL), count_del_node(0) {}
void ConcatStringList::DeleteStringList::appendNode(CharALNode *char_node_1, CharALNode *char_node_2, int *refCountHead, int *refCountTail, bool checkConcat)
{
    ConcatStringList::DelNode *pNew = new ConcatStringList::DelNode(char_node_1, char_node_2, refCountHead, refCountTail, checkConcat, NULL);
    if (count_del_node == 0) {
        head = pNew;
        tail = pNew;
    }
    else {
        tail->next = pNew;
        tail = pNew;
    }
    count_del_node++;
}
void ConcatStringList::DeleteStringList::updateDel()
{
    ConcatStringList::DelNode *p = head;
    while (p != NULL) {
        if (*(p->refCountHead) + *(p->refCountTail) == 0) {
            //xoa cac node o giua head va tail voi dieu kien list ko phai do concat
            if (p->checkConcat == false) {
                ConcatStringList::CharALNode *p_char = p->head_deleted->next;
                while (p_char != p->tail_deleted->next && p_char != p->tail_deleted) {
                    ConcatStringList::CharALNode *p_char_next = p_char->next;
                    delete p_char;
                    p_char = p_char_next;
                }
                p->head_deleted->next = NULL;
                p->tail_deleted->next = NULL;
            }
            //xoa DelNode hien tai (p) ra khoi DeleteStringList
            if (count_del_node == 1) {
                delete head;
                head = NULL;
                tail = NULL;
                count_del_node = 0;
                return;
            }
            else if (p == head) {
                ConcatStringList::DelNode *tmp = head->next;
                delete head;
                head = tmp;
                p = head;
            }
            else {
                ConcatStringList::DelNode *pre = head;
                while (pre->next != p) pre = pre->next;
                pre->next = p->next;
                if (p == tail) tail = pre;
                delete p;
                p = pre->next;
            }
            count_del_node--;
        }
        else p = p->next;
    }
}
// 3.3.4
int ConcatStringList::DeleteStringList::size() const
{
    return this->count_del_node;
}
// 3.3.5
std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    string res_string = "TotalRefCounts[";
    int total_ref = 0;
    ConcatStringList::DelNode *p = this->head;
    while (p != NULL) {
        if (p->head_deleted == p->tail_deleted) total_ref = *(p->refCountHead);
        else total_ref = *(p->refCountHead) + *(p->refCountTail);
        if (p != this->head) res_string += ',';
        res_string += to_string(total_ref);
        p = p->next;
    }
    res_string += "]";
    return res_string;
}