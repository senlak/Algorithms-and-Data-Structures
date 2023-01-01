#include "node.hpp"

template <typename Key, typename Info>
class Sequence
{
public:
    //default constructor
    Sequence();

    //copy constructor
    Sequence(const Sequence<Key, Info> &src);

    //destructor
    ~Sequence();

    //assignment operator
    Sequence<Key, Info> &operator=(const Sequence<Key, Info> &src);

    //comparion operator
    bool operator==(const Sequence<Key, Info> &src) const;

    //capacity
    bool empty() const;        //returns true if the Sequence is empty, else return false
    unsigned int size() const; //returns the size of Sequence

    //modifiers
    void push_front(const Key &key, const Info &info);                                                                           //adds element to the front of the Sequence
    bool pop_front();                                                                                                            //removes element from the front of the Sequence and returns true; if Sequence is empty returns false
    void push_back(const Key &key, const Info &info);                                                                            //adds element to the back of the Sequence
    bool pop_back();                                                                                                             //removes element from the back of the Sequence and returns true; if Sequence is empty returns false
    bool insert_at_pos(const Key &key, const Info &info, const Key &pos, const unsigned int occur = 1, const bool after = true); //inserts element at the given position of the Sequence and returns true; returns false if position not found
    bool insert_at_index(const Key &key, const Info &info, const unsigned int index);                                            //inserts element at the given index of the Sequence and returns true; returns false if index not found
    bool modify_at_pos(const Info &info, const Key &pos, const unsigned int occur = 1);                                          //modifies the info of the element in the given position of the Sequence and returns true; returns false if position not found
    bool modify_at_index(const Info &info, const unsigned int index);                                                            //modifies the info of the element in the given index of the Sequence and returns true; returns false if index not found
    bool erase_at_pos(const Key &pos, const unsigned int occur = 1);                                                             //removes the element in the given position of the Sequence and returns true; returns false if position not found
    bool erase_at_index(const unsigned int index);                                                                               //removes the element in the given index of the Sequence and returns true; returns false if index not found
    void swap(Sequence<Key, Info> &src);                                                                                         //swaps the elements of the given source and the object
    void clear();                                                                                                                //erases all the elements of the list

    //operations
    int get_index(const Key &pos, const unsigned int occur = 1) const;  //returns the index of the element at the given position; returns -1 if position not found
    const Info get(const Key &pos, const unsigned int occur = 1) const; //returns the info of the element at the given position; throws and error if position not found
    const Key key_at(const unsigned int index) const;                   //returns the key of the element at the given index; throws and error if index out of range
    const Info info_at(const unsigned int index) const;                 //returns the info of the element at the given index; throws and error if index out of range
    unsigned int count(const Key &key) const;                           //returns the number of elements with the given key
    void print() const;                                                 //prints all the elements of the Sequence

private:
    Node<Key, Info> *head;                                     //head node
    Node<Key, Info> *get_node(const unsigned int index) const; //returns the node at the given index; returns nullptr if index is out of range
};

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence()
{
    this->head = nullptr;
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &src)
{
    this->head = nullptr;
    *this = src;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    this->clear();
}

template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &src)
{
    if (*this == src)
    {
        return *this;
    }
    this->clear();
    if (src.head)
    {
        this->head = new Node<Key, Info>(*src.head);
        Node<Key, Info> *node = this->head;
        Node<Key, Info> *src_node = src.head->get_next();
        while (src_node)
        {
            Node<Key, Info> *n = new Node<Key, Info>(*src_node);
            node->set_next(n);
            node = node->get_next();
            src_node = src_node->get_next();
        }
    }
    return *this;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info> &src) const
{
    unsigned int size = src.size();
    if (size != this->size())
    {
        return false;
    }

    Node<Key, Info> *node = head;
    Node<Key, Info> *src_node = src.head;
    for (unsigned int i = 0; i < size; i++)
    {
        if (!(*node == *src_node))
        {
            return false;
        }
        node = node->get_next();
        src_node = src_node->get_next();
    }
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::empty() const
{
    if (this->head)
    {
        return false;
    }
    return true;
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const
{
    Node<Key, Info> *node = head;
    unsigned int size = 0;
    while (node)
    {
        size++;
        node = node->get_next();
    }
    return size;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key &key, const Info &info)
{
    this->head = new Node<Key, Info>(key, info, this->head);
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_front()
{
    if (head)
    {
        Node<Key, Info> *node = this->head->get_next();
        delete head;
        head = node;
        return true;
    }
    return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_back(const Key &key, const Info &info)
{
    if (this->head)
    {
        Node<Key, Info> *node = get_node(size() - 1);
        if (node)
        {
            node->set_next(new Node<Key, Info>(key, info));
        }
        return;
    }
    this->head = new Node<Key, Info>(key, info);
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_back()
{
    unsigned int size = this->size();
    if (size == 1)
    {
        delete this->head;
        this->head = nullptr;
        return true;
    }
    Node<Key, Info> *node = get_node(size - 2);
    if (node)
    {
        delete node->get_next();
        node->set_next(nullptr);
        return true;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::insert_at_pos(const Key &key, const Info &info, const Key &pos, const unsigned int occur, const bool after)
{
    int index = this->get_index(pos, occur);
    if (index < 0)
    {
        return false;
    }
    if ((index == 0) and !after)
    {
        this->push_front(key, info);
        return true;
    }
    if (!after)
    {
        index--;
    }
    Node<Key, Info> *node = get_node(index);
    node->set_next(new Node<Key, Info>(key, info, node->get_next()));
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::insert_at_index(const Key &key, const Info &info, const unsigned int index)
{
    if (index == 0)
    {
        this->push_front(key, info);
        return true;
    }
    Node<Key, Info> *node = get_node(index - 1);

    if (node)
    {
        node->set_next(new Node<Key, Info>(key, info, node->get_next()));
        return true;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::modify_at_pos(const Info &info, const Key &pos, const unsigned int occur)
{
    int index = this->get_index(pos, occur);
    if (index < 0)
    {
        return false;
    }
    Node<Key, Info> *node = get_node(index);
    node->set_info(info);
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::modify_at_index(const Info &info, const unsigned int index)
{
    Node<Key, Info> *node = get_node(index);
    if (node)
    {
        node->set_info(info);
        return true;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::erase_at_pos(const Key &pos, const unsigned int occur)
{
    int index = this->get_index(pos, occur);
    if (index < 0)
    {
        return false;
    }
    if (index == 0)
    {
        this->pop_front();
        return true;
    }

    Node<Key, Info> *prev = get_node(index - 1);
    Node<Key, Info> *node = prev->get_next();
    prev->set_next(node->get_next());
    delete node;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::erase_at_index(const unsigned int index)
{
    if (index >= this->size())
    {
        return false;
    }

    if (index == 0)
    {
        this->pop_front();
        return true;
    }

    Node<Key, Info> *prev = get_node(index - 1);
    Node<Key, Info> *node = prev->get_next();
    prev->set_next(node->get_next());
    delete node;
    return true;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::swap(Sequence<Key, Info> &src)
{
    Node<Key, Info> *tmp = src.head;
    src.head = this->head;
    this->head = tmp;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::clear()
{
    Node<Key, Info> *node = this->head;
    Node<Key, Info> *next = nullptr;
    while (node)
    {
        next = node->get_next();
        delete node;
        node = next;
    }
    this->head = nullptr;
}

template <typename Key, typename Info>
int Sequence<Key, Info>::get_index(const Key &pos, const unsigned int occur) const
{
    int occ = 1;
    int index = 0;
    Node<Key, Info> *node = this->head;
    while (node)
    {
        if ((node->get_key() == pos) and (occ = occur))
        {
            return index;
        }
        occ++;
        index++;
        node = node->get_next();
    }
    return -1;
}

template <typename Key, typename Info>
const Info Sequence<Key, Info>::get(const Key &pos, const unsigned int occur) const
{
    int index = this->get_index(pos, occur);
    if (index < 0)
    {
        throw std::out_of_range("Index out of range");
    }
    Node<Key, Info> *node = this->get_node(index);
    return node->get_info();
}

template <typename Key, typename Info>
const Key Sequence<Key, Info>::key_at(const unsigned int index) const
{
    Node<Key, Info> *node = this->get_node(index);
    if (node)
    {
        return node->get_key();
    }
    throw std::out_of_range("Index out of range");
}

template <typename Key, typename Info>
const Info Sequence<Key, Info>::info_at(const unsigned int index) const
{
    Node<Key, Info> *node = this->get_node(index);
    if (node)
    {
        return node->get_info();
    }
    throw std::out_of_range("Index out of range");
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::count(const Key &key) const
{
    unsigned int occ = 0;
    Node<Key, Info> *node = this->head;
    while (node)
    {
        if (node->get_key() == key)
        {
            occ++;
        }
        node = node->get_next();
    }
    return occ;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::print() const
{
    Node<Key, Info> *node = this->head;
    while (node)
    {
        node->print();
        node = node->get_next();
    }
}

template <typename Key, typename Info>
Node<Key, Info> *Sequence<Key, Info>::get_node(const unsigned int index) const
{
    unsigned int i = 0;
    Node<Key, Info> *node = this->head;
    while (node)
    {
        if (i == index)
        {
            return node;
        }
        i++;
        node = node->get_next();
    }
    return nullptr;
}
