#include "Printer.h"
#include "PrinterNative.h"

ref class Printer {

    void print(std::string ss) { //
        PrinterNative ^ pn = gcnew PrinterNative();
        pn->printnative(ss);
    }
};
