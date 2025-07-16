#Sena YAMAN - 20010011013- 2-3 TREE ekleme silme - Ödev5

import time

#2 3 ağaçlarda ekleme ve çıkarma işlemlerini yapınız.
#Ekleme silme işlemlerini ve ağacın son durumunu gösteriniz.
#Bu işlemleri görsel olarak yapınız.

#---FONKSIYONLAR---

#dugumleri olusturmak için class yapısı olusturup sağ sol ağırlıklar vericem
class node:
    def __init__(self,data):
        self.data=data
        self.sol = None
        self.sag = None

#düğümleri oluşturacak fonksiyon
def nodeolustur(data):
    yeninode = node(data)
    return yeninode

#şimdi ekleme işlemi için fonksiyon
#1.ilk önce root var mı diye bakmalıyız
#2.yeni gelen data yı küçük mü büyük mü diye kontrol edip
#3.eğer küçükse tree nin soluna büyükse treenin sağına eklemeliyim

# --- 2-3 TREE EKLE FONKSİYONU---
def nodekle(root, data):
    if root is None:
        root = nodeolustur(data)
    elif data <= root.data:
        root.sol = nodekle(root.sol, data)
    elif data > root.data:
        root.sag = nodekle(root.sag, data)
    return root

# --- 2-3 TREE SİLME FONKSİYONU--

#silinecek düğümü buldurup silme işlemi yaptırmalıyız

#iki dugumlu icin en kucuk dugumu bulduran fonksiyon

def enkucuk(root):
    if root.sol is not None:
        root = root.sol
    return root


def nodesil(root,data):
    if root is None:
        return root
    elif data < root.data:
        root.sol = nodesil(root.sol, data)
    elif data > root.data:
        root.sag = nodesil(root.sag, data)
    else:
        #dugum bulundu!
        #root düğümde ise
        if root.sol is None and root.sag is None:
            root = None
        #Tek dugum durumu
        #sol taraf icin
        elif root.sol is None:
            #şimdi sildiğimde kayma olacak o yüzden silmeden önce yanındaki kenarda tutmalıyım
            tut = root
            root = root.sol
            tut = None #burada da sildim
        #sag taraf icin
        elif root.sag is None:
            tut = root
            root = root.sag
            tut = None
        #İki dugum durumu
        else:
            #en kucuk dugumu bulup kenarda tutmalıyım bunuda fonksiyonlar bulduralımi
            tut = enkucuk(root.sag)
            #sagdakiler kucuk oldugu icin
            root.data = tut.data
            root.sag = nodesil(root.sag,tut.data)
    return root

def gorsellestirme(root,bosluk):
    if root is None:
        return
    bosluk += 10
    gorsellestirme(root.sag,bosluk)
    print()
    for i in range(10,bosluk):
        print(" ",end="")
    print(root.data)
    gorsellestirme(root.sol,bosluk)


# --- MENU ---
#sonsuz döngü ile ekrana gelmesini sağla
root = None #kök dizine None atayalım
while True:
    print("\t\t\t\t 2-3 TREE \n")
    print("1.Ekle\n2.Çıkar\n3.Ağacı Görselleştir\n4.Çıkış")
    secim = int(input("Seciminizi giriniz :"))
    if (secim == 1):
        sayi = int(input("Kaç düğüm giriceksiniz :"))
        i = 0
        while i<sayi:
            data = int(input("Düğüm değerini giriniz:"))
            # data: dugumun degeri
            root = nodekle(root,data)
            i +=1
        print("Tree Yapısı Oluşturuluyor")
        time.sleep(1)
        print("Düğümler oluşturuldu !")

    elif(secim==2):
        data = int(input("Silmek istediğiniz Düğüm değerini giriniz:"))
        root = nodesil(root,data)
        print("Siliniyor...")
        time.sleep(1)
        print("Silmek istediğiniz düğüm silindi !")
    elif(secim==3):
        print("\t\t\t\n\nOluşan 2-3 Tree\n\n")
        time.sleep(1)
        gorsellestirme(root,0)
    elif(secim==4):
        print("Çıkışınız Yapılıyor...")
        time.sleep(1)
        print("Çıkışınız Yapıldı !")
        break















