#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char id[10];
    float yuk;
    float max_kapasite;
    struct node* prev;
    struct node* next;
};

struct node* head = NULL;

struct node* yeniNode()
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->yuk = 0;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}




void ekleSunucu()
{
    struct node* yeniNode = (struct node*)malloc(sizeof(struct node));
    yeniNode->yuk = 0;
    printf("Sunucu ID'sini giriniz: ");
    scanf("%s", yeniNode->id);
    printf("Max yuk bilgisini giriniz: ");
    getchar();
    scanf("%f", &(yeniNode->max_kapasite));

    if (head == NULL)
    {
        head = yeniNode;
        head->prev = head;
        head->next = head;
    }
    else
    {
        yeniNode->prev = head->prev;
        yeniNode->next = head;
        head->prev->next = yeniNode;
        head->prev = yeniNode;
    }

     // Yeni sunucu eklendikten sonra sıralama işlemi

}


void siralama()
{
    int degisen;
    struct node* temp;
    struct node* son = NULL;

    while (1)
    {
        degisen = 0;
        struct node* bulundugum = head;

        while (bulundugum->next != son)
        {
            if (bulundugum->max_kapasite < bulundugum->next->max_kapasite)
            {
                // Değişim yap
                temp = bulundugum->next;
                bulundugum->next = temp->next;
                temp->next = bulundugum;

                if (bulundugum == head)
                    head = temp;

                degisen= 1;
            }
            bulundugum = bulundugum->next;
        }

        son = bulundugum;

        if (!degisen)
            break;
    }



}

void tuketici()
{
    if (head == NULL)
    {
        printf("Liste bos. Tuketici islemi yapilamaz.\n");
        return;
    }

    float istenilenYuk;
    printf("Istenilen yuk miktarini giriniz: ");
    scanf("%f", &istenilenYuk);

    struct node* guncel = head;

    if (guncel->max_kapasite < istenilenYuk)
    {
        printf("Ilk sunucu kapasitesi yetersiz. Tuketici islemi yapilamaz.\n");
        return;
    }

    while (guncel != NULL && istenilenYuk > 0)
    {
        if (guncel->max_kapasite >= istenilenYuk)
        {
            guncel->yuk += istenilenYuk;
            istenilenYuk = 0;
        }
        else
        {
            guncel->yuk = guncel->max_kapasite;
            istenilenYuk -= guncel->max_kapasite;
        }

        guncel = guncel->next;
    }

    printf("Tuketici islemi tamamlandi.\n");
}

void listele()
{
    siralama();

    struct node* guncel = head;
    if (head == NULL)
    {
        printf("Liste bos.\n");
        return;
    }
    do
    {
        printf("ID: %s, Yuk: %.2f, Max Kapasite: %.2f\n", guncel->id, guncel->yuk, guncel->max_kapasite);
        guncel = guncel->next;
    } while (guncel != head);
}

int main()
{
    int secim;
    while (1)
    {
        printf("\n1. Sunucu Ekle\n2. Tuketici\n3. Listele\n4. Cikis\nSecim yapin: ");
        scanf("%d", &secim);
        switch (secim)
        {
        case 1:
            ekleSunucu();
            break;
        case 2:
            tuketici();
            break;
        case 3:
            listele();
            break;
        case 4:
            return 0;
        default:
            printf("Gecersiz secenek");
        }
    }

    return 0;
}
