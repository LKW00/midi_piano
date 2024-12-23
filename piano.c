#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

#include "piano.h"
#include "record.h"
#pragma comment (lib, "winmm.lib")

BYTE pianoKey[NKEY] = {
    0x5A, 0x53, 0x58, 0x44, 0x43,
    0x56, 0x47, 0x42, 0x48, 0x4E, 0x4A, 0x4D,
    0x51, 0x32, 0x57, 0x33, 0x45,
    0x52, 0x35, 0x54, 0x36, 0x59, 0x37, 0x55,
    0x49, 0x39, 0x4F, 0x30, 0x50
};

char instName[][NINSTRUMENT] = {
    "Acoustic Grand", "Bright Acoustic", "Electric Grand", "Honky-Tonk",
    "Electric Piano 1", "Electric Piano 2", "Harpsichord", "Clav",
    "Celesta", "Glockenspiel", "Music Box", "Vibraphone",
    "Marimba", "Xylophone", "Tubular Bells", "Dulcimer",
    "Drawbar Organ", "Percussive Organ", "Rock Organ", "Church Organ",
    "Reed Organ", "Accordion", "Harmonica", "Tango Accordion",
    "Electric Guitar(nylon)", "Acoustic Guitar(steel)", "Electric Guitar(jazz)", "Electric Guitar(clean)",
    "Electric Guitar(muted)", "Overdriven Guitar", "Distortion Guitar", "Guitar Harmonics",
    "Acoustic Bass", "Electric Bass(finger)", "Electric Bass(pick)", "Fretless Bass",
    "Slap Bass 1", "Slap Bass 2", "Synth Bass 1", "Synth Bass 2",
    "Violin", "Viola", "Cello", "Contrabass",
    "Tremolo Strings", "Pizzicato Strings", "Orchestral Harp", "Timpani",
    "String Ensemble 1", "String Ensemble 2", "SynthStrings 1", "SynthStrings 2",
    "Choir Aahs", "Voice Oohs", "Synth Voice", "Orchestra Hit",
    "Trumpet", "Trombone", "Tuba", "Muted Trumpet",
    "French Horn", "Brass Section", "SynthBrass 1", "SynthBrass 2",
    "Soprano Sax", "Alto Sax", "Tenor Sax", "Baritone Sax",
    "Oboe", "English Horn", "Bassoon", "Clarinet",
    "Piccolo", "Flute", "Recorder", "Pan Flute",
    "Bottle", "Shakuhachi", "Whistle", "Ocarina",
    "Lead 1 (square)", "Lead 2 (sawtooth)", "Lead 3 (calliope)", "Lead 4 (chiff)",
    "Lead 5 (charang)", "Lead 6 (voice)", "Lead 7 (fifths)", "Lead 8 (bass+lead)",
    "Pad 1 (new age)", "Pad 2 (warm)", "Pad 3 (polysynth)", "Pad 4 (choir)",
    "Pad 5 (bowed)", "Pad 6 (metallic)", "Pad 7 (halo)", "Pad 8 (sweep)",
    "FX 1 (비)", "FX 2 (soundtrack)", "FX 3 (crystal)", "FX 4 (atmosphere)",
    "FX 5 (brightness)", "FX 6 (goblins)", "FX 7 (echoes)", "FX 8 (sci-fi)",
    "Sitar", "Banjo", "Shamisen", "Koto",
    "Kalimba", "Bagpipe", "Shana", "Shanai",
    "Tinkle Bell", "Agogo", "Steel Drums", "Woodblock",
    "Taiko Drum", "Melodic Tom", "Synth Drum", "Reverse Cymbal",
    "Guitar Fret Noise", "Breath Noise", "Seashore", "Bird Tweet",
    "Telephone Ring", "Helicopter", "Applause", "Gunshot"
};

void CALLBACK MidiOutProc(HMIDIOUT hMidiDevice, UINT uMsg, DWORD Instance, DWORD Param1, DWORD Param2)
{
}

void MIDIOutputError(MMRESULT mmResult)
{
    char szErrMsg[128];
    midiOutGetErrorText(mmResult, szErrMsg, sizeof(szErrMsg));
    MessageBox(0, szErrMsg, "Midi Error!!!", MB_OK);
}

long MIDIGetDevID(HMIDIOUT hMidiDevice)
{
    UINT uDeviceID;
    MMRESULT mmResult = midiOutGetID(hMidiDevice, &uDeviceID);
    if (mmResult != MMSYSERR_NOERROR)
    {
        MIDIOutputError(mmResult);
        return -1;
    }
    return (long)uDeviceID;
}

void MIDIGetDevCaps(HMIDIOUT hMidiDevice, MIDIOUTCAPS* Caps)
{
    long lDeviceID;
    MMRESULT mmResult;
    lDeviceID = MIDIGetDevID(hMidiDevice);
    if (lDeviceID < 0) return;
    mmResult = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));
    if (mmResult != MMSYSERR_NOERROR)
    {
        MIDIOutputError(mmResult);
    }
}

HMIDIOUT MIDIOpen(WORD wMidiNum)
{
    WORD wMidiMax = 0;
    MMRESULT mmResult = 0;
    HMIDIOUT hMidiDevice = NULL;
    wMidiMax = midiOutGetNumDevs();
    if (wMidiNum >= wMidiMax) wMidiNum = 0;
    mmResult = midiOutOpen(&hMidiDevice, wMidiNum, (DWORD_PTR)(MidiOutProc), (DWORD_PTR)NULL, CALLBACK_FUNCTION);
    if (mmResult != MMSYSERR_NOERROR)
    {
        MIDIOutputError(mmResult);
        return NULL;
    }
    return hMidiDevice;
}

LRESULT MIDIClose(HMIDIOUT hMidiDevice)
{
    MMRESULT mmResult;
    mmResult = midiOutClose(hMidiDevice);
    if (mmResult != MMSYSERR_NOERROR)
    {
        MIDIOutputError(mmResult);
        return FALSE;
    }
    return TRUE;
}

void MIDISendShortMsg(HMIDIOUT hMidiDevice, BYTE byteState, BYTE byteNote, BYTE byteValo)
{
    MIDIShortMSG sMsg;
    sMsg.stMIDIData.byteVelocity = byteValo;
    sMsg.stMIDIData.byteNote = byteNote;
    sMsg.stMIDIData.byteState = byteState;
    sMsg.stMIDIData.byteNULL = 0;
    midiOutShortMsg(hMidiDevice, sMsg.dwMIDIData);
    recordNote(byteState, byteNote, byteValo); // 녹음 기능 통합
}

void MIDIALLChannelSoundOff(HMIDIOUT hMidiDevice)
{
    BYTE channel;
    for (channel = 0; channel < 16; channel++)
    {
        MIDISendShortMsg(hMidiDevice, (BYTE)(0xB0 + channel), 0x78, 0);
    }
}

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void getCursorPosition(int* rows, int* cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        *rows = csbi.dwCursorPosition.Y; // Y는 0 기반
        *cols = csbi.dwCursorPosition.X; // X는 0 기반
    }
    else {
        *rows = -1;
        *cols = -1;
    }
}

void piano()
{
    int loop;
    BYTE key = 0;
    BYTE instrument = 0;
    BYTE volume = 127;
    BYTE octave = 48;
    BYTE velocity = 120;
    BYTE pedalState = 0; // 페달 상태 변수 추가 (0: 해제, 1: 눌림)


    int row, col;

    HMIDIOUT hMidiDevice;

    BYTE pianoKeyOnOff[NKEY] = { 0 };

    hMidiDevice = MIDIOpen(0);
    printf("[ESC] : Exit\n\n");
    printf(" Instrument : %-25s Octave : %03d Volume : %03d\n\n", instName[0], octave, volume);
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  |S| |D|  |  |G| |H| |J|  |  |2| |3|  |  |5| |6| |7|  |  |9| |0|  | ");
    puts(" |  ┕━┙ ┕━┙  |  ┕━┙ ┕━┙ ┕━┙  |  ┕━┙ ┕━┙  |  ┕━┙ ┕━┙ ┕━┙  |  ┕━┙ ┕━┙  | ");
    puts(" |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | ");
    puts(" | Z | X | C | V | B | N | M | Q | W | E | R | T | Y | U | I | O | P | ");
    puts(" ┕━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┙ ");

    MIDIALLChannelSoundOff(hMidiDevice);
    MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);

    loop = 1;
    while (loop)
    {
        if (GetKeyState(VK_ESCAPE) < 0)
            loop = 0;
        else if (GetKeyState(VK_RIGHT) < 0)
        {
            if (instrument < (NINSTRUMENT - 1))
                instrument += 1;
            MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
            getCursorPosition(&row, &col);
            gotoxy(col + 1, row - 10);
            printf("Instrument:%-24s", instName[instrument]);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_LEFT) < 0)
        {
            if (instrument != 0)
                instrument -= 1;
            MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
            getCursorPosition(&row, &col);
            gotoxy(col + 1, row - 10);
            printf("Instrument:%-24s", instName[instrument]);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_UP) < 0)
        {
            if (octave < (NNOTE - NKEY))
                octave += 12;
            getCursorPosition(&row, &col);

            gotoxy(col + 40, row - 10);
            printf("Octave : %03d", octave);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_DOWN) < 0)
        {
            if (octave != 0)
                octave -= 12;
            getCursorPosition(&row, &col);
            gotoxy(col + 40, row - 10);
            printf("Octave : %03d", octave);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_OEM_PLUS) < 0)
        {
            if (volume < (NVOLUME - 1))
                volume += 1;
            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            getCursorPosition(&row, &col);
            gotoxy(col + 53, row - 10);
            printf("Volume : %03d", volume);
            gotoxy(col, row);
            Sleep(150);
        }
        else if (GetKeyState(VK_OEM_MINUS) < 0)
        {
            if (volume != 0)
                volume -= 1;
            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            getCursorPosition(&row, &col);
            gotoxy(col + 53, row - 10);
            printf("Volume : %03d", volume);
            gotoxy(col, row);
            Sleep(150);
        }
        else if (GetKeyState(VK_SPACE) < 0) { // Spacebar for pedal
            if (pedalState == 0) {
                pedalState = 1; // 페달 활성화
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 127); // Sustain Pedal On
            }
        }else {
            if (pedalState == 1) {
                pedalState = 0; // 페달 비활성화
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 0); // Sustain Pedal Off
                MIDIALLChannelSoundOff(hMidiDevice); // 모든 채널의 음 정리
            }
        }
        
        for (key = 0; key < NKEY; key++)
        {
            if (GetKeyState(pianoKey[key]) < 0)
            {
                if (pianoKeyOnOff[key] == 0)
                {
                    pianoKeyOnOff[key] = 1;
                    MIDISendShortMsg(hMidiDevice, 0x90, (BYTE)(octave + key), velocity);
                }
            }
        }
        for (key = 0; key < NKEY; key++)
        {
            if (!(GetKeyState(pianoKey[key]) < 0))
            {
                if (pianoKeyOnOff[key] != 0)
                {
                    pianoKeyOnOff[key] = 0;
                    MIDISendShortMsg(hMidiDevice, 0x80, (BYTE)(octave + key), velocity);
                }
            }
        }
    }

    MIDIALLChannelSoundOff(hMidiDevice);
    MIDIClose(hMidiDevice);
}