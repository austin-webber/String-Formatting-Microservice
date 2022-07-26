// Austin Webber
// Description: Server which opens a ZeroMQ socket on port 5555, reads requests on it, 
//				expecting "Hello" from the client, and replies with "A message from CS361".
// CS361
// 7/16/2022

#include <iostream>
// zeromq header files, installed and integrated through vcpkg
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    // preparing our context
    zmq::context_t context;
    // deriving a request socket from the global context
    zmq::socket_t socket(context, zmq::socket_type::rep);
    // connect that socket over TCP to an endpoint
    socket.bind("tcp://127.0.0.1:5555");

    while (true)
    {
        zmq::message_t request;

        // waiting for next request from client
        std::cout << "Waiting for request..." << std::endl;
        socket.recv(request, zmq::recv_flags::none);

        // request received
        std::string client_request = request.to_string();
        std::string request_type = client_request.substr(0, 6);

        // server expects format request to come in the format "format<streak>*<habit>%<daysleft>"
        if (request_type == "format")
        {
            std::cout << "Received: " << request.to_string() << std::endl;

            // gets the whole string after "format"
            std::string request_body = client_request.substr(6);
            // grabbing the different variables in the message
            int streak_end = request_body.find("*");
            int habit_end = request_body.find("%");
            std::string streak = request_body.substr(0, streak_end);
            std::string habit = request_body.substr(streak_end + 1, habit_end - 2);
            std::string days_left = request_body.substr(habit_end + 1);

            // creating the response
            std::string response_message = "I am " + streak + " days into my habit: " + habit + "! There are " + days_left + " days left until I hit my goal.";
            int response_size = response_message.length();

            // send response back to client
            std::cout << "Sending reply..." << std::endl;
            zmq::message_t reply(response_size);
            memcpy(reply.data(), response_message.data(), response_size);
            socket.send(reply, zmq::send_flags::none);
        }
        // if request not in correct format, send an error message back
        else
        {
            std::cout << "Error: Message received is not in proper format." << std::endl;
            std::cout << "Sending reply..." << std::endl;
            zmq::message_t reply(56);
            memcpy(reply.data(), "ERROR: The message you sent is not in the proper format.", 56);
            socket.send(reply, zmq::send_flags::none);
        }
    }
    return 0;
}