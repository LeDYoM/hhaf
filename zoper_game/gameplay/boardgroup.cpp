#include "boardgroup.hpp"
#include "token.hpp"
#include "tokenzones.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/renderizables/renderizable.hpp>

#include <lib/board/boardmodel.hpp>
#include <lib/board/itile.hpp>

namespace zoper
{
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    BoardGroup::BoardGroup(SceneNode* parent, str name, vector2dst size) :
		BaseClass{ parent, std::move(name), size } {}

    BoardGroup::~BoardGroup() {}

    void BoardGroup::onCreated()
    {
        BaseClass::onCreated();

        m_mainBoardrg = parent()->createSceneNode("mainBoard");

        Rectf32 textBox{ scenePerspective() };
        position = textBox.leftTop();
        sceneNodeSize = textBox.size();

        const Rectf32 bBox(scenePerspective());

        Rectf32 tileBox({}, cellSize());
        for (size_type y{ 0U }; y < tableSize().y; ++y)
        {
            for (size_type x{ 0U }; x < tableSize().x; ++x)
            {
                static_cast<void>(createNodeAt({ x,y }, make_str("BoardGroupTile_", x, y), tileBox));
            }
        }

        p_boardModel = ensureComponentOfType<board::BoardModelComponent>();
        p_boardModel->initialize(tableSize(), this);
	}

	void BoardGroup::tileRemoved(const vector2dst, board::SITilePointer tile)
	{
		assert_release(std::dynamic_pointer_cast<Token>(tile) != nullptr, "Trying to delete invalid type from board");
		m_mainBoardrg->removeSceneNode(std::dynamic_pointer_cast<Token>(tile));
	}

    void BoardGroup::setLevel(const size_type level)
    {
        // Update background tiles
        for_each_tableSceneNode([this, level](const auto position, auto node) 
        {
            node->setTileColor(getBackgroundTileColor(level, position, TokenZones::pointInCenter(position)));
        });
    }

    Color BoardGroup::getBackgroundTileColor(const size_type level, 
        vector2dst tilePosition, const bool isCenter) const
    {
        if (level <= 25)
        {
            if (isCenter) 
            {
                if (level < 9)
                {
                    if (level % 2) 
                    {
                        return{ 10, 200, 50 };
                    }
                    else if (!(level % 3))
                    {
                        return{ 255, 70, 200 };
                    }
                    else 
                    {
                        return{ 255,100,100 };
                    }
                }
                else {
                    if (!(tilePosition.x % 2))
                    {
                        return (level < 15) ? Color{ 128, 128, 128 } : Color{ 255, 100, 100 };
                    }
                    else {
                        return (level < 15) ? Color{ 225, 255, 255 } : Color{ 100, 200, 200 };
                    }
                }
            }
            else
            {
                if (level < 2)
                {
                    return colors::Black;
                }
                else if (level < 3)
                {
                    return{ 255, 128, 0 };
                }
                else if (level < 5)
                {
                    return{ 100, 128, 255 };
                }
                else if (level < 10)
                {
                    if (level % 2)
                    {
                        return (tilePosition.x % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
                    }
                    else {
                        return (tilePosition.y % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
                    }
                }
                else if (level < 15)
                {
                    if (level % 2) 
                    {
                        if (tilePosition.x % 2)
                        {
                            return (tilePosition.y % 2) ? colors::White : Color{ 100,100,100 };
                        }
                        else 
                        {
                            return (tilePosition.y % 2) ? Color{ 0, 128, 255 } : Color{ 10, 250, 100 };
                        }
                    }
                    else {
                        return (tilePosition.x % 2) ?
                            ((tilePosition.y % 2) ? Color{ 25,25,25 } : Color{ 10, 12, 250 }) :
                            ((tilePosition.y % 2) ? Color{ 250, 50, 10 } : Color{ 10, 200, 10 });
                    }
                }
            }
        }
        return colors::Black;
    }

}