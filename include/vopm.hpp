#ifndef VOPM_HPP_
#define VOPM_HPP_

#include <string.h>
enum {
  kNumPrograms = 128,
  kNumOutputs = 2,

  kCon = 0,
  kFL,
  kAMS,
  kPMS,
  kNFQ,
  kNE,
  kSPD,
  kAMD,
  kPMD,
  kWF,
  kOpMsk,

  // OP M1
  kM1TL,

  kM1AR,
  kM1D1R,
  kM1D1L,
  kM1D2R,
  kM1RR,
  kM1KS,
  kM1MUL,
  kM1DT1,
  kM1DT2,
  kM1F_AME,

  // OP C1
  kC1TL,
  kC1AR,
  kC1D1R,
  kC1D1L,
  kC1D2R,
  kC1RR,
  kC1KS,
  kC1MUL,
  kC1DT1,
  kC1DT2,
  kC1F_AME,
  // OP M2
  kM2TL,
  kM2AR,
  kM2D1R,
  kM2D1L,
  kM2D2R,
  kM2RR,
  kM2KS,
  kM2MUL,
  kM2DT1,
  kM2DT2,
  kM2F_AME,
  // OP C2
  kC2TL,
  kC2AR,
  kC2D1R,
  kC2D1L,
  kC2D2R,
  kC2RR,
  kC2KS,
  kC2MUL,
  kC2DT1,
  kC2DT2,
  kC2F_AME,
  kNumParams,
  kMskM1,
  kMskC1,
  kMskM2,
  kMskC2,

  kFileLoad,
  kFileSave,
  kWf0,
  kWf1,
  kWf2,
  kWf3,
  kCon0,
  kCon1,
  kCon2,
  kCon3,
  kCon4,
  kCon5,
  kCon6,
  kCon7,
  kHdsw
};

class VOPM{
  VOPM();
  ~VOPM();
};

#endif // VOPM_HPP_
