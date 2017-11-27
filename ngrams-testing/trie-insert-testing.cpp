// #include "trie.hpp"
// #include "mvector.hpp"
// #include "gtest/gtest.h"
// #include "parser.hpp"
// #include <string>
// #include <fstream>
// #include <iostream>
// 
// using mstd::vector;
// using std::string;
// 
// class TrieInsertionTesting : public ::testing::Test {
// public:
//     trie t;
//     vector<string> v;
//     TrieInsertionTesting() {
//         t;
//         v;
//     }
// };
// 
// TEST_F(TrieInsertionTesting, insertEasy) {
//     v.push("a"); v.push("b"); v.push("c"); v.push("d");
//     t.add(v);
//     string trie_str = t.to_string();
//     string proper = "a\n\tb\n\t\tc\n\t\t\td\n";
//     EXPECT_EQ(trie_str, proper);
// }
// 
// TEST_F(TrieInsertionTesting, insertMed) {
//     parser p("../ngrams-testing/test-input/medium.input");
//     bool stop = false;
//     vector<string> v;
//     while (!stop) {
//         stop = p.next_init(&v);
//         if (v.size() == 0) continue;
//         t.add(v);
//         v.clear();
//     }
//     string output = t.to_string();
//     std::ofstream out("../ngrams-testing/output/output-medium.test");
//     out << output;
//     std::ifstream in("../ngrams-testing/test-input/output-medium.proper");
//     std::stringstream proper_output;
//     std::string line;
//     while (std::getline(in, line)) {
//         proper_output << line << "\n";
//     }
//     EXPECT_EQ(proper_output.str(), output);
// }
// 
// TEST_F(TrieInsertionTesting, insertLarge) {
//     parser p("../ngrams-testing/test-input/large.input");
//     bool stop = false;
//     vector<string> v;
//     while (!stop) {
//         stop = p.next_init(&v);
//         if (v.size() == 0) continue;
//         t.add(v);
//         v.clear();
//     }
//     string output = t.to_string();
//     std::ofstream out("../ngrams-testing/output/output-large.test");
//     out << output;
//     std::ifstream in("../ngrams-testing/test-input/output-large.proper");
//     std::stringstream proper_output;
//     std::string line;
//     while (std::getline(in, line)) {
//         proper_output << line << "\n";
//     }
//     EXPECT_EQ(proper_output.str(), output);
// }
