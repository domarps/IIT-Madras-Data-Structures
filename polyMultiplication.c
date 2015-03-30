/*
 Created by S Pramod <--> domarps
 http://cprogrammingquest.blogspot.in/2015_02_01_archive.html
*/
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>

typedef struct Dcontainer
{
  int coeff;
  int exp;
  struct Dcontainer *prev;
  struct Dcontainer *next;
}DL_node;

void DswapElement(DL_node* position1,DL_node* position2)
{ 
   int etemp,ctemp;
   if((position1 == NULL) || (position2 == NULL)) return;
   etemp = position1->exp;
   ctemp = position1->coeff;
   position1->exp   = position2->exp;
   position1->coeff = position2->coeff;
   position2->exp   = etemp;
   position2->coeff = ctemp;
}

DL_node *Dlast(DL_node* list)
{
  if(list == NULL) return list;
  while(list->next != NULL) 
  {
    list = list->next;
  }
  return list;
}

DL_node * partition(DL_node *l, DL_node *h)
{
    // set pivot as h element
    int x  = h->exp;
    int etemp;
    int ctemp;
    // similar to i = l-1 for array implementation
    DL_node *i = l->prev;
    DL_node *j;
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (j = l; j != h; j = j->next)
    {
        if (j->exp >= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
            ctemp    = i->coeff;
            i->coeff = j->coeff;
            j->coeff = ctemp;
            
            etemp    = i->exp;
            i->exp   = j->exp;
            j->exp   = etemp;
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    DswapElement(i, h);
    return i;
}
 
/* A recursive implementation of quicksort for linked list */
void _quickSort(DL_node* l, DL_node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        DL_node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}
 
// The main function to sort a linked list. It mainly calls _quickSort()
void quickSort(DL_node **poly_head)
{
    // Find last node
    DL_node* h = Dlast(*poly_head);
 
    // Call the recursive QuickSort
    _quickSort(*poly_head, h);
}

DL_node* DinsertFirst(DL_node** poly_head, int coeff, int exp)
{
   DL_node* new_node = (DL_node*)malloc(sizeof(DL_node));
   new_node->coeff = coeff;
   new_node->exp   = exp;
   new_node->next  = (*poly_head);
   new_node->prev  = NULL;
   if((*poly_head) != NULL) (*poly_head)->prev = new_node;
   (*poly_head) = new_node;
   return *poly_head;
}

void DinsertLast(DL_node** poly_head, int coeff, int exp)
{
   DL_node* new_node = (DL_node*)malloc(sizeof(DL_node));
   DL_node* last     = *poly_head;
   
   new_node->coeff = coeff;
   new_node->exp   = exp;
   
   new_node->next  = NULL;
   
   if(*poly_head == NULL)
   {
      new_node->prev = NULL;
      *poly_head = new_node;
      return;
   }
   
   while(last->next != NULL)
   {
                last = last->next;
   }
   
   last->next     = new_node;
   
   new_node->prev = last;
   return;
}

DL_node* Mul(DL_node* poly1,DL_node* poly2)
{
 DL_node* answer = NULL;
 //DL_node* new_DL_node;
 DL_node* temp   = NULL;
 //DL_node* last   = NULL;
 DL_node* p1temp = poly1;
 DL_node* p2temp = poly2;
 int coeff,exp;
 temp = (DL_node*)malloc(sizeof(DL_node));
 temp->next = NULL;
 
  while(p1temp != NULL )
  {
       p2temp = poly2;
       while(p2temp != NULL)
       {
          coeff = p1temp->coeff * p2temp->coeff;
          exp   = p1temp->exp    +  p2temp->exp;
          //printf("%d %d \n ",coeff , exp); 
          p2temp = p2temp->next;
          if(answer == NULL)
          {
             answer = DinsertFirst(&answer,coeff,exp);
          }
          else
          {
             DinsertLast(&answer,coeff,exp);
          }  
       }
       p1temp = p1temp->next;
      //printf("%d %d \n ",p1temp->coeff,p1temp->exp); 
  }
  return answer;
}

void Dprint_list(DL_node* poly)
{
  while(poly != NULL)
     {
         printf("%d %d\t ",poly->coeff,poly->exp);
         poly = poly->next;
     }
  printf("\n");      
  return;
}

void Purge(DL_node** poly)
{
   DL_node *cr,*pr,*run,*temp,*del;
   cr   = *poly;
   cr   = cr->next;
   pr   = *poly;
   while(cr != NULL)
   {
       if((*poly)->exp == cr->exp)
       {
           
           (*poly)->coeff += cr->coeff;
           temp        = cr->prev;
           temp->next  = cr->next;
           (temp->next)->prev = temp;
           del         = cr;
           cr          = cr->next;
           free(del);
       }
       else
       {
           cr  = cr->next;
           pr  = pr->next;
       }
   }
   cr = *poly;
   cr = cr->next;
   pr = *poly;
   while(cr != NULL)
   {
        run = *poly;
        while(run != cr)
        {
          if(run->exp  == cr->exp)
          {
                {
                     run->coeff += cr->coeff;
                }
                temp        = cr->prev;
                temp->next  = cr->next;
                (temp->next)->prev = temp;
                del         = cr;
                cr          = cr->next;
                free(del);
//                pr->next    = cr;
//                cr->prev    = pr;
          }
                run  = run->next;
         }
         if(run == cr)
         {
                cr   = cr->next;
                pr   = pr->next;
         } 
   }
   cr   = *poly;
   cr   = cr->next;
   //printf("%d %d \n", pr->coeff,pr->exp);
   while(cr != NULL)
   {
       if(pr->exp == cr->exp && pr != cr)
       {
           
           (pr)->coeff += cr->coeff;
           temp        = cr->prev;
           temp->next  = cr->next;
           (temp->next)->prev = temp;
           del         = cr;
           cr          = cr->next;
           free(del);
       }
       else
       {
           cr  = cr->next;
       }
   }
}
void Dprint_list_poly(DL_node* poly)
{
    int flag = 1;  //1 to print +
   int first=0;   
   while(poly != NULL)
     {
         if(poly->coeff !=0)
         {
          if(poly->exp == 0)         
                     {first =1;flag =1;  printf("%d",poly->coeff);}
          else if(poly->exp  == 1 && poly->coeff >1)
                   {first =1 ;flag = 1; printf("%dx",poly->coeff);}
          else if(poly->exp  == 1 && poly->coeff ==1)      
                    {first =1 ;flag = 1; printf("x");}
          else if(poly->coeff == 1)                       
                   {first =1 ;flag =1;  printf("x^%d",poly->exp);}
          else if(poly->coeff < 0 && poly->exp != 1)              
                   {first =1 ;flag = 1; printf("%dx^%d",poly->coeff,poly->exp);}
          else if(poly->coeff < 0 && poly->exp == 1)              
                   {first =1 ;flag = 1; printf("%dx",poly->coeff);}
          else
                   {first =1 ;flag = 1; printf("%dx^%d",poly->coeff,poly->exp);}
          poly = poly->next;
          if((poly)!=NULL && flag == 1 && first == 1 && ((poly->coeff)>0)) printf("+");
         }
         else
         {
             poly = poly->next;
             if(poly != NULL && (poly->coeff)>0 && first == 1) printf("+");
             flag = 0;
         }
      }
   if(flag == 0) printf("0");
   return;

}

int main()
{
  DL_node* poly1 =  NULL;
  DL_node* poly2 =  NULL;
  DL_node* x;
  int terms_1,terms_2;
  char s_1[100];
  char s_2[100];
  int n1,n2;
  int i =0;
  int temp;
  int coeff;
  int exp;
  //char l;
  char delimiters[] = " ";
  char *token;
  int tuple = 1;
  fscanf(stdin,"%d\n", &terms_1);
  n1 = 100;
  fgets(s_1,n1,stdin);
  fscanf(stdin,"%d\n", &terms_2);
  n2 = 100;
  fgets(s_2,n2,stdin);
  
  token = strtok (s_1, delimiters);      
  
  while( token != NULL ) 
  {
      //printf( " %s\n", token );
      temp  = atoi(token);
      if(tuple == 1) 
         {
               coeff = temp; 
               tuple++;
         }
         else  
         { 
               exp = temp; 
               tuple--;
               DinsertLast(&poly1, coeff, exp);
         }
         token = strtok(NULL, delimiters);
   }
  i = 0;
  
  token = strtok (s_2, delimiters);      /* token => "words" */
  while( token != NULL ) 
  {
      // printf( " %s\n", token );
       temp  = atoi(token);
       if(tuple == 1) 
       {
         coeff = temp; 
         tuple++;
       }
       else   
       { 
         exp = temp; 
         tuple--;
         DinsertLast(&poly2, coeff, exp);
       }
     token = strtok(NULL, delimiters);
  }  
   //Dprint_list(poly1);
   x =  Mul(poly1,poly2);
   //Dprint_list(x);
   Purge(&x);
   //Dprint_list(x);
   quickSort(&x);
   //Dprint_list(x);
   Dprint_list_poly(x);
   return 0;
}   
