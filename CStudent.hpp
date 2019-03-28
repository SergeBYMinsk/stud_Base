//
//  CStudent.hpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#define CStudent_hpp

#include <stdio.h>
// Структура, содержащая информацию о студенте
typedef struct _STUD_INFO{
    int num;
    char Name[20];
    char groupNumber[5];
    double mark;
    double money;
    bool signDormitory;
} STUD_INFO, LPSTUD_INFO;

class CStudent {
protected:
    STUD_INFO STUD;
public:
    CStudent();
    ~CStudent();
    virtual void __Show()=0;
    virtual void __Add()=0;
    virtual void __Del()=0;
    virtual void __Edit()=0;
    virtual void __Find()=0;
};
