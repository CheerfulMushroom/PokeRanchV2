#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Engine/BasicInterfaces/IGameState.h"
#include "../Engine/BasicInterfaces/IGameElement.h"
#include "../Game/States/include/AuthState.h"

class TestElement : public IGameElement {
public:
    ~TestElement() override {
        std::cout << "Deleted\n";
    };

    std::string getMeta(std::string arg) override {
        if (_meta.count(arg) == 1) {
            return _meta[arg];
        }
        return "";
    };

    bool isClicked() override {
        return false;
    };

    double getDistance() override {
        return 0;
    };

    void exec() override {};

    void render() override {};

    void update(double dt) override {
        dt += 1;
    };

    void add_meta(const std::string& key, std::string value) {
        _meta[key] = std::move(value);
    }

private:
    std::map<std::string, std::string> _meta;

};

TEST(AuthState, checkAddDelete) {
    auto state = AuthState();
    auto el1 = new TestElement();
    auto el2 = new TestElement();
    el1->add_meta("id", "192");
    el1->add_meta("type", "test");

    el2->add_meta("id", "12");
    el2->add_meta("type", "test");

    EXPECT_TRUE(state.getElementsAmount() == 0);

    state.addElement(el1);
    EXPECT_TRUE(state.getElementsAmount() == 1);

    state.addElement(el2);
    EXPECT_TRUE(state.getElementsAmount() == 2);

    state.deleteElement([=](IGameElement*) { return true; });
    EXPECT_TRUE(state.getElementsAmount() == 1);
    state.deleteElement([=](IGameElement*) { return true; });
    EXPECT_TRUE(state.getElementsAmount() == 0);

}
