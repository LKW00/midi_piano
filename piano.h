#pragma once

#include <windows.h>

#define NKEY 29
#define NINSTRUMENT 128
#define NNOTE 128
#define NVOLUME 128

typedef struct
{
    BYTE byteState;
    BYTE byteNote;
    BYTE byteVelocity;
    BYTE byteNULL;
} MIDIShortMSG_ST;

typedef union
{
    DWORD dwMIDIData;
    MIDIShortMSG_ST stMIDIData;
} MIDIShortMSG;

extern BYTE pianoKey[NKEY];
extern char instName[][NINSTRUMENT];

void piano();
void MIDISendShortMsg(HMIDIOUT hMidiDevice, BYTE byteState, BYTE byteNote, BYTE byteValo);
HMIDIOUT MIDIOpen(WORD wMidiNum);
LRESULT MIDIClose(HMIDIOUT hMidiDevice);
void MIDIALLChannelSoundOff(HMIDIOUT hMidiDevice);