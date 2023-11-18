#include <string>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <event2/bufferevent.h>

#include "insecure-data-handler.h"

#include "model/networking/utility/variants.h"

using namespace model;

using json = nlohmann::json;

namespace {
  struct Packet {
      std::string payload;
  };

  void to_json(json &j, const Packet &p) {
      j = json{{"payload", p.payload}};
  }

  void from_json(const json &j, Packet &p) {
      j.at("payload").get_to(p.payload);
  }
} // namespace

DataHandlerType InsecureDataHandler::GetType() {
  return type;
}

std::string InsecureDataHandler::FormatSend(std::string &data) {
  // create packet
  json packet = Packet { data };

  return packet.dump();
}

std::string InsecureDataHandler::FormatRead(std::string &data) {
  try {
    // check packet format
    auto packet = json::parse(data).template get<Packet>();
    
    // extract plaintext from packet
    return packet.payload;
    
  } catch (std::exception _) {
    // invalid packet - KISS
    return "";
  }
}