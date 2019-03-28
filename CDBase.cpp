//
//  CDBase.cpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//
#include "CDBase.hpp"
#include "kernel.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <io.h>
#ifdef __APPLE__
#include <sys/uio.h>
#else
#include <sys/io.h>
#endif
//#include <conio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <memory.h>
#include <iomanip>

using namespace std;

CDBase::CDBase(){}
CDBase::~CDBase(){}

void CDBase::__Show(){

    if(!(fp=fopen(fn,"rb")))
    {
        cout << ("Ошибка! Файл не может быть создан.\n") << endl;
        exit(1);
    }
    __TableCaption();
    fseek(fp,0,SEEK_SET);
    while(1){
        __ReadFile();
        if(feof(fp)) break;
        else __ShowStud();
    }
    __TableBottom(-1);
    fclose(fp);
}

void CDBase::__Add(){
    while(1){
        STUD.num=__FindMaxNum()+1;
        __AddStud();
        if(!__Check()){
            if(!(fp=fopen(fn,"ab+")))
            {
                cout << ("Ошибка! Файл не может быть создан.\n") << endl;
                exit(1);
            }
            __WriteFile();
            fclose(fp);
            return;
        }
        else cout << ("Такая запись уже существует. Повторите ввод.\n") << endl;
    }
}

void CDBase::__Del(){
    FILE *temp;
    int pr=0,number;
    int counter=0;
    while(1){
        cout << ("\nМЕНЮ УДАЛЕНИЯ\n1 - Удаление\n2 - Назад\n-> ") << endl;
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                cout << "id -> " << endl;
                number=__GetInt(cin);
                if(!(fp=fopen(fn,"rb")))
                {
                    cout << ("Ошибка! Файл не может быть создан.\n") << endl;
                    exit(1);
                }
                while(__ReadFile()){
                    if(feof(fp)) break;
                    if(STUD.num==number){
                        __TableCaption();
                        __ShowStud();
                        __TableBottom(1);
                        rewind(fp);
                        if(__BoolMenu()){
                            pr=1; break;
                        }
                        else return;
                    }
                }
                if(!pr){
                    cout << ("Нет данных\n") << endl;
                    fclose(fp);
                    break;
                }
                if(pr){
                    if(!(temp=fopen("temp.$$$","wb"))){
                        cout << ("\nОшибка! Временный файл не может быть открыт.\n") << endl;
                        exit(1);
                    }
                    while(__ReadFile()){
                        if(feof(fp)) break;
                        if(STUD.num!=number)
                            fwrite(&STUD,sizeof(STUD),1,temp);
                    }
                    fclose(fp);
                    fclose(temp);
                    if(remove(fn)==-1){
                        perror("remove");
                        return;
                    }
                    if(rename("temp.$$$",fn)==-1){
                        perror("rename");
                        return;
                    }
                    cout << ("запись удалена...\n") << endl;
                    return;
                }
                break;
            case 2:
                return;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..2\n") << endl;
                break;
        }
    }
}

void CDBase::__Edit(){
    int pr=0,counter=0;
    int number,size=sizeof(STUD);
    fpos_t filepos;
    while(1){
        cout << ("\nМЕНЮ РЕДАКТИРОВАНИЯ\n1 - Редактирование\n2 - Назад\n-> ") << endl;
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                cout<<"id ->";
                number=__GetInt(cin);
                if(!(fp=fopen(fn,"rb+")))
                {
                    cout << ("Ошибка! Файл не может быть создан.\n") << endl;
                    exit(1);
                }
                while(__ReadFile()){
                    if(feof(fp)) break;
                    if(STUD.num==number){
                        __TableCaption();
                        __ShowStud();
                        __TableBottom(1);
                        if(__BoolMenu()) pr=1 ;
                        else return;
                        fseek(fp,-1*size,1);
                        fgetpos(fp,&filepos);
                        break;
                    }
                }
                if(!pr){
                    cout << ("Нет данных\n") << endl;
                    break;
                }
                if(pr){
                    while(1){
                        __AddStud();
                        if (!__Check()){
                            fsetpos(fp, &filepos); //  разобраться с номером позиции
                            __WriteFile();
                            break;
                        }
                        else cout << ("Такая запись уже существует\n") << endl;
                    }
                }
                fclose(fp);
                break;
            case 2:
                return;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..2\n") << endl;
                break;
        }
    }
}

void CDBase::__Find(){
    int pr=0,number=0;
    int counter=0;
    char string[25];
    while(1){
        cout << ("\nМЕНЮ ПОИСКА\n1 - id\n2 - Фамилия И.О.\n3 - Назад\n-> ") << endl;
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                cout<<"id -> ";
                number=__GetInt(cin);
                if(!(fp=fopen(fn,"rb")))
                {
                    cout << ("Ошибка! Файл не может быть создан.\n") << endl;
                    exit(1);
                }
                while(__ReadFile()){
                    if(feof(fp)) break;
                    if(STUD.num==number){
                        __TableCaption();
                        __ShowStud();
                        __TableBottom(1);
                        pr=1;
                    }
                }
                if(!pr){
                    cout << ("Нет данных\n") << endl;
                    break;
                }
                fclose(fp);
                break;
            case 2:
                cout << ("Фамилия И.О.: ") << endl;
                cin.getline(string,25);
                if(!(fp=fopen(fn,"rb")))
                {
                    cout << ("Ошибка! Файл не может быть создан.\n") << endl;
                    exit(1);
                }
                while(__ReadFile()){
                    if(feof(fp)) break;
                    if(!strcmp(STUD.Name,string)){
                        __TableCaption();
                        __ShowStud();
                        __TableBottom(1);
                        pr=1;
                    }
                }
                if(!pr){
                    cout << ("Нет данных\n") << endl;
                    break;
                }
                fclose(fp);
                break;
            case 3:
                return;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..3\n") << endl;
                break;
        }
    }
}

void __Dormitory(CDBase &obj){
    int counter=0,max=0,out=0;
    double min_money=0;
    while(out!=1){
        cout << ("\nОБЩЕЖИТИЕ\n") << endl;
        cout << ("1 - Студенты нуждающиеся в общежитии\n") << endl;
        cout << ("2 - Студенты вне очереди попавшие в общежитие\n") << endl;
        cout << ("3 - Назад\n") << endl;
        if(!(obj.fp=fopen(obj.fn,"rb")))
        {
            cout << ("Ошибка! Файл не может быть создан.\n") << endl;
            exit(1);
        }
//        obj.__OpenFile("rb");
//        __RussianMessage("-> ");
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                obj.__TableCaption();
                max=0;
                while(obj.__ReadFile()){
                    if(feof(obj.fp)) break;
                    if(obj.STUD.signDormitory==1){
                        obj.__ShowStud();
                        max++;
                    }
                }
                obj.__TableBottom(max);
                fclose(obj.fp);
                break;
            case 2:
                cout << ("Минимальный доход студента\n-> ") << endl;
                min_money=__GetDouble(cin);
                obj.__TableCaption();
                max=0;
                while(obj.__ReadFile()){
                    if(feof(obj.fp)) break;
                    if(obj.STUD.signDormitory==1&&obj.STUD.money<=min_money){
                        obj.__ShowStud();
                        max++;
                    }
                }
                obj.__TableBottom(max);
                fclose(obj.fp);
                break;
            case 3:
                out=1;
                fclose(obj.fp);
                return;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..3\n") << endl;
                break;
        }
    }
    fclose(obj.fp);
}

bool CDBase::__ReadFile(){
    if(fread(&STUD,sizeof(STUD),1,fp)) return true;
    else return false;
}

bool CDBase::__WriteFile(){
    if(fwrite(&STUD,sizeof(STUD),1,fp)) return true;
    else return false;
}

// Поиск уже существующего студента
bool CDBase::__Check(){
    FILE *p_temp;
    STUD_INFO temp;
    bool pr=false;
    if(!(p_temp=fopen(fn,"rb"))){
        cout << ("\nОшибка! Файл не может быть открыт.\n") << endl;
        exit(1);
    }
    while(fread(&temp,sizeof(STUD),1,fp)){
        if(feof(p_temp)) break;
        if(!strcmp(STUD.Name,temp.Name)){
            pr=true; break;
        }
    }
    fclose(p_temp);
    return pr;
}

// Функция поиска максимального номера записи в файле БД
int  CDBase::__FindMaxNum(){
    int max=0;
    if(!(fp=fopen(fn,"rb")))
    {
        cout << ("Ошибка! Файл не может быть создан.\n") << endl;
        exit(1);
    }
    while(__ReadFile()){
        if(feof(fp)) break;
        if(STUD.num>max) max=STUD.num;
    }
    fclose(fp);
    return max;
}

// Возвращает количество записей в файле
int CDBase::__GetNumber(){
    FILE *fp;
    int fd,n=0;
    if(!(fp = fopen(fn,"rb"))){
        cout << ("\nОшибка! Файл не может быть открыт.\n") << endl;
        exit(1);
    }
    fd=fileno(fp);
    while (__ReadFile()) {
        if(feof(fp)) break;
        n++;
    }
//    n=filelength(fd)/sizeof(STUD);
    fclose(fp);
    return n;
}

void CDBase::__ShowStud(){
    cout << "| "<< setw(3) << setiosflags(ios::left);
    cout << STUD.num <<"| "<< setw(20);
    cout << STUD.Name <<"| "<< setw(9);
    cout << STUD.groupNumber <<"| "<< setw(5);
    cout << STUD.mark <<"| "<< setw(6);
    cout << STUD.money <<"| "<< setw(10);
    if(STUD.signDormitory==1) cout<<"+";
    else cout << "-";
    cout << "|\n";
}

void CDBase::__AddStud(){
    int counter=0,out=0;
    cout << ("\nid: "); cout<<STUD.num<<endl;
    cout << ("Фамилия И.О.: "); cin.getline(STUD.Name,20);
    cout << ("Номер группы: "); cin.getline(STUD.groupNumber,6);
    cout << ("Средний балл: "); STUD.mark=__GetDouble(cin);
    cout << ("Доход: "); STUD.money=__GetDouble(cin);
    while(out!=1){
        cout << ("Нужда в общежитии:\n1 - Да, 2 - Нет\n-> ") << endl;
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                STUD.signDormitory=1;
                out=1; break;
            case 2:
                STUD.signDormitory=0;
                out=1; break;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..2\n\n") << endl;
                break;
        }
    }
}

void CDBase::__TableCaption(){
    cout << ("\nСодержимое Базы Данных:\n");
    cout << "+----+---------------------+----------+------+-------+-----------+\n";
    cout << "| "<< setw(3) << setiosflags(ios::left);
    cout << ("id");
    cout << "| " << setw(29);
    cout << ("Фамилия И.О.");
    cout << "| " << setw(17);
    cout << ("№ группы");
    cout << "| " << setw(9);
    cout << ("Балл");
    cout << "| " << setw(11);
    cout << ("Доход");
    cout << "| " << setw(19);
    cout << ("Общежитие");
    cout << "|\n";
    cout << "+----+---------------------+----------+------+-------+-----------+\n";
}

void CDBase::__TableBottom(int max){
    int rows=0;
    rows=__GetNumber();
    if(rows==0||max==0){
        cout<<setw(5)<<"|"<<setw(22)<<"|"<<setw(11)<<"|";
        cout<<setw(7)<<"|"<<setw(8)<<"|"<<setw(12)<<"|"<<"|\n";
        cout<<"+----+---------------------+----------+------+-------+-----------+\n";
    }
    else cout<<"+----+---------------------+----------+------+-------+-----------+\n";
    if(max==-1) cout<<rows<<" rows in set ";
    else cout<<max<<" rows in set ";
    cout<<"("<<fn<<")\n";
}

bool CDBase::__BoolMenu(){
    int out=0;
    while(out!=1){
        cout << ("\nВы уверены?:\n1 - Да, 2 - Нет\n-> ");
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                out=1; break;
            case 2:
                out=1; return false;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..2\n");
                break;
        }
    }
    return true;
}

