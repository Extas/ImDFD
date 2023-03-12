#ifndef PIN_HPP
#define PIN_HPP

#include "NodeObj.h"
#include <algorithm>
#include <string>
#include <vector>

class Node;
class Link;

class Pin : public NodeObj {
public:
  explicit Pin(std::string name) : NodeObj(std::move(name)) {
  }

  ~Pin() override = default;

  Pin(const Pin &) = delete;
  Pin(Pin &&) noexcept = default;
  auto operator=(const Pin &) -> Pin & = delete;
  auto operator=(Pin &&) -> Pin & = delete;
};

class OutPin : public Pin {
public:
  using Pin::Pin;

  // TODO(Pin): Add other functionality specific to out pin if necessary
};

class InPin : public Pin {
public:
  using Pin::Pin;

  // TODO(Pin): Add other functionality specific to in pin if necessary
};

#endif // PIN_HPP
