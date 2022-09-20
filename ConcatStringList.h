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
    CharALNode* head;
    CharALNode* tail;
    int count_node;
    int count_char;

    void addNode(const char *);
    void addNode(string);

public:
    ConcatStringList(const char *);
    ConcatStringList();
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
        RefNode* head_ref;
        int count_ref_node;
    public:
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes
    public:
        DelNode* head_del;
        DelNode* tail_del;
        int count_del_node;
    public:
        int size() const;
        std::string totalRefCountsString() const;
    };

    class CharALNode {
    public:
        char* CharArrayList;
        CharALNode* next;
        int length;

    public:
        CharALNode(const char *);
        CharALNode(string);
        ~CharALNode();
    };

    class RefNode {
    public:
        CharALNode* data_ref;
        int num_of_ref;
        RefNode* next_ref_node;
    public:
        RefNode();
        RefNode(CharALNode *, int, RefNode *);
    };

    class DelNode {
    public:
        RefNode* head_del_concatlist;
        RefNode* tail_del_concatlist;
        DelNode* next_del_node;
    public:
        DelNode();
        DelNode(RefNode *, RefNode *, DelNode *);
    };
};

#endif // __CONCAT_STRING_LIST_H__