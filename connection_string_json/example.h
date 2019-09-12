#include <boost/optional.hpp>
#include <utility>

namespace example {


std::pair<bool, UString> GetConnectionString(const UString json);

boost::optional<SchemaValidator> GetSchema(const char *schema);

UString GetJsonSchema(const rapidjson::document&);
UString GetOdbcSchema(const rapidjson::document&);

constexpr auto JSON_SCHEMA{ 
    "{
        schema: \"somescheme\"   
     }" 
};

constexpr auto ODBC_SCHEMA{ "someodbcScheme" };



}
