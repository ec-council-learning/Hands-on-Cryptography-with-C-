# Makefile
DATA_DIR = ./data
ENC_KEY = `cat $(DATA_DIR)/random32.hex`
ENC_IV = `cat $(DATA_DIR)/random16.hex`
AES = AES-256/GCM

# Botan CLI shortcuts 
B = botan
RNG = $(B) rng --format=hex --auto
RSA = $(B) keygen --algo=RSA
PUB = $(B) pkcs8 --pub-out
CERT= $(B) gen_self_signed --der $(DATA_DIR)/id_rsa
ENC = $(B) cipher --cipher="$(AES)" --key=$(ENC_KEY) --nonce=$(ENC_IV)
DEC = $(B) cipher --cipher="$(AES)" --key=$(ENC_KEY) --nonce=$(ENC_IV) --decrypt
SIGN= $(B) sign $(DATA_DIR)/id_rsa
VER = $(B) verify $(DATA_DIR)/id_rsa.pub

keys:
	@echo "Secret key of 16 bytes in $(DATA_DIR)/random16.hex"; \
		$(RNG) 16 > $(DATA_DIR)/random16.hex
	@echo "Secret key of 32 bytes in $(DATA_DIR)/random32.hex"; \
		$(RNG) 32 > $(DATA_DIR)/random32.hex
	@echo "Secret key of 64 bytes in $(DATA_DIR)/random64.hex"; \
		$(RNG) 64 > $(DATA_DIR)/random64.hex
	@echo "RSA private key in $(DATA_DIR)/id_rsa"; \
		$(RSA) > $(DATA_DIR)/id_rsa
	@echo "RSA public key in $(DATA_DIR)/id_rsa.pub"; \
		$(PUB) $(DATA_DIR)/id_rsa > $(DATA_DIR)/id_rsa.pub
	@echo "X.509 (self-signed) Certificate in $(DATA_DIR)/my_domain.com.cert"; \
		$(CERT) my_domain.com > $(DATA_DIR)/my_domain.com.cert

encrypt:
	@echo "Creating encrypted copy of RSA private key in $(DATA_DIR)/id_rsa.sec"; \
		$(ENC) $(DATA_DIR)/id_rsa > $(DATA_DIR)/id_rsa.sec
decrypt:
	@echo "Decrypting RSA private key in $(DATA_DIR)/id_rsa.dec"; \
		$(DEC) $(DATA_DIR)/id_rsa.sec > $(DATA_DIR)/id_rsa.dec

sign:
	@echo "Signing $(DATA_DIR)/document in $(DATA_DIR)/document.sig"; \
		$(SIGN) $(DATA_DIR)/document > $(DATA_DIR)/document.sig
verify:
	@echo "Verifying ECDSA signature: $(DATA_DIR)/document.sig"; \
		$(VER) $(DATA_DIR)/document $(DATA_DIR)/document.sig