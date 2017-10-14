#include "trie.h"
#include "logger.h"

#include <iostream>

using namespace std;


trie::trie() {
    _root = new trie_node();
    _size = 0;
}

trie::~trie() {
    delete _root;
}

void trie::_in_order(trie_node *root) {
    if (root == nullptr) return;
    for (int i = 0; i < root->children_size(); i++) {
        _in_order(root->get_child(i));
        cout << root->get_word() << endl;
    }
}

void trie::print() {
    _in_order(_root);
}

void trie::add(mstd::string ngram) {
    // Start at the root
    trie_node *current = _root;

    // Get the parts of the N-Gram
    mstd::vector<mstd::string> grams = ngram.split(' ');

    // Go up until the previous to last part (we need to treat the last part differently)
    for (int i = 0; i < grams.size() - 1; i++) {
        // TODO: Binary search here

        if (!current->has_child(grams.at(i))) {
            // If the current trie_node doesn't already contain that child, add it (not as an end of word)
            current = current->add_child(grams.at(i), false);
        } else {
            // Otherwise, follow that child's path
            current = current->get_child(grams.at(i));
            if (current == nullptr) {
                mstd::logger::error("trie::add", "current is null");
                mstd::logger::f_error("trie::add", "current is null", "debug/log.txt");
                throw std::runtime_error("current is null");
            }
        }
    }

    mstd::string last_word = grams.get((int) grams.size() - 1);

    if (current->has_child(last_word)) {
        // If the word already existed in the tree, we simply mark it as the end of the N-Gram
        current->set_end_of_word();
    } else {
        // Otherwise we insert it to that node's children
        current->add_child(last_word, true);
    }

}

bool trie::search(mstd::string ngram) {
    trie_node *current = _root;
    mstd::vector<mstd::string> grams = ngram.split(' ');
    for (int i = 0; i < grams.size() - 1; i++) {
        if (!current->has_child(grams.get(i))) {
            return false;
        }
        current = current->get_child(grams.get(i));
    }

    return ((current = current->get_child(grams.get((int) grams.size() - 1))) != nullptr && current->is_end_of_word());
}
