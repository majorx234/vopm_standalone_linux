#include <stdio.h>
#include <float.h>
#include "opm.hpp"

#include "vopm.hpp"

const char TblLabel[kNumParams][8]={
  "Con","FL","AMS","PMS","NFQ", "NoiseEn",
  "SPD","AMD","PMD","WF","OpMsk",
  //OP M1
  "M1-TL","M1-AR","M1-D1R","M1-D1L","M1-D2R",
  "M1-RR","M1-KS","M1-MUL","M1-DT1","M1-DT2",
  "M1-AME",
  //OP C1
  "C1-TL","C1-AR","C1-D1R","C1-D1L","C1-D2R",
  "C1-RR","C1-KS","C1-MUL","C1-DT1","C1-DT2",
  "C1-AME",
  //OP M2
  "M2-TL","M2-AR","M2-D1R","M2-D1L","M2-D2R",
  "M2-RR","M2-KS","M2-MUL","M2-DT1","M2-DT2",
  "M2-AME",

  //OP C2
  "C2-TL","C2-AR","C2-D1R","C2-D1L","C2-D2R",
  "C2-RR","C2-KS","C2-MUL","C2-DT1","C2-DT2",
  "C2-AME"
};

VOPM::VOPM() {}

VOPM::~VOPM (){}
