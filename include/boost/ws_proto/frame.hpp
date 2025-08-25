//
// Copyright (c) 2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_BEAST_WS_PROTO_SRC_FRAME_HPP
#define BOOST_BEAST_WS_PROTO_SRC_FRAME_HPP

#include <boost/ws_proto/detail/config.hpp>

namespace boost {
namespace ws_proto {

/** The type of received control frame.

    Values of this type are passed to the control frame
    callback set using @ref stream::control_callback.
*/
enum class frame_type
{
    /// A WebSocket text frame
    text = 0,

    /// A WebSocket binary frame
    binary,

    /// A WebSocket continuation frame
    cont,

    /// A WebSocket close frame
    close,

    /// A WebSocket ping frame
    ping,

    /// A WebSocket pong frame
    pong
};

} // ws_proto
} // boost

#endif
