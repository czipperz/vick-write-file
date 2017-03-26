/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_VICK_WRITE_FILE_H
#define HEADER_GUARD_VICK_WRITE_FILE_H

#include <thread>

#include "contents.hh"

namespace vick {
namespace write_file {

/*!
 * \file vick-write-file/lib.hh
 * \brief Save a file to disk.
 */

/*!
 * \brief Save the file to disk, then return.
 *
 * Does not edit the contents.
 */
inline std::shared_ptr<change>
write(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Do `write()` in a new thread.
 */
inline std::shared_ptr<change>
write_async(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Writes the file synchronously if given a prefix arg > 0,
 * else writes asynchronously.
 */
inline std::shared_ptr<change>
write_maybe_async(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Save the file to file_name, then return.
 *
 * Returns `-1` if can't open the file, `0` otherwise.
 */
int write_to(const contents&, const char* file_name);

inline std::shared_ptr<change>
write(contents& c, boost::optional<int>) {
    write_to(c, c.file_name.c_str());
    return nullptr;
}

inline std::shared_ptr<change>
write_async(contents& c, boost::optional<int>) {
    std::thread(write_to, std::ref(c), c.file_name.c_str()).detach();
    return nullptr;
}

inline std::shared_ptr<change>
write_maybe_async(contents& c, boost::optional<int> op) {
    if (op && *op > 0) {
        return write(c, std::move(op));
    } else {
        return write_async(c, std::move(op));
    }
}
}
}

#endif
