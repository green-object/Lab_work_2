#ifndef ELEM_H
#define ELEM_H
#include "string"

using namespace std;

template <class K>
class elem
{
public:
    elem();
    K get_key() const {return key;}
    ~elem() = default;
    uint16_t get_value() const {return value;}
    void set_key(const K& new_key);
    void set_value(const uint16_t& value);
private:
    K key;
    uint16_t value;
};
template <class K>
elem<K>::elem(){
    key = "";
    value = 0;
}

template <class K>
void elem<K>::set_key(const K& new_key){
    key = new_key;
}

template <class K>
void elem<K>::set_value(const uint16_t& new_value){
    value = new_value;
}
#endif // ELEM_H
