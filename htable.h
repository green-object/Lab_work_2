#ifndef HTABLE_H
#define HTABLE_H
#include "string"
#include "istream"
#include "iostream"
#include "elem.h"
#include "fstream"

#define def_size 100

using namespace std;

template<class K>
class HTable
{

private:
    int size;

    elem<K> *mas[def_size];

    static int hash(string str){
            int ascii_sum = 0;
            for (auto s: str)
            {
                ascii_sum += s;
            }
            return ascii_sum % def_size;
        }

public:
    HTable();
    HTable(const HTable<K>& copy);
    ~HTable();
    void del_all();
    int get_size() const {return size;}
    void read_from_file(const string& input_file);
    void write_to_file(const string& output_file);
    void del_element(const K& key);
    bool check_element(const K& key) const;
    K get_min_mis() const;
    K get_max_mis() const;
    bool operator==(const HTable<K>& other) const;
    void operator<<(const K& new_key);
    uint16_t operator[](const K& key) const;
    elem<K> get_mas_i(int i) const;

};

template <class K> // конструктор по умолчанию
HTable<K>::HTable()
{
     for (int i = 0; i < def_size; i++)
     {
         elem<K>* curr;
         curr = new elem<K>;
         curr->set_value(0);
         curr->set_key("");
         this->mas[i] = curr;
     }
     size = 0;
};

template <class K> //конструктор копирования
HTable<K>::HTable(const HTable<K>& other)
{
    for (int i = 0; i < def_size; i++)
    {
        elem<K>* curr;
        curr = new elem<K>;
        this->mas[i] = curr;
        this->mas[i] = other.mas[i];
    }
    size = other.size;
}

template  <class K> // Деструктор
HTable<K>::~HTable<K>(){
    for (int i = 0; i< def_size; i++){
        mas[i]->~elem<K>();
        elem<K>* curr;
        curr = new elem<K>;
        curr->set_value(0);
        curr->set_key("");
        this->mas[i] = curr;
    }
}

template <class K> //очистка
void HTable<K>::del_all(){
    size = 0;
    for (int i = 0; i < def_size; i++){
        mas[i]->~elem<K>();
        elem<K>* curr;
        curr = new elem<K>;
        curr->set_value(0);
        curr->set_key("");
        this->mas[i] = curr;
    }
}

template <class K> //оператор ввода
void HTable<K>::operator<<(const K& new_key){
    auto key = hash(new_key);
    if (mas[key]->get_key() != new_key){
        mas[key]->set_key(new_key);
        mas[key]->set_value(1);
        size++;
    }
    else{
        mas[key]->set_value(mas[key]->get_value()+1);
    }
}

template <class K> //оператор сравнения коллекций
bool HTable<K>::operator==(const HTable<K>& other) const {
    bool flag = true;
    for (int i = 0; i < def_size; i++){
        if (other.mas[i]->get_key() != mas[i]->get_key() or other.mas[i]->get_value() != mas[i]->get_value()){
            flag = false;
        }
    }
    return flag;
}

template <class K> // удаления элемента по ключу
void HTable<K>::del_element(const K& string_key){
    bool flag = HTable<K>::check_element(string_key);
    if (flag == true){
        auto key = hash(string_key);
        mas[key]->~elem<K>();
        elem<K> *curr;
        curr = new elem<K>;
        curr->set_value(0);
        curr->set_key("");
        this->mas[key] = curr;
        size--;
    }
    else{
        throw out_of_range("the key does not exist");
    }
}

template <class K> // проверка существования элемента
bool HTable<K>::check_element(const K& string_key) const{
    auto key = hash(string_key);
    if (mas[key]->get_key() != ""){
        return true;
    }
    else{
        return false;
    }
}

template <class K> //оператор плучения значения по ключу
uint16_t HTable<K>::operator[](const K& string_key) const{
    bool flag = HTable<K>::check_element(string_key);
    if (flag == true){
        auto key = hash(string_key);
        return  mas[key]->get_value();
    }
    else{
        throw out_of_range("the key does not exist");
    }
}

template <class K> //получения ключа с максимумом ошибок
K HTable<K>::get_max_mis() const{
    int max = -1;
    int key = 0;
    for (int i = 0; i < def_size; i++){
        if (mas[i]->get_value() > max){
            max = mas[i]->get_value();
            key = i;
        }
    }
    return mas[key]->get_key();
}

template <class K> //получение елюча с минимумом ошибок
K HTable<K>::get_min_mis() const{
    int min = 10000000;
    int key = 0;
    for (int i = 0; i < def_size; i++){
        if (mas[i]->get_value() < min and mas[i]->get_value() != 0){
            min = mas[i]->get_value();
            key = i;
        }
    }
    return mas[key]->get_key();
}

template <class K> //чтения из файла
void HTable<K>::read_from_file(const string& input_file){
    string line;
    size = 0;
    ifstream in(input_file);
    if (in.is_open())
    {
        while (!in.eof())
        {
            in>>line;
            int key = hash(line);
            mas[key]->set_key(line);
            in >> line;
            mas[key]->set_value(stoi(line));
            size++;
        }
    }
}

template <class K> //запись в файл
void HTable<K>::write_to_file(const string& output_file){
    int k = 0;
    ofstream out(output_file);
    if (out.is_open()){
        for (int i = 0; i < def_size; i++){
            if (mas[i]->get_key() != "" and mas[i]->get_value() != 0){
                out << mas[i]->get_key() << endl;
                k++;
                if (k != size){
                out << mas[i]->get_value() << endl;
                }
                else{
                    out << mas[i]->get_value();
                }
            }
        }
    }

}

template <class K>
elem<K> HTable<K>::get_mas_i(int i) const{
    return *mas[i];
}

#endif // HTABLE_H
