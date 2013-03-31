CC=		g++

EXEC=	spider

OBJS=	objs/error.o\
		objs/file.o\
		objs/regx.o\
		objs/url.o\
		objs/str.o\
		objs/net.o\
		objs/dns.o\
		objs/pool.o\
		objs/core.o\
		objs/main.o

LIB=	pthread

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -l $(LIB)

objs/error.o:../common/error/error.cpp
	$(CC) -c ../common/error/error.cpp -o objs/error.o
	
objs/file.o:../common/file/file.cpp
	$(CC) -c ../common/file/file.cpp -o objs/file.o
	
objs/regx.o:../common/regx/regx.cpp
	$(CC) -c ../common/regx/regx.cpp -o objs/regx.o
	
objs/url.o:../common/url/url.cpp
	$(CC) -c ../common/url/url.cpp -o objs/url.o

objs/str.o:../common/str/str.cpp
	$(CC) -c ../common/str/str.cpp -o objs/str.o

objs/net.o:../common/net/net.cpp
	$(CC) -c ../common/net/net.cpp -o objs/net.o

objs/dns.o:dns/dns.cpp
	$(CC) -c dns/dns.cpp -o objs/dns.o

objs/pool.o:pool/pool.cpp
	$(CC) -c pool/pool.cpp -o objs/pool.o

objs/core.o:core/core.cpp
	$(CC) -c core/core.cpp -o objs/core.o

objs/main.o:main/main.cpp
	$(CC) -c main/main.cpp -o objs/main.o

clean:
	rm objs/*.o spider
