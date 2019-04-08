#include <iostream>
using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
};

class Tree{
public:
  Node *root;
  Tree(){ //constructor
    root = NULL;
  }
  void deleteTree(Node *node)
  {
      if (node == NULL){
        return;
      }

      //First recur on left suntree
      deleteTree(node->left);

      //Then recur on right subtree
      deleteTree(node->right);

      //Now deal with the node
      delete node;
  }
  ~Tree(){//destructor
    deleteTree(root);
  }

  Node* GetNewNode(int key){
    Node* newNode = new Node();
    newNode->key = key; //set data
    newNode->left = newNode->right = NULL;
    return newNode;
  }

  //To insert data in BST, returns address of root node
  Node* Insert(Node* node, int key){ //hmmm looks like preorder
    if(node == NULL){//empty tree
      return GetNewNode(key);
    }
    //If data to be inserted is lesser, insert in left subtree.
    else if(key < node->key){
      node->left = Insert(node->left, key);
    }
    //Else, insert in right subtree.
    else{
      node->right = Insert(node->right, key);
    }
    return node;
  }
  void insert(int key){
    cout<<"Key: "<<key<<endl;
    root = Insert(root, key);
    cout<<key<<" has been added"<<endl;
  }

  void printInorder(Node* node){
    if(node==NULL){
      return;
    }

    //First recur on left child
    printInorder(node->left);

    //Then print the data of the node
    cout<<node->key<<" ";

    //now recur on right child
    printInorder(node->right);
  }

  void printPreorder(Node* node){
    if(node==NULL){
      return;
    }

    //Then print the data of the node
    cout<<node->key<<" ";

    //First recur on left child
    printPreorder(node->left);

    //now recur on right child
    printPreorder(node->right);
  }
  void printPostorder(Node* node){
    if(node==NULL){
      return;
    }

    //First recur on left child
    printPostorder(node->left);

    //now recur on right child
    printPostorder(node->right);

    //Then print the data of the node
    cout<<node->key<<" ";
  }
  int sumNodes(Node *node){
  if(node == NULL){
    return 0;
  }
  else{
    return node->key + sumNodes(node->left) + sumNodes(node->right);
  }
  }
  int productNodes(Node *node){
  if(node == NULL){
    return 1;
  }
  else{
    return node->key * productNodes(node->left) * productNodes(node->right);
  }
  }

  Node *sumEven(Node *node, int &s){
    if(node==NULL){
      return 0;
    }

    //First recur on left child
    sumEven(node->left, s);

    //now recur on right child
    sumEven(node->right, s);

    //Then add value to running total
    if((node->key % 2) == 0){
      s = s + node->key;
    }

  }
  Node* Search(Node *node, int data){
    if(node == NULL){
      return NULL;
    }
    else if(node->key == data) {
      return node;
    }
    else if(data <= node->key) {
      return Search(node->left, data);
    }
    else {
      return Search(node->right, data);
    }
  }

  //min and max values
  Node* MaxValueNode(Node* currNode){
      if(currNode->right == NULL){
          return currNode;
      }
      return MaxValueNode(currNode->right);
  }

  Node* MinValueNode(Node* currNode){

      if(currNode->left == NULL){
        return currNode;
      }
      return MinValueNode(currNode->left);
  }
  //delete a node
  Node *deleteNode(Node *node, int c){
    //Base case
    if(node == NULL)
      return node;

    //Recursive calls for ancestors of
    //Node to be deleted -- traverse until found
    if(c < node->key){
      node->left = deleteNode(node->left, c);
      return node;
    }
    else if(c > node->key){
      node->right = deleteNode(node->right, c);
      return node;
    }

    //We reach here when root is the Node
    //to be deleted.

    //If one of the children is empty
    if (node->left == NULL){
      Node* temp = node->right;
      delete node;
      return temp;
    }
    else if(node->right == NULL) {
      Node* temp = node->left;
      delete node;
      return temp;
    }

    //If both children exist
    else{
      Node *temp = MinValueNode(node->right); //ind min in right subtree

      node->key = temp->key;

      //Delete the inorder successor
      node->right = deleteNode(node->right, temp->key);

      return node;
    }
  }


  void depthSearch(int data, int &temp){
    Node *ptr = root;
    bool found = false;
    while(!found){
      if (ptr->key == data){
        found = true;
      }
      else if(data < ptr->key){
        ptr = ptr->left;
        temp++;
      }
      else{
        ptr = ptr->right;
        temp++;
      }
    }
  }

  void getMaxDepth(Node* node, int &depth){
    int temp = 0;
    if (node == NULL)
      return;

    getMaxDepth(node->left, depth);
    getMaxDepth(node->right, depth);

    if(node->left == NULL && node->right == NULL){
      depthSearch(node->key, temp);
    }
    if(temp > depth){
      depth = temp;
    }
  }



};


int main(){
  Tree T;
  T.insert(12);
  T.insert(6);
  T.insert(16);
  T.insert(4);
  T.insert(8);
  T.insert(14);
  T.insert(18);
  T.insert(20);
  T.insert(22);
  cout<<T.root->key<<endl;
  cout<<"In order: ";
  T.printInorder(T.root);
  /*
  cout<<"Pre Order: ";
  T.printPreorder(T.root);
  cout<<"Post Order: ";
  T.printPostorder(T.root);
  */
  int sum = T.sumNodes(T.root);
  //cout<<endl<<"sum: "<<sum<<endl;
  int p = T.productNodes(T.root);
  //cout<<"product: "<<p<<endl;
  int s = 0;
  T.sumEven(T.root, s);
  //cout<<"sum evens: "<<s<<endl;
  return 0;
}
