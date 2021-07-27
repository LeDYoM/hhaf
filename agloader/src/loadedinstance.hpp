#ifndef LOADER_LOADEDINSTANCE_HPP
#define LOADER_LOADEDINSTANCE_HPP

namespace agloader
{
class LoadedInstancePrivate;

class LoadedInstance
{
public:
    LoadedInstance();
    ~LoadedInstance();

    bool load(const char* fileName);
    void const* loadMethod(const char* methodName);

    bool loaded() const;
    bool unload();
    void const* loadedData() const;

private:
    LoadedInstancePrivate* m_private;
};
}  // namespace agloader
#endif