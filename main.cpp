#include <boost/network/protocal/http/server.hpp>
#include <string>
#include <iostream>

namespace http = boost::network::http;

struct myServer;
typedef http::sever<myServer> server;

struct myServer{
  void operator() (server::request const &request,
		   server::response &response){
    std::string ip = source(request);
    response = server::response::stock_repy(
					    server::response::ok, std::string("Welcome, ip:")+ip+"!");
  }
};

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cerr << "Usage: "<<argv[0]<<" address port"<<std::endl;
    return 1;
  }

  try{
    myServer handler;
    server server_(argv[1], argv[2], handler);
    server_.run();
  }
  catch(std::exception &e){
    std::cerr <<e.what()<<std::endl;
    return 1;
  }
  return 0;
}
