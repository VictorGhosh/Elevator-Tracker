LDFLAGS = -L. -lglfw -lGL -ldl # -lpthread
CXXFLAGS = -g -Wall -Wno-write-strings -Wno-parentheses -Wno-deprecated-declarations -DLINUX #-pthread

vpath %.cpp ../src
vpath %.c   ../src/glad/src

OBJS = main.o world.o object.o elevator.o gpuProgram.o linalg.o strokefont.o fg_stroke.o glad.o datGet.o displayMaster.o

EXEC = elevator

all:    $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS) 

clean:
	rm -f *~ $(EXEC) $(OBJS) Makefile.bak buff.txt

depend:	
	makedepend -Y ../src/*.h ../src/*.cpp 2> /dev/null
	@echo ""
	@echo "Now edit the Makefile to remove the ../src/ prefix of all of the dependences for the .o files"
	@echo ""

# DO NOT DELETE

../src/elevator.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/elevator.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/elevator.o: ../src/object.h ../src/gpuProgram.h ../src/seq.h
../src/fg_stroke.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/fg_stroke.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/gpuProgram.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/gpuProgram.o: ../src/seq.h
../src/headers.o: ../src/glad/include/glad/glad.h
../src/headers.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/object.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/object.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/object.o: ../src/gpuProgram.h ../src/seq.h
../src/strokefont.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/strokefont.o: ../src/gpuProgram.h ../src/seq.h
../src/world.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/world.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/world.o: ../src/main.h ../src/elevator.h ../src/object.h
../src/world.o: ../src/gpuProgram.h ../src/seq.h
../src/elevator.o: ../src/elevator.h ../src/headers.h
../src/elevator.o: ../src/glad/include/glad/glad.h
../src/elevator.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/elevator.o: ../src/object.h ../src/gpuProgram.h ../src/seq.h
../src/fg_stroke.o: ../src/fg_stroke.h ../src/headers.h
../src/fg_stroke.o: ../src/glad/include/glad/glad.h
../src/fg_stroke.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/gpuProgram.o: ../src/gpuProgram.h ../src/headers.h
../src/gpuProgram.o: ../src/glad/include/glad/glad.h
../src/gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/gpuProgram.o: ../src/seq.h
../src/linalg.o: ../src/linalg.h
../src/main.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/main.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/main.o: ../src/gpuProgram.h ../src/seq.h ../src/world.h ../src/main.h
../src/main.o: ../src/elevator.h ../src/object.h ../src/strokefont.h
../src/object.o: ../src/headers.h ../src/glad/include/glad/glad.h
../src/object.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/object.o: ../src/object.h ../src/gpuProgram.h ../src/seq.h
../src/object.o: ../src/world.h ../src/main.h ../src/elevator.h
../src/strokefont.o: ../src/strokefont.h ../src/headers.h
../src/strokefont.o: ../src/glad/include/glad/glad.h
../src/strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/strokefont.o: ../src/gpuProgram.h ../src/seq.h ../src/fg_stroke.h
../src/world.o: ../src/world.h ../src/headers.h
../src/world.o: ../src/glad/include/glad/glad.h
../src/world.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
../src/world.o: ../src/main.h ../src/elevator.h ../src/object.h
../src/world.o: ../src/gpuProgram.h ../src/seq.h ../src/strokefont.h

../src/datGet.o: ../src/datGet.h
../src/displayMaster.o: ../src/displayMaster.h
