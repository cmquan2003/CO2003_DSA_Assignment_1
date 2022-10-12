#include "ConcatStringList.h"
// size_t used = 0;
// size_t deleted = 0;
// size_t constr = 0;
// size_t destr = 0;
// unsigned int attempt = 0;
// void *operator new(size_t size) throw(std::bad_alloc)
// {
//     ++constr;
//     used += size;

//     size_t *ptr = (size_t *)malloc(sizeof(size_t) + size);
//     ptr[0] = size;

//     return (void *)&ptr[1];
// }

// void operator delete(void *ptr) throw()
// {
//     ++destr;
//     deleted += ((size_t *)ptr)[-1];

//     free(&(((size_t *)ptr)[-1]));
// }

// bool isLeak()
// {
//     if (constr - destr == 0 && used - deleted == 0)
//         return false;
//     return true;
// }

// void checkleak()
// {
//     cout << "[" << attempt++ << "]"
//          << " simpleB: ";

//     if (isLeak())
//     {
//         cout << "Leakage detected. [ Total: " << used - deleted << " bytes | Average: " << (used - deleted) / (constr - destr) << " bytes ]" << endl;
//     }
//     else
//     {
//         cout << "No leakage found." << endl;
//     }

//     used = 0;
//     deleted = 0;
//     constr = 0;
//     destr = 0;
// }
void tc1() {
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc2() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is_an_assignment");

    // test concat
    ConcatStringList s3 = s1.concat(s2);
    cout << "s3: " << s3.toString() << endl;

    // test subString
    ConcatStringList s4 = s3.subString(5, 15);
    cout << "s4: " << s4.toString() << endl;

    // test reverse
    ConcatStringList s5 = s3.reverse();
    cout << "s5: " << s5.toString() << endl;
}

void tc3() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}
void tc4() {
    // Test subString
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4("_for_CSE_students");
    ConcatStringList s5 = s1.concat(s2);
    ConcatStringList s6 = s5.subString(0, s5.length());
    ConcatStringList s7 = s3.concat(s4);
    ConcatStringList s8 = s7.subString(0, s7.length());
    ConcatStringList s9 = s6.concat(s8);
    ConcatStringList s10 = s9.subString(5, 30);
    ConcatStringList s11 = s9.reverse();
    cout << s1.toString() << " " << endl;
    cout << s2.toString() << " " << endl;
    cout << s3.toString() << " " << endl;
    cout << s4.toString() << " " << endl;
    cout << s5.toString() << " " << endl;
    cout << s6.toString() << " " << endl;
    cout << s7.toString() << " " << endl;
    cout << s8.toString() << " " << endl;
    cout << s9.toString() << " " << endl;
    cout << s10.toString() << " " << s10.length() << endl;
    cout << s11.toString() << " " << s11.length() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}
void tc5() {
    // Test reverse
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");
    ConcatStringList s4("_for_CSE_students");
    ConcatStringList s9 = s3.concat(s4);
    ConcatStringList s10 = s9.reverse();
    ConcatStringList s5 = s1.reverse();
    ConcatStringList s6 = s2.reverse();
    ConcatStringList s7 = s3.reverse();
    ConcatStringList s8 = s4.reverse();
    cout << s1.toString() << " " << endl;
    cout << s2.toString() << " " << endl;
    cout << s3.toString() << " " << endl;
    cout << s4.toString() << " " << endl;
    cout << s5.toString() << " " << endl;
    cout << s6.toString() << " " << endl;
    cout << s7.toString() << " " << endl;
    cout << s8.toString() << " " << endl;
    cout << s9.toString() << " " << endl;
    cout << s10.toString() << " " << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,2,2,2,2,2,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    ConcatStringList s11 = s4.reverse().concat(s5).reverse();//"Hello,_for_CSE_students"
    cout << s11.toString() << " " << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,2,2,2,3,3,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2]
}
void tc6() {
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is");
    // ConcatStringList s6 = s1->concat(*s2);
    // ConcatStringList * s7 = new ConcatStringList(s6);// Copy constructor: Not mentioned in assignment -> Not appeared
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList s4 = s3->subString(1,10);
    ConcatStringList * s5 = new ConcatStringList("_an_assignment");
    ConcatStringList * s6 = new ConcatStringList(s4.concat(*s5));
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,2,3,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,2,3,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    delete s5;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    delete s6;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
}
void special_tc(){
    ConcatStringList * s1 = new ConcatStringList("Hello");                            // SPECIAL TEST CASE
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList("LOL");
    ConcatStringList * s4 = new ConcatStringList("HOHO");
    ConcatStringList * s5 = new ConcatStringList(s1->concat(*s2));//"Hello_world"
    ConcatStringList * s6 = new ConcatStringList(s5->reverse());//"dlrow_olleH"
    ConcatStringList * s7 = new ConcatStringList(s6->concat(*s3));//"dlrow_olleHLOL"
    ConcatStringList * s8 = new ConcatStringList(s7->subString(1,14));//"lrow_olleHLOL"
    ConcatStringList * s9 = new ConcatStringList(s8->concat(*s4));//"lrow_olleHLOLHOHO"
    cout << endl;
    cout <<"--------SPECIAL--------" << endl;
    cout <<"s1: "<<s1->toString()<<endl;
    cout <<"s2: "<<s2->toString()<<endl;
    cout <<"s3: "<<s3->toString()<<endl;
    cout <<"s4: "<<s4->toString()<<endl;
    cout <<"s5: "<<s5->toString()<<endl;
    cout <<"s6: "<<s6->toString()<<endl;
    cout <<"s7: "<<s7->toString()<<endl;
    cout <<"s8: "<<s8->toString()<<endl;
    cout <<"s9: "<<s9->toString()<<endl;
    cout << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,2,3,3,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,2,3,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,3,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,1,2,2,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,2,3,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,3,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc7() {
    ConcatStringList *s1 = new ConcatStringList("Mega_");
    ConcatStringList *s2 = new ConcatStringList(s1->concat(ConcatStringList("Cataclysm")));
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,3]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
}
void tc8() {
    // test flexible concatenation
    ConcatStringList *s1 = new ConcatStringList(" > msylcataC");
    ConcatStringList *s2 = new ConcatStringList("_ageM");
    ConcatStringList *s3 = new ConcatStringList("Kinkou");
    ConcatStringList *s4 = new ConcatStringList("_The_H");
    ConcatStringList *s5 = new ConcatStringList("uei");
    ConcatStringList *s6 = new ConcatStringList((s1->concat(*s2)).reverse());
    ConcatStringList *s7 = new ConcatStringList((s3->concat(*s4)).subString(0,12));
    ConcatStringList *s8 = new ConcatStringList(s7->concat(s5->reverse()));
    ConcatStringList *s9 = new ConcatStringList(s6->concat(s8->subString(0, s8->length())));
    cout << "s1: " << s1->toString() << endl;
    cout << "s2: " << s2->toString() << endl;
    cout << "s3: " << s3->toString() << endl;
    cout << "s4: " << s4->toString() << endl;
    cout << "s5: " << s5->toString() << endl;
    cout << "s6: " << s6->toString() << endl;
    cout << "s7: " << s7->toString() << endl;
    cout << "s8: " << s8->toString() << endl;
    cout << "s9: " << s9->toString() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,2,2,2,2,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[4,4,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,2,2,2,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2,4,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,2,2,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[4,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,2,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2,1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,0,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,0,0,0,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc9() {
    // test multiple reverse
    ConcatStringList *s1 = new ConcatStringList("lacigaM");
    ConcatStringList *s2 = new ConcatStringList("_Journey!");
    ConcatStringList *s3 = new ConcatStringList(s1->reverse().concat(*s2));
    ConcatStringList *s4 = new ConcatStringList(s2->reverse().subString(0,5));
    ConcatStringList *s5 = new ConcatStringList(s3->reverse().reverse());
    ConcatStringList *s6 = new ConcatStringList(s1->reverse().concat(s2->subString(1,s2->length()-1)));
    cout << "s1: " << s1->toString() << endl;
    cout << "s2: " << s2->toString() << endl;
    cout << "s3: " << s3->toString() << endl;
    cout << "s4: " << s4->toString() << endl;
    cout << "s5: " << s5->toString() << endl;
    cout << "s6: " << s6->toString() << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,1,2,2,3,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,2,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,2]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,0,0,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc10() {
    // test multiple subString
    ConcatStringList * s1 = new ConcatStringList("Hello,");
    ConcatStringList * s2 = new ConcatStringList("_this_is_an_assignment");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s4 = new ConcatStringList(s3->subString(0, 11).subString(4,8));//"o,_t"
    cout <<"s1: "<<s1->toString()<<endl;
    cout <<"s2: "<<s2->toString()<<endl;
    cout <<"s3: "<<s3->toString()<<endl;
    cout <<"s4: "<<s4->toString()<<endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,3,3,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,2,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[4]
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,2,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2]
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[2,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2]
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void tc11() {
    ConcatStringList s1("g");
    ConcatStringList s2("");
    ConcatStringList s3("abc");
    ConcatStringList s4(s3.concat(s2));//"abc"->""
    ConcatStringList s5(s4.subString(0, 3));//"abc"
    ConcatStringList s6(ConcatStringList("").concat(s5));//""->"abc"
    ConcatStringList s7(s1.concat(s6.subString(0, s6.length())));//"g"->""->"abc"
    cout << s4.toString() << " " /*<< s4.getNode()*/ << " " << s4.length() << endl;
    cout << s5.toString() << " " /*<< s5.getNode()*/ << " " << s5.length() << endl;
    cout << s6.toString() << " " /*<< s6.getNode()*/ << " " << s6.length() << endl;
    cout << s7.toString() << " " /*<< s7.getNode()*/ << " " << s7.length() << endl;
}
void NULLString_tc(){
    ConcatStringList * s1 = new ConcatStringList("");
    ConcatStringList * s2 = new ConcatStringList("");
    ConcatStringList * s3 = new ConcatStringList("Let's_test.");
    ConcatStringList * s4 = new ConcatStringList(s1->concat(*s3));
    ConcatStringList * s5 = new ConcatStringList(s4->subString(0,11));
    ConcatStringList * s6 = new ConcatStringList("_Can_it_still_correct_answer___???");
    ConcatStringList * s7 = new ConcatStringList(s2->concat(*s6));
    ConcatStringList * s8 = new ConcatStringList(s7->subString(0,s7->length()-6));
    ConcatStringList * s9 = new ConcatStringList(s5->concat(*s8));
    ConcatStringList * s10 = new ConcatStringList(s9->reverse());
    cout<<"-------------------------------------------------------"<<endl;
    cout<<"text content check"<<endl;
    cout<<"------------EXPECTED ANSWER HERE------------------"<<endl;
    cout<<"s1:\ns2:\n";
    cout<<"s3:Let's_test.\ns4:Let's_test.\ns5:Let's_test."<<endl;
    cout<<"s6:_Can_it_still_correct_answer___???\ns7:_Can_it_still_correct_answer___???\ns8:_Can_it_still_correct_answer"<<endl;
    cout<<"s9:Let's_test._Can_it_still_correct_answer"<<endl;
    cout<<"s10:rewsna_tcerroc_llits_ti_naC_.tset_s'teL"<<endl;
    cout<<"------------YOUR ANSWER HERE------------------------"<<endl;
    cout<<"s1:"<<s1->toString()<<endl;
    cout<<"s2:"<<s2->toString()<<endl;
    cout<<"s3:"<<s3->toString()<<endl;
    cout<<"s4:"<<s4->toString()<<endl;
    cout<<"s5:"<<s5->toString()<<endl;
    cout<<"s6:"<<s6->toString()<<endl;
    cout<<"s7:"<<s7->toString()<<endl;
    cout<<"s8:"<<s8->toString()<<endl;
    cout<<"s9:"<<s9->toString()<<endl;
    cout<<"s10:"<<s10->toString()<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<"get, length, indexof check"<<endl;
    cout<<"------------EXPECTED ANSWER HERE------------------"<<endl;
    cout<<"s1's length is 0"<<endl;
    cout<<"s2's length is 0"<<endl;
    cout<<"s3's length is 11"<<endl;
    cout<<"s4's length is 11"<<endl;
    cout<<"s5's length is 11"<<endl;
    cout<<"s6's length is 34"<<endl;
    cout<<"s7's length is 34"<<endl;
    cout<<"s8's length is 28"<<endl;
    cout<<"s9's length is 39"<<endl;
    cout<<"s10's length is 39"<<endl;
    cout<<"In s4, char at index 3 is:  '  "<<endl;
    cout<<"In s9, char at index 38 is:   r  "<<endl;
    cout<<"In s9, index of 'l' is: 22"<<endl;
    cout<<"------------YOUR ANSWER HERE------------------------"<<endl;
    cout<<"s1's length is "<<s1->length()<<endl;
    cout<<"s2's length is "<<s2->length()<<endl;
    cout<<"s3's length is "<<s3->length()<<endl;
    cout<<"s4's length is "<<s4->length()<<endl;
    cout<<"s5's length is "<<s5->length()<<endl;
    cout<<"s6's length is "<<s6->length()<<endl;
    cout<<"s7's length is "<<s7->length()<<endl;
    cout<<"s8's length is "<<s8->length()<<endl;
    cout<<"s9's length is "<<s9->length()<<endl;
    cout<<"s10's length is "<<s10->length()<<endl;
    cout<<"In s4, char at index 3 is:  "<<s4->get(3)<<endl;
    cout<<"In s9, char at index 38 is:   "<<s9->get(38)<<endl;
    cout<<"In s9, index of 'l' is: "<<s9->indexOf('l')<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<"It's time to delete"<<endl;
    cout<<"----------Info truoc khi delete----------"<<endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout<<"size of refList: "<<ConcatStringList::refList.size()<<endl;
    cout<<"----------bat dau delete-----------------"<<endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    delete s10;
    cout << "--------After deleting s10--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout<<"---------------------ket thuc test case-------------------------------------"<<endl;
}
void tc12() {
    ConcatStringList *s1 = new ConcatStringList("Mega_");
    ConcatStringList *s2 = new ConcatStringList("Cataclysm");
    ConcatStringList *s3 = new ConcatStringList("Kinkou");
    ConcatStringList *s4 = new ConcatStringList("_The_");
    ConcatStringList *s5 = new ConcatStringList("Hieu");
    ConcatStringList *s6 = new ConcatStringList((s1->concat(*s2)).subString(0,14));
    ConcatStringList *s7 = new ConcatStringList(s3->concat(*s4));
    ConcatStringList *s8 = new ConcatStringList((s7->subString(0, s7->length())).concat(*s5));
    ConcatStringList *s9 = new ConcatStringList(s8->subString(0, s8->length()));
    ConcatStringList *s10 = new ConcatStringList(s6->concat(*s9));
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,2,2,2,3,3,3,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[4,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,2,2,3,3,3,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[2,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,2,2,3,3,3,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,2,3,3,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,1,2,2,3,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,1,2,3,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,1,1,2,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,2,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,1,1,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1,1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[1,1,0,0,0,0,0,0,0,0,0]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[1,1]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s10;
    cout << "--------After deleting s10--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;//[]
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;//[]
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
void lasttc() {
    ConcatStringList *s1 = new ConcatStringList("This_");
    ConcatStringList *s2 = new ConcatStringList("is");
    ConcatStringList *s3 = new ConcatStringList("weird");
    ConcatStringList *s4 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList *s5 = new ConcatStringList(s4->reverse());
    ConcatStringList *s6 = new ConcatStringList(s3->concat(*s5));
    cout << endl;
    cout <<"--------LAST--------" << endl;
    cout <<"s1: "<<s1->toString()<<endl;
    cout <<"s2: "<<s2->toString()<<endl;
    cout <<"s3: "<<s3->toString()<<endl;
    cout <<"s4: "<<s4->toString()<<endl;
    cout <<"s5: "<<s5->toString()<<endl;
    cout <<"s6: "<<s6->toString()<<endl;
    cout << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of refList: " <<ConcatStringList::refList.size() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}
int main() {
    cout << "\n---Testing tc1():\n";
    tc1();
    cout << "\n---Testing tc2():\n";
    tc2();
    cout << "\n---Testing tc3():\n";
    tc3();
    cout << "\n---Testing tc4():\n";
    tc4();
    cout << "\n---Testing tc5():\n";
    tc5();
    cout << "\n---Testing tc6():\n";
    tc6();
    cout << "\n---Testing tc7():\n";
    tc7();
    cout << "\n---Testing tc8():\n";
    tc8();
    cout << "\n---Testing tc9():\n";
    tc9();
    cout << "\n---Testing tc10():\n";
    tc10();
    cout << "\n---Testing tc11():\n";
    tc11();
    cout << "\n---Testing tc12():\n";
    tc12();
    special_tc();
    NULLString_tc();
    lasttc();
    cout << ConcatStringList::refList.refCountsString() << "; Size = " << ConcatStringList::refList.size() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << "; Size = " << ConcatStringList::delStrList.size() << endl;
    cout << "Testing succeeded\n";
    // checkleak();
    return 0;
}
// g++ -o main main.cpp ConcatStringList.cpp -I . -std=c++11