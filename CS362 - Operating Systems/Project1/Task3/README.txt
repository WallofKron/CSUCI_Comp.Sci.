Task 3 functions exactly as described….

my typescript is just simply testing creation and deletion, printing what Memory looks like in between each creation/deletion. Here is the code from main:





    initialize();

   	 printMemoryContents();
    
    createFile("Cool", 123, "This is data in a file");
    
   	 printMemoryContents();
    
    createDirectory("RandDir", 123);
    
   	 printMemoryContents();

    createDirectory("Ayyyy", 555);
    
    	printMemoryContents();
    
    deleteDirectory("Ayyyy");
    
   	 printMemoryContents();
    
    deleteFile("Cool");

    	printMemoryContents();

    createFile("Where", 8390, "More Data! Wooo!");
    
    	printMemoryContents();

    createDirectory("What", 10196);

    	printMemoryContents();
    
    free(memory);
    free(bitvector);
