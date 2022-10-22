ifndef BITCOINSATELLITE
$(error BITCOINSATELLITE env variable needs to be set to the bitcoinsatellite repo path)
endif

CFLAGS= -Wall
CC= g++

FILES= decompress_transaction.cpp
FILES+= $(BITCOINSATELLITE)/src/libbitcoin_common.a
FILES+= $(BITCOINSATELLITE)/src/libbitcoin_consensus.a
FILES+= $(BITCOINSATELLITE)/src/libbitcoin_util.a
FILES+= $(BITCOINSATELLITE)/src/libbitcoin_node.a
FILES+= $(BITCOINSATELLITE)/src/crypto/libbitcoin_crypto_base.a
FILES+= $(BITCOINSATELLITE)/src/crypto/libbitcoin_crypto_avx2.a
FILES+= $(BITCOINSATELLITE)/src/crypto/libbitcoin_crypto_sse41.a
FILES+= $(BITCOINSATELLITE)/src/crypto/libbitcoin_crypto_x86_shani.a
FILES+= $(BITCOINSATELLITE)/src/secp256k1/.libs/libsecp256k1.a

decompress_transaction: decompress_transaction.cpp $(FILES)
	$(CC) $(CFLAGS) -o $@ -I$(BITCOINSATELLITE)/src $^

clean:
	rm -f decompress_transaction
