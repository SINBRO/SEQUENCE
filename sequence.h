//
// Created by andrey on 03.11.18.
//

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H


#include <cstdlib>
#include <type_traits>
#include <iterator>
#include <cstring>

/*struct seq_traits {
    using type = char;

    static constexpr bool eq(type a, type b) noexcept;

    static constexpr bool lt(type a, type b) noexcept;

    static constexpr void assign(type &r, const type &a);

    static std::size_t length(const type *s);
};*/

template<class T, class Traits>
struct sequence {
    //static_assert(std::is_same<T, typename Traits::type>::value, "Unconnected template types T and Traits");
    // :
    /*/home/andrey/CLionProjects/SEQUENCE/sequence.h: In instantiation of ‘struct sequence<char, std::char_traits<char> >’:
    /home/andrey/CLionProjects/SEQUENCE/seq_tests.cpp:54:23:   required from here
    /home/andrey/CLionProjects/SEQUENCE/sequence.h:43:17: error: no type named ‘type’ in ‘struct std::char_traits<char>’*/


    using size_type = std::size_t;
    using const_iterator = const T *;
    using reverse_const_iterator = std::reverse_iterator<const_iterator> const;
    using const_reference = const T &;
    static constexpr size_type npos = size_type(-1);

    constexpr sequence() noexcept;

    constexpr sequence(const sequence &other) noexcept;

    constexpr sequence(const T *s, size_type count);

    constexpr sequence(const T *s);

    constexpr sequence &operator=(const sequence &view) noexcept;

    constexpr const_iterator begin() const noexcept;

    constexpr const_iterator end() const noexcept;

    constexpr reverse_const_iterator rbegin() const noexcept;

    constexpr reverse_const_iterator rend() const noexcept;

    constexpr const_reference operator[](size_type pos) const;

    constexpr const_reference at(size_type pos) const; //throws std::out_of_range
    constexpr const_reference front() const;

    constexpr const_reference back() const;

    constexpr size_type size() const noexcept;

    constexpr bool empty() const noexcept;

    constexpr void remove_prefix(size_type n);

    constexpr void remove_suffix(size_type n);

    constexpr void swap(sequence &v) noexcept;

    //copies no more than count characters, return number of copyed elements
    size_type copy(T *dest, size_type count, size_type pos = 0) const; //throws std::out_of_range
    constexpr int compare(sequence v) const noexcept;

    constexpr sequence subseq(size_type pos = 0, size_type count = npos) const; //throws std::out_of_range

    constexpr size_type find(sequence v, size_type pos = 0) const noexcept;

    constexpr size_type rfind(sequence v, size_type pos = npos) const noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator==(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator!=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator<(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator>(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator<=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

    template<class T2, class Traits2>
    friend constexpr bool operator>=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept;

private:
    size_type _size = 0;
    T const *head = nullptr;
};

template<class T, class Traits>
constexpr sequence<T, Traits>::sequence() noexcept = default;

template<class T, class Traits>
constexpr sequence<T, Traits>::sequence(const sequence &other) noexcept : _size(other._size), head(other.head) {
}

template<class T, class Traits>
constexpr sequence<T, Traits>::sequence(const T *s, sequence::size_type count) : _size(count), head(s) {
}

template<class T, class Traits>
constexpr sequence<T, Traits>::sequence(const T *s) : _size(Traits::length(s)), head(s) {
}

template<class T, class Traits>
constexpr sequence<T, Traits> &sequence<T, Traits>::operator=(const sequence &view) noexcept {
    _size = view._size;
    head = view.head;
    return *this;
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_iterator sequence<T, Traits>::begin() const noexcept {
    return head;
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_iterator sequence<T, Traits>::end() const noexcept {
    return head + _size;
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::reverse_const_iterator sequence<T, Traits>::rbegin() const noexcept {
    return reverse_const_iterator(end());
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::reverse_const_iterator sequence<T, Traits>::rend() const noexcept {
    return reverse_const_iterator(begin());
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_reference sequence<T, Traits>::operator[](sequence::size_type pos) const {
    return head[pos];
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_reference sequence<T, Traits>::at(sequence::size_type pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Index out of bounds");
    }
    return head[pos];
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_reference sequence<T, Traits>::front() const {
    return head[0];
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::const_reference sequence<T, Traits>::back() const {
    return head[_size - 1];
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::size_type sequence<T, Traits>::size() const noexcept {
    return _size;
}

template<class T, class Traits>
constexpr bool sequence<T, Traits>::empty() const noexcept {
    return _size == 0;
}

template<class T, class Traits>
constexpr void sequence<T, Traits>::remove_prefix(sequence::size_type n) {
    if (n > _size) {
        throw std::runtime_error("Not enough elements to remove");
    }
    head += n;
    _size -= n;
}

template<class T, class Traits>
constexpr void sequence<T, Traits>::remove_suffix(sequence::size_type n) {
    if (n > _size) {
        throw std::runtime_error("Not enough elements to remove");
    }
    _size -= n;
}

template<class T, class Traits>
constexpr void sequence<T, Traits>::swap(sequence &v) noexcept {
    sequence<T, Traits> temp = v;
    v = *this;
    *this = temp;
}

template<class T, class Traits>
typename sequence<T, Traits>::size_type
sequence<T, Traits>::copy(T *dest, sequence::size_type count, sequence::size_type pos) const {
    if (pos > _size) {
        throw std::runtime_error("Index out of bounds");
    }
    for (size_type i = 0; i < std::min(count, _size - pos); ++i) {
        Traits::assign(dest[i], head[i + pos]);
    }
    return std::min(count, _size - pos);
}

template<class T, class Traits>
constexpr int sequence<T, Traits>::compare(sequence v) const noexcept { // min(len1, len2)
    if (_size == v._size) {
        for (const_iterator i = begin(), j = v.begin(); i != end(); ++i, ++j) {
            if (Traits::lt(*i, *j)) {
                return -1;
            }
            if (Traits::lt(*j, *i)) {
                return 1;
            }
        }
        return 0;
    }
    if (_size > v._size) {
        return 1;
    }
    return -1;
}

template<class T, class Traits>
constexpr sequence<T, Traits> sequence<T, Traits>::subseq(sequence::size_type pos, sequence::size_type count) const {
    if (pos > _size) {
        throw std::runtime_error("Index out of bounds");
    }
    return sequence<T, Traits>(head + pos, std::min(count, head - pos));
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::size_type
sequence<T, Traits>::find(sequence v, sequence::size_type pos) const noexcept {
    if (pos > _size) {
        throw std::runtime_error("Index out of bounds");
    }
    if (v._size > _size) {
        return npos;
    }
    for (size_type i = pos; i < _size - v._size; ++i) {
        if (std::memcmp(head + i, v.head, v._size * sizeof(T)) == 0) {
            return i;
        }
    }
    return npos;
}

template<class T, class Traits>
constexpr typename sequence<T, Traits>::size_type
sequence<T, Traits>::rfind(sequence v, sequence::size_type pos) const noexcept {
    if (pos > _size) {
        throw std::runtime_error("Index out of bounds");
    }
    if (v._size > _size) {
        return npos;
    }
    for (size_type i = std::min(pos, _size - v.size()) + 1; i > 0; --i) {
        if (std::memcmp(head + (i - 1), v.head, v._size * sizeof(T)) == 0) {
            return i - 1;
        }
    }
    return npos;
}

template<class T2, class Traits2>
constexpr bool operator==(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return lhs.compare(rhs) == 0;
}

template<class T2, class Traits2>
constexpr bool operator!=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return !(lhs == rhs);
}

template<class T2, class Traits2>
constexpr bool operator<(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return lhs.compare(rhs) == -1;
}

template<class T2, class Traits2>
constexpr bool operator>(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return rhs < lhs;
}

template<class T2, class Traits2>
constexpr bool operator<=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return !(lhs > rhs);
}

template<class T2, class Traits2>
constexpr bool operator>=(sequence<T2, Traits2> lhs, sequence<T2, Traits2> rhs) noexcept {
    return !(lhs < rhs);
}

namespace std {
    template<class T, class Traits>
    struct hash<sequence<T, Traits>> {
        std::size_t operator()(const sequence<T, Traits> &s) const noexcept;
    };

    template<class T, class Traits>
    std::size_t hash<sequence<T, Traits>>::operator()(const sequence<T, Traits> &s) const noexcept {
        std::size_t res = 0;
        for (std::size_t i = 0; i < s.size(); ++i) {
            res+= std::hash(s[i]);
        }
        return res;
    }
}


#endif //SEQUENCE_SEQUENCE_H
