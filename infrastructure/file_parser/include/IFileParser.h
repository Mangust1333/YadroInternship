#ifndef IFILEPARSER_H
#define IFILEPARSER_H

#include "ParseData.h"

namespace FileParser {
    class IFileParser {
    public:
        virtual ~IFileParser() = default;
        virtual ParseData parse() = 0;
    };
} // FileParser

#endif