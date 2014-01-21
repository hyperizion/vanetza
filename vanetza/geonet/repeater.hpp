#ifndef REPEATER_HPP_AH49FXB1
#define REPEATER_HPP_AH49FXB1

#include <vanetza/geonet/data_request.hpp>
#include <vanetza/geonet/packet.hpp>
#include <vanetza/geonet/timestamp.hpp>
#include <boost/heap/priority_queue.hpp>
#include <memory>

namespace vanetza
{
namespace geonet
{

class Router;

class Repeater
{
public:
    template<class REQUEST>
    void add(const REQUEST& request, const DownPacket& payload, Timestamp now)
    {
        if (request.repetition) {
            REQUEST request_duplicate = request;
            decrement_by_one(request_duplicate.repetition.get());
            if (!has_further_repetition(request_duplicate)) {
                request_duplicate.repetition.reset();
            }
            m_repetitions.emplace(request_duplicate, payload,
                    now + Timestamp::duration_type(request.repetition->interval));
        }
    }

    void trigger(Router&, Timestamp now);

private:
    struct Repetition
    {
        Repetition(const DataRequestVariant&, const DownPacket&, Timestamp next);

        DataRequestVariant m_request;
        std::unique_ptr<DownPacket> m_payload;
        Timestamp m_next;
    };

    struct compare_repetition
    {
        bool operator()(const Repetition& lhs, const Repetition& rhs) const;
    };

    boost::heap::priority_queue<
            Repetition,
            boost::heap::compare<compare_repetition>
        > m_repetitions;
};

} // namespace geonet
} // namespace vanetza

#endif /* REPEATER_HPP_AH49FXB1 */
