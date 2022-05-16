#pragma once

using namespace System;
#include "PrinterNative.h"
namespace dllfunc {
public
    ref class Printer {
        Native::Printer *pn;

    public:
        Printer() { pn = new Native::Printer {}; };
        auto print(System::String ^) -> void;
    };
}
