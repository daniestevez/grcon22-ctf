// Copyright (c) 2022 Daniel Estevez
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <compressor.h>
#include <pubkey.h>
#include <serialize.h>
#include <streams.h>
#include <version.h>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

void usage(char **argv) {
    std::cerr << "Usage: " << argv[0] << " codec_version" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv);
        return 1;
    }

    codec_version_t codec_version;
    *reinterpret_cast<std::uint8_t*>(&codec_version) = std::stoi(argv[1]);

    std::vector<std::uint8_t> tx_data;
    char c;
    std::uint8_t b;
    while (std::cin.good()) {
        std::cin >> c;
        if (!std::cin.good()) break;
        b = c >= 'a' ? 10 + c - 'a' : c - '0';
        std::cin >> c;
        b <<= 4;
        b |= c >= 'a' ? 10 + c - 'a' : c - '0';
        tx_data.push_back(b);
    }
    fprintf(stderr, "input\nlength = %ld\ndata = ", tx_data.size());
    for (auto aa : tx_data) {
        fprintf(stderr, "%02x", aa);
    }
    fprintf(stderr, "\n");

    CTransactionRef tx;
    // This is needed to initialize secp256k1_context_verify
    ECCVerifyHandle ecc_handle;

    VectorInputStream stream(&tx_data, SER_NETWORK, PROTOCOL_VERSION);
    stream >> CTxCompressor(tx, codec_version);
    std::vector<std::uint8_t> tx_data_out;
    VectorOutputStream stream_out(&tx_data_out, SER_NETWORK, PROTOCOL_VERSION);
    stream_out << *tx;

    fprintf(stderr, "output\n");
    for (auto aa : tx_data_out) {
        fprintf(stderr, "%02x", aa);
    }
    fprintf(stderr, "\n");

    return 0;
}
