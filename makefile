RPG: main.o LazyEngine.o Map.o Cursor.o MapEditor.o GameObject.o
	gcc -Wall -o RPG LazyEngine.o Map.o Cursor.o MapEditor.o GameObject.o main.o -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf

main.o: LazyEngine.o Map.o Cursor.o MapEditor.o GameObject.o
	gcc -Wall -c main.cpp

LazyEngine.o: Graphics.o Input.o
	gcc -Wall -c LazyEngine.cpp

Map.o: LazyEngine.o
	gcc -Wall -c Map.cpp

Cursor.o: LazyEngine.o
	gcc -Wall -c Cursor.cpp

MapEditor.o: Map.o Cursor.o LazyEngine.o
	gcc -Wall -c MapEditor.cpp

GameObject.o: LazyEngine.o
	gcc -Wall -c GameObject.cpp

Menu.o: LazyEngine.o UIObject.o
	gcc -Wall -c Menu.cpp

Input.o:
	gcc -Wall -c Input.cpp

Graphics.o:
	gcc -Wall -c Graphics.cpp

clean:
	rm *.o
	rm *.gch
	rm RPG
