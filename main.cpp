#include <stdio.h>
#include<iostream>
#include<string>
#include <stdlib.h>
using namespace std;
struct dict {
  struct dict *left,*right;
  char *word;
  char *meaning;
}*Root=NULL;
typedef struct dict dictionary;
int check(char[],char[]);
void insert(dictionary *);
void Search();
void view(dictionary *);

int check(char *a,char *b){
     int i,j,c;
     printf("%s\n",a);
     printf("%s\n",b);
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){
       if(a[i]>b[j]){
         c=1;
         break;
       }
        else if(b[j]>a[i]){
          c=-1;
          break;
        }
      else
         c=0;
     }
     if(c==1)
       return 1;
      else if(c==-1)
        return -1;
      else
        return 0;
}

void Search(){
  int flag=0;
  dictionary *ptr;
  ptr=Root;
  char w[10];
  printf("\nEnter word");
  scanf("%s",w);
  while(ptr!=NULL && flag==0){
    if(check(w,ptr->word)>0)
       ptr=ptr->right;
    else if(check(w,ptr->word)<0)
          ptr=ptr->left;
    else if(check(w,ptr->word)==0){
       flag=1;
       printf("\n%s",ptr->meaning);
    }

    }
    if(flag==0)
      printf("\nWord not found");
}

void insert(dictionary *temp){
  int flag=0;
  dictionary *ptr,*par;
  ptr=Root;
    printf("%s\n",temp->word);
    //printf("%s",temp->meaning);
  if(Root==NULL)
     Root=temp;
  else{
     while(ptr!=NULL ){
       if(check(temp->word,ptr->word)>0){
         par=ptr;
         ptr=ptr->right;
       }

       else if(check(temp->word,ptr->word)<0)
     {
       par=ptr;
       ptr=ptr->left;
     }
       else if(check(temp->word,ptr->word)==0){
          flag=1;
            printf("\nWord exists!!");
          break;
       }

   }
       if(flag==0 && ptr==NULL){

         if(check(par->word,temp->word)==1)
            par->left=temp;
         else if(check(par->word,temp->word)==-1)
            par->right=temp;
       }

     }

}

void view(dictionary *ptr){
  if(Root==NULL)
    printf("\nEmpty dictionary\n");

  else if(ptr !=NULL){
   view(ptr->left);
   printf("\nWord:%s\n",ptr->word);
   printf("\nMeaning:%s\n",ptr->meaning);
   view(ptr->right);
  }

}

int main(int argc, char const *argv[]) {
  int ch;
  FILE *stream;
            char *line = NULL;
            size_t len = 0;
            int read;
            int i=0;
  dictionary *temp;
  while(ch!=4){
    printf("\n1.Search\n2.Insert\n3.View\n4.Exit\nYour choice please..");
    scanf("%d",&ch);
    switch (ch) {
      case 1:
            Search();
            break;
      case 2:
            stream = fopen("a.txt", "r");
            if (stream == NULL)
                exit(EXIT_FAILURE);
            while ((read = getline(&line, &len, stream)) != -1) {
                if(i%2==0){
                    printf("%d ",i);
                    //printf("Retrieved line of length %d :\n", read);
                    //printf("%s", line);
                    temp=(dictionary*)malloc(sizeof(dictionary));
                      temp->left=NULL;
                      temp->right=NULL;
                      temp->word = line;
                      printf("%s",temp->word);
                }
                else{
                    printf("%d ",i);
                    //printf("Retrieved line of length %d :\n", read);
                    //printf("%s", line);
                    temp->meaning = line;
                    printf("%s",temp->meaning);
                    insert(temp);
                }
                //printf("%s",temp->word);
                //printf("%s",temp->meaning);
                i++;
            }
            free(line);
            fclose(stream);
          break;
      case 3:
      view(Root);
      break;
      case 4:exit(0);
    }
  }
  return 0;
}
