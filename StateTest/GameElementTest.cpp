#include <gtest/gtest.h>

#include "GameElement.h"


TEST(GameElement, checkAddMeta) {
    auto el = std::make_unique<GameElement>();
    EXPECT_TRUE(el->addMeta("id", "192"));
    EXPECT_TRUE(el->addMeta("type", "test"));

    EXPECT_FALSE(el->addMeta("id", "131"));
}
