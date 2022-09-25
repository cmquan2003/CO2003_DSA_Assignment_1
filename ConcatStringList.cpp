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
ConcatStringList::DelNode::DelNode() : head_deleted(NULL), tail_deleted(NULL), refCountHead(NULL), refCountTail(NULL), next(NULL) {}
ConcatStringList::DelNode::DelNode(CharALNode *head_deleted, CharALNode *tail_deleted, int *refCountHead, int *refCountTail, DelNode *next)
        : head_deleted(head_deleted), tail_deleted(tail_deleted), refCountHead(refCountHead), refCountTail(refCountTail), next(next) {}

// Implementation of class ConcatStringList
// 3.2.1
ConcatStringList::ConcatStringList(const char * s) : count_node(1)
{
    // Create 1 Node with the CharArrayList <-- s
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s);
    head = pNew;
    tail = pNew;
    count_char = pNew->length;
}
// Private Stuff =))
ConcatStringList::ConcatStringList() : head(NULL), tail(NULL), count_node(0), count_char(0) {}
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
    
    return res_S;
}
// 3.2.9
ConcatStringList::~ConcatStringList()
{
    if (count_node==0) return;
    ConcatStringList::CharALNode *p;
    while (head != tail->next) {
        p = head;
        head = head->next;
        delete p;
    }
}

// Implementation of class ReferencesList
// 3.3.1
int ConcatStringList::ReferencesList::size() const
{
    return this->count_ref_node;
}
// 3.3.2
int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    // if (index < 0 || index >= this->count_ref_node) throw out_of_range("Index of references list is invalid!");
    // ConcatStringList::RefNode *p = this->head;
    // int i = 0;
    // while (p != NULL) {
    //     if (i == index) return p->num_of_ref;
    //     p = p->next_ref_node;
    //     i++;
    // }
    return -1;
}
// 3.3.3
std::string ConcatStringList::ReferencesList::refCountsString() const
{
    string res_string = "RefCounts[";
    // ConcatStringList::RefNode *p = this->head;
    // while (p != NULL) {
    //     if (p != this->head) res_string += ',';
    //     res_string += to_string(p->num_of_ref);
    // }
    // res_string += ']';
    return res_string;
}
ConcatStringList::RefNode * ConcatStringList::ReferencesList::addNode(CharALNode *& char_node)
{
    ConcatStringList::RefNode *pNew = new ConcatStringList::RefNode(char_node, 1, NULL);
    // if (this->count_ref_node == 0) {
    //     this->head = this->tail = pNew;
    // }
    // else {
    //     pNew->next_ref_node = this->head;
    //     this->head = pNew;
    // }
    // this->count_ref_node++;
    return pNew;
}
void ConcatStringList::ReferencesList::swapNode(RefNode * ref_node)
{
    // if (this->head == ref_node) {// at least 2 node
    //     ConcatStringList::RefNode *tmp = this->head->next_ref_node; // now we need to swap head with tmp
    //     this->head->next_ref_node = tmp->next_ref_node;
    //     tmp->next_ref_node = this->head;
    //     this->head = tmp;
    //     if (this->count_ref_node == 2) this->tail = this->head->next_ref_node;
    // }
    // else {// at least 3 node
    //     ConcatStringList::RefNode *p = this->head;
    //     while (p->next_ref_node != ref_node) {
    //         p = p->next_ref_node;
    //     }
    //     ConcatStringList::RefNode *tmp = ref_node->next_ref_node;
    //     ref_node->next_ref_node = tmp->next_ref_node;
    //     p->next_ref_node = tmp;
    //     tmp->next_ref_node = ref_node;
    //     if (this->tail == tmp) this->tail = ref_node;
    // }
}
void ConcatStringList::ReferencesList::updateRefList(CharALNode * char_node)
{
    // ConcatStringList::RefNode *p = this->head;
    // while (p != NULL) {
    //     if (p->data_ref == char_node) {
    //         p->num_of_ref++;
    //         break;
    //     }
    // }
    // if (p == NULL) p = addNode(char_node);
    // while (p->next_ref_node != NULL && p->next_ref_node->num_of_ref != 0 && p->num_of_ref > p->next_ref_node->num_of_ref) {
    //     // swap Node
    //     swapNode(p);
    // }
}

// Implementation of class DeleteStringList
// 3.3.4
int ConcatStringList::DeleteStringList::size() const
{
    return this->count_del_node;
}
// 3.3.5
std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    string res_string = "TotalRefCounts[";
    // int total_ref = 0;
    // ConcatStringList::DelNode *p = this->head;
    // while (p != NULL) {
    //     if (p->head_del_concatlist == p->tail_del_concatlist) total_ref = p->head_del_concatlist->num_of_ref;
    //     else total_ref = p->head_del_concatlist->num_of_ref + p->tail_del_concatlist->num_of_ref;
    //     if (p != this->head) res_string += ',';
    //     res_string += to_string(total_ref);
    // }
    res_string += "]";
    return res_string;
}