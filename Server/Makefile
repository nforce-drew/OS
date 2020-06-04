NAME = server
SOURCES = Sources/
INCLUDES = Headers/

all: clean $(NAME)
$(NAME):
	@g++ $(SOURCES)Server.cpp $(SOURCES)MainHeader.cpp $(SOURCES)FileHeader.cpp $(SOURCES)ServerFunctions.cpp -I $(INCLUDES) -o $(NAME)
clean:
	@/bin/rm -f $(NAME)