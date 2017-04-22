#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/core/log.hpp>
#include <lib/draw/icomponent.hpp>
#include <lib/draw/components/inputcomponent.hpp>

#include <vector>

namespace lib
{
	namespace draw
	{
		class Scene;
		namespace nodes
		{
			class NodeText;
		}
	}

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

		void displayDebugVars()
		{
			for (auto&& dv : m_varsData) {
				logDebug(dv());
			}
		}
		virtual void update() override
		{
			draw::InputComponent::update();

			if (isPressed(input::Key::Num1)) {
				m_displayVarsNextFrame = true;
			}

			if (m_displayVarsNextFrame) {
				m_displayVarsNextFrame = false;
				displayDebugVars();
			}
		}

		void addOrUpdateDebugVar(const str_const &id, str_const data)
		{
			const auto iterator(std::find_if(m_varsData.begin(), m_varsData.end(), 
				[&id](const auto &dvi) { return dvi.id() == id; }
			));
			if (iterator != m_varsData.end()) {
				// Update
				iterator->setValue(data);
			}
			else {
				// Add
				m_varsData.emplace_back(std::move(id),std::move(data) );
			}
		}

	private:
		std::vector<DebugVarIterator> m_varsData;
	};

	namespace core
	{
		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();

			void addDebugVars(const sptr<draw::Scene> &scene);
		};
	}
}

#endif
