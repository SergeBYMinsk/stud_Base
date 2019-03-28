//
//  CInterface.cpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#include "CInterface.hpp"
#include "kernel.hpp"
#include <stdio.h>

//#include <conio.h>


using namespace std;


CInterface::CInterface(){}

CInterface::CInterface(int numparm,char **m_parm){
    if(numparm>1){
        switch(m_parm[1][1]){
            case 'o':
              // CFileStud::CFileStud(&m_parm[1][3]);
                // вызвать котструктор базового класса "CFileStud" с параметром, передать &m_parm[1][3] в качестве имени файла
                break;
            case 'c':
                // вызвать котструктор базового класса "CFileStud" с параметром, передать &m_parm[1][3] в качестве имени файла
                break;
            default:
                cout << ("Ошибка ввода! Неизвестный параметр!") << endl;
                break;
        }
    }
}

CInterface::~CInterface(){}

void CInterface::__Start(){
    int counter;
    int out=0;
    if(__IsSet()) __Menu();
    else{
        while(out!=1){
            cout << ("\n1 - Создать базу данных\n2 - Открыть базу данных\n") << endl;
            cout << ("3 - Выход\n-> ") << endl;
            counter=__GetInt(cin);
            switch(counter){
                case 1:
                    __CreateDataBase();
                    __Menu();
                    break;
                case 2:
                    __OpenDataBase();
                    __Menu();
                    break;
                case 3:
                    out=1;
                    cout << ("До свиданья!\n\n") << endl;
                    break;
                default:
                    cout << ("Ошибка ввода! Число должно быть в диапазоне 1..3\n") << endl;
                    break;
            }
        }
    }
}

void CInterface::__Menu(){
    int counter;
    while(1){
        cout << ("\nМЕНЮ:\n1 - Просмотреть\n2 - Добавить\n") << endl;
        cout << ("3 - Удалить\n4 - Редактировать\n5 - Поиск\n") << endl;
        cout << ("6 - Общежитие\n") << endl;
        cout << ("7 - О программе...\n8 - Назад\n-> ") << endl;
        counter=__GetInt(cin);
        switch(counter){
            case 1:
                __Show(); break;
            case 2:
                __Add(); break;
            case 3:
                __Del(); break;
            case 4:
                __Edit(); break;
            case 5:
                __Find(); break;
            case 6:
                __Dormitory(*this); break;
            case 7:
                __About(); break;
            case 8:
                return;
            default:
                cout << ("Ошибка ввода! Число должно быть в диапазоне 1..9\n") << endl;
                break;
        }
    }
}

void CInterface::__About(){
    cout << ("Copyright(C) 2019, Стерликов Сергей\n") << endl;
    cout << ("MyBase v2.1\n") << endl;
}








