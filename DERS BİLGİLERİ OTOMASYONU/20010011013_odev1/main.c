#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//SENA YAMAN 20010011013 VERI YAPILARI ODEVÝ-1


struct Ders
{
    char dersAd[30];
    char dersKod[10];
    float not;
    struct Ders *next;
};

struct Ogrenci
{
    char ad[30];
    char soyad[30];
    char no[10];
    struct Ders *ders;
    float ort;
    struct Ogrenci *next;
};

struct Ogrenci *ilkOgrenci = NULL;

struct Ders *dersDugum(const char *dersAd, const char *dersKod, float not)
{
    struct Ders *ders = (struct Ders*)malloc(sizeof(struct Ders));
    strcpy(ders->dersAd, dersAd);
    strcpy(ders->dersKod, dersKod);
    ders->not = not;
    ders->next = NULL;
    return ders;
}

void listele(struct Ogrenci *ogrenci)
{
    // Baðlý liste boþsa uyarý ver
    if (ogrenci == NULL) {
        printf("Baðlý Listede Öðrenci yok!\n");
        return;
    }

    // Butun nodelarý dolasarak yazdýracak
    while (ogrenci != NULL)
    {
        printf(" Ogrenci Adi: %s\n Soyadi: %s\n Ogrenci No:%s\n Ortalama: %.2f\n",ogrenci->ad, ogrenci->soyad,ogrenci->no,ogrenci->ort);
        ogrenci = ogrenci->next;
    }
}

void arama(const char *arananKod)
{
    struct Ogrenci *ogrenci = ilkOgrenci;
    // ogrencilerin nodelarýný gezmem gerekiyor
    while (ogrenci != NULL) {
        struct Ders *ders = ogrenci->ders;

        while (ders != NULL) {
            if (strcmp(ders->dersKod, arananKod) == 0) {
                printf("Ogrenci Adý: %s, Soyadi: %s, Ders Kodu: %s, Ders Notu: %.2f\n", ogrenci->ad, ogrenci->soyad, ders->dersKod, ders->not);
            }

            ders = ders->next;
        }

        ogrenci = ogrenci->next;
    }
}

void silme(const char *silinenSoyad) {
    struct Ogrenci *start = ilkOgrenci;
    struct Ogrenci *oncekiNode = NULL;

    // Baðlý liste boþsa uyarý ver
    if (start == NULL) {
        printf("Baðli Listede Ogrenci yok!\n");
        return;
    }

    while (start != NULL) {
        // ogrencinin soyadý var mý bakýyorum
        if (strcmp(start->soyad, silinenSoyad) == 0) {
            // Eðer soyad eþleþiyorsa bu öðrenciyi listeden çýkar

            if (oncekiNode == NULL) {
                // Ýlk öðrenci siliniyorsa
                // Ýlk ogrenciyi çýkardýðým için ilk node'a gösterdigi node'u aticam
                ilkOgrenci = start->next;
            } else {
                // 5->7->3->8
                // 5->7->8
                // eðer onceki node bos degilse:
                // silmek istedigim node'un onceki nodun gosterdigi node'a = silmek istedigim node'un gosterdigi node'u aticam

                oncekiNode->next = start->next;
            }

            free(start);

            return;
        }

        oncekiNode = start;
        start = start->next;
    }

    // Eðer soyadý bulunamazsa
    printf("Soyadi '%s' olan ogrenci bulunamadi.\n", silinenSoyad);
}

int main()
{
    FILE *dosya = fopen("20010011013.txt", "r");

    if (dosya == NULL)
    {
        printf("Dosya Acilamadi!\n");
        return 1;
    }

    char ad[30], soyad[30], no[10], dersAd1[30], dersAd2[30], dersAd3[30];
    char dersKod1[10], dersKod2[10], dersKod3[10];
    float dersNot1, dersNot2, dersNot3;

    while (fscanf(dosya, "%s %s %s %s %s %f %s %s %f %s %s %f", ad, soyad, no, dersAd1, dersKod1, &dersNot1, dersAd2, dersKod2, &dersNot2, dersAd3, dersKod3, &dersNot3) == 12)
    {
        struct Ogrenci *ogrenci = (struct Ogrenci *)malloc(sizeof(struct Ogrenci));
        strcpy(ogrenci->ad, ad);
        strcpy(ogrenci->soyad, soyad);
        strcpy(ogrenci->no, no);

        ogrenci->ders = dersDugum(dersAd1, dersKod1, dersNot1);
        ogrenci->ders->next = dersDugum(dersAd2, dersKod2, dersNot2);
        ogrenci->ders->next->next = dersDugum(dersAd3, dersKod3, dersNot3);

        // Ortalama hesaplama
        ogrenci->ort = (dersNot1 + dersNot2 + dersNot3) / 3.0;

        // Baðlý liste olusturuyorum
        ogrenci->next = ilkOgrenci;
        ilkOgrenci = ogrenci;
    }

    fclose(dosya);

    int secim;
    do {
        printf("\n1. LISTELE (Tum Ogrencileri)\n");
        printf("2. ARAMA (Ders Koduna Gore)\n");
        printf("3. SILME (Soyada Gore)\n");
        printf("4. CIKIS\n");
        printf("Secim->");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                listele(ilkOgrenci);
                break;

            case 2:
                {
                    char arananKod[10];
                    printf("Aranan ders kodunu girin: ");
                    scanf("%s", arananKod);
                    arama(arananKod);
                }
                break;

            case 3:
                {
                    char silinenSoyad[30];
                    printf("Silmek istediginiz ogrencinin soyadini girin: ");
                    scanf("%s", silinenSoyad);
                    silme(silinenSoyad);
                }
                break;

            case 4:
                printf("Programdan cikiliyor.\n");
                break;

            default:
                printf("Gecersiz secenek! Lutfen 1, 2, 3 veya 4 girin.\n");
        }
    } while (secim != 4);

    // Çýkýþ seçeneði seçilene kadar menüyü tekrar tekrar göster

    return 0;
}
