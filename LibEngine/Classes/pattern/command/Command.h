#ifndef _COMMAND_H_
#define _COMMAND_H_

/*

*/
class Command {
public:
    //纯虚函数，只提供接口，没有默认的实现
    virtual void execute() = 0;
};
#endif //_COMMAND_H_