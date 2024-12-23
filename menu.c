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
        system("cls"); // �ܼ� ȭ�� �����
        printf("====== MENU ======\n");
        printf("1. �ǾƳ� ����\n");
        printf("2. ���̵� ���α׷�\n");
        printf("3. ���� ����\n");
        printf("4. ���� ����\n");
        printf("5. ���� ���\n");
        printf("6. ����\n");
        printf("==================\n");
        printf("����: ");
        scanf("%d", &choice);

        system("cls"); // �ܼ� ȭ�� �����
        switch (choice) {
        case 1:
            printf("\n");
            runPiano();
            break;
        case 2:
            printf("���̵� ���α׷��� �����߽��ϴ�.\n");
            Guide();
            break;
        case 3:
            printf("������ �����մϴ�.\n");
            startRecording();
            break;
        case 4:
            printf("������ �����մϴ�.\n");
            stopRecording();
            break;
        case 5:
            printf("������ ����մϴ�.\n");
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
            printf("���α׷� ����.\n");
            exit(0);
            break;
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
            Sleep(1000); // �߸��� �Է� �� ��� ���
        }
    }
    return 0;
}

void runPiano() {
    piano();  // �ǾƳ� ����
}