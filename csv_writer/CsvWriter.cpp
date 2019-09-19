#include "CsvWriter.h"

static bool ShouldEscape(const char c);
static std::string CleanString(std::string val);

CsvWriter::CsvWriter(std::iostream &output, const char delimiter, const unsigned numFields)
    : m_output{output}
    , m_delimiter{delimiter}
    , m_numFields{numFields} {
}

CsvWriter::~CsvWriter() { 
    Flush();
}

void CsvWriter::Push(const char val) {
    m_tokens.emplace_back(1, val);
}

void CsvWriter::Push(const int val) {
    m_tokens.emplace_back(std::to_string(val));
}

void CsvWriter::Push(const int64_t val) {
    m_tokens.emplace_back(std::to_string(val));
}

void CsvWriter::Push(const float val) {
    m_tokens.emplace_back(std::to_string(val));
}

void CsvWriter::Push(const double val) {
    m_tokens.emplace_back(std::to_string(val));
}

void CsvWriter::Push(std::string val) {
    const auto tmp{ CleanString(std::move(val)) };
    m_tokens.emplace_back("\"");
    m_tokens.back() += std::move(tmp);
    m_tokens.back() += "\"";
}

void CsvWriter::PushEmpty() {
    m_tokens.emplace_back();
}

void CsvWriter::Write() {
    auto tokenIter{ m_tokens.begin() };
    for(unsigned i{ 0 }; i < m_numFields; ++i) {
        if(i > 0) {
            m_output << m_delimiter;
        }

        if(tokenIter != m_tokens.end()) {
            m_output << (*tokenIter++);
        }
    }
    m_output << "\n";
    m_tokens.clear();
}

void CsvWriter::Flush() {
    m_output.flush();
}

bool ShouldEscape(const char c) {
    static const std::string ShouldEscape{ R"("')" };
    return ShouldEscape.find(c) != std::string::npos;
}

std::string CleanString(std::string val) {
    for(auto c{ val.begin() }; c != val.end(); ++c) {
        if(ShouldEscape(*c)) {
            c = val.insert(c, '\\');
            ++c;
        }
    }
    return val;
}
