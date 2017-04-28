#ifdef STATEMENT_H
#define STATEMENT_H

class Statement
{
  public:
    // KOOL, virtual void execute() will allow me to call the 
    // function so that all statements would execute without having
    // to know how it should be executed. So any statements can overrride
    // the virtual function execute and execute if differently in its 
    // statement block. NICE!
    virtual void execute() = 0;
};

#endif
