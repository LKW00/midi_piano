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
    puts(" |  ┕━┙ ┕━┙  |  ┕━┙ ┕━┙ ┕━┙  |  ┕━┙ ┕━┙  |  ┕━┙ ┕━┙ ┕━┙  |  ┕━┙ ┕━┙  | ");
    puts(" |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | ");
    puts(" | Z | X | C | V | B | N | M | Q | W | E | R | T | Y | U | I | O | P | ");
    puts(" ┕━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┷━━━┙ ");
}

void playSong(HMIDIOUT hMidiDevice, Note* song, int noteCount) {
    BYTE velocity = 120; // 음의 강도

    for (int i = 0; i < noteCount; i++) {
        MIDISendShortMsg(hMidiDevice, 0x90, song[i].note, velocity); // 음표 ON
        displayNoteOnScore(song[i].note);
        Sleep(song[i].duration); // 음표 지속
        MIDISendShortMsg(hMidiDevice, 0x80, song[i].note, velocity); // 음표 OFF
        Sleep(50); // 음표 사이 간격
    }
    gotoxy(0, 12);
}

void Guide() {
    HMIDIOUT hMidiDevice = MIDIOpen(0); // MIDI 장치 열기
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
    {67, 450}, {64, 450}, {64, 900}, {65, 450}, {62, 450}, {62, 900},            // 솔 미 미 파 레 레
    {60, 450}, {62, 450}, {64, 450}, {65, 450}, {67, 450}, {67, 450}, {67, 900}, // 도 레 미 파 솔 솔 솔 솔
    {67, 450}, {64, 450}, {64, 450}, {64, 450}, {65, 450}, {62, 450}, {62, 900}, // 솔 미 미 미 파 레 레
    {60, 450}, {64, 450}, {67, 450}, {67, 450}, {64, 450}, {64, 450}, {64, 900}, // 도 미 솔 솔 미 미 미
    {62, 450}, {62, 450}, {62, 450}, {62, 450}, {62, 450}, {64, 450}, {65, 900}, // 레 레 레 레 레 미 파
    {64, 450}, {64, 450}, {64, 450}, {64, 450}, {64, 450}, {65, 450}, {67, 900}, // 미 미 미 미 미 파 솔
    {67, 450}, {64, 450}, {64, 900}, {65, 450}, {62, 450}, {62, 900},            // 솔 미 미 파 레 레
    {60, 450}, {64, 450}, {67, 450}, {67, 450}, {64, 450}, {64, 450}, {64, 900}  // 도 미 솔 솔 미 미 미 
    };
    Note schoolbell[] = {
        {67, 450}, {67, 450}, {69, 450}, {69, 450}, {67, 450}, {67, 450}, {64, 900}, // 솔 솔 라 라 솔 솔 미
        {67, 450}, {67, 450}, {64, 450}, {64, 450}, {62, 1350},                       // 솔 솔 미 미 레
        {67, 450}, {67, 450}, {69, 450}, {69, 450}, {67, 450}, {67, 450}, {64, 900}, // 솔 솔 라 라 솔 솔 미
        {67, 450}, {64, 450}, {62, 450}, {64, 450}, {60, 1350}                       // 솔 미 레 미 도

    };

    int choice;
    printf("Select a song:\n");
    printf("1. 떴다 떴다 비행기\n");
    printf("2. 반짝 반짝 작은별\n");
    printf("3. 나비야\n");
    printf("4. 학교종\n");
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

    // 가이드 연주 후 사용자 연주 모드로 전환
    int loop = 1;
    BYTE key = 0;
    BYTE instrument = 0;
    BYTE volume = 127;
    BYTE octave = 48;
    BYTE velocity = 120;
    BYTE pedalState = 0; // 페달 상태 변수 추가 (0: 해제, 1: 눌림)

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
                pedalState = 1; // 페달 활성화
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 127); // Sustain Pedal On
            }
        }
        else {
            if (pedalState == 1) {
                pedalState = 0; // 페달 비활성화
                MIDISendShortMsg(hMidiDevice, 0xB0, 64, 0); // Sustain Pedal Off
                MIDIALLChannelSoundOff(hMidiDevice); // 모든 채널의 음 정리
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