//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BIND_HANDLER_HPP
#define BOOST_BEAST_BIND_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/type_traits.hpp>
#include <boost/beast/core/detail/bind_handler.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

/** Bind parameters to a completion handler, creating a new handler.

    This function creates a new handler which, when invoked, calls
    the original handler with the list of bound arguments. Any
    parameters passed in the invocation will be subtituted for
    placeholders present in the list of bound arguments. Parameters
    which are not matched to placeholders are silently discarded.
    The passed handler and arguments are forwarded into the returned
    handler, which provides the same `io_service` execution guarantees
    as the original handler.

    Unlike `boost::asio::io_service::wrap`, the returned handler can
    be used in a subsequent call to `boost::asio::io_service::post`
    instead of `boost::asio::io_service::dispatch`, to ensure that
    the handler will not be invoked immediately by the calling
    function.

    Example:

    @code
    template<class AsyncReadStream, class ReadHandler>
    void
    signal_aborted(AsyncReadStream& stream, ReadHandler&& handler)
    {
        stream.get_io_service().post(
            bind_handler(std::forward<ReadHandler>(handler),
                boost::asio::error::operation_aborted, 0));
    }
    @endcode

    @param handler The handler to wrap.

    @param args A list of arguments to bind to the handler. The
    arguments are forwarded into the returned object.
*/
template<class Handler, class... Args>
#if BOOST_BEAST_DOXYGEN
implementation_defined
#else
detail::bound_handler<
    typename std::decay<Handler>::type, Args...>
#endif
bind_handler(Handler&& handler, Args&&... args)
{
#if 0
    static_assert(is_completion_handler<
        Handler, void(Args...)>::value,
            "Handler requirements not met");
#endif
    return detail::bound_handler<typename std::decay<
        Handler>::type, Args...>(std::forward<
            Handler>(handler), std::forward<Args>(args)...);
}

} // beast
} // boost

#endif
