#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "TString.h"


class TError
{
protected:
  TString err;
  TString func;
  TString fil;
  int lin;
public:
    TError(char* error, char* function, char* file, int line);
    TError(const char* error, const char* function, const char* file, int line);

    void what();
};