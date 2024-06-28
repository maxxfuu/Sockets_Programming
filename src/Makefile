
output: main.o HttpHandler.o response.o server.o
# take object files and create an executable called output 
	g++ main.o HttpHandler.o response.o server.o -o output

main.o: main.cpp
	g++ -c main.cpp 

HttpHandler.o: HttpHandler/HttpHandler.cpp HttpHandler/HttpHandler.hpp 
	g++ -c HttpHandler/HttpHandler.cpp 

response.o: response/response.cpp response/response.hpp 
	g++ -c response/response.cpp 

server.o: server/server.cpp server/server.hpp 
	g++ -c server/server.cpp 

sockets.o: 

clean: 
	rm *.o output 


#target: dependencies 
#	action 