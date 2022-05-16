#pragma once
#include "PrinterNative.h"
using namespace System;

namespace dllprint {
public
    ref class Printer {
        PrinterNative *pn;
        void           print(System::String ^);
        Printer();
    };
}
