//
//  CFileStud.hpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#include <stdio.h>

class CFileStud{
protected:
    char fn[80]; // имя базы данных
    FILE *fp;
public:
    CFileStud();
    CFileStud(char *);
    ~CFileStud();
    void __OpenDataBase();
    void __CreateDataBase();
    bool __IsSet();
    void __OpenFile(char *);
};
