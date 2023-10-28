// ******************************************************** Assignment 3 *****************************************************
                     //********************** Templates, assert and Exception Handling ***************************
#include <iostream>
using namespace std;

template<typename T>
class Node{
   public:
    Node<T> *left_Most_Child;
    Node<T> *Second_Child;
    Node<T> *Third_Child;
    Node<T> *right_Most_Child;
    T *data;
};

template<typename T>
class Quartenary_Search_Tree{
   public:
    Node<T> *Root;
    Quartenary_Search_Tree(){

    }
    Quartenary_Search_Tree(T &initial_State){
        if(initial_State.length == 0){
            cout<<"input is empty Tree";
        }else{
            make(&initial_State);
        }
    }
    void make(T &initial_State){
       
    }
    void insert(T &element){
        if(Root == nullptr){
            Root = new Node<T>();
            Root->data = element;
            return;
        }
        Root = insertHelper(Root,element);
    }
    T* insertHelper(Node<T> *root,T *element){
        if(root == nullptr){
            Node<T> newNode = new Node<T>();
            newNode->data = element;
            return newNode;
        }
        T temp = root->data;
        int rootKey = temp->key;
        int elementKey = element->key; 
        if(elementKey >= 0 && elementKey < (rootKey/2)){
            root->left_Most_Child = insertHelper(root->left_Most_Child,element);
        }else if(elementKey >= (rootKey/2) && elementKey < rootKey){
            root->Second_Child = insertHelper(root->Second_Child,element);
        }else if(elementKey >= rootKey && elementKey < (2*rootKey)){
            root->Third_Child = insertHelper(root->Third_Child,element);
        }else if(elementKey >= (2*rootKey)){
            root->right_Most_Child = insertHelper(root->right_Most_Child,element);
        }
        return root;
    }
    void Delete(){

    }
    void preorder(T *root){
        if(root == nullptr){
            return;
        }
        cout<<root->data->key;
        preorder(root->left_Most_Child);
        preorder(root->Second_Child);
        preorder(root->Third_Child);
        preorder(root->right_Most_Child);
    }
    void postorder(T *root){
        if(root == nullptr){
            return;
        }
        postorder(root->left_Most_Child);
        postorder(root->Second_Child);
        postorder(root->Third_Child);
        postorder(root->right_Most_Child);
        cout<<root->data->key;
    }
};

class customClass_1{
    public:
        int key;
};
class customClass_2{
    public:
        int key;
};
int main(){
    Quartenary_Search_Tree<customClass_1> QSTtree = Quartenary_Search_Tree<customClass_1>();
    customClass_1 obj = customClass_1();
    obj.key = 10;
    QSTtree.insert(obj);
    return 0;
}

