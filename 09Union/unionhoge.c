#include <stdio.h>

enum hogetype{
    hoge0type, hoge1type,
};

struct hoge0{
    enum hogetype type;
    int a;
};

struct hoge1
{
    enum hogetype type;
    char b;
};

union hoge{
    enum hogetype type;
    struct hoge0 h0;
    struct hoge1 h1;
};
