/*
  Created by S Pramod <--> domarps
*/
#include<stdio.h>
#include<stdlib.h>
int lastLabel = 0;

struct node
{
    int data;
    int label;
    struct node* parent;
    struct node* rightChild;
    struct node* leftChild;
};

struct node* createNode(int d)
{
   struct node* newN = (struct node*)malloc(sizeof(struct node));
   newN->data = d;
   newN->leftChild  = '\0';
   newN->rightChild = '\0';
   lastLabel++;
   newN->label      = lastLabel;
   return newN;
}
struct Queue
{
   int front,rear;
   int size;
   struct node** array;
};

typedef struct tree
{
   struct node* root;
   int size;
}BinaryTree;

////////Binary Tree Helper Functions//////////////////////
BinaryTree* createTree()
{
     BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
     t->root       = '\0';
     t->size       = 0;
     return t;
}

int size(BinaryTree *t)
{
   return t->size;
}

struct node* root(BinaryTree *t)
{
    return t->root;
}

struct node* parent(struct node* n)
{
   return n->parent;
}

int isInternal(struct node *n)
{
   return n->leftChild != '\0' || n->rightChild != '\0';
}

int isExternal(struct node *n)
{
        return !isInternal(n);
}

int isRoot(struct node* n)
{
   return n->parent == '\0';
}

int hasBothChild(struct node* temp)        
{
      if((temp!= '\0') && (temp->leftChild != '\0') && (temp->rightChild != '\0')) return 1;
}
////////Binary Tree Helper Functions//////////////////////

/////////Queue Helper Functions//////////////////////////
//
//
//createQueue takes queueSize as input and returns a '\0'-initialized queue
struct Queue* createQueue(int size)
{
   struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
   queue->front = queue->rear = -1;
   queue->size  = size;

   queue->array = (struct node**)malloc(queue->size * sizeof(struct node*));
   int i;
   for(i = 0; i < size; i++) queue->array[i] = '\0';
   return queue;
}
//check if Queue is empty
int isEmpty(struct Queue* queue)               
{
   return queue->front == -1;
}
//check if Queue is Full
int isFull(struct  Queue* queue)                 
{
   return (queue->rear == queue->size-1);
}
//check if Queue has only one Item
int hasOnlyOneItem(struct Queue* queue)         
{
  return (queue->front == queue->rear);
}
//ENQUEUE
void Enqueue(struct node* root, struct Queue *queue)
{
   if(isFull(queue)) return;
   queue->array[++queue->rear] = root;
   if(isEmpty(queue))  ++queue->front;
}
//DEQUEUE
struct node* Dequeue(struct Queue* queue)
{
       if(isEmpty(queue))  return '\0';
       struct node* temp = queue->array[queue->front];
       if (hasOnlyOneItem(queue))     queue->front = queue->rear = -1;
       else                           ++queue->front;
       return temp;
}
//Get Front of the Queue
struct node* getFront(struct Queue* queue) 
{
      return queue->array[queue->front];
}
/////////Queue Helper Functions//////////////////////////
//Helper function to find the number of nodes of a particular subTree
int sizeFind(struct node* stree)
{
  if(stree == '\0') return 0;
  else              return(sizeFind(stree->leftChild) + 1 + sizeFind(stree->rightChild));
} 

//Helper function to find the a particular nodes given the node's key
int sizeQuery(struct node* root,int key, int size)
{
   struct Queue *queue     = createQueue(size);
   struct node  *temp_node   = root;
   
   while(temp_node)
   {
      if(temp_node->data == key)
      {
            return sizeFind(temp_node);
      }
      if(temp_node->leftChild != '\0')
      {
             Enqueue(temp_node->leftChild, queue);
      }
      if(temp_node->rightChild != '\0')
      {
        Enqueue(temp_node->rightChild, queue);
      }
      temp_node = Dequeue(queue);
   }
   return 0; 
}

    
//insert data in the pre-existing Complete Binary Tree
void insert(struct node** root, int data, struct Queue* queue)
{
   struct node* temp = createNode(data);
   if(!*root)      
   {
       *root = temp;
   }
   else     
   {
       struct node* front = getFront(queue);
       if((front->leftChild) == '\0')
       {
          front->leftChild  = temp; 
          temp->parent = front;
       }
       else if((front->rightChild) == '\0')        
       { 
         front->rightChild = temp;
         temp->parent      = front;
       }
       if(hasBothChild(front))       Dequeue(queue);
   }   
   Enqueue(temp,queue);
}
//perform Level Order Traversal
void levelOrder(struct node* root, int size)
{
   struct Queue* queue = createQueue(size);
   Enqueue(root, queue);
   int label = 0;
   while(!isEmpty(queue))
   {
      struct node* temp = Dequeue(queue);
      label++;
      temp->label = label;
      if(temp->leftChild)  Enqueue(temp->leftChild,  queue);
        if(temp->rightChild) Enqueue(temp->rightChild, queue);
   }
}
//perform InOrder Traversal                              
void inOrder(struct node* root)
{
   if(root == '\0') return;
   if(isInternal(root)) inOrder(root->leftChild);
   printf("%d ", root->data);
   if(isInternal(root)) inOrder(root->rightChild);
}
//perform Query 
int Query(struct node* root,int key,int size)
{
   int count = 0;
   int rear,front;
   struct Queue *queue     = createQueue(size);
   struct node  *temp_node   = root;                                                                   
   while(temp_node)
   {
      if(temp_node->data == key)
      {
            count++;
      }
      if(temp_node->leftChild != '\0')
      {
             Enqueue(temp_node->leftChild, queue);
      }
      if(temp_node->rightChild != '\0')
      {
             Enqueue(temp_node->rightChild, queue);
      }
      temp_node = Dequeue(queue);
   }
   return count;
}
//Get Pointer will return the node given the Root of the CBT and the Label
struct node* getPointer(int label,struct node* root)
{
    struct node* parentPointer;
    struct node* child;
    if(root!= '\0' && label == 1) return root;
    else
    {
         parentPointer    =  getPointer(label/2, root);
         child            =   parentPointer->leftChild;
//         printf("What should have  Happened here  Label %d %d %d \n",label, child->data,child->label);
//         printf("What should have  Happened here  Label %d %d %d \n",label, parentPointer->leftChild->data, parentPointer->leftChild-> label);
         if(parentPointer != '\0' && child != '\0')
         {  
          if((parentPointer->leftChild->label) == label)   return parentPointer->leftChild;
          else                                             return parentPointer->rightChild;
         }
    }
}
//The helper function will remove the node containing the Key(multiple instances possible), then it would replace that node with the Last Node
struct node* Delete(struct node* root,int key,int size)
{
    int count = 0;
    int rear,front;
    struct Queue *queue       = createQueue(size);
    struct node  *temp_node   = root;
    while(temp_node)
    {
      if(temp_node->data == key)
      {
        struct node* lastValue = getPointer(lastLabel,root);
        if(lastValue != '\0') 
        {
          temp_node->data  = lastValue->data;
          if(lastValue->label == lastValue->parent->leftChild->label) 
                                 lastValue->parent->leftChild = '\0';
          else                        
                                 lastValue->parent->rightChild = '\0';
        }  
        free(lastValue);
        lastLabel--;
      }
      if(temp_node != NULL)
      {  
         if(temp_node->leftChild != '\0')
        {
           Enqueue(temp_node->leftChild, queue);
        }
        if(temp_node->rightChild != '\0')
        {
          Enqueue(temp_node->rightChild, queue);
        }
      }  
      
      if(!(temp_node != NULL && temp_node->data == key)) temp_node = Dequeue(queue);
   }
   return root;
}
   
int main()
{
   int num_items;
   int key;
   int num_Ops;
   char op;
   int op_key;
   int ctr;
   int qcount;
   int i;
   int stree_ctr;
   scanf("%d",&num_items); 
   struct node*  root  = '\0';
   struct Queue* queue = createQueue(num_items);
   for(ctr = 0; ctr < num_items; ctr++)
   {
      scanf("%d",&key);
      insert(&root,key, queue);
   }
   levelOrder(root,num_items);
   inOrder(root);
   printf("\n");
   //num_items is just the initial number of elements
   scanf("%d",&num_Ops);
   for(i = 0; i < num_Ops ; i++)
   {
           
     while((op = getchar())== '\n');
     scanf("%d",&op_key);
     if(op ==  'i') 
      {
                       insert(&root,op_key,queue);
                       inOrder(root);
                       printf("\n");
      }
      else if(op == 'q')
      { 
                       qcount = Query(root,op_key,lastLabel);
                       printf("%d\n",qcount);
      }               
      else if(op == 's')
      {
                       stree_ctr = sizeQuery(root,op_key,lastLabel);
                       printf("%d\n",stree_ctr);
      }
      else if(op == 'r')
      {
                       root = Delete(root,op_key,lastLabel);
                       inOrder(root);
                       printf("\n");
      }
   }
   return 0;
}
