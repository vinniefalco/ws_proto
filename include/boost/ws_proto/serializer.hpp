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

/** A serializer for WebSocket protocol frames
*/
class serializer
{
    http_proto::detail::workspace ws_;
    buffers::circular_buffer cb_;

public:
    using const_buffers_type =
        buffers::circular_buffer::const_buffers_type;

    BOOST_WS_PROTO_DECL
    ~serializer();

    /** Constructor.
    */
    BOOST_WS_PROTO_DECL
    serializer();

    //--------------------------------------------
    //
    // Input area
    //
    //--------------------------------------------

    /*
    start()

        - complete message in one ConstBufferSequence
        - incremental message in multiple ConstBufferSequence
        - array of complete messages
        - `stream` object streaming api
        - ping, pong, close

    */
    BOOST_WS_PROTO_DECL
    void
    start(
        bool binary);

    BOOST_WS_PROTO_DECL
    template<class ConstBufferSequence>
    std::size_t
    copy_some(
        ConstBufferSequence const& data);

    BOOST_WS_PROTO_DECL
    void
    finish();



    BOOST_WS_PROTO_DECL
    void
    append(
        frame_header const& fh);

    BOOST_WS_PROTO_DECL
    void
    write(
        buffers::const_buffer payload);

    //--------------------------------------------
    //
    // Output area
    //
    //--------------------------------------------

    /** Return the number of bytes in the read area
    */
    std::size_t
    size() const noexcept
    {
        return cb_.size();
    }

    /** Return a constant buffer sequence representing the serialized output
    */
    const_buffers_type
    data() const noexcept
    {
        return cb_.data();
    }

    /** Remove bytes from the read area
    */
    void
    consume(std::size_t n)
    {
        cb_.consume(n);
    }

};

} // ws_proto
} // boost

#endif
