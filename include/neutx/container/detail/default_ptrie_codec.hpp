// ex: ts=4 sw=4 ft=cpp et indentexpr=
/**
 * \file
 * \brief default codec used to store trie and find root node
 *
 * \author Dmitriy Kargapolov
 * \since 22 February 2014
 *
 */

/*
 * Copyright (C) 2014 Dmitriy Kargapolov <dmitriy.kargapolov@gmail.com>
 * Use, modification and distribution are subject to the Boost Software
 * License, Version 1.0 (See accompanying file LICENSE_1_0.txt or copy
 * at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef _NEUTX_CONTAINER_DETAIL_DEFAULT_PTRIE_CODEC_HPP_
#define _NEUTX_CONTAINER_DETAIL_DEFAULT_PTRIE_CODEC_HPP_

namespace neutx {
namespace container {
namespace detail {

template<typename AddrType>
struct mmap_trie_codec_impl {

    // default trie encoder
    class writer {
        typedef std::pair<const void *, size_t> buf_t;
        AddrType root;
        buf_t buf;

    public:
        template<typename T> writer(T&) {}

        template<typename F, typename S>
        void store(F f, S&) {
            // store trie nodes, get root node address
            root = f();
            // fill output buffer with root node address
            buf.first = &root;
            buf.second = sizeof(root);
        }

        const buf_t& buff() const { return buf; }
    };

    // find root node address
    struct get_root {
        AddrType operator()(const void *m_addr, size_t m_size) {
            size_t s = sizeof(AddrType);
            if (m_size < s)
                throw std::runtime_error("short file");
            return *(const AddrType *) ((const char *) m_addr + m_size - s);
        }
    };

};

struct mmap_trie_codec {
    template<typename AddrType>
    struct bind {
        typedef typename mmap_trie_codec_impl<AddrType>::writer encoder;
        typedef typename mmap_trie_codec_impl<AddrType>::get_root root_finder;
    };
};

} // namespace detail
} // namespace container
} // namespace neutx

#endif // _NEUTX_CONTAINER_DETAIL_DEFAULT_PTRIE_CODEC_HPP_
