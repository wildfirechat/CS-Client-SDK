#include "MessagePayload.h"
#include "../JsonTools.h"

namespace WFCLib {

MessagePayload::MessagePayload()
{
}


MessagePayload::~MessagePayload()
{
}

void MessagePayload::Unserialize(const void *pvalue) {

    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int type;
    getValue(value, "type", contentType);

//            std::string searchableContent;
    getValue(value, "searchableContent", searchableContent);

//            std::string pushContent;
    getValue(value, "pushContent", pushContent);

//            std::string content;
    getValue(value, "content", content);

//            std::string binaryContent;
    getValue(value, "binaryContent", binaryContent);
    binaryContent = base64Decode(binaryContent);

//            std::string localContent;
    getValue(value, "localContent", localContent);

//            int mediaType;
    getValue(value, "mediaType", mediaType);

//            std::string remoteMediaUrl;
    getValue(value, "remoteMediaUrl", remoteMediaUrl);

//            std::string localMediaPath;
    getValue(value, "localMediaPath", localMediaPath);
//
//            int mentionedType;
    getValue(value, "mentionedType", mentionedType);

//            std::list<std::string> mentionedTargets;
    getValue(value, "mentionedTargets", mentionedTargets);
    
    getValue(value, "extra", extra);
}


void MessagePayload::Serialize(void *pwriter) const  {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            int type;
    writer.String("type");
    writer.Int(contentType);

//            std::string searchableContent;
    writer.String("searchableContent");
    writer.String(searchableContent);

//            std::string pushContent;
    writer.String("pushContent");
    writer.String(pushContent);

//            std::string content;
    writer.String("content");
    writer.String(content);

//            std::string binaryContent;
    writer.String("binaryContent");
    std::string base64edStr = base64Encode(binaryContent);
    writer.String(base64edStr);

//            std::string localContent;
    writer.String("localContent");
    writer.String(localContent);

//            int mediaType;
    writer.String("mediaType");
    writer.Int(mediaType);

//            std::string remoteMediaUrl;
    writer.String("remoteMediaUrl");
    writer.String(remoteMediaUrl);

//            std::string localMediaPath;
    writer.String("localMediaPath");
    writer.String(localMediaPath);
//
//            int mentionedType;
    writer.String("mentionedType");
    writer.Int(mentionedType);

//            std::list<std::string> mentionedTargets;
    writer.String("mentionedTargets");
    writer.StartArray();
    for (std::list<std::string>::const_iterator it = mentionedTargets.begin(); it != mentionedTargets.end(); ++it) {
        writer.String(*it);
    }
    writer.EndArray();

    writer.String("extra");
    writer.String(extra);
    
    writer.EndObject();
}

};
