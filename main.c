#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <ctype.h>
char *text="C:\\Users\\oguzn\\OneDrive\\Masaüstü\\proje3.txt";
int b=0;
struct Node {
  char *kelime;
  int adet;
  struct Node* next;
};
struct Node* deg=NULL;

void basaEkle(struct Node** ref, char *kelime,int adet) {

  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));


    new_node->kelime  = kelime;
    new_node->adet  = adet;

    new_node->next = (*ref);
    (*ref)    = new_node;

}


void sonrakiDugumeEkle(struct Node** ref,struct Node* eklenecek) {

  struct Node* temp = *ref;
  struct Node* dolas = temp->next;
  while(dolas!=NULL){
    if(eklenecek->adet>dolas->adet){
        eklenecek->next=dolas;
        temp->next=eklenecek;
        break;
    }
    temp=dolas;
    dolas=dolas->next;
  }

}

void sonaEkle(struct Node** ref, char* kel) {
  struct Node* yeni_dugum = (struct Node*)malloc(sizeof(struct Node));
  struct Node* son = *ref;

  yeni_dugum->kelime= kel;
  yeni_dugum->adet= 1;
  yeni_dugum->next = NULL;

  if (*ref == NULL) {
    *ref = yeni_dugum;
    return;
  }

  while (son->next != NULL)
    son = son->next;

  son->next = yeni_dugum;
  return;
}


void yazdir(struct Node* node) {
    int i=1;
  while (node != NULL) {
    printf("%d. %s %d \n",i, node->kelime,node->adet);
    node = node->next;
    i++;
  }
}

int ara(struct Node **head, char *kel)
{   struct Node* temp=*head;
    struct Node* temp2=NULL;
    if(strcmp(temp->kelime,kel)==0){
        temp->adet++;
        b=0;
        return 0;
    }
    else{
    b++;
    temp2=temp;
    temp=temp->next;
    while (temp != NULL)
    {
        if (strcmp(temp->kelime,kel)==0)
        {   temp->adet++;
            temp2->next=temp->next;
            deg=temp;
            return 1;
        }
        temp2=temp;
        temp = temp->next;
    }
}
    return 0;
}


int main() {
  struct Node* head = NULL;
  FILE *f=fopen(text,"r");
  char metin[500000];
  if(f==NULL){
    printf("Dosya bulunamadi!");
  }
  else{
  for(int i=0;!feof(f);i++){
    metin[i]=getc(f);
  }
  }
  char *kelime;
  kelime=strtok(metin," \n");
  sonaEkle(&head,kelime);

  while(1){

    kelime=strtok(NULL," \n");

    if(kelime==NULL){
        break;
        }

    if(isprint(kelime[strlen(kelime)-1])==0){
        kelime[strlen(kelime)-1]='\0';
    }
    if(ara(&head,kelime)==true){

        if(deg->adet>head->adet){
            basaEkle(&head,deg->kelime,deg->adet);
        }
        else if(b!=0){
            sonrakiDugumeEkle(&head,deg);
            b=0;
        }

    }
    else if(b==0);
    else
    sonaEkle(&head,kelime);
    }


  fclose(f);
  yazdir(head);
  return 0;
}
