//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#include <boost/ws_proto/serializer.hpp>
#include <boost/buffers/copy.hpp>
#include <boost/endian/conversion.hpp>
#include <cstdint>
#include <memory>

/*
    Usage Matrix

    Client sending a message:

    * a single ConstBufferSequence
    * a single MutableBufferSequence
    * array of const individual contiguous buffers
    * array of mutable individual contiguous buffers
    * writes directly into the serializer via stream api(?)

    * copy caller provided buffer into serializer, apply mask
    * compress caller data into serializer
    * mask caller's buffer in-place and send
    * mask caller's buffer in-place, compress and send

    Server sending a message:

    
*/

namespace boost {
namespace ws_proto {

namespace {

template<class DynamicBuffer>
void
write(DynamicBuffer& db, frame_header const& fh)
{
    std::size_t n;
    std::uint8_t b[14];
    b[0] = (fh.fin ? 0x80 : 0x00) | static_cast<std::uint8_t>(fh.op);
    if(fh.rsv1)
        b[0] |= 0x40;
    if(fh.rsv2)
        b[0] |= 0x20;
    if(fh.rsv3)
        b[0] |= 0x10;
    b[1] = fh.mask ? 0x80 : 0x00;
    if(fh.len <= 125)
    {
        b[1] |= fh.len;
        n = 2;
    }
    else if(fh.len <= 65535)
    {
        b[1] |= 126;
        auto len_be = endian::native_to_big(
            static_cast<std::uint16_t>(fh.len));
        std::memcpy(&b[2], &len_be, sizeof(len_be));
        n = 4;
    }
    else
    {
        b[1] |= 127;
        auto len_be = endian::native_to_big(
            static_cast<std::uint64_t>(fh.len));
        std::memcpy(&b[2], &len_be, sizeof(len_be));
        n = 10;
    }
    if(fh.mask)
    {
        auto key_le = endian::native_to_little(
            static_cast<std::uint32_t>(fh.key));
        std::memcpy(&b[n], &key_le, sizeof(key_le));
        n += 4;
    }
    db.commit(buffers::copy(db.prepare(n),
        buffers::const_buffer(b, n)));
}

} // (anon)

serializer::
~serializer()
{
}

serializer::
serializer()
    : ws_(65536)
{
    std::size_t n;
    n = ws_.size() - 1024;
    cb_ = { ws_.data(), n };
    ws_.reserve_front(n);
}

void
serializer::
append(
    frame_header const& fh)
{
    write(cb_, fh);
}

} // ws_proto
} // boost
