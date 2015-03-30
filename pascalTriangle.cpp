#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void trim(char* str)
{
  int i,begin;
  begin = 0;
  int end = strlen(str) -1 ;
  while(isspace(str[begin])) begin++;
  while((end >= begin) && isspace(str[end])) end--;
  for(i=begin; i <= end; i++) str[i-begin] = str[i];
  str[i-begin] = '\0';
}    

int pascal(int row,int column)
  {
     if(row == 1 && column == 1)   return 1;
     else if(column == 0 || column > row) return 0; 
     else           return  pascal(row - 1,column-1) + pascal(row - 1,column);
  } 
 
void space(int num, int mul) // for spaces in between elements
  {
      int i;
      num *= mul;
      for(i=0; i<num; i++) printf(" ");
  }
int main()
  {
      char s[20];
      const char* delim = " ,  ";
      char *token;
      int ctr;
      int row;
      int rows;
      int transactions;
      int **array;
      int **arr_pascal;
      int *temp;
      int *coeff;
      int cols = 10;
      int i=0,r=0,c=0,j;
      int sum=0,k=0;
      fscanf(stdin,"%d\n", &rows);
      fscanf(stdin,"%d\n", &transactions);
      arr_pascal =  malloc(rows * sizeof(int *));
      array  =  malloc(transactions * sizeof(int *));
      temp   =  malloc(20* sizeof(int));
      coeff  =  malloc(transactions * sizeof(int));
      
      for(i = 0;i < transactions; i++)
      {         
      
        fgets(s,20,stdin);
        r=0;
		trim(s);
        token = strtok(s,delim);
        temp[r] = atoi(token);
        r++;
        while(token != NULL) 
          {   
            token = strtok(NULL, delim);
            if(token != NULL)  
              {
                temp[r] = atoi(token);
                r++;
              }  
          }
        array[i] = malloc((r) * sizeof(int));
        coeff[i] = r-1; //printf("%d \n",coeff[i]);
        for(ctr = 0; ctr < (r); ctr++) 
        {  
            array[i][ctr] = temp[ctr]; 
        }
       }
//     Printing Pascal's Triangle
        for(i=1;i<=(rows+1);i++)
       {

          arr_pascal[i-1] = malloc(i*sizeof(int)); 
          for(j=1;j<=i;j++)
          {
             arr_pascal[i-1][j-1] = pascal(i,j);
           }
       }  
       for(i = 0;  i < transactions ; i++)  
       {
          sum = 0;
          row = array[i][0];
          if(row > rows) 
          {
                   sum = -1;
          }
          else 
          {  
           for(k=1;k<=coeff[i];k++)
           {

                   if(array[i][k] > array[i][0]) { sum = -1; break;}
                   sum = sum + arr_pascal[row][array[i][k]];
           }         
          }  
          printf("%d ",sum);
       }          
   return 0;
}
