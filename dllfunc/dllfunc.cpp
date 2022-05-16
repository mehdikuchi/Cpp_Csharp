#include "dllfunc.h"
#include <msclr\marshal_cppstd.h>
auto dllfunc::Printer::print(System::String ^ ss) -> void {
    msclr::interop::marshal_context context;

    pn->print(context.marshal_as<std::string>(ss));
}
