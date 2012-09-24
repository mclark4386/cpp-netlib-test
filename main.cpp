#include <network/protocol/http/server.hpp>
#include <string>
#include <iostream>

namespace http = boost::network::http;

struct myServer;
typedef http::sync_server<myServer> server;

struct myServer{
  void operator() (server::request const &req,
		   server::response &res){
    // std::string ip;
    // req.get_uri(&ip);
    std::ostringstream data;
    data << "Hello, World";//"Welcome, ip:"<< ip << "!";
    //   res.set_status(200);
    //   res.set_body(data.str());
    res = server::response::stock_reply(200, data.str());
  }

  void log(...){

  }
};

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cerr << "Usage: "<<argv[0]<<" address port"<<std::endl;
    return 1;
  }

  try{
    myServer handler;
    http::server_options options;
    server server_(options.address(argv[1]).port(argv[2]), handler);
    server_.run();
  }
  catch(std::exception &e){
    std::cerr <<e.what()<<std::endl;
    return 1;
  }
  return 0;
}
