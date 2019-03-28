//
//  CFileStud.cpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#include "CFileStud.hpp"
#include "kernel.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


CFileStud::CFileStud(){
    fn[0]=NULL;
}

CFileStud::CFileStud(char *file){
    
}

CFileStud::~CFileStud(){}

bool CFileStud::__IsSet(){
    if(fn[0]!=0) return true;
    else return false;
}


void CFileStud::__CreateDataBase(){
    cout << ("Введите имя новой БД: ") << endl;
    fflush(stdin);
    cin>>fn;
    strcat(fn,".txt");
    if(!(fp=fopen(fn,"wb"))){
        cout << ("Ошибка! Файл не может быть создан.\n") << endl;
        exit(1);
    }
    cout<<fn;
    cout << (" создан...\n") << endl;
    fclose(fp);
}

void CFileStud::__OpenDataBase(){
    cout << ("Введите имя БД: ") << endl;
    fflush(stdin);
    cin>>fn;
    strcat(fn,".txt");
    if(!(fp=fopen(fn,"rb")))
    {
        cout << ("Ошибка! Файл не может быть создан.\n") << endl;
        exit(1);
    }
    cout<< fn << endl;
    cout << (" открыт...\n");
    fclose(fp);
}



