#pragma once

#include "GenericBulkLoader.h"

class SnowflakeLocalStage : public GenericBulkLoader {
     public:
        std::string GetFormatSpecificOptions() final;
        void Prepare() final;
        void Close() final;
        void Reset() final;

        void PushData(const int) final;
        void PushData(const double) final;
        void PushData(std::string) final;

    private:
};
