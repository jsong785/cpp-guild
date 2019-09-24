#pragma once

#include <memory>

class GenericBulkLoader;

class BulkLoaderDriver {
    public:
        BulkLoaderDriver(std::unique_ptr<GenericBulkLoader> loader);
        ~BulkLoaderDriver();
        BulkLoaderDriver(const BulkLoaderDeriver&) = delete;
        BulkLoaderDriver(BulkLoaderDeriver &&) = default;

        BulkLoaderDriver& operator=(const BulkLoaderDeriver) = delete;
        BulkLoaderDriver& operator=(BulkLoaderDeriver&&) = default;

    private:
        std::unique_ptr<GenericBulkLoader> m_loader;
};
