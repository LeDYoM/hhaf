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
		class DebugVarIterator
		{
		public:
			DebugVarIterator() = default;
			DebugVarIterator(str_const id, str_const data) 
				: m_id{ std::move(id) }, m_data{ std::move(data) } {}

			void setValue(const str_const nv) 
			{
				m_data = nv;
			}

			const str_const operator()() const noexcept {
				return { m_id + ": " + m_data };
			}

			inline const str_const id() const noexcept { return m_id; }
		private:
			str_const m_id;
			str_const m_data;
		};

		class DebugVarsComponent : public draw::InputComponent
		{
		public:
			bool m_displayVarsNextFrame{ false };

			void displayDebugVars();
			virtual void update() override;

			void addOrUpdateDebugVar(const str_const &id, str_const data);

		private:
			std::vector<DebugVarIterator> m_varsData;
		};
	}
}

#endif
