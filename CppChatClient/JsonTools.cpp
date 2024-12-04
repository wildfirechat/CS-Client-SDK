//
//  JsonTools.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "JsonTools.h"

namespace WFCLib {

 /**
     * Given a source string of length len, this returns the amount of
     * memory the destination string should have.
     *
     * remember, this is integer math
     * 3 bytes turn into 4 chars
     * ceiling[len / 3] * 4 + 1
     *
     * +1 is for any extra null.
     */
#define modp_b64_encode_len(A) ((A+2)/3 * 4 + 1)
    
    /**
     * Given a base64 string of length len,
     *   this returns the amount of memory required for output string
     *  It maybe be more than the actual number of bytes written.
     * NOTE: remember this is integer math
     * this allocates a bit more memory than traditional versions of b64
     * decode  4 chars turn into 3 bytes
     * floor[len * 3/4] + 2
     */
#define modp_b64_decode_len(A) (A / 4 * 3 + 2)

static void init_conversion_tables(void);

/*  Global variables used in this source file only */
static unsigned char char_to_base64[128];
static char base64_to_char[64];
static int tables_initialised = 0;

int EncodeBase64(const unsigned char* sSrc, unsigned char* sTarget, const int nSize) {
    int target_size = 0;                /*  Length of target buffer          */
    int nb_block;                       /*  Total number of blocks           */
    unsigned char
    *p_source,                      /*  Pointer to source buffer         */
    *p_target,                      /*  Pointer to target buffer         */
    value;                          /*  Value of Base64 byte             */

    if (nSize == 0)
        return (0);

    if (!tables_initialised)
        init_conversion_tables();

    /*    Bit positions
                  | byte 1 | byte 2 | byte 3 |
    source block   87654321 87654321 87654321         -> 3 bytes of 8 bits

                  | byte 1 | byte 2 | byte 3 | byte 4 |
    Encoded block  876543   218765   432187   654321  -> 4 bytes of 6 bits
    */

    nb_block = (int)(nSize / 3);

    /*  Check if we have a partially-filled block                            */
    if (nb_block * 3 != (int) nSize)
        nb_block++;

    target_size = (int) nb_block * 4;
    sTarget [target_size] = '\0';

    p_source = (unsigned char*)sSrc;          /*  Point to start of buffers        */
    p_target = sTarget;

    while (nb_block--) {
        /*  Byte 1                                                           */
        value       = *p_source >> 2;
        *p_target++ = base64_to_char [value];

        /*  Byte 2                                                           */
        value = (*p_source++ & 0x03) << 4;

        if ((int)(p_source - sSrc) < nSize)
            value |= (*p_source & 0xF0) >> 4;

        *p_target++ = base64_to_char [value];

        /*  Byte 3 - pad the buffer with '=' if block not completed          */
        if ((int)(p_source - sSrc) < nSize) {
            value = (*p_source++ & 0x0F) << 2;

            if ((int)(p_source - sSrc) < nSize)
                value |= (*p_source & 0xC0) >> 6;

            *p_target++ = base64_to_char [value];
        } else
            *p_target++ = '=';

        /*  Byte 4 - pad the buffer with '=' if block not completed          */
        if ((int)(p_source - sSrc) < nSize) {
            value       = *p_source++ & 0x3F;
            *p_target++ = base64_to_char [value];
        } else
            *p_target++ = '=';
    }

    return (target_size);
}

int DecodeBase64(const unsigned char* sSrc, unsigned char* sTarget, const int nSize) {
    int
    target_size = 0;                /*  Length of target buffer          */
    int
    nb_block;                       /*  Total number of block            */
    unsigned char
    value,                          /*  Value of Base64 byte             */
    *p_source,                      /*  Pointer in source buffer         */
    *p_target;                      /*  Pointer in target buffer         */

    int        n;

    if (nSize == 0)
        return (0);

    if (!tables_initialised)
        init_conversion_tables();

    /*  Bit positions
                  | byte 1 | byte 2 | byte 3 | byte 4 |
    Encoded block  654321   654321   654321   654321  -> 4 bytes of 6 bits
                  | byte 1 | byte 2 | byte 3 |
    Decoded block  65432165 43216543 21654321         -> 3 bytes of 8 bits
    */

    nb_block    = nSize / 4;
    target_size = (int) nb_block * 3;
    sTarget [target_size] = '\0';

    p_source = (unsigned char*) sSrc;          /*  Point to start of buffers        */
    p_target = sTarget;

    while (nb_block--) {
        /*  Byte 1                                                           */
        *p_target    = char_to_base64 [(unsigned char) * p_source++] << 2;
        value        = char_to_base64 [(unsigned char) * p_source++];
        *p_target++ += ((value & 0x30) >> 4);

        /*  Byte 2                                                           */
        *p_target    = ((value & 0x0F) << 4);
        value        = char_to_base64 [(unsigned char) * p_source++];
        *p_target++ += ((value & 0x3C) >> 2);

        /*  Byte 3                                                           */
        *p_target    = (value & 0x03) << 6;
        value        = char_to_base64 [(unsigned char) * p_source++];
        *p_target++ += value;
    }

    // ����ĩβ�ж��ٸ�'='
    for (n = nSize - 1; n >= 0; --n) {
        if (sSrc[n] == '=')
            target_size--;
        else
            break;
    }

    return (target_size);
}

static void init_conversion_tables(void) {
    unsigned char
    value,                          /*  Value to store in table          */
    offset,
    index;                          /*  Index in table                   */

    /*  Reset the tables                                                     */
    memset(char_to_base64, 0, sizeof(char_to_base64));
    memset(base64_to_char, 0, sizeof(base64_to_char));

    value  = 'A';
    offset = 0;

    for (index = 0; index < 62; index++) {
        if (index == 26) {
            value  = 'a';
            offset = 26;
        } else if (index == 52) {
            value  = '0';
            offset = 52;
        }

        base64_to_char [index] = value + index - offset;
        char_to_base64 [value + index - offset] = index;
    }

    base64_to_char [62]  = '+';
    base64_to_char [63]  = '/';
    char_to_base64 ['+'] = 62;
    char_to_base64 ['/'] = 63;

    tables_initialised = 1;
}

std::string base64Decode(const std::string &base64str) {
    if (base64str.empty()) {
        return std::string();
    }

    int len2 = (int)modp_b64_decode_len(base64str.size());
    char * tmp = (char *)calloc( len2, sizeof(unsigned char));
    int len = (int)DecodeBase64((unsigned char*)base64str.c_str(), (unsigned char*)tmp, (int)base64str.size());
    std::string result = std::string(tmp, len);
    free(tmp);

    return result;
}

std::string base64Encode(const std::string &str) {
    if (str.empty()) {
        return std::string();
    }

    unsigned int tmpLen = (unsigned int)str.length();
    const unsigned char *ptmp = (const unsigned char *)str.c_str();


    int dstlen = modp_b64_encode_len(tmpLen);

    char* dstbuf = (char*)malloc(dstlen);
    memset(dstbuf, 0, dstlen);

    int retsize = EncodeBase64(ptmp, (unsigned char*)dstbuf, tmpLen);
    dstbuf[retsize] = '\0';


    std::string result = std::string(dstbuf);
    free(dstbuf);
    dstbuf = NULL;

    return result;
}

bool getValue(const Value &value, const std::string &tag, int &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt()) {
            ret = v.GetInt();
            return true;
        }
    }
    return false;
}

bool getValue(const Value &value, const std::string &tag, long &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt64()) {
            ret = v.GetInt64();
            return true;
        } else if (v.IsInt()) {
            ret = v.GetInt();
            return true;
        }
    }
    return false;
}

bool getValue(const Value &value, const std::string &tag, int64_t &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt64()) {
            ret = v.GetInt64();
            return true;
        }
    }
    return false;
}

bool getValue(const Value &value, const std::string &tag, bool &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsBool()) {
            ret = v.GetBool();
            return true;
        }
    }
    return false;
}


bool getValue(const Value &value, const std::string &tag, std::string &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsString()) {
            ret = v.GetString();
            return true;
        }
    }
    return false;
}

bool getValue(const Value &value, const std::string &tag, Serializable &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsObject()) {
            ret.Unserialize(&v);
            return true;
        }
    }
    return false;
}

bool getValue(const Value &value, const std::string &tag, std::list<std::string> &ret) {
    if (value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsArray()) {
            for (int i = 0; i < v.Size(); i++) {
                const Value &t = v[i];
                if (t.IsString()) {
                    ret.push_back(t.GetString());
                }
            }
            return true;
        }
    }
    return false;
}


bool JsonParser::getValue(const std::string &tag, int &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt()) {
            ret = v.GetInt();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, long &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt64()) {
            ret = v.GetInt64();
            return true;
        } else if (v.IsInt()) {
            ret = v.GetInt();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, int64_t &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsInt64()) {
            ret = v.GetInt64();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, float &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsFloat()) {
            ret = v.GetFloat();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, double &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsDouble()) {
            ret = v.GetDouble();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, bool &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsBool()) {
            ret = v.GetBool();
            return true;
        }
    }
    return false;
}


bool JsonParser::getValue(const std::string &tag, std::string &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsString()) {
            ret = v.GetString();
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, Serializable &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsObject()) {
            ret.Unserialize(&v);
            return true;
        }
    }
    return false;
}

bool JsonParser::getValue(const std::string &tag, std::list<std::string> &ret) {
    if (parsed && value.HasMember(tag)) {
        const Value &v = value[tag];
        if (v.IsArray()) {
            for (int i = 0; i < v.Size(); i++) {
                const Value &t = v[i];
                if (t.IsString()) {
                    ret.push_back(t.GetString());
                }
            }
            return true;
        }
    }
    return false;
}

JsonParser::JsonParser(const std::string &json) :value(), parsed(false) {
    if (value.Parse(json).HasParseError()) {
        printf("\nParsing to document failure(%s).\n", json.c_str());
        return ;
    }
    parsed = true;
}

JsonParser::~JsonParser() { }

std::list<std::string> parseStringList(const std::string &jsonListStr) {
    std::list<std::string> result;
    
    Document document;
    if (document.Parse(jsonListStr).HasParseError()) {
        printf("\nParsing to document failure(%s).\n", jsonListStr.c_str());
        return result;
    }
    
    if (document.IsArray()) {
        for (int i = 0; i < document.Size(); i++) {
            const Value& object = document[i];
            
            if (object.IsString()) {
                result.push_back(object.GetString());
            }
        }
    }
    
    return result;
}


void JsonBuilder::setValue(const std::string &tag, int value) {
    if (value) {
        writer.String(tag);
        writer.Int(value);
    }
}
void JsonBuilder::setValue(const std::string &tag, long value) {
    if (value) {
        writer.String(tag);
        writer.Int((int)value);
    }
}

void JsonBuilder::setValue(const std::string &tag, float value) {
    if (value) {
        writer.String(tag);
        writer.Double(value);
    }
}

void JsonBuilder::setValue(const std::string &tag, double value) {
    if (value) {
        writer.String(tag);
        writer.Double(value);
    }
}
void JsonBuilder::setValue(const std::string &tag, int64_t value) {
    if (value) {
        writer.String(tag);
        writer.Int64(value);
    }
}

void JsonBuilder::setValue(const std::string &tag, bool value) {
    if (value) {
        writer.String(tag);
        writer.Bool(value);
    }
}

void JsonBuilder::setValue(const std::string &tag, const std::string &value) {
    writer.String(tag);
    writer.String(value);
}

void JsonBuilder::setValue(const std::string &tag, const Serializable *pValue) {
    writer.String(tag);
    writer.StartObject();
    
    pValue->Serialize(&writer);
    
    writer.EndObject();
}

void JsonBuilder::setValue(const std::string &tag, const std::list<std::string> &value) {
    writer.String(tag);
    writer.StartArray();
    for (std::list<std::string>::const_iterator it = value.begin(); it != value.end(); ++it) {
        writer.String(*it);
    }
    writer.EndArray();
}

std::string JsonBuilder::build() {
    writer.EndObject();
    return std::string(sb.GetString(), sb.GetLength());
}

JsonBuilder::JsonBuilder():sb(), writer(sb) {
    writer.StartObject();
}

JsonBuilder::~JsonBuilder() {
    
}

};
