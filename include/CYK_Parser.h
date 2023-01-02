#include "Grammar.h"

class AbstractParser {
 protected:
  AbstractParser() = default;

  virtual bool Parse(const Grammar&, const std::string&) = 0;
};

class CYK : public AbstractParser {
 public:
  bool Parse(const Grammar&, const std::string&) override;
};