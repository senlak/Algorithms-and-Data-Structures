#include <iostream>

template <typename Key, typename Info>
class Node
{
public:
    Node(const Key &key, const Info &info, Node<Key, Info> *next = nullptr); //default constructor
    Node(const Node<Key, Info> &src);                                        //copy constructor
    bool operator==(const Node<Key, Info> &src) const;                       //comparion operator
    const Key &get_key() const;                                              //returns the key of the node
    const Info &get_info() const;                                            //returns the info of the node
    Node<Key, Info> *get_next() const;                                       //return the pointer to next node
    void set_key(const Key &key);                                            //sets the key of the node to the given key
    void set_info(const Info &info);                                         //sets the info of the node to the given info
    void set_next(Node<Key, Info> *next);                                    //sets the pointer to next node to the given pointer to a node
    void print();                                                            //displays the key and info of the node

private:
    Key key;               //key of the node
    Info info;             //info of the node
    Node<Key, Info> *next; //pointer to next node
};

template <typename Key, typename Info>
Node<Key, Info>::Node(const Key &key, const Info &info, Node<Key, Info> *next)
{
    this->key = key;
    this->info = info;
    this->next = next;
}

template <typename Key, typename Info>
Node<Key, Info>::Node(const Node<Key, Info> &src)
{
    this->key = src.key;
    this->info = src.info;
    this->next = nullptr;
}

template <typename Key, typename Info>
bool Node<Key, Info>::operator==(const Node<Key, Info> &src) const
{
    if ((this->key == src.get_key()) and (this->info == src.get_info()))
    {
        return true;
    }
    return false;
}

template <typename Key, typename Info>
const Key &Node<Key, Info>::get_key() const
{
    return this->key;
}

template <typename Key, typename Info>
const Info &Node<Key, Info>::get_info() const
{
    return this->info;
}

template <typename Key, typename Info>
Node<Key, Info> *Node<Key, Info>::get_next() const
{
    return this->next;
}

template <typename Key, typename Info>
void Node<Key, Info>::set_key(const Key &key)
{
    this->key = key;
}

template <typename Key, typename Info>
void Node<Key, Info>::set_info(const Info &info)
{
    this->info = info;
}

template <typename Key, typename Info>
void Node<Key, Info>::set_next(Node<Key, Info> *next)
{
    this->next = next;
}

template <typename Key, typename Info>
void Node<Key, Info>::print()
{
    std::cout << this->key << ": " << this->info << "\n";
}
