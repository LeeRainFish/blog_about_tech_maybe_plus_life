#include <iostream>

using namespace std;




enum class RequestType
{
    REQ_HANDLER1;
    REQ_HANDLER2;
    REQ_HANDLER3;
}
// 请求信息
class Request
{
    string description;
    RequestType reqType;
public:
    Request();
    RequestTypet getReqType() const {return reqType;};
    const string& getDescription();
}

// 责任链父类,抽象接口
class ChainHandler
{
    ChainHandler *nextChain;
public:
    ChainHandler();
    void setNext(ChainHandler *next){nextChain = next;}
    void handle(const Request &req)
    {
        if (canHandleRequest(req))
            processRequest(req);
        else
            sendRequestToNextHandler(req);
    }

protected:
    // 内否处理
    virtual bool canHandleRequest(const Request &req); 
    // 处理请求
    virtual void processRequest(const Request &req);
    // 传递请求
    virtual void sendRequestToNextHandler(const Request &req);
}


class Handler1 : public ChainHandler
{

protected:
    // 内否处理
    virtual bool canHandleRequest(const Request &req)
    {

    }
    // 处理请求
    virtual void processRequest(const Request &req)
    {

    }
    // 传递请求
    virtual void sendRequestToNextHandler(const Request &req)
    {


    }

}



int main()
{

    Handler1 h1;
    Handler2 h2;
    Handler3 h3;

    h1.setNextChain(&h2);
    h2.setNextChain(&h3);

    Request req("prcess task .........",RequestType::REQ_HANDLER1);
    h1.handle(req);


    return 0;
}
