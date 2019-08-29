#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include <ftw.h>

static bool show_all = false;

static int cb(const char* fpath, const struct stat* sb, int typeflag)
{
    if (not show_all) {
        std::string_view sv{fpath};
        if (sv.npos != sv.find("/.")) return 0;
    }
    std::cout << fpath << '\n';
    return 0;
}

int main(int argc, const char** argv)
{
    std::vector<std::string> args{argv + 1, argv + argc};

    auto iter = std::find(args.begin(), args.end(), "-a");
    if (args.end() != iter) {
        show_all = true;
        args.erase(std::remove(args.begin(), args.end(), "-a"), args.end());
    }

    if (0 == args.size()) args.push_back(".");

    for (const auto& arg: args) {
        int rc{ ftw(arg.c_str(), &cb, 20) };
        if (0 != rc) {
            std::perror("ftw");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

