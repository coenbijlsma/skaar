#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define ALIST_INIT_SIZE 10

class arraylist{
private:
    // vars
    int _size;
    void** _array;
    
    // methods
    int deep_copy(void** from, void** to);
    int deep_copy_except(void** from, void** to, int except);
    
public:
    arraylist();
    arraylist(void** data);
    ~arraylist();
    
    int add(void *elem);
    int add(int pos, void *elem);
    void clear();
    arraylist* clone();
    int contains(void* elem);
    void* get(int pos);
    int remove(int pos);
    int remove(void* elem);
    int size();
    void** to_array();
    
};

#endif
