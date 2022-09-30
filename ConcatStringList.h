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
    CharALNode* head; // Free memory of all CharALNodes in Concat->Destructor
    CharALNode* tail;
    int count_node;
    int count_char;
    bool checkConcat;

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

// Declare attributes and methods for ReferencesList, DeleteStringList and all Node structures
public:
    class ReferencesList {
        // TODO: may provide some attributes
    public:
        RefNode* head; // Free memory of all RefNodes in Concat->Destructor at appropriate moment
        RefNode* tail;
        int count_ref_node;

        ReferencesList();
        // after creating a ConcatStringList
        void insertNode(CharALNode * char_node_1, CharALNode * char_node_2=NULL);
        void updateConcat(CharALNode *, CharALNode *);
        void split(RefNode *, RefNode *&, RefNode *&);
        RefNode *mergeList(RefNode *&, RefNode *&);
        void mergeSort(RefNode *&);
        void sort();
        // after deleting a ConcatStringList
        void reduceRef(CharALNode *&, CharALNode *&, int *&, int *&);
        void recheckRef();
    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes
    public:
        DelNode* head; // Free memory of all DelNodes in Concat->Destructor at appropriate moment
        DelNode* tail;
        int count_del_node;

        DeleteStringList();
        void appendNode(CharALNode *, CharALNode *, int *, int *, bool);
        void updateDel();
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
        bool checkConcat;
        DelNode *next;
    public:
        DelNode();
        DelNode(CharALNode *, CharALNode *, int *, int *, bool, DelNode *);
    };
};

#endif // __CONCAT_STRING_LIST_H__