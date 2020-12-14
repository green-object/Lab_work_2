#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include "string"
#include "htable.cpp"
#include "elem.h"
#include "assert.h"

#define inputfile "C:\\Users\\Ivan\\Desktop\\input_int_f.txt"
#define outputfile "C:\\Users\\Ivan\\Desktop\\output_int_f.txt"

using namespace std;

void chek_def_size(){
    HTable<string> ht;
    assert(0 == ht.get_size());
}

void chek_plus_size(){
    HTable<string> ht;
    ht << "povar";
    assert(1 == ht.get_size());
}

void chek_plus_key(){
    HTable<string> ht;
    ht << "povar";
    ht << "povar";
    assert(1 == ht.get_size());
    assert(2 == ht.operator[]("povar"));
}

void chek_is_key(){
    HTable<string> ht;
    ht << "povar";
    assert(1 == ht.check_element("povar"));
}

void chek_value(){
    HTable<string> ht;
    ht << "povar";
    assert(1 == ht.operator[]("povar"));
}

void chek_minus_size(){
    HTable<string> ht;
    ht << "povar";
    try {
        ht.del_element("rabotnik");
    }
    catch(out_of_range& er) {
    }
    assert(1 == ht.get_size());
    try {
        ht.del_element("povar");
    }
    catch(out_of_range& er) {
    }
    assert(0 == ht.get_size());
}

void chek_del_key(){
    HTable<string> ht;
    ht << "povar";
    ht.del_element("povar");
    assert(0 == ht.check_element("povar"));
}

void chek_rav(){
    HTable<string> ht;
    HTable<string> ht1;
    ht << "povar";
    ht.del_all();
    assert(ht == ht1);
}

void chek_copy(){
    HTable<string> ht;
    ht << "povar";
    HTable<string> ht1(ht);
    assert(ht == ht1);
    ht.del_element("povar");
    assert(0 == (ht == ht1));
}

void chek_write(){
    HTable<string> ht;
    HTable<string> ht1;
    ht.read_from_file(inputfile);
    ht.write_to_file(outputfile);
    ht1.read_from_file(outputfile);
    ht1.write_to_file(outputfile);
    assert(ht1 == ht);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    chek_def_size();
    chek_plus_size();
    chek_plus_key();
    chek_is_key();
    chek_value();
    chek_minus_size();
    chek_del_key();
    chek_rav();
    chek_copy();
    chek_write();
    //cout << "hello world!!!" << endl;
    return a.exec();
}
