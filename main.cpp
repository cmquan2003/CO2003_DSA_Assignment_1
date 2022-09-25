#include "ConcatStringList.h"

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
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    ConcatStringList s5 = s1.concat(s2).concat(s3);
    cout << "s5: " << s5.toString() << endl;

    // test subString
    ConcatStringList s6 = s5.subString(5, 15);
    cout << "s6: " << s6.toString() << endl;
    
    // test reverse
    ConcatStringList s7 = s5.reverse();
    cout << "s7: " << s7.toString() << endl;
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
    cout << s1.toString() << " " << s1.getNode() << endl;
    cout << s2.toString() << " " << s2.getNode() << endl;
    cout << s3.toString() << " " << s3.getNode() << endl;
    cout << s4.toString() << " " << s4.getNode() << endl;
    cout << s5.toString() << " " << s5.getNode() << endl;
    cout << s6.toString() << " " << s6.getNode() << endl;
    cout << s7.toString() << " " << s7.getNode() << endl;
    cout << s8.toString() << " " << s8.getNode() << endl;
    cout << s9.toString() << " " << s9.getNode() << endl;
    cout << s10.toString() << " " << s10.getNode() << " " << s10.length() << endl;
    cout << s11.toString() << " " << s11.getNode() << " " << s11.length() << endl;
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
    cout << s1.toString() << " " << s1.getNode() << endl;
    cout << s2.toString() << " " << s2.getNode() << endl;
    cout << s3.toString() << " " << s3.getNode() << endl;
    cout << s4.toString() << " " << s4.getNode() << endl;
    cout << s5.toString() << " " << s5.getNode() << endl;
    cout << s6.toString() << " " << s6.getNode() << endl;
    cout << s7.toString() << " " << s7.getNode() << endl;
    cout << s8.toString() << " " << s8.getNode() << endl;
    cout << s9.toString() << " " << s9.getNode() << endl;
    cout << s10.toString() << " " << s10.getNode() << endl;
    // ConcatStringList s8 = s4.reverse().concat(s5).reverse().reverse().reverse();//"tnemngissa_na_si_siht_,olleHHello,_this_is"
    // cout << "s8: " << s8.toString() << endl;
    // ConcatStringList s9 = s1.reverse();
    // cout << "s9: " << s9.toString() << endl;
    // ConcatStringList s10 = s4.concat(s1);
    // cout << "s10: " << s10.toString() << endl;// Destructor have problem for s10!!
}
int main() {
    // cout << "---Testing tc1():\n";
    // tc1();
    // cout << "---Testing tc2():\n";
    // tc2();
    // cout << "---Testing tc3():\n";
    // tc3();
    // cout << "---Testing tc4():\n";
    // tc4();
    cout << "---Testing tc5():\n";
    tc5();
    cout << "Testing succeeded";
    return 0;
}
// g++ -o main main.cpp ConcatStringList.cpp -I . -std=c++11