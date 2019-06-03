#ifndef SAJSONPARSER_H
#define SAJSONPARSER_H

#include <string>

#include "fuzzyjsonparser.h"

namespace fuzzyjson {

class RapidjsonParser : public Parser {
    public:
    RapidjsonParser() : Parser("rapidjson") {};
    bool parse(char* json, int size) override
    {
        rapidjson::Document d;
        d.Parse(json, size);

        return !d.HasParseError();
    }

    private:
    std::unordered_map<rapidjson::ParseErrorCode, Parser> error_correspondances {
        { rapidjson::ParseErrorCode::kParseErrorNone, ParsingResult::ok },
        { rapidjson::ParseErrorCode::kParseErrorDocumentEmpty, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorDocumentRootNotSingular, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorValueInvalid, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorObjectMissName, ParsingResult::other_error},
        { rapidjson::ParseErrorCode::kParseErrorObjectMissColon, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorObjectMissCommaOrCurlyBracket, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorArrayMissCommaOrSquareBracket, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorStringUnicodeEscapeInvalidHex, ParsingResult::encoding_error },
        { rapidjson::ParseErrorCode::kParseErrorStringUnicodeSurrogateInvalid, ParsingResult::string_error },
        { rapidjson::ParseErrorCode::kParseErrorStringEscapeInvalid, ParsingResult::string_error },
        { rapidjson::ParseErrorCode::kParseErrorStringMissQuotationMark, ParsingResult::string_error },
        { rapidjson::ParseErrorCode::kParseErrorStringInvalidEncoding, ParsingResult::string_error },
        { rapidjson::ParseErrorCode::kParseErrorNumberTooBig, ParsingResult::number_error },
        { rapidjson::ParseErrorCode::kParseErrorNumberMissFraction, ParsingResult::number_error },
        { rapidjson::ParseErrorCode::kParseErrorNumberMissExponent, ParsingResult::number_error },
        { rapidjson::ParseErrorCode::kParseErrorTermination, ParsingResult::other_error },
        { rapidjson::ParseErrorCode::kParseErrorUnspecificSyntaxError, ParsingResult::other_error },
    };
};
}

#endif