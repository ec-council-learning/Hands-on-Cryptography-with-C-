// src/garden.h
#ifndef __BEETRANSPORT_GARDEN_H__
#define __BEETRANSPORT_GARDEN_H__
#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map
#include "flower.h"

namespace BeeTransport {
  class PrivateGarden
  {
  private:
    std::vector<std::string> m_keys;
    std::vector<std::string> m_grains;
    std::vector<std::string> m_breeds;
    std::vector<std::unique_ptr<BeeTransport::Flower>> m_flowers;
    std::map<std::string, std::string> m_parent_of;

  public:
    bool with_debug = false;

    PrivateGarden() : PrivateGarden(8) {}
    PrivateGarden(size_t);

    virtual ~PrivateGarden() {
      m_flowers.clear();
      m_keys.clear();
      m_grains.clear();
    }

    inline void SetDebugMode(bool d) { with_debug = d; }

    /// \brief Returns the number of flowers in the garden
    unsigned int CountFlowers() const { return m_flowers.size(); }

    /// \brief Creates new Flower instances by key size
    void SeedNewFlowers();

    /// \brief Safely wraps pollen grains to prepare for safe transport
    void PrepareSafeBeeTransport();

    /// \brief Uses pollen grains to create new Flower instances
    void ExecuteSafeBeeTransport();

    /// \brief Returns the string representation of a PrivateGarden
    operator std::string() const;

  private:
    typedef std::map<std::string, std::vector<std::string>> hierarchy_map_t;

    /// \brief Makes a BeeTransport::Flower instance (factory)
    std::unique_ptr<BeeTransport::Flower> make_flower(const std::string&);

    /// \brief Returns the root BeeTransport::Flower seed
    std::string get_root_seed(const std::string&) const;

    /// \brief Returns the hierarchy map with children by parent seed
    hierarchy_map_t get_hierarchy() const;

  };
}
#endif