#konu:Huffman ve LZW algoritmalarında girdi txt dosyasından okunacak ve bu girdiye göre algoritma çalışacaktır.
#Algoritmalar çalıştıktan sonra her bir algoritma için ayrı txt dosyalarına kodların çalışma zamanı, sıkıştırılmadan önceki boyut ve sıkıştırıldıktan sonraki boyut yazılacaktır.
#Hazır kütüphane kullanmak yasaktır.

#Dosyadan okuma işlemi için fonksiyon:
#dosyayı okuma modunda açıcam
from typing import List


def readfile(dosyadi):
    with open(dosyadi,'r') as file:
        text = file.read()
    return text

girdidosya = "20010011013.txt"
text = readfile(girdidosya)

#Dosya Yazma
def writefile(compressedfilename, compressedtext):
    with open(compressedfilename, 'w') as file:
        file.write(compressedtext)
    return compressedtext

# --- LZW CODE ---

#text den okuttuğumuz değerler için dictionaryde değer atayarak yer vermemiz lazım


#şimdi bunları sıkıştırdığımız bir fonksiyon yazmalıyız
def lzwCompress(text):
    bosdictionary = {}
    for i in text:
        if i not in bosdictionary:
            # degerlerine her bir yeni keşif için artık ilk tanımlanandan sonrası için ekleyerek gidicez yani dictionary de bulunan elemana ekleyerek
            bosdictionary[i] = len(bosdictionary) + 1
    lzwList = []
    intable = ""
    bit = 256
    for i in text:
        attd = intable+i
        if attd in bosdictionary:
            intable = attd
        else:
            lzwList.append(bosdictionary[intable])
            bosdictionary[attd] = bit
            bit += 1
            intable = i
    if intable != "":
        lzwList.append(bosdictionary[intable])
    return lzwList
 # simdi bunu bizim yeni bir sıkıştırılmış dosyaya yazdırmamız lazım
writefile("compressed.txt", ' '.join(map(str, lzwCompress(text))))

#şimdi hesaplamaları yapıp bunları bir txt dosyasına yazdırmalıyım
ilk = len(text)
son = len(lzwCompress(text))
sure = son/ilk

#txt dosyası açıp yazdırma kısımı
hesaplamafile = "lzwhesapla.txt"
hesapla = "Sikistirilmadan onceki :{} \nSikistirildiktan sonraki : {} \nSure : {}".format(ilk,son,sure)
writefile(hesaplamafile,hesapla)

# --- HUFFMAN CODE ---

#frekansları bir dictionary'ye atayalım
frekans = {}
for i in text:
    if i in frekans:
        frekans[i] += 1
    else:
        frekans[i] = 1
print("Frekans Dictionary: {}".format(frekans))

#Ağaç yapısı için düğüm oluşturuyorum
class dugum:
    sag = None

    def __init__(self,freq,karakter,sag=None,sol=None):
        self.freq=freq
        self.karakter=karakter
        self.sag=sag
        self.sol = sol
        self.yon = "" #0 ve 1 lerden oluscak


siralifrekans: list[int] = []

for i in frekans.values():
    #dictionarydeki valueları  aldim ve bunlari yeni diziye atayip siraladim
    siralifrekans.append(i)
siralifrekans.sort()
siralandi = []
siralandi = siralifrekans

#tree yapısını oluşturmaya çalışma
k = 0
for k in range(0,len(siralandi),2):
    dugum.sag = siralandi[k]

m = 0
for m in range(0,len(siralandi),1):
    dugum.sol = siralandi[m]


#tree yi yazdirma

w = 0
while w<len(siralandi)/2:
    if dugum is not None:
        print(dugum.sag)
        print(dugum.sol)
    w +=1

