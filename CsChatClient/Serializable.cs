using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient
{
    public interface Serializable
    {
        void Serialize(JsonWriter writer);
        bool Unserialize(JsonReader reader);
    }
}
