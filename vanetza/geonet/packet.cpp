#include "packet.hpp"

namespace vanetza
{
namespace geonet
{

std::size_t size(const detail::PacketVariant& packet, OsiLayer layer)
{
    struct size_visitor : public boost::static_visitor<std::size_t>
    {
        size_visitor(OsiLayer layer) : m_layer(layer) {}

        std::size_t operator()(const CohesivePacket& packet)
        {
            return size(packet, m_layer);
        }

        std::size_t operator()(const ChunkPacket& packet)
        {
            return size(packet, m_layer);
        }

        OsiLayer m_layer;
    };

    size_visitor visitor(layer);
    return boost::apply_visitor(visitor, packet);
}

std::size_t size(const detail::PacketVariant& packet, OsiLayer from, OsiLayer to)
{
    struct size_visitor : public boost::static_visitor<std::size_t>
    {
        size_visitor(OsiLayer from, OsiLayer to) : m_from(from), m_to(to) {}

        std::size_t operator()(const CohesivePacket& packet)
        {
            return size(packet, m_from, m_to);
        }

        std::size_t operator()(const ChunkPacket& packet)
        {
            return size(packet, m_from, m_to);
        }

        OsiLayer m_from;
        OsiLayer m_to;
    };

    size_visitor visitor(from, to);
    return boost::apply_visitor(visitor, packet);
}

} // namespace geonet
} // namespace vanetza