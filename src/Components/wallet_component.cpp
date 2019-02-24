#include "wallet_component.hpp"

WalletComponent::WalletComponent() :
  coins(0)
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
