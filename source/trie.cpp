#include "trie.hpp"
#include "logger.hpp"
#include "helpers.hpp"

using mstd::vector;
using std::string;
using std::cout;
using std::endl;

#define SIZE 3

/*
 * Trie Implementation
 */
trie::trie() {
    _root = new trie_node();
    _num_nodes = 0;
    _num_ngrams = 0;
}

trie::~trie() {
    delete _root;
}

void trie::add(const vector<string> &ngram) {
    cout << "NEW NGRAM: " << helpers::join(ngram, ' ') << "\n" << endl;
    // Start at the root
    trie_node *current = _root;

    // Go up until the previous to last part (we need to treat the last part differently)
    for (int i = 0; i < ngram.size() - 1; i++) {

        trie_node *child;
        if ((child = current->get_child(ngram.at(i))) == nullptr) {
            // If the current trie_node doesn't already contain that child, add it (not as an end of word)
            current = current->add_child(ngram.at(i), false);
            _num_nodes++;
        } else {
            // Otherwise, follow that child's path
            current = child;
        }
    }

    std::string last_word = ngram.get_cpy((int) ngram.size() - 1);
    trie_node *child;
    if ((child = current->get_child(last_word)) != nullptr) {
        // If the word already existed in the tree, we simply mark it as the end of the N-Gram
        child->set_end_of_word(true);
    } else {
        // Otherwise we insert it to that node's children
        current = current->add_child(last_word, true);
        _num_nodes++; //Added this here too.
    }
    _num_ngrams++;

    current = _root;
    for (size_t i = 0; i < current->children_size(); i++) {
        std::cout << current->get_children().at(i).get_word() << " ";
    }
    std::cout << "CHILDREN SIZE : " << current->children_size() << '\n';
    printf("\n");
}

bool trie::search(const vector<string> &ngram, mstd::queue<std::string> *results) {
    trie_node *current = _root;
    for (size_t i = 0; i < current->children_size(); i++) {
        std::cout << current->get_children().at(i).get_word() << " ";
    }
    std::cout << "CHILDREN SIZE : " << current->children_size() << '\n';
    printf("\n");

    std::stringstream ss;

    for (size_t i = 0; i < ngram.size(); i++) {
        trie_node *child;
        for (size_t j = i; j < ngram.size(); j++) {
            if ((child = current->get_child(ngram.at(j))) == nullptr) {
                std::cout << "BGAINW ME : " << ngram.at(j) <<'\n';
                // std::cout << "KAI J : " << j << " KAI I : " << i <<'\n';
                ss.str("");
                ss.clear();
                current = _root;
                break;
            }
            else{
                ss << ngram.at(j) + " ";
                std::cout << "MPAINW : " << ss.str() <<'\n';
                if (child->is_end_of_word()) {
                    results->push(ss.str());
                }
                current = child;
            }
        }
    }
    ss.str("");
    ss.clear();
    return results->empty() ? false : true;

    // trie_node *current = _root;
    // for (int i = 0; i < ngram.size() - 1; i++) {
    //     if ((current = current->get_child(ngram.get(i))) == nullptr) {
    //         return false;
    //     }
    // }
    //
    // return ((current = current->get_child(ngram.get((int) ngram.size() - 1))) != nullptr && current->is_end_of_word());
}


/*
 * trie_node implementation
 */

trie::trie_node::trie_node()
        : _word(""), _eow(false), _parent(nullptr) {
    _children = nullptr;
}

trie::trie_node::trie_node(const std::string &word, bool eow, trie_node *par)
        : _word(word), _eow(eow), _parent(par) {
    _children = nullptr;
}

trie::trie_node::trie_node(const trie_node &other)
        : _word(other._word), _eow(other._eow), _parent(other._parent) {
    if (other._children == nullptr) {
        _children = nullptr;
        return;
    }
    _children = new mstd::vector<trie_node>(*other._children);
}

trie::trie_node::trie_node(trie_node &&other) noexcept {
    _word = other._word;
    _eow = other._eow;
    _parent = other._parent;
    _children = other._children;
    other._children = nullptr;
}

trie::trie_node::~trie_node() {
    delete _children;
}

trie::trie_node *trie::trie_node::add_child(std::string word, bool eow) {
    if (_children == nullptr) {
        _children = new mstd::vector<trie_node>(SIZE);
    }

    trie_node new_node(word, eow, this);
    if (_children->size() == 0) {
        return _children->m_push(new_node);
        // The position of the child is the position of the last element of the vector
    } else {

       int at;
       if (!_bsearch_children(word, &at)) {
           std::cout << "AT : " << at <<'\n';
           return _children->m_insert_at((size_t) at, new_node);
       } else{ //if word already exists
           //if we are careful to call add_child only when the child we are adding doesnt not already exists, this line is not useful
           return nullptr;
       }
    }
}

const mstd::vector<trie::trie_node> &trie::trie_node::get_children() {
    return *_children;
}

trie::trie_node *trie::trie_node::get_child(int index) {
    return _children->at_p(index);
}

trie::trie_node *trie::trie_node::get_child(std::string &word) {
    if (_children == nullptr) return nullptr;
    int index;
    if(!_bsearch_children(word,&index)){    // Not found
        return nullptr;
    } else{                                 // Found
        return get_child(index);
    }
}

bool trie::trie_node::_bsearch_children(std::string &word, int *index) {
   if (_children->at(0)._word > word) {
       *index = 0;
       return false;
   }
   if (_children->at(_children->size() - 1)._word < word) {
       *index = _children->size();
    //    std::cout << "MALAKA ME : " << *index <<'\n';
       return false;
   }
    int left = 0;
    int right = (int) _children->size() - 1;
    while (left <= right) {
        int mid = left + ((right-left) / 2);
        if (_children->at(mid)._word == word) {
            *index = mid;
            return true;
        }

        if (left == right) {    //mid._word != word here, so we return where the new word should be added.
            if (_children->at(left)._word > word) {
                *index = left;
            }
            else{
                *index = left+1;
            }
            return false;
        }

        if (_children->at(mid)._word > word) {
            right = mid - 1;
        }
        else if (_children->at(mid)._word < word) {
            left = mid + 1;
        }

    }
}

void trie::trie_node::push_child(trie_node *node) {
    if (_children == nullptr) {
        _children = new mstd::vector<trie_node>(SIZE);
    }
    _children->m_push(*node);
}

bool trie::trie_node::is_end_of_word() {
    return _eow;
}

size_t trie::trie_node::children_size() {
    return _children->size();
}

std::string trie::trie_node::get_word() {
    return _word;
}

void trie::trie_node::set_end_of_word(bool eow) {
    _eow = eow;
}

trie::trie_node &trie::trie_node::operator=(const trie::trie_node &other) {
    _word = other._word;
    _eow = other._eow;
    if (other._children != nullptr) {
        delete _children;
        _children = new mstd::vector<trie_node>(*other._children);
    }
    _parent = other._parent;
    return *this;
}

// Move assignment operator
// "Steals" the _children pointer from the other
// trie_node
trie::trie_node &trie::trie_node::operator=(trie::trie_node &&other) noexcept {
    _word = other._word;
    _eow = other._eow;
    _children = other._children;
    other._children = nullptr;
    _parent = other._parent;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const trie::trie_node &other) {
    out << other._word;
    return out;
}
