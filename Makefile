OBJECTS = main.o david.o lorin.o donovan.o
INCLUDES = cacheProj.h

%.o: %.c ${INCLUDES}
	gcc -g -c $< 

project: ${OBJECTS}
	gcc -g -o project ${OBJECTS} -lm

clean:
	rm -f ${OBJECTS}