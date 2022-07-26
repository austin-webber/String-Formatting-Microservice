# String Formatting Microservice
 A string formatting microservice complete with client and server code.
 This microservice is implemented using ZeroMQ, an asynchronous messaging library that allows for distributed or concurrent applications to communicate with each other.

## Communication Contract

 Specifically, this microservice was programmed for use by my partner in CS361 at OSU. 
 They created a habit tracker. The application (client) will send a string of variables to the server, which will take the variables and send them back in a specific format.
 
 - #### How to REQUEST data from the server: 
    First, you need to build the ZeroMQ library for your given programming language.
    Next, ZeroMQ requires that you prepare a context and a socket to request data from.
    This socket must be connected over TCP to an endpoint.
    Now you can prepare your request using the "message_t" data type.
    Finally, you can use the socket to send your request to the server.
    
    These steps can be observed in the example below:
    ![image](https://user-images.githubusercontent.com/68242504/180920790-6e519092-4711-4676-a847-d7468e04ab22.png)

    
 - #### How to RECEIVE data from the server:
    First, you need to declare your reply using the "message_t" data type.
    Then you can use the asynchronous ".recv()" function on your socket which will wait for a reply.
    That's it! You can do with this reply as you will. 
    In the example below, the reply is converted to a string and printed to the console.
    
    ![image](https://user-images.githubusercontent.com/68242504/180921163-0371266c-2924-4829-9253-5acbc21b949c.png)
    
    
    
 Finally, here is a **UML sequence diagram** showing how requesting and receiving data works:
 ![Sequence Diagram Client and Server Parallel Call Example(1)](https://user-images.githubusercontent.com/68242504/180923772-cf60c6f1-651d-4fc5-9a7c-b72033c635bb.jpg)
