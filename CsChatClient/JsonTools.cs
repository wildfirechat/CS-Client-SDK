using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            return JsonConvert.SerializeObject(value);
        } 

        static public string getNextString(JsonReader reader)
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

        static public int getNextInt(JsonReader reader)
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

        static public bool getNextBoolean(JsonReader reader)
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

        static public Int64 getNextBigInt(JsonReader reader)
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


        static public object getNextObject(JsonReader reader, bool isInArray, Type type)
        {
            if (!isInArray)
                reader.Read();

            if(type == typeof(List<string>))
            {
                return getNextStringList(reader, isInArray);
            }
            Serializable s = (Serializable)Activator.CreateInstance(type);
            if(s.Unserialize(reader))
            {
                return s;
            }
            return null;
        }

        static public List<string> getNextStringList(JsonReader reader, bool isInArray)
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
        static public List<int> getNextIntList(JsonReader reader, bool isInArray)
        {
            List<int> result = new List<int>();
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.EndArray:
                        return result;
                    case JsonToken.Integer:
                        result.Add((int)((Int64)reader.Value));
                        break;
                    default:
                        Console.WriteLine("not expact value");
                        break;
                }
            }
            return null;
        }

        static public void serializeList<T>(JsonWriter writer, List<T> value)
        {
            writer.WriteStartArray();
            foreach(var v in value)
            {
                if (typeof(Serializable).IsAssignableFrom(typeof(T)))
                {
                    Serializable s = (Serializable)v;
                    s.Serialize(writer);
                } else
                {
                    writer.WriteValue(v);
                }
            }
            writer.WriteEndArray();
        }
        static public void serializeStringList(JsonWriter writer, List<string> value)
        {
            writer.WriteStartArray();
            foreach (var v in value)
            {
                writer.WriteValue(v);
            }
            writer.WriteEndArray();
        }

    }
}
