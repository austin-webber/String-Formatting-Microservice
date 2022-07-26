// Austin Webber
// Description: Connects a ZeroMQ request socket to port 5555, 
//              sends "Hi!" to server, expects "A message from CS361" back.
// CS361
// 7/16/2022

#include <iostream>
#include <string>
// zeromq header files, installed and integrated through vcpkg
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    // PREPARING OUR CONTEXT AND SOCKET
    // context
    zmq::context_t context;
    // deriving a request socket from the context
    zmq::socket_t socket(context, zmq::socket_type::req);

    // displaying set up message
    std::cout << "Connecting to server..." << std::endl;

    // connect socket over TCP to an endpoint
    socket.connect("tcp://127.0.0.1:5555");

    // sending format request
    // defining the request
    // The int parameter "5" passed in refers to the size of the request message in bytes
    zmq::message_t request(24);
    memcpy(request.data(), "format7*Daily Reading%23", 24);
    // displaying progress message
    std::cout << "Sending format request..." << std::endl;
    // sending request to server
    socket.send(request, zmq::send_flags::none);

    // get the reply
    zmq::message_t reply;
    socket.recv(reply, zmq::recv_flags::none);
    // displaying reply sent back from server
    std::cout << "Received reply: " << reply.to_string() << std::endl;

    return 0;
}