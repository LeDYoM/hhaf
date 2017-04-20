#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/draw/icomponent.hpp>

#include <map>

namespace lib
{
	namespace gui
	{
		class TextGroup;
	}
	namespace draw
	{
		class Scene;
	}

	class DebugVarIterator
	{
		DebugVarIterator(str_const id, str_const data, const sptr<gui::TextGroup> tg) : data{ data }, linkedTextGroup{tg->addTextLine()}
		{
		}
	private:
		str_const m_id;
		str_const m_data;
		sptr<draw::nodes::NodeText> linkedTextGroup;
	};
	class DebugVarsComponent : public draw::IComponent
	{
		virtual void update() override
		{

		}

		void addOrUpdateDebugVar(const str_const &id, str_const data)
		{
			const auto iterator(m_varsData.find(id));
			if (iterator != m_varsData.end()) {
				// Update
				iterator->second.data = std::move(data);
			}
			else {
				// Add
				auto textLine = _attachedNode()->addTextLine(id + ":" + data);
				m_varsData[id] = DebugVarIterator{std::move(data),std::move(textLine)};
			}
		}

		gui::TextGroup *const _attachedNode() { return dynamic_cast<gui::TextGroup*const>(attachedNode()); }

	private:
		std::map<str_const, DebugVarIterator> m_varsData;
	};

	namespace core
	{
		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();

			void update();
			void addDebugVars(const sptr<draw::Scene> &scene);
			void addStandardDebugVars();
		private:
			void activeSceneChanged(const sptr<draw::Scene> &currentScene);
			sptr<gui::TextGroup> debugVarsNodeForScene(const sptr<draw::Scene> &currentScene);
			sptr<gui::TextGroup> m_currentDebugVarsNode;
			bool m_activeSceneChanged{ true };
		};
	}
}

#endif
