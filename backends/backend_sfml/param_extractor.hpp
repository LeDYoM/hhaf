#ifndef HAF_BACKEND_SFMLB_PARAM_EXTRACTOR__INCLUDE_HPP
#define HAF_BACKEND_SFMLB_PARAM_EXTRACTOR__INCLUDE_HPP

namespace haf::backend::sfmlb
{
class ParamExtractor
{
public:
    constexpr ParamExtractor(const unsigned int size,
                             const unsigned int* const data) :
        size_{size}, data_{data}
    {}

    unsigned int getParam(const unsigned int def_param = 0U)
    {
        if (current_ < size_)
        {
            return data_[current_++];
        }
        return def_param;
    }

private:
    unsigned int current_{0U};
    const unsigned int size_;
    const unsigned int* const data_;
};

}  // namespace haf::backend::sfmlb

#endif
