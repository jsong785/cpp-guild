#pragma once

#include <string>

class GenericBulkLoader {
    public:
        virtual ~GenericBulkLoader() = default;

        virtual std::string GetFormatSpecificOptions() = 0;
        virtual void Prepare() = 0;
        virtual void Close() = 0;
        virtual void Reset() = 0;

        virtual void PushData(const int) = 0;
        virtual void PushData(const double) = 0;
        virtual void PushData(std::string) = 0;
};

