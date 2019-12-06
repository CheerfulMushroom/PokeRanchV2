#include <iostream>
#include "AuthState.h"
#include "Form.h"


AuthState::AuthState() {
    addElement(std::make_unique<Form>());
}