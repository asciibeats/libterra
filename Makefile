LIBNAME := terra
LIBDIR := /usr/lib
INCLUDEDIR := /usr/include

CFLAGS := -I/usr/include -Isrc -fmax-errors=1 -Wall -Werror
CFLAGS += -O3 -finline-functions -fPIC
LDLIBS := -lm -lstdc++ -lringnoise

SOURCES := src/$(LIBNAME).cc
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))
OUTFILE := lib$(LIBNAME).so

$(OUTFILE): $(OBJECTS)
	gcc -shared -o $(OUTFILE) $(OBJECTS) $(LDLIBS)

$(OBJECTS): src/%.o: src/%.cc
	gcc $(CFLAGS) -c $< -o $@

install:
	cp src/$(LIBNAME).h $(INCLUDEDIR)
	cp $(OUTFILE) $(LIBDIR)

uninstall:
	rm -f $(INCLUDEDIR)/$(LIBNAME).h
	rm -f $(LIBDIR)/$(OUTFILE)

demo: $(OUTFILE) src/demo.cc
	gcc $(CFLAGS) src/demo.cc -L. -lstdc++ -lterra -o demo
	chmod +x demo

clean:
	rm -f $(OUTFILE) src/*.o demo
