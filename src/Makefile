
output: main.o http_handler.o response.o server.o
# take object files and create an executable called output 
	g++ main.o http_handler.o response.o server.o -o output

main.o: main.cpp
	g++ -c main.cpp 

http_handler.o: HttpHandler/http_handler.cpp HttpHandler/http_handler.hpp 
	g++ -c HttpHandler/http_handler.cpp 

response.o: response/response.cpp response/response.hpp 
	g++ -c response/response.cpp 

server.o: server/server.cpp server/server.hpp 
	g++ -c server/server.cpp 

sockets.o: 

clean: 
	rm *.o output 


#target: dependencies 
#	action 