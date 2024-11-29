HTPS_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SYSTEM_CONFIGURATION_TEMPLATE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_CONFIGURATION_TEMPLATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/filesystem/ifile_serializer.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::sys
{
template <typename DeserializableDataType, typename InnerDataType>
class SystemConfiguration
{
public:
    bool loadConfiguration(SubSystemViewer sub_system_viewer,
                           htps::str const& configuration_file)
    {
        DeserializableDataType current;
        auto file_serializer{
            sub_system_viewer.subSystem<sys::IFileSerializer>()};
        auto const result{
            file_serializer->deserializeFromFile(configuration_file, current)};

        DisplayLog::debug_if(result != IFileSerializer::Result::Success,
                             "Cannot parse ", configuration_file);

        if (result == IFileSerializer::Result::Success)
        {
            data_ = htps::move(current.data);
        }

        return result == IFileSerializer::Result::Success;
    }

    InnerDataType const& data() const noexcept { return data_; }

protected:
    InnerDataType& data() noexcept { return data_; }

private:
    InnerDataType data_;
};
}  // namespace haf::sys

#endif
