#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
// Forward declaration of Node structures
public:
    class CharALNode; 
    class RefNode;
    class DelNode;

// Declare attributes and methods for ConcatStringList
private:
    CharALNode* head; // Free memory of all Nodes in Concat->Destructor
    CharALNode* tail;
    int count_node;
    int count_char;

    ConcatStringList();
    void appendNode(string);
    void appendNode(const char *);

public:
    ConcatStringList(const char * s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();
// End ConcatStringList's member declaration
int getNode() {return this->count_node;}

// Declare attributes and methods for ReferencesList, DeleteStringList and all Node structures
public:
    class ReferencesList {
        // TODO: may provide some attributes
    public:
        RefNode* head;
        RefNode* tail;
        int count_ref_node;

        RefNode * addNode(CharALNode *&); // add node at begining of list
        void swapNode(RefNode *); // swap current node with the node right behind
        void updateRefList(CharALNode *);
    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes
    public:
        DelNode* head;
        DelNode* tail;
        int count_del_node;

        void addNode(DelNode *);
        void updateDelList();
    public:
        int size() const;
        std::string totalRefCountsString() const;
    };

    class CharALNode {
    public:
        char *CharArrayList; // Free memory of CharArrayList in CharALNode->Destructor
        int length;
        CharALNode *next;

    public:
        CharALNode(const char *);
        CharALNode(string);
        CharALNode(const CharALNode &);
        ~CharALNode();
    };

    class RefNode {
    public:
        CharALNode *data;
        int refCount;
        RefNode *next;
    public:
        RefNode();
        RefNode(CharALNode *, int, RefNode *);
    };

    class DelNode {
    public:
        CharALNode *head_deleted;
        CharALNode *tail_deleted;
        int *refCountHead;
        int *refCountTail;
        DelNode *next;
    public:
        DelNode();
        DelNode(CharALNode *, CharALNode *, int *, int *, DelNode *);
    };
};

#endif // __CONCAT_STRING_LIST_H__