#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "account-view-model.h"

using namespace view_model;

AccountViewModel::AccountViewModel(
    std::function<void(int)> setViewState
) {
    this->setViewState = setViewState;
}

void AccountViewModel::LoginObserver() {
    // if login is correct
    this->setViewState(0);
}