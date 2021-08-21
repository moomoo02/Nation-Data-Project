#ifndef VISITOR_H
#define VISITOR_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"

/* a visitor can visit any of my specific data types */
class Visitor {
  public:
  virtual void visit(shared_ptr<psData> ps) = 0;
  virtual void visit(shared_ptr<demogData> dd) = 0;
  virtual void visit(psCombo* psc) = 0;
};
#endif

