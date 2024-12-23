#pragma once
#include <windows.h>

typedef struct {
    BYTE note;   // 음표
    int duration; // 지속 시간 (밀리초)
} Note;