#include <iostream>
#include <stdexcept>
using namespace std;


namespace family {

    class treenode {
    public:
        string name;
        string rank;
        treenode *left;
        treenode *right;

        //constractor+destractor

        treenode (std::string root);
        ~treenode();

    };
    class Tree {

    public:

        int counter;
        treenode *root;
        bool equal(string a, string b);

        void addFatherRecursive(string child, string father, treenode *node);

        void addMotherRecursive(string child, string mother, treenode *node);

  //      void printpostorderprivate(treenode *node);

        treenode *findNodeName(string name, treenode *node);

        treenode *findNodeRank(string name, treenode *node);

    public:
        Tree(string name);
       void display();
        void print(treenode* root, int level);
        ~Tree();

        int HighRecursive(string name, treenode *node, int level);

        Tree &addFather(string child, string father);

        Tree &addMother(string child, string mother);

        bool cheakIfMotherExist(string child,treenode* node);

        bool cheakIfFatherExist(string child,treenode* node);
  //      void printPostorder();
        string relation(string name);
        treenode *findNodeName2(string name, treenode *node) ;

        void remove(string name);

        string find(string name);

    };
};