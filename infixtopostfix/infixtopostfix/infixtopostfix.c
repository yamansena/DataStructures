#include <stdio.h>
#include <stdlib.h>

//SENA YAMAN 20010011013 ODEV3 INFIX TO POSTFIX

//stack struct

struct stack
{
    char data; //stackdaki veriler
    struct stack* next; //baglý liste oldugu icin
    struct stack* last; //dairesel baglý liste oldugu icin
};

struct stack* top=NULL; //en ustteký degerý tutmamý saglayacak (LIFO)

//stackler olusturmam icin:

struct stack* stackKontrol()
{
    //yer ayiriyorum
    struct stack* stack = (struct stack*)malloc(sizeof(struct stack));
    //stack bos mu kontrolu
    if(stack==NULL)
    {
        printf("Stack bos!");
        return 1;
    }
    //ilk stack old icin nextini null yapicam
    stack->next=NULL;
    //dairesel old icin lastinida self olarak yapicam
    stack->last=stack;
    return stack;

}

//push fonksiyonu ile stack'e ekleme yapicam

void push(char veri)
{
    struct stack* eklenecek;
    eklenecek = (struct stack*)malloc(sizeof(struct stack));
    eklenecek->data = veri;
    eklenecek->next = NULL;

    if (top == NULL)
    {
        // Eğer stack boşsa, yeni elemanı ekleyin ve last'i kendisine ayarlayın (çünkü dairesel bağlı liste).
        eklenecek->last = eklenecek;
        top = eklenecek;
    }
    else
    {
        // Stack doluysa, yeni elemanın last'ini mevcut son elemanın last'ine ayarlayın.
        eklenecek->last = top->last;
        // Yeni elemanı stack'in sonuna ekleyin.
        top->next = eklenecek;
        // Yeni elemanı stack'in sonu (top) olarak ayarlayın.
        top = eklenecek;
    }

}

//silme fonksiyonu
char pop()
{
    char item;

    if (top == NULL)
    {
        printf("Stack boş, silme işlemi yapılamaz!");
        return '\0'; // Boş stack'ten çıkarma işlemi başarısız olduğunda bir değer döndürülmeliyim
    }

    item = top->data;

    struct stack* temp = top;
    top = top->next;

    free(temp); // Hafızayı bosalt
    // LIFO mantığına uygun olarak en üstteki elemanı pop yaptığınız için, top'u degistirmeliyim
    // top'i kontrol et
    if (top == NULL)
    {
        // Stack boşsa last'i de NULL olarak ayarla
        top = NULL;
    }

    return item;
}

//operator = +,-,/,*,(,)
//operand = 1....9

//oncelik fonksiyonu
//operator kontrolü

int oncelik(char operatorler)
{
    switch(operatorler)
    {
    case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    default:
        return -1;
    }
}


//operand kontrolü
int kontrolOperand(char karakter)
{
    //karakter degiskeninin a ile z arasinda olup olmadigini kontrol edicem
    if((karakter>='a' && karakter <='z')|| (karakter>='A' && karakter <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//infix'den postfix'e ceviren fonksiyon

void infixToPostfix(const char* infix,FILE* cikti)
{
    int i;
    //simdi benim onceligim ( 'di ) bunu gorene kadar stack'e push yapicam
    //infix ifadeyi dizi'ye atarsam dolasmam daha kolay olur
    for(i=0; infix[i]; i++)
    {
        //operand'a infix[i] parametresini gondericem
        if(kontrolOperand(infix[i]))
        {
            fprintf(cikti,"%c",infix[i]);
        }
        else if(infix[i]=='(')
        {
            push(infix[i]);
        }
        else if(infix[i]==')')
        {
            while (top != NULL && top->data != '(')
            {
                fprintf(cikti,"%c", pop());
                return;
            }

            if (top != NULL && top->data != '(')
            {
                fprintf(cikti,"İnfix ifadesi geçersiz");
                return;
            }
            else
            {
                pop(); // '(' isaretini stack'ten cikar
            }
        }
        else
        {
            while (top != NULL && oncelik(infix[i]) <= oncelik(top->data))
            {
                fprintf(cikti, "%c", pop());
            }
            push(infix[i]);

        }
        while (top != NULL)
        {
            fprintf(cikti, "%c", pop());
        }
    }

}



int main()
{
    //Dosya okuma islemleri

    char* infixFile= 'infix.txt';
    char* postfixFile = 'postfix.txt';
    //okuma modunda aciyorum
    FILE* GinfixFile = fopen(infixFile,"r");
    //dosya bossa hata ver
    if(GinfixFile==NULL)
    {
        printf("Dosya bos! İnfix bir ifade giriniz !");
        return 1;

    }
    FILE* cFile = fopen(postfixFile,"w");
    if(cFile == NULL)
    {
        printf("Dosya acilamadi!");
        fclose(GinfixFile);
        return 1;
    }

    //infix ifadeyi dizi'ye atiyorum
    char infix[100];
    fgets(infix,sizeof(infix),GinfixFile);
    infixToPostfix(infix,cFile);
    //dosyalarla isim bittigi icin kapatiyorum
    fclose(GinfixFile);
    fclose(cFile);

    return 0;


}
