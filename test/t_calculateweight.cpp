
#include <iostream>
#include <stdio.h>

#include <unistd.h>

#include "ZCalculatedWeight.h"


int main()
{

  A7::ZCalculatedWeight CalWeight;

  CalWeight.SetModuleProtocol(A7::ZCalculatedWeight::PROTOCOL_ROTA2);

  getchar();
  CalWeight.SetModuleProtocol(A7::ZCalculatedWeight::PROTOCOL_ROTA1);

  getchar();
  CalWeight.SetModuleProtocol(A7::ZCalculatedWeight::PROTOCOL_TSC);

  getchar();
  return 0;
}
