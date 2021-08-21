#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "psCombo.h"
#include "visitor.h"
#include <iomanip>

class visitorReport : public Visitor {
public:
  void visit(psData * e){
    //cout << *e;
  }
  void visit(demogData * e){
      cout << "print summary demog Data:\n";
      cout << *e;
  }
  void visit(psCombo * e){
    cout << "print aggregate police shooting data:\n";
    cout << *e;
  }

private:
};

#endif