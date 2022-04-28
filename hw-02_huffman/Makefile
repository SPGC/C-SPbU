CCFLAGS = -Wall -Werror -Wextra

hw-02_huffman: obj obj/CoderDecoder.o obj/main.o obj/HuffmanTree.o obj/IOModule.o obj/Node.o obj/Exception.o
	g++ $(CCFLAGS) --std=c++17 -o hw-02_huffman obj/CoderDecoder.o obj/main.o obj/HuffmanTree.o obj/IOModule.o obj/Node.o obj/Exception.o
	chmod +x hw-02_huffman

obj:
	mkdir obj

obj/Node.o: include/Node.hpp src/Node.cpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/Node.o -c src/Node.cpp 

obj/CoderDecoder.o: include/Node.hpp src/CoderDecoder.cpp include/CoderDecoder.hpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/CoderDecoder.o -c src/CoderDecoder.cpp 

obj/HuffmanTree.o: include/Node.hpp src/HuffmanTree.cpp include/HuffmanTree.hpp include/Exception.hpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/HuffmanTree.o -c src/HuffmanTree.cpp 

obj/IOModule.o: include/Node.hpp src/IOModule.cpp include/IOModule.hpp include/CoderDecoder.hpp include/Exception.hpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/IOModule.o -c src/IOModule.cpp 

obj/main.o: include/IOModule.hpp src/main.cpp include/HuffmanTree.hpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/main.o -c src/main.cpp

obj/Exception.o: include/Exception.hpp src/Exception.cpp
	g++ -I include $(CCFLAGS) --std=c++17 -o obj/Exception.o -c src/Exception.cpp 

clean:
	rm -r obj
	rm hw-02_huffman
	