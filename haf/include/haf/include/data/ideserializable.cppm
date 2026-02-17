export module haf:data:ideserializable;

import :core;

namespace haf::data
{
class IDeserializable
{
public:
    virtual bool deserialize(mcs::Object const&) = 0;
    virtual ~IDeserializable()                   = default;
};

template <typename T>
class DeserializableDictionary : public IDeserializable
{
public:
    DeserializableDictionary() = default;

    bool deserialize(mcs::Object const& obj)
    {
        bool result{false};

        for (auto const& element : obj.objects())
        {
            T element_data;
            element_data.deserialize(element.second);
            result &= elements_.add(element.first, htps::move(element_data));
        }
        return result;
    }

    htps::Dictionary<T>& elements() noexcept { return elements_; }
    htps::Dictionary<T> const& elements() const noexcept { return elements_; }

private:
    htps::Dictionary<T> elements_;
};

template <typename T>
class DeserializableVector : public IDeserializable
{
public:
    DeserializableVector() = default;

    bool deserialize(mcs::Object const& obj)
    {
        for (auto const& element : obj.objects())
        {
            T element_data;
            element_data.deserialize(element.second);
            elements_.push_back(htps::move(element_data));
        }
        return true;
    }

    htps::vector<T>& elements() noexcept { return elements_; }
    htps::vector<T> const& elements() const noexcept { return elements_; }

private:
    htps::vector<T> elements_;
};

}  // namespace haf::data
