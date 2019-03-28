//
//  CDBase.hpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//


#include "CFileStud.hpp"
#include "CStudent.hpp"
#include <iostream>
#include <iomanip>

class CDBase:public CFileStud,public CStudent{
private:
    int counter;
public:
    CDBase();
    ~CDBase();
    void __Show();
    void __Add();
    void __Del();
    void __Edit();
    void __Find();
    int __FindMaxNum();
    int __GetNumber();
    bool __Check();
    bool __ReadFile();
    bool __WriteFile();
    bool __BoolMenu();
    void __TableCaption();
    void __TableBottom(int);
    void __ShowStud();
    void __AddStud();
    friend void __Dormitory(CDBase &);
};


