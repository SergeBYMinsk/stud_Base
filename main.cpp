//
//  main.cpp
//  stud_Base
//
//  Created by Sergey Sterlikov on 3/20/19.
//  Copyright © 2019 Sergey Sterlikov. All rights reserved.
//

#include "kernel.hpp"
#include "CInterface.hpp"

 int main (int numparm,char **m_parm){
     setlocale(LC_ALL,"rus");
    CInterface *p;
    if(numparm>1) p=new CInterface(numparm,m_parm);
    else p=new CInterface();
    p->__About();
    p->__Start();
}
