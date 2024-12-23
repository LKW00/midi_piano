#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "piano.h"
#include "Guide.h"
#include "record.h"

void runPiano();

int main() {
    int choice;
    while (1) {
        system("cls"); // 콘솔 화면 지우기
        printf("====== MENU ======\n");
        printf("1. 피아노 연습\n");
        printf("2. 가이드 프로그램\n");
        printf("3. 녹음 시작\n");
        printf("4. 녹음 중지\n");
        printf("5. 녹음 재생\n");
        printf("6. 종료\n");
        printf("==================\n");
        printf("선택: ");
        scanf("%d", &choice);

        system("cls"); // 콘솔 화면 지우기
        switch (choice) {
        case 1:
            printf("\n");
            runPiano();
            break;
        case 2:
            printf("가이드 프로그램을 선택했습니다.\n");
            Guide();
            break;
        case 3:
            printf("녹음을 시작합니다.\n");
            startRecording();
            break;
        case 4:
            printf("녹음을 중지합니다.\n");
            stopRecording();
            break;
        case 5:
            printf("녹음을 재생합니다.\n");
            HMIDIOUT hMidiDevice = MIDIOpen(0);
            if (hMidiDevice != NULL) {
                playRecording(hMidiDevice);
                MIDIClose(hMidiDevice);
            }
            else {
                printf("Failed to open MIDI device.\n");
            }
            break;
        case 6:
            printf("프로그램 종료.\n");
            exit(0);
            break;
        default:
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
            Sleep(1000); // 잘못된 입력 시 잠시 대기
        }
    }
    return 0;
}

void runPiano() {
    piano();  // 피아노 실행
}