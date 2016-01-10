all : RiffParser
	
RiffParser : RiffParser.cpp	
	g++ -g RiffParser.cpp -o RiffParser

clean : 
	rm -rf RiffParser
	rm -rf sandbox

sandbox : sandbox.cpp
	g++ sandbox.cpp -o sandbox

