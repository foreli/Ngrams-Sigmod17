#include <iostream>
#include <cmd_parser.h>
#include <parser.h>
#include "trie.h"
#include "mstring.h"
#include "mvector.h"
#include "hash_table.h"

using std::cout;
using std::endl;
using mstd::string;
using mstd::vector;

mstd::string mstd::logger::file;

int main(int argc, char **argv) {
    mstd::logger::file = "../debug/log.txt";
    if (argc < 3) {
        cout << "Invalid number of arguments. Usage: " << argv[0] << " -i <init_file> -q <query_file> [--debug]" << endl;
        return 1;
    }
    mstd::hash_table<string> ht(5);
    ht.put("-i", "<s>");
    ht.put("-q", "<s>");
    ht.put("--debug", "<none>");
    mstd::cmd_parser parser;
    int status = parser.parse(argc, argv, ht);
    switch (status) {
        case UNKNOWN_ARG:
            cout << "Unknown arguments found. Usage: " << argv[0] << " -i <init_file> -q <query_file> [--debug]" << endl;
            return 1;
        case WRONG_FORMAT:
            cout << "Wrong usage found. Usage: " << argv[0] << " -i <init_file> -q <query_file> [--debug]" << endl;
            return 1;
        case WRONG_INPUT:
            std::cerr << "Our input was wrong" << endl;
            return 1;
    }

    try {
        string init_file = parser.get_string("-i");
        string query_file = parser.get_string("-q");
    } catch (std::runtime_error &e) {
        mstd::logger::error("main", "User has not provided both -i and -q. Exiting..", BOTH);
        return 1;
    }

    trie t;
    t.add("Hello World this is an N-Gram");
    t.add("Hello World");
    t.add("Hello");
    string s = t.search("Hello World this is an N-Gram") ? "The N-Gram exists" : "The N-Gram does not exist";
    cout << s << endl;
    s = t.search("Hello") ? "The N-Gram exists" : "The N-Gram does not exist";
    cout << s << endl;
    s = t.search("hi") ? "The N-Gram exists" : "The N-Gram does not exist";
    cout << s << endl;

//    parser init_parser("../file.init");
//    if (!init_parser.is_open()) {
//        mstd::logger::error("main", "file has not been opened");
//        return 1;
//    }
//
//    vector<string> v;
//
//    while (!init_parser.next_init(&v)) {
//        for (int i = 0; i < v.size(); i++) {
//            cout << v[i] << endl;
//        }
//        cout << endl;
//    }
//
//    parser query_parser("../file.query");
//    if (!query_parser.is_open()) {
//        mstd::logger::error("main", "file has not been opened");
//        return 1;
//    }
//
//    int type;
//    while (!query_parser.next_query(&v, &type)) {
//        switch (type) {
//            case INSERTION:
//                mstd::logger::success("main", "Got insertion operation");
////                for (int i = 0; i < v.size(); i++) {
////                    cout << v[i] << endl;
////                }
////                break;
//            case QUERY:
//                mstd::logger::success("main", "Got query operation");
//                break;
//            case DELETION:
//                mstd::logger::success("main", "Got deletion operation");
//                break;
//            case UNKNOWN_OP:
//                mstd::logger::warn("main", "Got an unknown operation");
//                break;
//        }
//        for (int i = 0; i < v.size(); i++) {
//            cout << v[i] << endl;
//        }
//    }
}