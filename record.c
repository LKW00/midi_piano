#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NOTES 1000

static RecordedNote recordedNotes[MAX_NOTES];
static int noteCount = 0;
static int recording = 0;
static DWORD startTime;

void startRecording() {
    noteCount = 0;
    recording = 1;
    startTime = timeGetTime();
}

void stopRecording() {
    recording = 0;
}

void recordNote(BYTE state, BYTE note, BYTE velocity) {
    if (recording && noteCount < MAX_NOTES) {
        recordedNotes[noteCount].state = state;
        recordedNotes[noteCount].note = note;
        recordedNotes[noteCount].velocity = velocity;
        recordedNotes[noteCount].timestamp = timeGetTime() - startTime;
        noteCount++;
    }
}

void playRecording(HMIDIOUT hMidiDevice) {
    for (int i = 0; i < noteCount; i++) {
        Sleep(recordedNotes[i].timestamp - (i > 0 ? recordedNotes[i - 1].timestamp : 0));
        MIDISendShortMsg(hMidiDevice, recordedNotes[i].state, recordedNotes[i].note, recordedNotes[i].velocity);
    }
}