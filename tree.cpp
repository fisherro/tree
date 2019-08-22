#include <ftw.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

static int cb(const char* fpath, const struct stat* sb, int typeflag)
{
    std::cout << fpath << '\n';
    return 0;
}

int main(int argc, const char** argv)
{
#if 1
    std::vector<std::string> args{argv + 1, argv + argc};
    if (0 == args.size()) args.push_back(".");
    for (const auto& arg: args) {
        int rc{ ftw(arg.c_str(), &cb, 20) };
        if (0 != rc) {
            std::perror("ftw");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
#else
    for (int i = 1; i < argc; ++i) {
        int rc = ftw(argv[i], &cb, 20);
        if (0 != rc) {
            std::perror("ftw");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
#endif
}

#if 0
int main(int argc, const char** argv)
{
    struct Range {
        char* f;
        char* l;
        Range(char* first, char* last): f(first), l(last) {}
        char* begin() const { return f; }
        char* end() const { return l; }
    };

    for (const char* arg: Range{argv + 1, argv + argc}) {
        const char* arg = *arg_;
        int rc = ftw(arg,
                [](const char* fpath, const struct stat* sb, int typeflag){
                    std::cout << fpath << '\n';
                    return 0;
                }, 100);
        if (0 != rc) {
            std::perror("ftw");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
#endif

