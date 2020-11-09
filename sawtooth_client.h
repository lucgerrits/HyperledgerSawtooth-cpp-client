//////////////////////////////////////////////////////////////////
//To show errors:
void abort(void) __THROW __attribute__((__noreturn__));
#define TEST_FAILURE(msg)                                        \
    do                                                           \
    {                                                            \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, msg); \
        abort();                                                 \
    } while (0)
#define EXPECT(x, c) __builtin_expect((x), (c))
#define CHECK(cond)                                        \
    do                                                     \
    {                                                      \
        if (EXPECT(!(cond), 0))                            \
        {                                                  \
            TEST_FAILURE("test condition failed: " #cond); \
        }                                                  \
    } while (0)
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//Define some constants:
#define LOAD_DEFAULT_KEYS true
#define SAWTOOTH_REST_API "http://localhost:8008"
#define PRIVATE_KEY_SIZE 32
#define PUBLIC_KEY_SIZE 64
#define PUBLIC_KEY_SERILIZED_SIZE 33
#define PRIVATE_KEY "0152fdf6e81e0a694cf8f361e14d32d8b25e605c669dc06940c500c546ee8a3f"
#define PUBLIC_KEY "0265e1a0353a5de3ad229f0c96fe4851949c856d5ad57717d4615c981ddea1f841"
#define SIGNATURE_SERILIZED_SIZE 64
#define HASH_SHA256_SIZE 32
#define SETTINGS_CARTP_FACTORY_ADDRESS "000000a87cb5eafdcca6a89a6f6aa92a4b7cb206c8aaa93d80a76817373ca1c7634a4b"
#define NONCE_SIZE 10

#define VERBOSE false

//secp256k1
#include "secp256k1/include/secp256k1.h"
//////////////////////////////////////////////////////////////////
//crypto++
#include "cryptopp/cryptlib.h"
#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
#include "cryptopp/sha.h"
using CryptoPP::SHA256;
using CryptoPP::SHA512;
#include "cryptopp/filters.h"
using CryptoPP::Redirector;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

//////////////////////////////////////////////////////////////////
//protobuf
#include "protobuf/src/google/protobuf/util/json_util.h"
#include "protos_pb_h/transaction.pb.h"
#include "protos_pb_h/batch.pb.h"
#include "protos_pb_h/seth.pb.h"
//////////////////////////////////////////////////////////////////

#ifndef SAWTOOTH_CLIENT
#define SAWTOOTH_CLIENT

struct SawtoothKeys
{
    std::string privKey = PRIVATE_KEY;
    std::string pubKey = PUBLIC_KEY;
    SECP256K1_API::secp256k1_pubkey publicKey;
    unsigned char privateKey[PRIVATE_KEY_SIZE];
    unsigned char publicKey_serilized[PUBLIC_KEY_SERILIZED_SIZE];
};

struct SawtoothSigature
{
    SECP256K1_API::secp256k1_ecdsa_signature signature;
    std::string signature_serilized_str = "";
    unsigned char signature_serilized[SIGNATURE_SERILIZED_SIZE];
};

struct SawtoothMessage
{
    std::string message = "";
    std::string message_hash_str = "";
    unsigned char message_hash_char[HASH_SHA256_SIZE];
};

std::string UcharToHexStr(unsigned char *data, int len);
int chhex(char ch);
void HexStrToUchar(unsigned char *dest, const char *source, int bytes_n);
void generateRandomBytes(unsigned char *key, int length);
std::string sha256Data(std::string data);
std::string sha512Data(std::string data);
void emptyBytes(unsigned char *data, int len);
std::string ToHex(std::string s, bool upper_case);
void buildIntkeyAddress(std::string txnFamily, std::string entryName, unsigned char *ouput35bytes);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
int sendData(std::string data, std::string api_endpoint);
int LoadKeys(
    SECP256K1_API::secp256k1_context *ctx,
    SawtoothKeys &Keys);
int GenerateKeyPair(
    SECP256K1_API::secp256k1_context *ctx,
    SawtoothKeys &Keys);
void printProtoJson(google::protobuf::Message &message);

#endif