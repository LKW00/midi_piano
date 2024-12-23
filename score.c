#include "score.h"
#include <stdio.h>

void displayNoteOnScore(BYTE note) {
    switch (note) {
    case 60: printf("Z "); break;
    case 61: printf("S "); break;
    case 62: printf("X "); break;
    case 63: printf("D "); break;
    case 64: printf("C "); break;
    case 65: printf("V "); break;
    case 66: printf("G "); break;
    case 67: printf("B "); break;
    case 68: printf("H "); break;
    case 69: printf("N "); break;
    case 70: printf("J "); break;
    case 71: printf("M "); break;
    case 72: printf("Q "); break;
    case 73: printf("2 "); break;
    case 74: printf("W "); break;
    case 75: printf("3 "); break;
    case 76: printf("E "); break;
    case 77: printf("R "); break;
    case 78: printf("5 "); break;
    case 79: printf("T "); break;
    case 80: printf("6 "); break;
    case 81: printf("Y "); break;
    case 82: printf("7 "); break;
    case 83: printf("U "); break;
    case 84: printf("I "); break;
    case 85: printf("9 "); break;
    case 86: printf("O "); break;
    case 87: printf("0 "); break;
    case 88: printf("P "); break;
    default: printf("? "); break; // 알 수 없는 음표
    }
}

void clearScore() {
    system("cls");
}