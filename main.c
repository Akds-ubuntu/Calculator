
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <complex.h>
#define MAX_SIZE 100
#define MINUS 0
#define PLUS 1

 
double Sin(double x){
    return (round(sin(x)*1000000)/1000000);
}
struct opred{
    char type;// 0 для чисел,'-' для операций вычитания и т.д
    double value;//значение числа
};
// Узел связанного списка
struct Node
{
    struct opred data;               // целочисленные данные
    struct Node* next;      // указатель на следующий узел
};
int nodesCount;

// Вспомогательная функция для добавления элемента `x` в stack
void push(struct Node **top, struct opred x)        // вставляем в начало
{
    // выделяем новый узел в куче
    struct Node* node = NULL;
    node = (struct Node*)malloc(sizeof(struct Node));

    // проверяем, заполнен ли Stack (heap). Тогда вставка элемента будет
    // привести к переполнению stack
    if (!node)
    {
        printf("Heap Overflow\n");
        exit(-1);
    }

   // printf("Inserting %d\n", x);

    // устанавливаем данные в выделенном узле
    node->data = x;

    // устанавливаем указатель .next нового узла так, чтобы он указывал на текущий
    // верхний узел списка
    node->next = *top;

    // обновить верхний указатель
    *top = node;

    // увеличить размер stack на 1
    nodesCount += 1;
}
// Вспомогательная функция для проверки, пуст stack или нет
int isEmpty(struct Node* top) {
    return top == NULL;
}
// Вспомогательная функция для возврата верхнего элемента stack
struct opred peek(struct Node *top)
{
    // проверка на пустой stack
    if (!isEmpty(top)) {
        return top->data;
    }
    else {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }
}
// Вспомогательная функция для извлечения верхнего элемента из stack
struct opred pop(struct Node** top)        // удалить в начале
{
    struct Node *node;

    // проверка на опустошение stack
    if (*top == NULL)
    {
       // printf("вы ввели что то странное\n");
        exit(EXIT_FAILURE);
    }

    // принять к сведению данные верхнего узла
    struct opred x = peek(*top);

    //printf("Removing %d\n", x);

    node = *top;

    // обновляем верхний указатель, чтобы он указывал на следующий узел
    *top = (*top)->next;

    // уменьшить размер stack на 1
    nodesCount -= 1;

    // освободить выделенную память
    free(node);

    return x;
}
// Вспомогательная функция для возврата числа узлов stack
int size(void) {
    return nodesCount;
}
void maths(struct Node** Stack_s, struct Node** Stack_h,struct opred *item)//функция которая производит вычисления
{
    double a,b,c;
    a = pop(Stack_h).value;//вынимат верхний эллемент из стэка с числами
    switch(pop(Stack_s).type){
        case '+':
            b=pop(Stack_h).value;
            c=a+b;
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
            break;
        case '-':
            b=pop(Stack_h).value;
            c=b-a;
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
            
            break;
        case '*':
            b=pop(Stack_h).value;
            c=a*b;
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
           
            break;
        case '/':
            b=pop(Stack_h).value;
            if(a==0){
                printf("Otvet=ERROR!\n");
                break;
            }
            c=b/a;
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
            break;
        case '^':
            b=pop(Stack_h).value;
            c=pow(b,a);
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
            break;
        case 's':
            c=Sin(a);
            (*item).type='0';
            (*item).value=c ;
            push(Stack_h,*item);
            break;
    }
}
int getRang(char ch)//функция которая устанавливает приоритет операциям
{
    if ((ch=='+')||(ch=='-'))return 1;
    if ((ch=='*')||(ch=='/'))return 2;
    if (ch=='^')return 3;
    if(ch=='s')return 4;
    else return 0;
}

int main(){
    struct Node* Stack_s=NULL;//стэк с операции
    struct Node* Stack_h=NULL;//стэк с числами
    struct opred tip;
    setlocale(LC_ALL, "");//подключает русский язык
    char str[MAX_SIZE],ch,sp[3]={0};
    char number[MAX_SIZE]={0};
    char unknow[MAX_SIZE]={0};
    int i=0,flag=0;
    double value;
    double E=exp(1);
    printf("Введите строку: ");
    fgets(str,MAX_SIZE,stdin);// считываем строку с помощью fgets
    sp[0]=str[0];
    while(sp[0]!='\0'){
        sp[0]=str[i];
        if(sp[0]=='-'&& i==0){
            flag=1;//флаг который определяет отр число или нет
        }
        if((sp[0]>='0' && sp[0]<='9')||sp[0]=='.'){
            strcat(number, sp);//отделяет число
        }
        else if((sp[0]>='a' && sp[0]<='z')||(sp[0]>='A' && sp[0]<='Z')){
            strcat(unknow, sp);//отделяет переменные
        }
        else if(sp[0]=='+'||sp[0]=='-'||sp[0]=='*'||sp[0]=='/'||sp[0]=='^')//добовляет числа в стэк операции в стэк и пременные
        {
            if(isEmpty(Stack_s)){
                if(number[0]!='\0'){
                    if(flag==1){
                        value=-atof(number);
                        tip.type='0';
                        tip.value=value;
                        push(&Stack_h,tip);
                        printf("Stack_h=%lf\n",peek(Stack_h).value);
                        number[0]='\0';
                        
                    }
                    else if(flag==0){
                        value=atof(number);
                        tip.type='0';
                        tip.value=value;
                        push(&Stack_h,tip);
                        printf("Stack_h=%lf\n",peek(Stack_h).value);
                        number[0]='\0';
                        
                    }
                }
                if(number[0]=='\0'){
                    value=0;
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h,tip);
                    printf("Stack_h=%lf\n",peek(Stack_h).value);

                    
                }
                if(unknow[0]!='\0'){
                    if(unknow[0]=='E'&&unknow[1]=='\0'){
                        tip.type='0';
                        tip.value=E;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else if(unknow[0]=='P'&&unknow[1]=='I'&&unknow[2]=='\0'){
                        tip.type='0';
                        tip.value=M_PI;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else
                    {
                        printf("Введите переменную %s=",unknow);
                        scanf("%lf",&value);
                        tip.type='0';
                        tip.value=value;
                        push(&Stack_h, tip);
                        unknow[0]='\0';
                    }
                }
                if(i!=0){
                    ch=sp[0];
                    tip.type=ch;
                    tip.value=0;
                    push(&Stack_s,tip);
                    printf("Stack_s=%c\n",peek(Stack_s).type);
                }
            }
            else if(!isEmpty(Stack_s) && getRang(sp[0]) > getRang(peek(Stack_s).type)){
                if(number[0]!='\0'){
                    value=atof(number);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h,tip);
                    printf("Stack_h!=%lf\n",peek(Stack_h).value);
                    number[0]='\0';
                    
                }
                if(unknow[0]!='\0'){
                    if(unknow[0]=='E'&&unknow[1]=='\0'){
                        tip.type='0';
                        tip.value=E;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else if(unknow[0]=='P'&&unknow[1]=='I'&&unknow[2]=='\0'){
                        tip.type='0';
                        tip.value=M_PI;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else
                    {
                        printf("Введите переменную %s=",unknow);
                        scanf("%lf",&value);
                        tip.type='0';
                        tip.value=value;
                        push(&Stack_h, tip);
                        unknow[0]='\0';
                    }
                }
                ch=sp[0];
                tip.type=ch;
                tip.value=0;
                push(&Stack_s,tip);
                printf("Stack_s=%c\n",peek(Stack_s).type);
            }
            else if(!isEmpty(Stack_s) && getRang(sp[0]) <= getRang(peek(Stack_s).type)){
                if(number[0]!='\0'){
                    value=atof(number);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h,tip);
                    printf("Stack_h!=%lf\n",peek(Stack_h).value);
                    number[0]='\0';
                    
                }
                else if(unknow[0]!='\0'){
                    if(unknow[0]=='E'&&unknow[1]=='\0'){
                        tip.type='0';
                        tip.value=E;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else if(unknow[0]=='P'&&unknow[1]=='I'&&unknow[2]=='\0'){
                        tip.type='0';
                        tip.value=M_PI;
                        push(&Stack_h,tip);
                        unknow[0]='\0';
                    }
                    else
                    {
                        printf("Введите переменную %s=",unknow);
                        scanf("%lf",&value);
                        tip.type='0';
                        tip.value=value;
                        push(&Stack_h, tip);
                        unknow[0]='\0';
                    }
                }
                maths(&Stack_s,&Stack_h,&tip);
                ch=sp[0];
                tip.type=ch;
                tip.value=0;
                push(&Stack_s,tip);
                printf("Stack_s=%c\n",peek(Stack_s).type);
            }
        }
        else if(sp[0]=='\0'){
            if(number[0]!='\0'){
                value=atof(number);
                tip.type='0';
                tip.value=value;
                push(&Stack_h,tip);
                printf("Stack_h0=%lf\n",peek(Stack_h).value);
            }
            else if(unknow[0]!='\0'){
                if(unknow[0]=='E'&&unknow[1]=='\0'){
                    tip.type='0';
                    tip.value=E;
                    push(&Stack_h,tip);
                    unknow[0]='\0';
                }
                else if(unknow[0]=='P'&&unknow[1]=='I'&&unknow[2]=='\0'){
                    tip.type='0';
                    tip.value=M_PI;
                    push(&Stack_h,tip);
                    unknow[0]='\0';
                }
                else
                {
                    printf("Введите переменную %s=",unknow);
                    scanf("%lf",&value);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h, tip);
                    unknow[0]='\0';
                }
            }
        }
        else if(sp[0]=='('){
            ch=sp[0];
            tip.type=ch;
            tip.value=0;
            push(&Stack_s,tip);
            printf("Stack_s(=%c\n",peek(Stack_s).type);
        }
        else if(sp[0]==')'){
            if(number[0]!='\0'){
                if(flag==1){
                    value=-atof(number);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h,tip);
                    printf("Stack_h)=%lf\n",peek(Stack_h).value);
                    number[0]='\0';
                    
                }
                else if(flag==0){
                    value=atof(number);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h,tip);
                    printf("Stack_h)=%lf\n",peek(Stack_h).value);
                    number[0]='\0';
                    
                }
            }
            else if(unknow[0]!='\0'){
                if(unknow[0]=='E'&&unknow[1]=='\0'){
                    tip.type='0';
                    tip.value=E;
                    push(&Stack_h,tip);
                    unknow[0]='\0';
                }
                else if(unknow[0]=='P'&&unknow[1]=='I'&&unknow[2]=='\0'){
                    tip.type='0';
                    tip.value=M_PI;
                    push(&Stack_h,tip);
                    unknow[0]='\0';
                }
                else
                {
                    printf("Введите переменную %s=",unknow);
                    scanf("%lf",&value);
                    tip.type='0';
                    tip.value=value;
                    push(&Stack_h, tip);
                    unknow[0]='\0';
                }
            }
            while(peek(Stack_s).type!='(')
            {
                maths(&Stack_s,&Stack_h,&tip);
                printf("Stack_s(=%c\n",peek(Stack_s).type);
            }
            pop(&Stack_s).type;
        }
        i++;
    }
        while(!isEmpty(Stack_s))//производит решение пока не закончится стэк с операциями
        {
            maths(&Stack_s,&Stack_h,&tip);
        }
        printf("Ответ=%lf\n",pop(&Stack_h).value);//выводит конечный ответ
}

