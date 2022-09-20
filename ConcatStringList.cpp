#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

// Implementation of subclass CharALNode
ConcatStringList::CharALNode::CharALNode(const char * data) : next(NULL), length(0)
{
    while (data[this->length] != '\0') this->length++;

    this->CharArrayList = new char[this->length+1]; // Free memory of CharArrayList in CharALNode->Destructor
    for (int i = 0; i < this->length; i++) {
        this->CharArrayList[i] = data[i];
    }
    this->CharArrayList[this->length] = '\0';
}

ConcatStringList::CharALNode::CharALNode(string data) : next(NULL)
{
    this->length = data.size();

    this->CharArrayList = new char[this->length+1]; // Free memory of CharArrayList in CharALNode->Destructor
    for (int i = 0; i < this->length; i++) {
        this->CharArrayList[i] = data[i];
    }
    this->CharArrayList[this->length] = '\0';
}

ConcatStringList::CharALNode::~CharALNode()
{
    delete[] this->CharArrayList;
}
// Implementation of subclass RefNode
ConcatStringList::RefNode::RefNode() : data_ref(NULL), num_of_ref(0), next_ref_node(NULL) {}
ConcatStringList::RefNode::RefNode(CharALNode * data_ref, int num_of_ref, RefNode * next_ref_node)
                        : data_ref(data_ref), num_of_ref(num_of_ref), next_ref_node(next_ref_node) {}

ConcatStringList::DelNode::DelNode() : head_del_concatlist(NULL), tail_del_concatlist(NULL), next_del_node(NULL) {}
ConcatStringList::DelNode::DelNode(RefNode * head_del_concatlist, RefNode * tail_del_concatlist, DelNode * next_del_node)
                        : head_del_concatlist(NULL), tail_del_concatlist(NULL), next_del_node(NULL) {}

// Implementation of class ConcatStringList
ConcatStringList::ConcatStringList(const char * s)
{
    // Create 1 Node with the CharArrayList <-- s
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s); // Free memory of all Nodes in this->Destructor
    this->head = this->tail = pNew;
    this->count_node = 1;
    this->count_char = pNew->length;
}

ConcatStringList::ConcatStringList() : head(NULL), tail(NULL), count_node(0), count_char(0) {}

void ConcatStringList::addNode(const char * s)
{
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s); // Free memory of all Nodes in this->Destructor
    if (this->count_node == 0)
        this->head = this->tail = pNew;
    else {
        this->tail->next = pNew;
        this->tail = pNew;
    }
    this->count_node++;
    this->count_char += pNew->length;
}

void ConcatStringList::addNode(string s)
{
    ConcatStringList::CharALNode *pNew = new ConcatStringList::CharALNode(s); // Free memory of all Nodes in this->Destructor
    if (this->count_node == 0)
        this->head = this->tail = pNew;
    else {
        this->tail->next = pNew;
        this->tail = pNew;
    }
    this->count_node++;
    this->count_char += pNew->length;
}

int ConcatStringList::length() const
{
    return this->count_char;
}

char ConcatStringList::get(int index) const
{
    if (index < 0 || index >= this->count_char) throw out_of_range("Index of string is invalid!");
    ConcatStringList::CharALNode *p = head;
    char res_c;
    while (p != this->tail->next) {
        if (index < p->length) {
            res_c = p->CharArrayList[index];
            break;
        }
        else index -= p->length;
        p = p->next;
    }
    return res_c;
}//O(k) node

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
        
    // length of new string list should be to - from
    // to - cnt <= p->length: new list has only 1 node
    // to - cnt > p->length: more than 1 node

    if (to - cnt <= p->length) {
        char *tmp_char = new char[to - from + 1];
        for (int i = 0; i < to-from; i++) {
            tmp_char[i] = p->CharArrayList[from - cnt + i];
        }
        tmp_char[to-from] = '\0';

        res_S.addNode(tmp_char);

        delete[] tmp_char;
    }
    else {
        int length_of_substr = to - from;
        int i = from;
        while (p != this->tail->next) {
            int first_word_idx = i - cnt;
            int length_of_new_word = min(p->length - first_word_idx, to - cnt);
            string tmp_str(p->CharArrayList);
            string tmp_sub_str = tmp_str.substr(first_word_idx, length_of_new_word);
            
            res_S.addNode(tmp_sub_str);

            i += length_of_new_word;
            if (i < to) {
                cnt += p->length;
                p = p->next;
            }
            else break;
        }
    }
    return res_S;
}

ConcatStringList ConcatStringList::reverse() const
{
    ConcatStringList res_S;
    ConcatStringList::CharALNode *p_curr = this->head;
    // Reverse the string
    while (p_curr != this->tail->next) {
        string tmp_string(p_curr->CharArrayList);
        string tmp_string_reversed(tmp_string.rbegin(), tmp_string.rend());
        res_S.addNode(tmp_string_reversed);
        p_curr = p_curr->next;
    }
    // Reverse the list
    res_S.tail = res_S.head;
    p_curr = res_S.head;
    ConcatStringList::CharALNode *p_next = NULL, *p_prev = NULL;
    while (p_curr != NULL) {
        p_next = p_curr->next;
        p_curr->next = p_prev;
        p_prev = p_curr;
        p_curr = p_next;
    }
    res_S.head = p_prev;
    return res_S;
}

ConcatStringList::~ConcatStringList()
{
    ConcatStringList::CharALNode *p;
    while (this->head != this->tail->next) {
        p = this->head;
        this->head = this->head->next;
        delete p;
    }
}

// Implementation of class ReferencesList
int ConcatStringList::ReferencesList::size() const
{
    return this->count_ref_node;
}
int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0 || index >= this->count_ref_node) throw out_of_range("Index of references list is invalid!");
    ConcatStringList::RefNode *p = this->head_ref;
    int i = 0;
    while (p != NULL) {
        if (i == index) return p->num_of_ref;
        p = p->next_ref_node;
        i++;
    }
    return -1;
}
std::string ConcatStringList::ReferencesList::refCountsString() const
{
    string res_string = "RefCounts[";
    ConcatStringList::RefNode *p = this->head_ref;
    while (p != NULL) {
        if (p != this->head_ref) res_string += ',';
        res_string += to_string(p->num_of_ref);
    }
    res_string += ']';
    return res_string;
}

// Implementation of class DeleteStringList
int ConcatStringList::DeleteStringList::size() const
{
    return this->count_del_node;
}
std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    string res_string = "TotalRefCounts[";
    int total_ref = 0;
    ConcatStringList::DelNode *p = this->head_del;
    while (p != NULL) {
        if (p->head_del_concatlist == p->tail_del_concatlist) total_ref = p->head_del_concatlist->num_of_ref;
        else total_ref = p->head_del_concatlist->num_of_ref + p->tail_del_concatlist->num_of_ref;
        if (p != this->head_del) res_string += ',';
        res_string += to_string(total_ref);
    }
    res_string += "]";
    return res_string;
}