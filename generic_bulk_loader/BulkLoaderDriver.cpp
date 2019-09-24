#include "BulkLoaderDriver.h"

BulkLoaderDriver::BulkLoaderDriver(std::unique_ptr<GenericBulkLoader> loader)
    : m_loader{std::move(loader)} {
}

BulkLoaderDriver::~BulkLoaderDriver() = default;
