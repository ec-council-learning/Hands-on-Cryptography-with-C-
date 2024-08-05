// src/identity.cpp
#include "identity.h"
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/ec_group.h> // EC_Group
#include <botan/pkcs8.h> // PKCS8::PEM_encode
#include <botan/x509_key.h> // X509::PEM_encode
#include <fstream> // std::ofstream
#include <filesystem> // std::filesystem

/// \brief Default constructor. Creates an ECDSA identity for EC domain secp256r1.
Siggie::Identity::Identity() {
  Botan::AutoSeeded_RNG rng;

  m_private_key = std::make_unique<PrivateKeyImpl>(
    rng, Botan::EC_Group("secp256r1")
  );

  m_public_key = std::make_unique<PublicKeyImpl>(
    Botan::EC_Group("secp256r1"), m_private_key->public_point()
  );
}

/// \brief Creates an identity with file \a filename and pass \a passphrase.
Siggie::Identity::Identity(
  const std::string& filename,
  const std::string& passphrase
) {
  std::string err_string;

  try {
    Botan::DataSource_Stream input(filename);
    std::unique_ptr<Botan::Private_Key> priv = Botan::PKCS8::load_key(
      input,
      passphrase
    );

    m_private_key = std::make_unique<PrivateKeyImpl>(
      priv->pkcs8_algorithm_identifier(), priv->private_key_bits()
    );

    m_public_key = std::make_unique<PublicKeyImpl>(
      Botan::EC_Group("secp256r1"), m_private_key->public_point()
    );

    return ;
  }
  catch(Botan::Exception& e) {
    err_string = e.what();
  }

  // private key could not be loaded
  throw std::runtime_error("Loading ECDSA private key failed (" + err_string + ")");
}

/// \brief Copy constructor. Creates an identity based on the other's private key.
Siggie::Identity::Identity(const Identity& other) {
  Botan::AutoSeeded_RNG rng;

  m_private_key = std::make_unique<PrivateKeyImpl>(
    rng, Botan::EC_Group("secp256r1"), (other.m_private_key)->private_value()
  );

  m_public_key = std::make_unique<PublicKeyImpl>(
    Botan::EC_Group("secp256r1"), m_private_key->public_point()
  );
}

/// \brief Default class destructor. Uses the opportunity for zeroing keys.
Siggie::Identity::~Identity() {
  // take-over ownership
  PrivateKeyImpl* priv = m_private_key.release();
  PublicKeyImpl* pub = m_public_key.release();

  // zeroing key memory space
  std::memset(reinterpret_cast<void*>(&priv), 0, sizeof(priv));
  std::memset(reinterpret_cast<void*>(&pub), 0, sizeof(pub));

  // pointer deletion
  delete priv;
  delete pub;
}

/// \brief Saves the private key to file \a filename with password \a passphrase.
void Siggie::Identity::Export(
  const std::string& filename,
  const std::string& passphrase
) const {
  std::filesystem::directory_entry entry{filename};
  if (entry.exists())
    throw std::runtime_error("Error: File overwrite not yet supported.");

  Botan::AutoSeeded_RNG rng;
  auto priv_bytes = Botan::PKCS8::BER_encode(*m_private_key, rng, passphrase);
  auto pub_bytes  = Botan::X509::PEM_encode(*m_public_key);

  std::ofstream out_priv(filename),
                out_pub(filename + ".pub");

  out_priv << std::string(priv_bytes.begin(), priv_bytes.end()) << std::flush;
  out_pub  << pub_bytes << std::flush;

  out_priv.close();
  out_pub.close();
}

/// \brief Exports the private key instance for use outside of the class.
std::unique_ptr<Siggie::PrivateKeyImpl> Siggie::Identity::ExportPrivateKey() const {
  return std::make_unique<PrivateKeyImpl>(
    m_private_key->pkcs8_algorithm_identifier(),
    m_private_key->private_key_bits()
  );
}

/// \brief Exports the public key instance for use outside of the class.
std::unique_ptr<Siggie::PublicKeyImpl> Siggie::Identity::ExportPublicKey() const {
  return std::make_unique<PublicKeyImpl>(
    Botan::EC_Group("secp256r1"),
    m_private_key->public_point()
  );
}