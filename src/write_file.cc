/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <cstdio>
#include <functional>
#include <thread>
#include <utility>

#include "../lib.hh"

namespace vick {
namespace write_file {
int write_to(const contents& c, const char* file_name) {
    struct file {
        FILE* raw;
        file(const char* fn)
            : raw(std::fopen(fn, "w")) {}
        ~file() { std::fclose(raw); }
    } f(file_name);

    if (f.raw == NULL) {
        return -1;
    }
    for (const auto& l : c.cont) {
        std::fwrite(l.c_str(), sizeof(l[0]), l.size(), f.raw);
    }
    return 0;
}
}
}
