#include "wallet_component.hpp"

WalletComponent::WalletComponent(int _coins) : coins(_coins)
{
}

bool WalletComponent::spend(int amount)
{
  if (coins >= amount) {
    coins -= amount;
    return true;
  }
  else {
    return false;
  }
}

void WalletComponent::earn(int amount)
{
  coins += amount;
}
