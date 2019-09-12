#include <functional>
#include <vector>

namespace example {

std::pair<bool, UString> GetConnectionString(const UString json)
{
    if(JsonIsNotValid(json)) {
        return { false, "JSON IS NOT VALID!" };
    }

    using SchemaFunc = std::function<UString(const rapidjson::document&)>;
    static const std::vector<SchemaFunc> FuncList {
        GetJsonSchema,
        GetOdbcSchema
    };

    const rapidjson::Document doc{ json } ;
    for(const auto &func : FuncList) {
        const auto res{ f(doc) };
        if(res.Length() > 0) {
            return { true, std::move(res) );
        }
    }
    return { false, "nothing matches any schemas" };
}

boost::optional<SchemaValidator> GetSchema(const char *schema)
{
    if(SchemaIsNotValidAlthoughThisIsProgrammerError(schema)) {
        return {};
    }
    return SomeValidSchema;
}

UString GetJsonSchema(const rapidjson::document&)
{
    const auto schema{ GetSchema(JSON_SCHEMA) };
    if(!schema.is_initialized()) {
        return {};
    }
    return SOMESCHEMASTRING;
}

UString GetOdbcSchema(const rapidjson::document&)
{
    const auto schema{ GetSchema(ODBC_SCHEMA) };
    if(!schema.is_initialized()) {
        return {};
    }
    return SOMESCHEMASTRING;
}

}

