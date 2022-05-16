#include "dllprint.h"
#include "PrinterNative.h"
#include <msclr\marshal_cppstd.h>

void dllprint::Printer::print(System::String ^ ss) { //
    msclr::interop::marshal_context context;
    std::string                     sss = context.marshal_as<std::string>(ss);
    pn->printnative(sss);
}
dllprint::Printer::Printer() { //
    pn = new PrinterNative();
}