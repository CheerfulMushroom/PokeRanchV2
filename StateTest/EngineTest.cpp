#include <gtest/gtest.h>

#include "GameElement.h"
#include "GameState.h"
#include "Engine.h"


TEST(Engine, checkSetState) {
    Engine engine;

    auto state = std::make_unique<GameState>();
    auto el1 = std::make_unique<GameElement>();
    auto el2 = std::make_unique<GameElement>();
    EXPECT_TRUE(el1->addMeta("id", "192"));
    EXPECT_TRUE(el1->addMeta("type", "test"));

    EXPECT_TRUE(el2->addMeta("id", "12"));
    EXPECT_TRUE(el2->addMeta("type", "test"));

    EXPECT_EQ(state->getElementsAmount(), 0);

    state->addElement(std::move(el1));
    EXPECT_EQ(state->getElementsAmount(), 1);

    state->addElement(std::move(el2));
    EXPECT_EQ(state->getElementsAmount(), 2);

    EXPECT_NO_THROW(engine.setState(std::move(state)));

}
