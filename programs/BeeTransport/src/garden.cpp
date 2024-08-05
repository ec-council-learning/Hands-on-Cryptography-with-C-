// src/garden.cpp
#include "garden.h"
#include "camellia.h" // TinyCamellia, MediumCamellia, LargeCamellia
#include <memory>
#include <iostream>
#include <sstream>
#include <botan/auto_rng.h>
#include <botan/base64.h>
#include <botan/block_cipher.h>

using BeeTransport::Flower;
using BeeTransport::TinyCamellia,
      BeeTransport::MediumCamellia,
      BeeTransport::LargeCamellia;

BeeTransport::PrivateGarden::PrivateGarden(size_t count_flowers)  {
  Botan::AutoSeeded_RNG rng;

  for (auto i = 0; i < count_flowers; i++) {
    uint8_t rand_byte = rng.next_byte();
    size_t key_size = 0;

    if (rand_byte <= 85) key_size = 16;
    else if (rand_byte <= 170) key_size = 24;
    else /* uint8_t max 255 */ key_size = 32;

    m_keys.push_back(
      Botan::base64_encode(rng.random_vec(key_size))
    );
  }

  m_parent_of = std::map<std::string, std::string>{};
}

/// \brief Makes a BeeTransport::Flower instance (factory)
std::unique_ptr<Flower> BeeTransport::PrivateGarden::make_flower(
  const std::string& key
) {
  std::unique_ptr<Flower> flower;
  auto seed = Botan::base64_decode(key);

  if (seed.size() == 16)
    flower = std::make_unique<TinyCamellia>(key);
  else if (seed.size() == 24)
    flower = std::make_unique<MediumCamellia>(key);
  else /* seed.size() == 32 */
    flower = std::make_unique<LargeCamellia>(key);

  // Look-above container for faster parent discovery
  m_parent_of.emplace(flower->get_bud(), flower->get_seed()); // (child, parent)

  std::cout << "-> created flower: " << key << std::endl;
  if (with_debug) std::cout << "   -> algorithm: " << flower->name() << std::endl;

  return /* std::move */flower;
}

/// \brief Creates new Flower instances by key size
void BeeTransport::PrivateGarden::SeedNewFlowers() {
  for (auto current_seed : m_keys) {
    std::unique_ptr<Flower> flower = make_flower(current_seed);
    m_flowers.emplace_back(std::move(flower));
  }
}

/// \brief Safely wraps pollen grains to prepare for safe transport
void BeeTransport::PrivateGarden::PrepareSafeBeeTransport() {
  Botan::AutoSeeded_RNG rng;
  for (auto& flower : m_flowers) {
    // Flowers create grains once
    if (flower->has_breed) continue;

    // Flowers create 1 grain for bee's transport
    auto seed = flower->get_seed();
    auto bud = flower->get_bud();
    auto grain = Botan::base64_decode(bud);

    // Keys are encrypted so that bees' cannot unwrap them ;]
    m_grains.emplace_back(flower->encrypt(
      std::string(grain.begin(), grain.end())
    ));

    flower->has_breed = true;
  }
}

/// \brief Uses pollen grains to create new Flower instances
void BeeTransport::PrivateGarden::ExecuteSafeBeeTransport() {
  Botan::AutoSeeded_RNG rng;
  for (int i = 0, m = m_grains.size(); i < m; i++) {
    auto safe_grain = m_grains.at(i);

    // We use an iterator to avoid usage of copy constructors (deleted)
    auto flower = m_flowers.begin() + i;

    // This flower's breed must be created once only
    if (m_breeds.end() != std::find(m_breeds.begin(), m_breeds.end(), (*flower)->get_seed()))
      continue;

    // Keys are decrypted to create the new flower's seed
    // Having the flower instance means you could use: flower->get_bud()
    auto bud = (*flower)->decrypt(safe_grain); // unwrapping bud
    auto bud_bytes = std::vector<uint8_t>(bud.begin(), bud.end());
    auto bud_seed = Botan::base64_encode(bud_bytes);

    // Creates the new baby flower "buddy"
    std::unique_ptr<Flower> buddy = make_flower(bud_seed);

    m_breeds.emplace_back((*flower)->get_seed());
    m_flowers.emplace_back(std::move(buddy));
  }
}

/// \brief Returns the string representation of a PrivateGarden
BeeTransport::PrivateGarden::operator std::string() const {
  std::stringstream stream;
  auto children_of = get_hierarchy();

  for (auto breed : children_of) {
    stream << "- " << breed.first;
    for (auto child : breed.second) {
      stream << std::endl << " -> " << child;
    }
    stream << std::endl;
  }

  return stream.str();
}

/// \brief Returns the root BeeTransport::Flower seed
std::string BeeTransport::PrivateGarden::get_root_seed(
  const std::string& seed
) const {
  typedef std::map<std::string, std::string>::const_iterator parent_it_t;

  // Move up until root-level parent can be found
  parent_it_t iter;
  std::string root = seed;
  while ((iter = m_parent_of.find(root)) != m_parent_of.end()) {
    root = iter->second; // (child, parent)
  }

  return root;
}

std::map<std::string, std::vector<std::string>>
BeeTransport::PrivateGarden::get_hierarchy() const {
  hierarchy_map_t children_of = hierarchy_map_t{};
  for (auto const& flower: m_flowers) {
    auto seed = flower->get_seed();
    auto bud  = flower->get_bud();

    // If the flower has no breed yet, don't display it's bud (not transported)
    if (m_breeds.end() == std::find(m_breeds.begin(), m_breeds.end(), flower->get_seed()))
      continue;

    // Move up until root-level parent found
    std::string parent = get_root_seed(seed);

    // If the current flower has a parent, add this flower to the children
    if (parent != seed) {
      auto root = children_of.find(parent);
      (root->second).emplace_back(bud);
    }
    // Creates the children vector for this flower
    else {
      children_of.emplace(seed, std::vector{bud});
    }
  }

  return children_of;
}