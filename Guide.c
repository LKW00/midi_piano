#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "piano.h"
#include "Guide.h"
#include "score.h"

void displayPiano() {
    system("cls");
    printf("[ESC] : Exit\n\n");
    printf(" Instrument : %-25s Octave : %03d Volume : %03d\n\n", "Acoustic Grand", 48, 127);
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  | ");
    puts(" |  |S| |D|  |  |G| |H| |J|  |  |2| |3|  |  |5| |6| |7|  |  |9| |0|  | ");
    puts(" |  �Ʀ��� �Ʀ���  |  �Ʀ��� �Ʀ��� �Ʀ���  |  �Ʀ��� �Ʀ���  |  �Ʀ��� �Ʀ��� �Ʀ���  |  �Ʀ��� �Ʀ���  | ");
    puts(" |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | ");
    puts(" | Z | X | C | V | B | N | M | Q | W | E | R | T | Y | U | I | O | P | ");
    puts(" �Ʀ��������������������������������������������������������������������������������������������������������������������������������������� ");
}

void playSong(HMIDIOUT hMidiDevice, Note* song, int noteCount) {
    BYTE velocity = 120; // ���� ����

    for (int i = 0; i < noteCount; i++) {
        MIDISendShortMsg(hMidiDevice, 0x90, song[i].note, velocity); // ��ǥ ON
        displayNoteOnScore(song[i].note);
        Sleep(song[i].duration); // ��ǥ ����
        MIDISendShortMsg(hMidiDevice, 0x80, song[i].note, velocity); // ��ǥ OFF
        Sleep(50); // ��ǥ ���� ����
    }
    gotoxy(0, 12);
}

void Guide() {
    HMIDIOUT hMidiDevice = MIDIOpen(0); // MIDI ��ġ ����
    if (hMidiDevice == NULL) {
        printf("Failed to open MIDI device.\n");
        return;
    }

    Note song1[] = {
        {64, 600}, {62, 300}, {60, 450}, {62, 450}, {64, 450}, {64, 450},
        {64, 900}, {62, 450}, {62, 450}, {62, 900},  {64, 450}, {64, 450},
        {64, 900}, {64, 600}, {62, 300}, {60, 450}, {62, 450},{64, 450},
        {64, 450}, {64, 900}, {62, 450}, {62, 450}, {64, 600}, {62, 300},
        {60, 900}
    };

    Note song2[] = {
        {60, 500}, {60, 500}, {67, 500}, {67, 500}, {69, 500}, {69, 500}, {67, 1000},
        {65, 500}, {65, 500}, {64, 500}, {64, 500}, {62, 500}, {62, 500}, {60, 1000}
    };
    Note butterfly[] = {
    {67, 450}, {64, 450}, {64, 900}, {65, 450}, {62, 450}, {62, 900},            // �� �� �� �� �� ��
    {60, 450}, {62, 450}, {64, 450}, {65, 450}, {67, 450}, {67, 450}, {67, 900}, // �� �� �� �� �� �� �� ��
    {67, 450}, {64, 450}, {64, 450}, {64, 450}, {65, 450}, {62, 450}, {62, 900}, // �� �� �� �� �� �� ��
    {60, 450}, {64, 450}, {67, 450}, {67, 450}, {64, 450}, {64, 450}, {64, 900}, // �� �� �� �� �� �� ��
    {62, 450}, {62, 450}, {62, 450}, {62, 450}, {62, 450}, {64, 450}, {65, 900}, // �� �� �� �� �� �� ��
    {64, 450}, {64, 450}, {64, 450}, {64, 450}, {64, 450}, {65, 450}, {67, 900}, // �� �� �� �� �� �� ��
    {67, 450}, {64, 450}, {64, 900}, {65, 450}, {62, 450}, {62, 900},            // �� �� �� �� �� ��
    {60, 450}, {64, 450}, {67, 450}, {67, 450}, {64, 450}, {64, 450}, {64, 900}  // �� �� �� �� �� �� �� 
    };
    Note schoolbell[] = {
        {67, 450}, {67, 450}, {69, 450}, {69, 450}, {67, 450}, {67, 450}, {64, 900}, // �� �� �� �� �� �� ��
        {67, 450}, {67, 450}, {64, 450}, {64, 450}, {62, 1350},                       // �� �� �� �� ��
        {67, 450}, {67, 450}, {69, 450}, {69, 450}, {67, 450}, {67, 450}, {64, 900}, // �� �� �� �� �� �� ��
        {67, 450}, {64, 450}, {62, 450}, {64, 450}, {60, 1350}                       // �� �� �� �� ��

    };

    int choice;
    printf("Select a song:\n");
    printf("1. ���� ���� �����\n");
    printf("2. ��¦ ��¦ ������\n");
    printf("3. �����\n");
    printf("4. �б���\n");
    printf("Choice: ");
    scanf("%d", &choice);

    clearScore();
    displayPiano();
    switch (choice) {
    case 1:
        playSong(hMidiDevice, song1, sizeof(song1) / sizeof(song1[0]));
        break;
    case 2:
        playSong(hMidiDevice, song2, sizeof(song2) / sizeof(song2[0]));
        break;
    case 3:
        playSong(hMidiDevice, butterfly, sizeof(butterfly) / sizeof(butterfly[0]));
        break;
    case 4:
        playSong(hMidiDevice, schoolbell, sizeof(schoolbell) / sizeof(schoolbell[0]));
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

    // ���̵� ���� �� ����� ���� ���� ��ȯ
    int loop = 1;
    BYTE key = 0;
    BYTE instrument = 0;
    BYTE volume = 127;
    BYTE octave = 48;
    BYTE velocity = 120;
    BYTE pedalState = 0; // ��� ���� ���� �߰� (0: ����, 1: ����)

    int row, col;

    BYTE pianoKeyOnOff[NKEY] = { 0 };

    MIDIALLChannelSoundOff(hMidiDevice);
    MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);

    while (loop) {
        if (GetKeyState(VK_ESCAPE) < 0)
            loop = 0;
        else if (GetKeyState(VK_RIGHT) < 0) {
            if (instrument < (NINSTRUMENT - 1))
                instrument += 1;
            MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
            getCursorPosition(&row, &col);
            gotoxy(col + 1, row - 10);
            printf("Instrument:%-24s", instName[instrument]);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_LEFT) < 0) {
            if (instrument != 0)
                instrument -= 1;
            MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
            getCursorPosition(&row, &col);
            gotoxy(col + 1, row - 10);
            printf("Instrument:%-24s", instName[instrument]);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_UP) < 0) {
            if (octave < (NNOTE - NKEY))
                octave += 12;
            getCursorPosition(&row, &col);
            gotoxy(col + 40, row - 10);
            printf("Octave : %03d", octave);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_DOWN) < 0) {
            if (octave != 0)
                octave -= 12;
            getCursorPosition(&row, &col);
            gotoxy(col + 40, row - 10);
            printf("Octave : %03d", octave);
            gotoxy(col, row);
            Sleep(200);
        }
        else if (GetKeyState(VK_OEM_PLUS) < 0) {
            if (volume < (NVOLUME - 1))
                volume += 1;
            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            getCursorPosition(&row, &col);
            gotoxy(col + 53, row - 10);
            printf("Volume : %03d", volume);
            gotoxy(col, row);
            Sleep(150);
        }
        else if (GetKeyState(VK_OEM_MINUS) < 0) {
            if (volume != 0)
                volume -= 1;
            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            getCursorPosition(&row, &col);
            gotoxy(col + 53, row - 10);
            printf("Volume : %03d", volume);
            gotoxy(col, row);
            Sleep(150);
        }else if (GetKeyState(VK_SPACE) < 0) { // Spacebar for pedal
            if (pedalState == 0) {
                pedalState = 1; // ��� Ȱ��ȭ
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 127); // Sustain Pedal On
            }
        }
        else {
            if (pedalState == 1) {
                pedalState = 0; // ��� ��Ȱ��ȭ
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 0); // Sustain Pedal Off
                MIDIALLChannelSoundOff(hMidiDevice); // ��� ä���� �� ����
            }
        }
        
        for (key = 0; key < NKEY; key++) {
            if (GetKeyState(pianoKey[key]) < 0) {
                if (pianoKeyOnOff[key] == 0) {
                    pianoKeyOnOff[key] = 1;
                    MIDISendShortMsg(hMidiDevice, 0x90, (BYTE)(octave + key), velocity);
                }
            }
        }
        
        for (key = 0; key < NKEY; key++) {
            if (!(GetKeyState(pianoKey[key]) < 0)) {
                if (pianoKeyOnOff[key] != 0) {
                    pianoKeyOnOff[key] = 0;
                    MIDISendShortMsg(hMidiDevice, 0x80, (BYTE)(octave + key), velocity);
                }
            }
        }
    }

    MIDIALLChannelSoundOff(hMidiDevice);
    MIDIClose(hMidiDevice);
}