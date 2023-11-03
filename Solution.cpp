// ****************************************************** Assignment 3 *****************************************************
                    //********************** Templates, assert and Exception Handling ***************************
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//*****************************************************Custom Exception******************************************************************
class NodeNotFound :public exception{
    public:
        string message(){
            string res = "Node is not found in the Quantenary Search tree";
            return res;
        }
};



//************************************Data structure Quanternary Search tree using templates***********************************************

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
        dnodeParent = findParent(Root,key);
        dnode = find(Root,key);

        try{
            if(dnode == nullptr){
                throw NodeNotFound();
            }
        }catch(NodeNotFound e){
            cout<<e.message()<<endl;
            exit(1);
        }
        
        if(dnode->left_Most_Child == nullptr && dnode->Second_Child == nullptr && dnode->Third_Child == nullptr && dnode->right_Most_Child == nullptr){
            if(dnodeParent == nullptr){
                Root = nullptr;
                // cout<<"Here at root == null\n";
                return;
            }else{
                 if(dnodeParent->left_Most_Child != nullptr && dnodeParent->left_Most_Child->data->key == key){
                    dnodeParent->left_Most_Child = nullptr;
                }else if(dnodeParent->Second_Child != nullptr && dnodeParent->Second_Child->data->key == key){
                    dnodeParent->Second_Child = nullptr;
                }else if(dnodeParent->Third_Child != nullptr && dnodeParent->Third_Child->data->key == key){
                    dnodeParent->Third_Child = nullptr;
                }else if(dnodeParent->right_Most_Child != nullptr && dnodeParent->right_Most_Child->data->key == key){
                    dnodeParent->right_Most_Child = nullptr;
                }
                // cout<<"Leave else\n";
            }
            return;
        }

        Node<T> *predecessor = findPredecessor(dnode);
        if(predecessor != nullptr){
             T *newData = predecessor->data;
             int tempKey = newData->key;
             dnode->data->key = -1;
             Delete(newData->key);
             dnode->data = newData;
             dnode->data->key = tempKey;
             deleteHelper(dnode);
            //  cout<<"predecessor\n";
        }else{
            Node<T> *successor = findSuccessor(dnode);
            if(successor != nullptr){
                T *newData = successor->data;
                int tempKey = newData->key;
                dnode->data->key = -1;
                Delete(newData->key);
                dnode->data = newData;
                dnode->data->key = tempKey;  
                deleteHelper(dnode);
                // cout<<"Successor\n"; 
            }
        }
    }
    Node<T>* deletetHelper1(Node<T> *root,Node<T> *element){
        // cout<<"At deleteHelper1\n";
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
        // cout<<"Delete Helper\n";
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
    Node<T>* findParent(Node<T> *Root,int key){
        if(Root == nullptr){
            return nullptr;
        }
        int dataKey = Root->data->key;
        if(Root->left_Most_Child != nullptr && Root->left_Most_Child->data->key == key){
            return Root;
        }else if(Root->Second_Child != nullptr && Root->Second_Child->data->key == key){
            return Root;
        }else if(Root->Third_Child != nullptr && Root->Third_Child->data->key == key){
            return Root;
        }else if(Root->right_Most_Child != nullptr && Root->right_Most_Child->data->key == key){
            return Root;
        }
        if(key >= 0 && key < (dataKey/2)){
            return findParent(Root->left_Most_Child,key);
        }else if(key >= (dataKey/2) && key < (dataKey)){
            return findParent(Root->Second_Child,key);
        }else if(key > dataKey && key < (2*dataKey)){
            return findParent(Root->Third_Child,key);
        }else if(key >= (2*dataKey)){
            return findParent(Root->right_Most_Child,key);
        }
        return nullptr;
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




//***********************************************Two custom Classes (NON PRIMITIVE DATA TYPES)*******************************
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




//*************************************************Driver Code with Menu driven Acess to Data structure***************************************
int main(){
    cout<<"Please select one custom class (NON PRIMITIVE TYPE) from below:- \n";
    cout<<"1 - custom class 1\n";
    cout<<"2 - custom class 2\n";
    int choice = 1;
    cin>>choice;
    if(choice == 1){
        customClass_1 obj;
        obj.key = 10;
        customClass_1 obj1;
        obj1.key = 20;
        customClass_1 array[2] = {obj1,obj};
        Quartenary_Search_Tree<customClass_1> QSTtree(array);
        // customClass_1 obj2;
        // obj2.key = 0;
        // QSTtree.insert(&obj2);
        // customClass_1 obj3;
        // obj3.key = 30;
        // QSTtree.insert(&obj3);
        // customClass_1 obj4;
        // obj4.key = 40;
        // QSTtree.insert(&obj4);

        while(true){
            cout<<"Select an option to perform:-\n";
            cout<<"0 - Insertion\n";
            cout<<"1 - Deletion\n";
            cout<<"2 - Preorder\n";
            cout<<"3 - Postorder\n";
            cout<<"4 - Exit\n";
            int option = 4;
            cin>>option;
            switch(option){
                case 0: {
                        cout<<"Enter the key to insert: ";
                        int key;
                        cin>>key;
                        assert((key >= 0));
                        customClass_1 *obj = new customClass_1(key);

                        try{ 
                            QSTtree.insert(obj);
                        }catch(exception e){
                            cout<<"Exception occured while inserting elements, when ths key is:- "<<key<<endl;
                            cout<<e.what();
                            return 0;
                        }

                        cout<<"Now After Insertion the tree is :- \n";
                        QSTtree.preorder();
                        break;
                    }
                case 1:{
                        cout<<"Enter the key to delete from Tree: ";
                        int key;
                        cin>>key;
                        assert((key >= 0));

                        try{
                            QSTtree.Delete(key);
                        }catch(exception e){
                            cout<<"Exception occured while Deleting elements, when ths key is:- "<<key<<endl;
                            cout<<e.what();
                            return 0;
                        }
                        
                        cout<<"Now After Deletion the tree is :- \n";
                        QSTtree.preorder();
                        break;
                        }
                case 2:{
                        QSTtree.preorder();
                        break;
                        }
                case 3:{
                        QSTtree.postorder();
                        break;
                        }
                case 4: {
                        exit(0);
                        }
                    
            }
        }
    }else if(choice == 2){
        customClass_2 obj;
        obj.key = 10;
        customClass_2 obj1;
        obj1.key = 20;
        customClass_2 array[2] = {obj1,obj};
        Quartenary_Search_Tree<customClass_2> QSTtree(array);
        // customClass_1 obj2;
        // obj2.key = 0;
        // QSTtree.insert(&obj2);
        // customClass_1 obj3;
        // obj3.key = 30;
        // QSTtree.insert(&obj3);
        // customClass_1 obj4;
        // obj4.key = 40;
        // QSTtree.insert(&obj4);

        while(true){
            cout<<"Select an option to perform:-\n";
            cout<<"0 - Insertion\n";
            cout<<"1 - Deletion\n";
            cout<<"2 - Preorder\n";
            cout<<"3 - Postorder\n";
            cout<<"4 - Exit\n";
            int option = 4;
            cin>>option;
            switch(option){
                case 0: {
                        cout<<"Enter the key to insert: ";
                        int key;
                        cin>>key;
                        assert((key >= 0));
                        customClass_2 *obj = new customClass_2(key);

                        try{
                            QSTtree.insert(obj);
                        }catch(exception e){
                            cout<<"Exception occured while inserting elements, when ths key is:- "<<key<<endl;
                            cout<<e.what();
                            return 0;
                        }

                        cout<<"Now After Insertion the tree is :- \n";
                        QSTtree.preorder();
                        break;
                    }
                case 1:{
                        cout<<"Enter the key to delete from Tree: ";
                        int key;
                        cin>>key;
                        assert((key >= 0));

                        try{
                            QSTtree.Delete(key);
                        }catch(exception e){
                            cout<<"Exception occured while Deleting elements, when ths key is:- "<<key<<endl;
                            cout<<e.what();
                            return 0;
                        }
                        
                        cout<<"Now After Deletion the tree is :- \n";
                        QSTtree.preorder();
                        break;
                        }
                case 2:{
                        QSTtree.preorder();
                        break;
                        }
                case 3:{
                        QSTtree.postorder();
                        break;
                        }
                case 4: {
                        exit(0);
                        }
                    
            }
        }
    }
        
    return 0;
}

