#include <iostream>
#include <stdexcept>
#include"FamilyTree.hpp"
using namespace std;




namespace family {
/*

    treenode *Tree::creatNode(string name) {
        treenode *n = new treenode;
        n->name = name;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
*/

    treenode::treenode(std::string root)
    {
        name = root;
        right = NULL;
        left = NULL;
        rank ="";

    }
    treenode::~treenode()
    {
        delete right;
        delete left;
    }

    Tree::Tree(string Name) {
        root = new treenode(Name);
        root->rank = "me";
        counter = 1;
    }

    Tree::~Tree() {
        delete root;
    }

    bool Tree::equal(string a, string b) {
        if (a.length() != b.length())
            return false;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i])
                return false;

        }
        return true;
    }


    int Tree::HighRecursive(string name, treenode *node, int level) {
        if (node == NULL)
            return 0;
        if (equal(node->name, name))
            return level;

        int downlevel = HighRecursive(name, node->left, level + 1);

        if (downlevel != 0)
            return downlevel;

        downlevel = HighRecursive(name, node->right, level + 1);

        return downlevel;
    }

    void Tree::addFatherRecursive(string child, string father, treenode *node) {

        if (node == NULL)
            return;
        if (node != NULL) {
            if (node->name != "" && equal(node->name, child)) {
                counter++;
                if (node->left == NULL) {
                    node->left = new treenode(father);
                    int level = 0;
                    int num = HighRecursive(father, root, level);
                    if (num == 1)
                        node->left->rank = "father";
                    if (num == 2)
                        node->left->rank = "grandfather";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            node->left->rank = node->left->rank + "great-";
                        }
                        node->left->rank = node->left->rank + "grandfather";
                    }
                }else throw invalid_argument("wrong");
            }
        }

        addFatherRecursive(child, father, node->left);
        addFatherRecursive(child, father, node->right);

    }


    void Tree::addMotherRecursive(string child, string mother, treenode *node) {

        if (node == NULL)
            return;
        if (node != NULL) {
            if (node->name != "" && equal(node->name, child)) {
                counter++;
                if (node->right == NULL) {
                    node->right =  new treenode(mother);
                    int level = 0;
                    int num = HighRecursive(mother, root, level);

                    if (num == 1)
                        node->right->rank = "mother";
                    if (num == 2)
                        node->right->rank = "grandmother";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            node->right->rank = node->right->rank + "great-";
                        }
                        node->right->rank = node->right->rank + "grandmother";
                    }

                }else throw invalid_argument("wrong");
            }
        }
        addMotherRecursive(child, mother, node->left);
        addMotherRecursive(child, mother, node->right);

    }


    treenode *Tree::findNodeName(string name, treenode *node) {
        if (node == NULL)
            return NULL;
        if (node != NULL && equal(node->name, name))
            return node;

        treenode *found = findNodeName(name, node->left);

        if (found != NULL)
            return found;

        return findNodeName(name, node->right);
    }


    treenode *Tree::findNodeRank(string name, treenode *node) {
        if (node == NULL)
            return NULL;

        if (equal(node->rank, name))
            return node;

        treenode *found = findNodeRank(name, node->left);

        if (found != NULL)
            return found;

        return findNodeRank(name, node->right);
    }




    void Tree::display() //help from geeksforgeeks
    {
        cout << "notice! the mothers is up and fathers is down!" << endl;
        // Root without spaces
        print(root, 0);
    }
    void Tree::print(treenode* root, int space) //Print (right,root,left)--> (mather,child,father)
    {
        if (root == NULL) // Nothing to print
            return;

        //  For know how much space to take (We want it be clear for show)
        space =space+ counter;

        // mother first
        print(root->right, space);


        cout<<endl;
        for (int i = counter; i < space; i++)
            cout<<" ";
        cout<<root->name<<"\n\n";

        // father
        print(root->left, space);
    }
    bool Tree:: cheakIfFatherExist(string child,treenode* node)
    {

        if (node == NULL)
            return false;

        if (equal(node->name,child))
        {
            if(node->left==NULL)
                return true;
        }



        bool ans1 = cheakIfFatherExist(child, node->left);

        if(ans1)
            return true;


        bool ans2 = cheakIfFatherExist(child, node->right);

        return ans2;
    }

    bool Tree:: cheakIfMotherExist(string child,treenode* node)
    {

        if (node == NULL)
            return false;

        if (equal(node->name,child))
        {
            if(node->right==NULL)
                return true;
        }



        bool ans1 = cheakIfMotherExist(child, node->left);

        if(ans1)
            return true;


        bool ans2 = cheakIfMotherExist(child, node->right);

        return ans2;
    }
    Tree &Tree::addFather(string child, string father) {

        if(cheakIfFatherExist(child,root))
            addFatherRecursive(child, father, root);
                else
        throw std::runtime_error("we have a father for this child");

        return *this;

    }


    Tree &Tree::addMother(string child, string mother) {

            if(cheakIfMotherExist(child,root))
        addMotherRecursive(child, mother, root);
            else
                throw std::runtime_error("we have a mother for this child");
        return *this;
    }

    string Tree::relation(string name) {

        string s = "unrelated";
        if (equal(root->name, name))
            return root->rank;

        treenode *node = findNodeName(name, root);
        if (node != NULL && equal(node->name, name))
            return node->rank;
        else
            return s;
    }


    void Tree::remove(string name) {
        if (root->name==name) throw invalid_argument("cant remove");
        treenode *node = findNodeName2(name, root);
if(node==NULL) throw invalid_argument("cant remove");

        if (node->left!=NULL&&node->left->name==name)
        {
            delete node->left;
            node->left = NULL;
            counter--;
        }
        if (node->right!=NULL&&node->right->name==name)
        {
            delete node->right;
            node->right = NULL;
            counter--;

        }
    }
    treenode *Tree::findNodeName2(string name, treenode *node) {
        if (node == NULL)
            return NULL;
        if ((node->left!= NULL && equal(node->left->name, name))||(node->right!= NULL && equal(node->right->name, name)))
            return node;

        treenode *found = findNodeName2(name, node->left);

        if (found != NULL)
            return found;

        return findNodeName2(name, node->right);
    }





    string Tree::find(string name) {
        treenode *node = findNodeRank(name, root);
        if (node==NULL) throw invalid_argument("no relation");
        return node->name;

    }

   /* void Tree::printpostorderprivate(treenode *ptr) {
        if (ptr != NULL) {
            if (ptr->left != NULL) {
                printpostorderprivate(ptr->left);
            }
            cout << ptr->name << " ";

            if (ptr->right != NULL) {
                printpostorderprivate(ptr->right);
            }

        } else
            cout << "emty" << " ";
    }
*/
   /* void Tree::printPostorder() {

        printpostorderprivate(root);

    }*/
};
