using Newtonsoft.Json;

namespace CsChatClient
{
    public interface ISerializable
    {
        void Serialize(JsonWriter writer);
        bool Unserialize(JsonReader reader);
    }
}
