using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using CsChatClient.Messages;
using System.Collections;

namespace CsChatClient
{
    public class WfcJsonConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            if (typeof(MessageContent).IsAssignableFrom(objectType))
            {
                return true;
            }


            if (typeof(ISerializable).IsAssignableFrom(objectType))
            {
                return true;
            }

            if (objectType == typeof(Dictionary<string, long>))
            {
                return true;
            }

            if (HasImplementedRawGeneric(objectType, typeof(IList<>)))
            {
                Type[] types = objectType.GetGenericArguments();
                if(types != null && types.Length == 1)
                {
                    Type t = types[0];
                    if (typeof(ISerializable).IsAssignableFrom(t))
                    {
                        return true;
                    }
                }
            }

            return false;
        }


        private bool HasImplementedRawGeneric(Type type, Type generic)
        {
            return type.GetInterfaces().Any(x => generic == (x.IsGenericType ? x.GetGenericTypeDefinition() : x));
        }

        public override object ReadJson(JsonReader reader, Type objectType,  object existingValue, JsonSerializer serializer)
        {
            if (typeof(ISerializable).IsAssignableFrom(objectType))
            {
                ISerializable s = (ISerializable)Activator.CreateInstance(objectType);
                if (s.Unserialize(reader))
                {
                    return s;
                }
            }
            else if (HasImplementedRawGeneric(objectType, typeof(IList<>)))
            {
                Type t = objectType.GetGenericArguments()[0];
                if (typeof(ISerializable).IsAssignableFrom(t))
                {
                    var result = Activator.CreateInstance(objectType);
                    while (reader.Read())
                    {
                        switch (reader.TokenType)
                        {
                            case JsonToken.StartObject:
                                {
                                    var msg = (GetNextObject(reader, true, t, serializer));
                                    ((IList)result).Add((ISerializable)msg);
                                }
                                break;
                            case JsonToken.EndArray:
                                return result;
                            default:
                                break;

                        }
                    }
                    return null;
                } else if(objectType == typeof(List<string>))
                {
                    return JsonTools.GetNextStringList(reader, false);
                }
                else if (objectType == typeof(List<int>))
                {

                } 
                
            }
            else if (objectType == typeof(Dictionary<string, long>))
            {
                return JsonTools.GetNetStringLongMap(reader);
            }

            return null;
        }


        private string GetNextString(JsonReader reader)
        {
            if(reader.Read() && reader.TokenType == JsonToken.String)
            {
                return (string)reader.Value;
            } else
            {
                throw new Exception();
            }
        }
        private int GetNextInt(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Integer)
            {
                long n = (long)reader.Value;
                return (int)n;
            }
            else
            {
                throw new Exception();
            }
        }
        private bool GetNextBoolean(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Boolean)
            {
                return (bool)reader.Value;
            }
            else
            {
                throw new Exception();
            }
        }

        private long GetNextBigInt(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Integer)
            {
                long n = (long)reader.Value;
                return n;
            }
            else
            {
                throw new Exception();
            }
        }

        private object GetNextObject(JsonReader reader, bool isInArray, Type type, JsonSerializer serializer)
        {
            if(!isInArray)
                reader.Read();

            return ReadJson(reader, type, null, serializer);
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            if (typeof(MessageContent).IsAssignableFrom(value.GetType()))
            {
                MessageContent content = (MessageContent)value;
                MessagePayload payload = content.Encode();
                
                payload.ContentType = content.GetMessageType();
                payload.MentionedType = content.MentionedType;
                payload.MentionedTargets = content.MentionedTargets;
                payload.Extra = content.Extra;
                value = payload;
            }


            if (typeof(ISerializable).IsAssignableFrom(value.GetType()))
            {
                ISerializable s = (ISerializable)value;
                s.Serialize(writer);
            }
            else if (HasImplementedRawGeneric(value.GetType(), typeof(IList<>)))
            {
                Type t = value.GetType().GetGenericArguments()[0];
                if (typeof(ISerializable).IsAssignableFrom(t))
                {
                    writer.WriteStartArray();
                    foreach(var ss in (IList)value)
                    {
                        ISerializable s = (ISerializable)ss;
                        s.Serialize(writer);
                    }
                    writer.WriteEndArray();
                }
                else if (value.GetType() == typeof(List<string>))
                {
                    writer.WriteStartArray();
                    foreach (var ss in (IList)value)
                    {
                        string s = (string)ss;
                        writer.WriteValue(s);
                    }
                    writer.WriteEndArray();
                }
                else if (value.GetType() == typeof(List<int>))
                {
                    writer.WriteStartArray();
                    foreach (var ss in (IList)value)
                    {
                        int s = (int)ss;
                        writer.WriteValue(s);
                    }
                    writer.WriteEndArray();
                }
            }
        }
    }
}
