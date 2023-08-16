#include <string>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <event2/bufferevent.h>

#include "insecure-data-handler.h"
#include "variants.h"

using namespace model;

using json = nlohmann::json;

DataHandlerType InsecureDataHandler::GetType() {
  return type;
}

std::string InsecureDataHandler::FormatSend(std::string &data) {
  // create packet
  std::string packet = json({
    { "payload", data },
  }).dump();

  return packet;
}

std::string InsecureDataHandler::FormatRead(std::string &data) {
  // check packet format
  json packet = json::parse(data);
  
  if (!packet.contains("payload")) {
    // invalid packet, payload missing - KISS
    return "";
  }

  // extract plaintext from packet
  return packet.at("payload");
}