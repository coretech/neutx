// ex: ts=4 sw=4 ft=cpp et indentexpr=
/**
 * \file
 * \brief digit aho-corasick trie composition demo
 *
 * \author Dmitriy Kargapolov
 * \since 19 February 2014
 *
 */

/*
 * Copyright (C) 2014 Dmitriy Kargapolov <dmitriy.kargapolov@gmail.com>
 * Use, modification and distribution are subject to the Boost Software
 * License, Version 1.0 (See accompanying file LICENSE_1_0.txt or copy
 * at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <neutx/container/digit_trie.hpp>

#include <iostream>

namespace ct = neutx::container;

// payload type
typedef std::string data_t;

// digit trie types
typedef ct::digit_trie<data_t, ct::Trie_AhoCorasick> types;

// trie node type
typedef types::node_type node_t;

// trie type
typedef types::trie_type trie_t;

// concrete trie store type
typedef types::store_type store_t;

// key element position type
typedef types::position_type pos_t;

// fold functor example
static bool fun(std::string& acc, const data_t& data, const store_t&,
        pos_t begin, pos_t end, bool has_next) {
    if (data.empty())
        return true;
    acc = data;
    std::cout << begin << ":" << end << ":" << has_next << ":" << acc << "\n";
    return true;
}

// foreach functor example
static void enumerate(const std::string& key, node_t& node, store_t&) {
    std::cout << "'" << key << "' -> '" << node.data() << "'" << std::endl;
}

int main() {
    trie_t trie;

    // store some data
    trie.store("123", "three");
    trie.store("1234", "four");
    trie.store("12345", "five");
    trie.make_links();

    // fold through the key-matching nodes considering not only the key given,
    // but also all its suffixes, preferring longest one
    std::string ret;
    trie.fold_full("01234567", ret, fun);
    std::cout << "lookup result: " << (ret.empty() ? "not found" : ret)
        << std::endl;

    // traverse all the nodes
    trie.foreach<ct::up, std::string>(enumerate);
    trie.foreach<ct::down, std::string>(enumerate);

    return 0;
}
