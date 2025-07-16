#Sena Yaman 20010011013 ÖDEV-3 HUFFMAN TREE

#binary = 01100001011000100110001101100100011000010110001001100011011001000110000101100001011000010110001001100010

#1 ve 0 lardan olusan bit dizisini aldım
bitler = input("Bit dizisini giriniz ")
# 8 erli ayırması kolay olsun diye bu girileni boş diziye atıcam
bitDizi=[]

#bitleri 8 erli ayırıyorum  ve boş diziye atıyorum
for i in range(0,len(bitler),8):
    bit = bitler[i:i+8]
    bitDizi.append(bit)
print("Bit Dizi : {}".format(bitDizi))

frekansDizi = []
#Ayırdığım 8'erli bitleri ASCİİ'ye çeviriyorum
for i in bitDizi:
    frekansDizi.append(chr(int(i,2)))
# Şimdi benim bu bulduğum harfleri bir boş diziye atadım oradan frekanslarını buldurmam lazım
#frekansları bir dictionary'ye atayalım
frekans = {}
for i in frekansDizi:
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


siralifrekans = []

for i in frekans.values():
    #dictionarydeki valueları  aldim ve bunlari yeni diziye atayip siraladim
    siralifrekans.append(i)
siralifrekans.sort()
siralandi = []
siralandi = siralifrekans

#tree yapısını oluşturmaya çalışma
k = 0
for k in range(0,len(siralandi),2):
    dugum.sag.freq = siralandi[k]


m = 1
for m in range(0,len(siralandi),2):
    dugum.sol = siralandi[m]


#tree yi yazdirma

w = 0
while w<len(siralandi)/2:
    if dugum is not None:
        print(dugum.sag)
        print(dugum.sol)
    w +=1

