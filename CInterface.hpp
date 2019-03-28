//
//  CInterface.hpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#include <stdio.h>
#include "CDBase.hpp"

class CInterface:public CDBase{
public:
    CInterface();
    CInterface(int,char **);
    ~CInterface();
    void __Start();
    void __Menu();
    void __About();
};
