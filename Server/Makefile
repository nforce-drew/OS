NAME = server
SOURCES = Sources/
INCLUDES = Headers/

all: clean $(NAME)
$(NAME):
	@g++ $(SOURCES)Server.cpp $(SOURCES)MainHeader.cpp $(SOURCES)FileHeader.cpp $(SOURCES)Headers.cpp $(SOURCES)ServerFunctions.cpp $(SOURCES)DataBaseFunctions.cpp -I $(INCLUDES) -l sqlite3 -o $(NAME)
clean:
	@/bin/rm -f $(NAME)