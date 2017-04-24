#ifndef LIB_DEBUGCOMPONENT_INCLUDE_HPP
#define LIB_DEBUGCOMPONENT_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/draw/icomponent.hpp>
#include <lib/draw/components/inputcomponent.hpp>
#include <lib/core/log.hpp>

#include <vector>

namespace lib
{
	namespace draw
	{
		class DebugVar
		{
		public:
			DebugVar(str_const id, str_const data) : m_id{ std::move(id) }, m_data{ std::move(data) } {}

			inline void setValue(const str_const &nv) noexcept { m_data = nv; }
			inline const str_const operator()() const noexcept { return { m_id + ": " + m_data }; }
			inline const str_const id() const noexcept { return m_id; }
		private:
			str_const m_id;
			str_const m_data;
		};

		using DebugVarAccessor = sptr<DebugVar>;

		class DebugVarsComponent final : public draw::InputComponent
		{
		public:
			virtual void update() override;
			void addOrUpdateDebugVar(DebugVarAccessor & dba, const str_const &id, str_const data);
			void addOrUpdateDebugVar(DebugVarAccessor & dba, const str_const &id, const u32 data);

		private:
			void displayDebugVars();

			std::vector<sptr<DebugVar>> m_varsData;
			bool m_displayVarsNextFrame{ false };
		};
	}
}

#endif
