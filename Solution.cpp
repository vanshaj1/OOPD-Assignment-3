// ******************************************************** Assignment 3 *****************************************************
                     //********************** Templates, assert and Exception Handling ***************************
#include <iostream>
#include <cassert>
#include <vector>
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
    int noOfNodesInTree = 0;
    Quartenary_Search_Tree(T initial_State[]){
            make(initial_State);
    }
    void make(T initial_State[]){
       for(int i = 0;i< (sizeof(initial_State) / sizeof(initial_State[0]));i++){
          insert(&initial_State[i]);
       }
       cout<<"Tree initialized successfully \n";
    }
    void insert(T *element){
        if(Root == nullptr){
            Root = new Node<T>();
            Root->data = element;
            return;
        }
        Root = insertHelper(Root,element);
        noOfNodesInTree++;
    }
    Node<T>* insertHelper(Node<T> *root,T *element){
        if(root == nullptr){
            Node<T> *newNode = new Node<T>();
            newNode->data = element;
            return newNode;
        }
        T *temp = root->data;
        int rootKey = temp->key;
        int elementKey = element->key; 
        if(elementKey >= 0 && elementKey < (rootKey/2)){
            root->left_Most_Child = insertHelper(root->left_Most_Child,element);
        }else if(elementKey >= (rootKey/2) && elementKey < rootKey){
            root->Second_Child = insertHelper(root->Second_Child,element);
        }else if(elementKey > rootKey && elementKey < (2*rootKey)){
            root->Third_Child = insertHelper(root->Third_Child,element);
        }else if(elementKey >= (2*rootKey)){
            root->right_Most_Child = insertHelper(root->right_Most_Child,element);
        }
        return root;
    }
    Node<T>* findPredecessor(Node<T> *dnode){
        if(dnode == nullptr){
            return nullptr;
        }
        Node<T>* temp = nullptr;
        if(dnode->Second_Child != nullptr){
            temp = dnode->Second_Child;
        }else{
            temp = dnode->left_Most_Child;
        }
        if(temp != nullptr){
            while(temp->right_Most_Child != nullptr ){
                temp = temp->right_Most_Child;
            }
        }
        return temp;
    }
    Node<T>* findSuccessor(Node<T>* dnode){
        if(dnode == nullptr){
            return nullptr;
        }
         Node<T> *temp = nullptr;
        if(dnode->Third_Child != nullptr){
            temp = dnode->Third_Child;  
        }else{
            temp = dnode->right_Most_Child;
        }
        if(temp != nullptr){
            while(temp->left_Most_Child != nullptr ){
                temp = temp->left_Most_Child;
            }
        }
        
        return temp;
    }
    void Delete(int key){
       Node<T> *dnodeParent = nullptr;
        Node<T> *dnode = nullptr;
        int child = 0;
        if(Root->data->key == key){
            dnode = Root;
        }else{
            dnodeParent = find(Root,key);
            if(dnodeParent == nullptr){
                cout<<"Element with this key is not present, please check what do you want to delete \n";
                return;
            }
           
            if(dnodeParent != nullptr && dnodeParent->left_Most_Child != nullptr && dnodeParent->left_Most_Child->data != nullptr  && dnodeParent->left_Most_Child->data->key == key){
                dnode = dnodeParent->left_Most_Child;
            }
            if(dnodeParent != nullptr && dnodeParent->Second_Child != nullptr && dnodeParent->Second_Child->data != nullptr && dnodeParent->Second_Child->data->key == key){
                child = 1;
                dnode = dnodeParent->Second_Child;
            }
            if(dnodeParent != nullptr && dnodeParent->Third_Child != nullptr && dnodeParent->Third_Child->data != nullptr && dnodeParent->Third_Child->data->key == key){
                child = 2;
                dnode = dnodeParent->Third_Child;
            }
            if(dnodeParent != nullptr && dnodeParent->right_Most_Child != nullptr && dnodeParent->right_Most_Child->data != nullptr && dnodeParent->right_Most_Child->data->key == key){
                child = 3;
                dnode = dnodeParent->right_Most_Child;
            }
        }
        
        if(dnode == nullptr){
            return;
        }
        Node<T> *predecessor = findPredecessor(dnode);
        if(predecessor != nullptr){
             T *newData = predecessor->data;
             dnode->data = newData;
             Delete(newData->key);
             deleteHelper(dnode);
        }else{
            Node<T> *successor = findSuccessor(dnode);
            if(successor != nullptr){
                T *newData = successor->data;
                dnode->data = newData;  
                Delete(newData->key);
                deleteHelper(dnode); 
            }else{
                
                if(child == 0){
                    dnodeParent->left_Most_Child = nullptr;
                }else if(child == 1){
                    dnodeParent->Second_Child = nullptr;
                }else if(child == 2){
                    dnodeParent->Third_Child = nullptr;
                }else if(child == 3){
                    dnodeParent->right_Most_Child = nullptr;
                }
            }
        }
    }
    void preorderForDelete(Node<T>* root,vector<T*> &traversal){
        if(root == nullptr){
            return;
        }
        traversal.push_back(root->data);
        preorderForDelete(root->left_Most_Child,&traversal);
        preorderForDelete(root->Second_Child,&traversal);
        preorderForDelete(root->Third_Child,&traversal);
        preorderForDelete(root->right_Most_Child,&traversal);
    }
    void Inorder(Node<T>* root,T* traversal[],int idx){
        if(root == nullptr){
            return;
        }
        Inorder(root->left_Most_Child,traversal,idx);
        Inorder(root->Second_Child,traversal,idx);
        traversal.push_back(root->data);
        Inorder(root->Third_Child,traversal,idx);
        Inorder(root->right_Most_Child,traversal,idx);
    }
    Node<T>* deletetHelper1(Node<T> *root,Node<T> *element){
        if(root == nullptr){
            Node<T> *newNode = new Node<T>();
            newNode = element;
            return newNode;
        }
        T *temp = root->data;
        int rootKey = temp->key;
        int elementKey = element->data->key; 
        if(elementKey >= 0 && elementKey < (rootKey/2)){
            root->left_Most_Child = deletetHelper1(root->left_Most_Child,element);
        }else if(elementKey >= (rootKey/2) && elementKey < rootKey){
            root->Second_Child = deletetHelper1(root->Second_Child,element);
        }else if(elementKey > rootKey && elementKey < (2*rootKey)){
            root->Third_Child = deletetHelper1(root->Third_Child,element);
        }else if(elementKey >= (2*rootKey)){
            root->right_Most_Child = deletetHelper1(root->right_Most_Child,element);
        }
        return root;
    }
    void deleteHelper(Node<T>* dnode){
        if(dnode == nullptr){
            return;
        }
        int rootKey = dnode->data->key;
        if(dnode->left_Most_Child != nullptr){
            if(dnode->left_Most_Child->data->key >= 0 && dnode->left_Most_Child->data->key < (rootKey/2)){
               //nothing
            }else{
                deletetHelper1(dnode,dnode->left_Most_Child);
                dnode->left_Most_Child = nullptr;
            } 
        }
        if(dnode->Second_Child != nullptr){
            if(dnode->Second_Child->data->key >= (rootKey/2) && dnode->Second_Child->data->key < rootKey){
                //nothing
            }else{
                deletetHelper1(dnode,dnode->Second_Child);
                dnode->Second_Child = nullptr;
            } 
        }
        if(dnode->Third_Child != nullptr){
            if(dnode->Third_Child->data->key > rootKey && dnode->Third_Child->data->key < (2*rootKey)){
                //nothing
            }else{
                deletetHelper1(dnode,dnode->Third_Child);
                dnode->Third_Child = nullptr;
            }
        }
        if(dnode->right_Most_Child != nullptr){
            if(dnode->right_Most_Child->data->key >= (2*rootKey)){
                //nothing
            }else{
                deletetHelper1(dnode,dnode->right_Most_Child);
                dnode->right_Most_Child = nullptr;   
            }
        } 


    }
    Node<T>* find(Node<T> *Root,int key){
        if(Root == nullptr){
            return nullptr;
        }
        int dataKey = Root->data->key;

        if(Root->data->key == key){
            return Root;
        }

        if(key >= 0 && key < (dataKey/2)){
            return find(Root->left_Most_Child,key);
        }else if(key >= (dataKey/2) && key < (dataKey)){
            return find(Root->Second_Child,key);
        }else if(key > dataKey && key < (2*dataKey)){
            return find(Root->Third_Child,key);
        }else if(key >= (2*dataKey)){
            return find(Root->right_Most_Child,key);
        }
    }
    void preorder(){
        if(Root == nullptr){
            cout<<"No element in tree is present to show";
        }
        cout<<"preorder of Elements:- \n";
        preorderHelper(Root);
    }
    void preorderHelper(Node<T> *root){
        if(root == nullptr){
            return;
        }
        cout<<root->data->key<<endl;
        preorderHelper(root->left_Most_Child);
        preorderHelper(root->Second_Child);
        preorderHelper(root->Third_Child);
        preorderHelper(root->right_Most_Child);
    }
    void postorder(){
        if(Root == nullptr){
            cout<<"No element in tree is present to show";
        }
        cout<<"postorder of Elements:- \n";
        postorderHelper(Root);
    }
    void postorderHelper(Node<T> *root){
        if(root == nullptr){
            return;
        }
        postorderHelper(root->left_Most_Child);
        postorderHelper(root->Second_Child);
        postorderHelper(root->Third_Child);
        postorderHelper(root->right_Most_Child);
        cout<<root->data->key<<endl;
    }
};

class customClass_1{
    public:
        int key;
        customClass_1(){

        }
        customClass_1(int key){
            this->key = key;
        }
};
class customClass_2{
    public:
        int key;
        customClass_2(){

        }
        customClass_2(int key){
            this->key = key;
        }
};
int main(){
    customClass_1 obj;
    obj.key = 10;
    customClass_1 obj1;
    obj1.key = 20;
    customClass_1 array[2] = {obj,obj1};
    Quartenary_Search_Tree<customClass_1> QSTtree(array);
    char ch;
    cin >> ch;
    switch (ch)
    {
    case 'I':
        QSTtree.insert(obj);
        break;
    case 'D': 
        QSTtree.Delete(10);
    case 'P':
        QSTtree.preorder();
    case 'T':
        QSTtree.postorder();               
    default:
        break;
    }
    return 0;
}

