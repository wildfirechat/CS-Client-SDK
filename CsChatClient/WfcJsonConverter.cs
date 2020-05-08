using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using CsChatClient.Messages;
using CsChatClient.Models;
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


            if (typeof(Serializable).IsAssignableFrom(objectType))
            {
                return true;
            }
          
            if(HasImplementedRawGeneric(objectType, typeof(IList<>)))
            {
                Type[] types = objectType.GetGenericArguments();
                if(types != null && types.Length == 1)
                {
                    Type t = types[0];
                    if (typeof(Serializable).IsAssignableFrom(t))
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
            if (typeof(Serializable).IsAssignableFrom(objectType))
            {
                Serializable s = (Serializable)Activator.CreateInstance(objectType);
                if (s.Unserialize(reader))
                {
                    return s;
                }
            }
            else if (HasImplementedRawGeneric(objectType, typeof(IList<>)))
            {
                Type t = objectType.GetGenericArguments()[0];
                if (typeof(Serializable).IsAssignableFrom(t))
                {
                    var result = Activator.CreateInstance(objectType);
                    while (reader.Read())
                    {
                        switch (reader.TokenType)
                        {
                            case JsonToken.StartObject:
                                {
                                    var msg = (getNextObject(reader, true, t, serializer));
                                    ((IList)result).Add((Serializable)msg);
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
                    return JsonTools.getNextStringList(reader, false);
                }
                else if (objectType == typeof(List<int>))
                {

                }
            }

            return null;
        }


        private string getNextString(JsonReader reader)
        {
            if(reader.Read() && reader.TokenType == JsonToken.String)
            {
                return (string)reader.Value;
            } else
            {
                throw new Exception();
            }
        }
        private int getNextInt(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Integer)
            {
                Int64 n = (Int64)reader.Value;
                return (int)n;
            }
            else
            {
                throw new Exception();
            }
        }
        private bool getNextBoolean(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Boolean)
            {
                return (Boolean)reader.Value;
            }
            else
            {
                throw new Exception();
            }
        }

        private Int64 getNextBigInt(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.Integer)
            {
                Int64 n = (Int64)reader.Value;
                return n;
            }
            else
            {
                throw new Exception();
            }
        }

        private object getNextObject(JsonReader reader, bool isInArray, Type type, JsonSerializer serializer)
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
                MessagePayload payload = content.encode();
                
                payload.contentType = content.getType();
                payload.mentionedType = content.mentionedType;
                payload.mentionedTargets = content.mentionedTargets;
                payload.extra = content.extra;
                value = payload;
            }


            if (typeof(Serializable).IsAssignableFrom(value.GetType()))
            {
                Serializable s = (Serializable)value;
                s.Serialize(writer);
            }
            else if (HasImplementedRawGeneric(value.GetType(), typeof(IList<>)))
            {
                Type t = value.GetType().GetGenericArguments()[0];
                if (typeof(Serializable).IsAssignableFrom(t))
                {
                    writer.WriteStartArray();
                    foreach(var ss in (IList)value)
                    {
                        Serializable s = (Serializable)ss;
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
