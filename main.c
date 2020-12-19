#include <stdio.h>
#include <stdlib.h>
char *file_path="C:\\Users\\tanal\\Desktop\\proje3.txt";

struct dugum{
char *kelime;
int kelime_adet;
struct dugum* next;
};

void yazdir(struct dugum* n){
    int i=1;
    while(n!=NULL){
        printf("%d. %s ",i,n->kelime);
        printf("%d\n",n->kelime_adet);
        n=n->next;
        i++;
    }
}

void basaElemanEkle(struct dugum** head_ref, char *y_kelime, int y_kelime_adet){
    struct dugum* yeni_dugum = (struct dugum*) malloc(sizeof(struct dugum));

    yeni_dugum->kelime = y_kelime;
    yeni_dugum->kelime_adet = y_kelime_adet;
    yeni_dugum->next = (*head_ref);
    (*head_ref) = yeni_dugum;
}

void arkasinaElemanEkle(struct dugum* prev_node, char *y_kelime, int y_kelime_adet){
    if(prev_node==NULL){
        printf("Referans verilen onceki dugum bos olamaz.");
        return;
    }

    struct dugum* yeni_dugum =(struct dugum*) malloc(sizeof(struct dugum));

    yeni_dugum->kelime = y_kelime;
    yeni_dugum->kelime_adet= y_kelime_adet;
    yeni_dugum->next = prev_node->next;
    prev_node->next = yeni_dugum;
}

void sonaElemanEkle(struct dugum** head_ref, char *y_kelime, int y_kelimeadet){
    struct dugum* yeni_dugum =(struct dugum*) malloc(sizeof(struct dugum));
    struct dugum *son = *head_ref;

    yeni_dugum->kelime= y_kelime;
    yeni_dugum->kelime_adet=y_kelimeadet;
    yeni_dugum->next=NULL;

    if(*head_ref==NULL)
    {
        *head_ref=yeni_dugum;
        return;
    }
    while(son->next != NULL)
        son= son->next;

    son->next=yeni_dugum;
    return;
}


int main()
{

    FILE *dosya=fopen(file_path,"r");
    if(dosya==NULL){
        printf("Dosya acilamadi.\n");
    }
    else{
        printf("Dosya acildi.\n");
    }

    while(!feof(dosya))
        printf("%c",fgetc(dosya));

    printf("\n");
    fclose(dosya);

    struct dugum* head =NULL;
    sonaElemanEkle(&head,"asd",5);// 5
    basaElemanEkle(&head,"ddd",3);// 3-5
    basaElemanEkle(&head,"aaa",2);// 2-3-5
    sonaElemanEkle(&head,"sss",4);// 2-3-5-4
    arkasinaElemanEkle(head->next, "abc", 6);//2-3-6-5-4

    printf("\nYaratilan liste:\n");
    yazdir(head);

    return 0;
}