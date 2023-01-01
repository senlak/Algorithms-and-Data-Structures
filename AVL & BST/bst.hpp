#include <iostream>

template <typename Key, typename Info>
class BinarySearchTree
{
     struct Node
     { // node structure
          Key key;
          Info info;
          Node *left, *right; // left and right nodes
          Node(const Key &key, const Info &info) : key(key), info(info), left(nullptr), right(nullptr){};
     } * root; // root node

     void copy(Node *node)
     {
          if (node)
          {
               insert(node->key, node->info);
               copy(node->left);
               copy(node->right);
          }
     }

     void clear(Node *node)
     {
          if (node)
          {
               clear(node->left);
               clear(node->right);
               delete node;
          }
     }

     Node *find(Node *node, const Key &key) const
     {
          if (node)
          {
               if (node->key == key)
                    return node;
               Node *l = find(node->left, key), *r = find(node->right, key);
               return l ? l : r;
          }
          return node;
     }

     Node *insert(Node *node, const Key &key, const Info &info)
     {
          // return a new node if the tree is empty
          if (node == nullptr)
               return new Node(key, info);

          // traverse to the right place and insert the node
          if (key < node->key)
               node->left = insert(node->left, key, info);
          else
               node->right = insert(node->right, key, info);

          return node;
     }

     Node *remove(Node *node, const Key &key)
     {
          if (node)
          {

               if (key < node->key)
                    node->left = remove(node->left, key);
               else if (key > node->key)
                    node->right = remove(node->right, key);
               else
               {
                    if (node->left == nullptr)
                    {
                         Node *temp = node->right;
                         delete node;
                         return temp;
                    }
                    else if (node->right == nullptr)
                    {
                         Node *temp = node->left;
                         delete node;
                         return temp;
                    }

                    Node *current = node->right;
                    while (current and current->left)
                         current = current->left;

                    node->key = current->key;
                    node->right = remove(node->right, current->key);
               }
          }
          return node;
     }

     int count(Node *node) const
     {
          if (node)
               return 1 + count(node->left) + count(node->right);
          return 0;
     }

     int height(Node *node) const
     {
          if (node)
          {
               // compute the height of each subtree
               int ld = height(node->left);
               int rd = height(node->right);

               // return the larger one
               return std::max(ld, rd) + 1;
          }
          return -1;
     }

     // print tree by inorder traversal
     void print_inorder(Node *node) const
     {
          if (node)
          {
               // traverse left node
               print_inorder(node->left);

               // print current node data
               std::cout << "(" << node->key << ", " << node->info
                         << ")"
                         << ",  ";

               // traverse right node
               print_inorder(node->right);
          }
     }

     // print the tree in graphical format
     void print_graph(Node *root, std::string indent, const bool &last) const
     {
          if (root)
          {
               std::cout << indent;
               if (last)
               {
                    std::cout << "R----";
                    indent += "   ";
               }
               else
               {
                    std::cout << "L----";
                    indent += "|  ";
               }
               std::cout << root->key << "\n";
               print_graph(root->left, indent, false);
               print_graph(root->right, indent, true);
          }
     }

public:
     BinarySearchTree() : root(nullptr){};

     BinarySearchTree(const BinarySearchTree &src)
     {
          root = nullptr;
          if (this != &src)
               copy(src.root);
     }

     BinarySearchTree(BinarySearchTree &&src) : root(src.root) { src.root = nullptr; };

     BinarySearchTree &operator=(const BinarySearchTree &src)
     {
          *this = src;
     }

     ~BinarySearchTree()
     {
          clear();
     }

     bool empty() const
     {
          return root == nullptr;
     }

     bool exists(const Key &key) const
     {
          if (find(root, key))
               return true;
          return false;
     }

     bool insert(const Key &key, const Info &info)
     {
          if (!exists(key))
          {
               root = insert(root, key, info);
               return true;
          }
          return false;
     }

     bool remove(const Key &key)
     {
          if (exists(key))
          {
               root = remove(root, key);
               return true;
          }
          return false;
     }

     Info &find(const Key &key) const
     {
          Node *node = find(root, key);
          if (node)
               return node->info;
          throw "Element with given key does not exist!";
     }

     Info &operator[](const Key &key)
     {
          Node *node = find(root, key);
          if (node)
               return node->info;
          throw "Element with given key does not exist!";
     }

     int count() const
     {
          return count(root);
     }

     int height() const
     {
          return height(root);
     }

     void clear()
     {
          clear(root);
          root = nullptr;
     }

     void print_inorder() const
     {
          print_inorder(root);
     }

     void print_graph() const
     {
          print_graph(root, "", true);
     }
};
