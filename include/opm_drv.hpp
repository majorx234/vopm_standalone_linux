#ifndef OPM_DRV_HPP_
#define OPM_DRV_HPP_
#include <list>

using namespace std;

#define CHMAX 8
#define VOMAX 128

#define ERR_NOERR 0x0000
#define ERR_NOFILE 0x10000000
#define ERR_SYNTAX 0x20000000
#define ERR_LESPRM 0x30000000

#define CHSLOT8 15 // Midi 15Ch assigned OPM8ch

class OPDATA {
public:
  // EG-Level
  unsigned int TL;
  unsigned int D1L;
  // EG-ADR
  unsigned int AR;
  unsigned int D1R;
  unsigned int D2R;
  unsigned int RR;
  // DeTune
  unsigned int KS;
  unsigned int DT1;
  unsigned int MUL;
  unsigned int DT2;
  unsigned int F_AME;

  OPDATA(void);
};

class CHDATA {
public:
  unsigned int F_PAN; // L:0x80Msk R:0x40Msk
  unsigned int CON;
  unsigned int FL;
  unsigned int AMS;
  unsigned int PMS;
  unsigned int F_NE;
  unsigned int OpMsk;
  class OPDATA Op[4];
  char Name[16];
  unsigned int SPD;
  unsigned int PMD;
  unsigned int AMD;
  unsigned int WF;
  unsigned int NFQ;
  CHDATA(void);
  // ~CHDATA(void);
};

struct TBLMIDICH {
  int VoNum;    // tone number 0-.
  int Bend;     // Pitchbend -8192～+8191[signed 14bit]
  int Vol;      // Volume 0-127
  int Pan;      // L:0x80 Msk,R:0x40 Msk
  int BendRang; // Pitch bend range 1-? [semitone multiplier].
  int PMD;
  int AMD;
  int SPD;
  int OpTL[4]; // Relative change in OpTL
  unsigned int RPN;
  unsigned int NRPN;
  bool CuRPN;
  int BfNote;     // Previous note number (for portamento)
  int PortaSpeed; // portamento speed
  bool PortaOnOff;
  int LFOdelay;
};

class OPMDRV {
  // friend class VOPM;
private:
  unsigned int SampleTime; // Delta time specified by the host
  char CuProgName[64];     // programme name currently selected for the host
  int CuProgNum;           // programme number currently selected for HOST

  int NoisePrm;  // OPM noise parameter
  int MstVol;    // master volume
  bool PolyMono; // Poly true,Mono false
  class Opm *pOPM;
  int OpmClock; // clock of the OPM 0:3.58MHz 1:4MHz
  // CH Pronunciation management double linked list
  list<int> PlayCh, WaitCh;

  struct {
    int VoNum;     // onne number 0-.
    int MidiCh;    // Midi channel
    int Note;      // Note number (0-127,when not in use 255)
    int Vel;       // velocity
    int PortaBend; // Bend offset for portamento.
    int PortaSpeed;
    int LFOdelayCnt;
  } TblCh[CHMAX];

  struct TBLMIDICH TblMidiCh[16]; // Midi channel setup table

  int AtachCh(void);        // Add channel
  void DelCh(int);          // Channel deletion
  int ChkEnCh(void);        // Returns the available channels.
  int ChkSonCh(int, int);   // MidiCh and find the channel that is being
                            // pronounced from velocity.
  int NonCh(int, int, int); // MidiCh notes, pronounced with velocity.
  int NoffCh(int, int);     // MidiChとノートで消音する。

  void SendVo(int);       // send tone parameters to OPM
  void SendKc(int);       // Set tone scale data to OPM
  void SendTl(int);       // sets the channel volume
  void SendPan(int, int); // sets the Paning
  void SendLfo(int);

public:
  OPMDRV(class Opm *); // Constructor

  class CHDATA VoTbl[VOMAX]; // Tone table
                             // SLOT Set class per tone
  // TODO what is MidiProgramName in VST
  // MidiProgramName MidiProg[16];
  void setDelta(unsigned int);            // set delta time
  void NoteOn(int Ch, int Note, int Vol); // note on
  void NoteOff(int Ch, int Note);         // note off
  void NoteAllOff(int Ch);                // all notes off
  void ForceAllOff(int Ch);               // forced sound stop
  void ForceAllOff();                     // forced sound stop (on all channels)
  void BendCng(int Ch, int Bend);         // pitch bend change
  void VolCng(int Ch, int Vol);           // volume change
  void VoCng(int Ch, int VoNum);          // tone change
  void MsVolCng(int MVol);                // master volume change
  void PanCng(int Ch, int Pan);           // Pan change
  int Load(char *);                       // Load tone, LFO settings
  int Save(char *);                       // save tone, LFO settings
  int getProgNum(void);                   // get tone number
  void setProgNum(long);                  // set tone number
  void setProgName(char *);               // set  tone name
  char *getProgName(void);                // get tone name
  char *getProgName(int);                 // get tone name
  unsigned char getPrm(int);              // parameter set by index(Vst kNum)
  void setPrm(int, unsigned char); // parameter acquisition by index(Vst kNum)
  void setRPNH(int, int);
  void setNRPNH(int, int);
  void setRPNL(int, int);
  void setNRPNL(int, int);
  void setData(int, int);
  void setPoly(bool);
  void AutoSeq(int sampleframes);
  void setPortaSpeed(int MidiCh, int speed);
  void setPortaOnOff(int MidiCh, bool onoff);
  void setPortaCtr(int MidiCh, int Note);
  void setLFOdelay(int MidiCh, int data);

  ~OPMDRV(void); // destructor
  // TODO what is MidiProgramName in VST
  // long getMidiProgram(long channel, MidiProgramName *curProg);
  void ChDelay(int);

  void setCcTL_L(int MidiCh, int data, int OpNum);
  void setCcTL_H(int MidiCh, int data, int OpNum);

  void setCcLFQ_L(int MidiCh, int data);
  void setCcLFQ_H(int MidiCh, int data);

  void setCcPMD_L(int MidiCh, int data);
  void setCcPMD_H(int MidiCh, int data);

  void setCcAMD_L(int MidiCh, int data);
  void setCcAMD_H(int MidiCh, int data);

private:
  int CalcLim8(int VoData, int DifData);
  int CalcLim7(int VoData, int DifData);
  int CalcLimTL(int VoData, int DifData);

  void setAMD(int ch, int Amd);
  void setPMD(int ch, int Pmd);
  void setSPD(int ch, int Spd);
  void setTL(int ch, int Tl, int OpNum);
};
#endif // OPM_DRV_HPP_
