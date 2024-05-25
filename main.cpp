#include "parser.h"
#include <exception>

// uxel if-y ev while-y
// if-um ev while-um popoxakan chenq karox haytararel ev chenq karox unenal nerdrvac if kam while
// while-y chi karox anverj cikl ynknel, ajcinqn paymani da\ty chi karox datark linel
// while kisat
// fixed bug!
// char float_arr[x] = { '2', 'c', 3, 4 } ;

int main() {
    std::string filename = "file.txt";
    Parser parser(filename);

    parser.load_from_file();

    parser.parse();

    // parser.print_include();
    // parser.print_int();
    // parser.print_char();
    // parser.print_float();
    // parser.print_double();
    // parser.print_bool();
    // parser.print_string();


    // parser.print_int_array();
    // parser.print_char_array();
    // parser.print_float_array();
    // parser.print_double_array();
    // parser.print_bool_array();
}
