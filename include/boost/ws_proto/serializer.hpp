//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_SERIALIZER_HPP
#define BOOST_WS_PROTO_SERIALIZER_HPP

#include <boost/ws_proto/detail/config.hpp>
#include <boost/ws_proto/frame.hpp>
#include <boost/buffers/circular_buffer.hpp>
#include <boost/http_proto/detail/workspace.hpp>
#include <stdexcept>

namespace boost {
namespace ws_proto {

class serializer
{
    http_proto::detail::workspace ws_;
    buffers::circular_buffer bs_;

public:
    using buffers_type =
        buffers::circular_buffer::const_buffers_type;

    void
    append_frame_header();

};

} // ws_proto
} // boost

#endif
