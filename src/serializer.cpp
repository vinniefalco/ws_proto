//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#include <boost/ws_proto/serializer.hpp>

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
append_frame_header()
{
}

} // ws_proto
} // boost
