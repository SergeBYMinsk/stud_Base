//
//  kernel.cpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

//#include <windows.h>
#include <stdio.h>
#include <iomanip>
#include "kernel.hpp"
#include <iostream>

using namespace std;

// ввод целого числа
int __GetInt(istream &in){
    int value;
    while(1){
        in>>value;
        if(in.peek()=='\n'){
            in.get(); break;
        }
        else{
            cout << ("повторите ввод (ожидается целое число):\n") << endl;
            in.clear();
            while(in.get()!='\n'){};
        }
    }
    return value;
}

// ввод вещественного числа
double __GetDouble(istream &in){
    double value;
    while(1){
        in>>value;
        if(in.peek()=='\n'){
            in.get(); break;
        }
        else{
            cout << ("повторите ввод (ожидается вещественное число):\n") << endl;
            in.clear();
            while(in.get()!='\n'){};
        }
    }
    return value;
}

// русский текст в консоли
void __RussianMessage(char *str){
    char message[100];
    setlocale(LC_ALL, "ru");
    cout << message;
}


