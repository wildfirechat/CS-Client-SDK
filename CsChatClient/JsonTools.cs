using Newtonsoft.Json;
using System;
using System.Collections.Generic;

namespace CsChatClient
{
    public class JsonTools
    {
        public static T Jsonfy<T>(string jsonString)
        {
            WfcJsonConverter convert = new WfcJsonConverter();
            return JsonConvert.DeserializeObject<T>(jsonString, convert);
        }

        public static string Stringfy(object value)
        {
            WfcJsonConverter convert = new WfcJsonConverter();
            return JsonConvert.SerializeObject(value, convert);
        } 

        static public string GetNextString(JsonReader reader)
        {
            if (reader.Read() && reader.TokenType == JsonToken.String)
            {
                return (string)reader.Value;
            }
            else
            {
                throw new Exception();
            }
        }

        static public int GetNextInt(JsonReader reader)
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

        static public bool GetNextBoolean(JsonReader reader)
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

        static public long GetNextBigInt(JsonReader reader)
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


        static public object GetNextObject(JsonReader reader, bool isInArray, Type type)
        {
            if (!isInArray)
                reader.Read();

            if(type == typeof(List<string>))
            {
                return GetNextStringList(reader, isInArray);
            }
            ISerializable s = (ISerializable)Activator.CreateInstance(type);
            if(s.Unserialize(reader))
            {
                return s;
            }
            return null;
        }

        static public Dictionary<string, long> GetNetStringLongMap(JsonReader reader)
        {
            Dictionary<string, long> result = new Dictionary<string, long>();
            string key = null;
            long value = 0;
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.StartObject:
                        key = null;
                        value = 0;
                        break;
                    case JsonToken.EndObject:
                        result.Add(key, value);
                        break;
                    case JsonToken.EndArray:
                        return result;
                    case JsonToken.String:
                        key = (string)reader.Value;
                        break;
                    case JsonToken.Integer:
                        value = (long)reader.Value;
                        break;
                    default:
                        Console.WriteLine("not expact value");
                        break;
                }
            }
            return result;
        }

        static public List<string> GetNextStringList(JsonReader reader, bool isInArray)
        {
            List<string> result = new List<string>();
            while(reader.Read())
            {
                switch(reader.TokenType)
                {
                    case JsonToken.EndArray:
                        return result;
                    case JsonToken.String:
                        result.Add((string)reader.Value);
                        break;
                    default:
                        Console.WriteLine("not expact value");
                        break;
                }
            }
            return null;
        }
        static public List<int> GetNextIntList(JsonReader reader, bool isInArray)
        {
            List<int> result = new List<int>();
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.EndArray:
                        return result;
                    case JsonToken.Integer:
                        result.Add((int)((long)reader.Value));
                        break;
                    default:
                        Console.WriteLine("not expact value");
                        break;
                }
            }
            return null;
        }

        static public void SerializeList<T>(JsonWriter writer, List<T> value)
        {
            writer.WriteStartArray();
            if(value != null)
            {
                foreach (var v in value)
                {
                    if (typeof(ISerializable).IsAssignableFrom(typeof(T)))
                    {
                        ISerializable s = (ISerializable)v;
                        s.Serialize(writer);
                    }
                    else
                    {
                        writer.WriteValue(v);
                    }
                }
            }

            writer.WriteEndArray();
        }
        static public void SerializeStringList(JsonWriter writer, List<string> value)
        {
            writer.WriteStartArray();
            foreach (var v in value)
            {
                writer.WriteValue(v);
            }
            writer.WriteEndArray();
        }

        public static Dictionary<string, long> JsonfyStringLongMap(string jsonString)
        {
            Dictionary<string, long> resul = new Dictionary<string, long>();

            return null;
        }

    }
}
