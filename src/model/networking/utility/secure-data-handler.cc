#include <event2/bufferevent.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <string>

#include "model/networking/utility/decode.h"
#include "model/networking/utility/encode.h"
#include "secure-data-handler.h"

using namespace model;

using json = nlohmann::json;

namespace {
struct Packet {
    std::string nonce;
    std::string payload;
};

void to_json(json& j, const Packet& p) {
    j = json{{"nonce", p.nonce}, {"payload", p.payload}};
}

void from_json(const json& j, Packet& p) {
    j.at("nonce").get_to(p.nonce);
    j.at("payload").get_to(p.payload);
}
} // namespace

SecureDataHandler::SecureDataHandler(
    unsigned char* session_key_rx,
    unsigned char* session_key_tx) : session_key_rx(session_key_rx), session_key_tx(session_key_tx) {}

DataHandlerType SecureDataHandler::GetType() {
    return type;
}

std::string SecureDataHandler::FormatSend(std::string& data) {
    // create nonce
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];
    randombytes_buf(nonce, sizeof(nonce));

    // encrypt message with shared secret
    unsigned long long data_len = data.length();
    unsigned char data_ptr[data_len + 1];
    strcpy((char*)data_ptr, data.c_str());

    unsigned char ciphertext[data_len + crypto_aead_xchacha20poly1305_ietf_ABYTES];
    unsigned long long ciphertext_len;

    if (crypto_aead_xchacha20poly1305_ietf_encrypt(
            ciphertext,
            &ciphertext_len,
            data_ptr,
            data_len,
            NULL,
            0,
            NULL,
            nonce,
            session_key_tx.get())) {
        // message encryption failed - KISS
        return "";
    }

    // create packet
    json packet = Packet{Bin2Base64(nonce, crypto_box_NONCEBYTES), Bin2Base64(ciphertext, ciphertext_len)};

    // encode packet with base64
    return packet.dump();
}

std::string SecureDataHandler::FormatRead(std::string& data) {
    try {
        // check packet format
        auto packet = json::parse(data).template get<Packet>();

        // decode packet with base64
        auto [nonce, _] = Base642Bin(packet.nonce);

        auto [ciphertext, ciphertext_len] = Base642Bin(packet.payload);

        // decrypt ciphertext with shared secret
        unsigned char plaintext[ciphertext_len - crypto_aead_xchacha20poly1305_ietf_ABYTES];
        unsigned long long plaintext_len;

        if (crypto_aead_xchacha20poly1305_ietf_decrypt(
                plaintext,
                &plaintext_len,
                NULL,
                ciphertext,
                ciphertext_len,
                NULL,
                0,
                nonce,
                session_key_rx.get())) {
            // message decryption failed - KISS
            free(nonce);
            free(ciphertext);

            return "";
        }

        free(nonce);
        free(ciphertext);

        // cast to string with length specified to avoid losing data from array conversion
        return std::string((char*)plaintext, plaintext_len);

    } catch (std::exception _) {
        // invalid packet - KISS
        return "";
    }
}
