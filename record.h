#pragma once
#include <windows.h>

typedef struct {
    BYTE state;
    BYTE note;
    BYTE velocity;
    DWORD timestamp;
} RecordedNote;

void startRecording();
void stopRecording();
void recordNote(BYTE state, BYTE note, BYTE velocity);
void playRecording(HMIDIOUT hMidiDevice);