#pragma once

#include <string>
#include <iostream>
#include <vector>

class CsvWriter {
    public:
        CsvWriter(std::iostream &output, const char delimiter, const unsigned numFields);
        ~CsvWriter();

        CsvWriter(const CsvWriter&) = delete;
        CsvWriter(CsvWriter&&) = default;

        CsvWriter& operator=(const CsvWriter&) = delete;
        CsvWriter& operator=(CsvWriter&&) = default;

        void Push(const char val);
        void Push(const int val);
        void Push(const int64_t val);
        void Push(const float val);
        void Push(const double val);
        void Push(std::string val);
        void PushEmpty();

        void Write();
        void Flush();

    private:
        std::iostream &m_output;
        const char m_delimiter{ ',' };
        const unsigned m_numFields{ 0 };
        std::vector<std::string> m_tokens;
};
