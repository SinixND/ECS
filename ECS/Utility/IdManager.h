#ifndef IDMANAGER_H_20231210202055
#define IDMANAGER_H_20231210202055

#include <cassert>
#include <cstddef>
#include <limits>
#include <unordered_set>

namespace snx
{
    class IdManager
    {
    public:
        auto requestId() -> size_t
        {

            if (!freeIds_.empty())
            {
                return recycledId();
            }

            return incrementedId();
        }

        void suspendId(size_t id)
        {
            if (activeIds_.count(id) < 1)
            {
                return;
            }

            auto usedIdsIterator{activeIds_.find(id)};
            freeIds_.insert(*usedIdsIterator);
            activeIds_.erase(usedIdsIterator);
        }

    private:
        std::unordered_set<size_t> activeIds_{};
        std::unordered_set<size_t> freeIds_{};

    private:
        auto recycledId() -> size_t
        {
            size_t id{};
            auto freeIdsIterator{freeIds_.begin()};
            id = *freeIdsIterator;

            activeIds_.insert(id);
            freeIds_.erase(freeIdsIterator);

            return id;
        }

        auto incrementedId() -> size_t
        {
            static size_t maxId = std::numeric_limits<size_t>::max();
            static size_t lastId{0};
            // Start with id = 1
            ++lastId;

            assert(lastId < maxId && "ID OVERFLOWING!");

            activeIds_.insert(lastId);

            return lastId;
        }
    };

} // namespace snx

#endif
