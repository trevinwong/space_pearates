#ifndef WALLET_COMPONENT_H
#define WALLET_COMPONENT_H

#include "../Utility/utility.hpp"
#include "base_component.hpp"

class WalletComponent : public BaseComponent {
public:
  WalletComponent();

  bool spend(int amount);
  void earn(int amount);

  int coins;

  static const int typeID = ComponentType::wallet;
  inline virtual int getTypeID() const { return typeID; };
private:

};

#endif // !WALLET_COMPONENT_H
