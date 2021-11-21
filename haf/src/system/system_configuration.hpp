#ifndef HAF_SYSTEM_SYSTEM_CONFIGURATION_TEMPLATE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_CONFIGURATION_TEMPLATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include "system/systemdatawrappercreator.hpp"
#include <haf/include/filesystem/fileserializer.hpp>

namespace haf::sys
{
template <typename DeserializableDataType, typename InnerDataType>
class SystemConfiguration
{
public:
    bool loadConfiguration(SystemBase& system_instance,
                           htps::str const& configuration_file)
    {
        SystemDataWrapperCreator data_wrapper_creator{system_instance};
        DeserializableDataType current;
        auto file_serializer{
            data_wrapper_creator.dataWrapper<sys::FileSerializer>()};
        auto const result{
            file_serializer->deserializeFromFile(configuration_file, current)};

        DisplayLog::debug_if(result != FileSerializer::Result::Success,
                             "Cannot parse ", configuration_file);

        if (result == FileSerializer::Result::Success)
        {
            data_ = std::move(current.data);
        }

        return result == FileSerializer::Result::Success;
    }

    InnerDataType const& data() const noexcept { return data_; }

protected:
    InnerDataType& data() noexcept { return data_; }


private:
    InnerDataType data_;
};
}  // namespace haf::sys

#endif
