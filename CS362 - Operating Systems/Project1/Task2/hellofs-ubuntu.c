#define FUSE_USE_VERSION  26
   
  #include <stdlib.h>
  #include <fuse.h>
  #include <stdio.h>
  #include <string.h>
  #include <errno.h>
  #include <fcntl.h>
   
  static const char *hello_str = "Hello World!\n";
  static const char *hello_path = "/hello";

  static const char *second_str = "FileSYSTEM!\n";
  static const char *second_path = "/second";

  static const char *third_str = "No access to this text!\n";
  static const char *third_path = "/third";
  
  static const char *fourth_path = "/fourth";

  	int r;


  static int hello_getattr(const char *path, struct stat *stbuf){

      int res = 0;
      memset(stbuf, 0, sizeof(struct stat));
      if(strcmp(path, "/") == 0) {
          stbuf->st_mode = S_IFDIR | 0755;
          stbuf->st_nlink = 2;
      }
      else if(strcmp(path, hello_path) == 0) {

          stbuf->st_mode = S_IFREG | 0444;
          stbuf->st_nlink = 1;
          stbuf->st_size = strlen(hello_str);

      } else if(strcmp(path, second_path) == 0) {

          stbuf->st_mode = S_IFREG | 0444;
          stbuf->st_nlink = 1;
          stbuf->st_size = strlen(second_str);

      } else if(strcmp(path, third_path) == 0) {

          stbuf->st_mode = S_IFREG | 0400;
          stbuf->st_nlink = 1;
          stbuf->st_size = strlen(third_str);
	  

      } else if(strcmp(path, fourth_path) == 0) {

          stbuf->st_mode = S_IFREG | 0444;
          stbuf->st_nlink = 1;
	  r = (rand() % 12);
          stbuf->st_size = r;
      }
	
      else{
          res = -ENOENT;
	  }
      return res;
  }
  



  static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                           off_t offset, struct fuse_file_info *fi){

      (void) offset;
      (void) fi;
  
      if(strcmp(path, "/") != 0)
          return -ENOENT;
  
      filler(buf, ".", NULL, 0);
      filler(buf, "..", NULL, 0);
      filler(buf, hello_path + 1, NULL, 0);
      filler(buf, second_path + 1, NULL, 0);
      filler(buf, third_path + 1, NULL, 0);
      filler(buf, fourth_path + 1, NULL, 0);
  
      return 0;
  }
  



  static int hello_open(const char *path, struct fuse_file_info *fi){

      if(strcmp(path, hello_path) != 0){
	     if(strcmp(path, second_path) != 0){
			if(strcmp(path, third_path) != 0){
				if(strcmp(path, fourth_path) != 0){

					          return -ENOENT;
				}
			}

		}

	}
  
      if((fi->flags & 3) != O_RDONLY)
          return -EACCES;
  
      return 0;
  }
  



  static int hello_read(const char *path, char *buf, size_t size, off_t offset,
                        struct fuse_file_info *fi){

      size_t len;
      (void) fi;

if(strcmp(path, hello_path) != 0 && strcmp(path, second_path) != 0 && strcmp(path, third_path) != 0 && strcmp(path, fourth_path) != 0){

        if(strcmp(path, hello_path) == 0){

	      len = strlen(hello_str);
      		if (offset < len) {
          		if (offset + size > len)
            		  size = len - offset;
         	 memcpy(buf, hello_str + offset, size);
     			 } else{
         			 size = 0;
  				}
}
	if(strcmp(path, second_path) == 0){

 		len = strlen(second_str);
      		if (offset < len) {
          		if (offset + size > len)
            		  size = len - offset;
         	 memcpy(buf, second_str + offset, size);
     			 } else{
         			 size = 0;
  				}
}	
	if(strcmp(path, third_path) == 0){
 		len = strlen(third_str);
      		if (offset < len) {
          		if (offset + size > len)
            		  size = len - offset;
         	 memcpy(buf, third_str + offset, size);
     			 } else{
         			 size = 0;
  				}

}
	if(strcmp(path, fourth_path) == 0){
		char tempstring[r];

		for(int i = 0; i < r; i++){
			tempstring[i] = 'X';

		}				//set array vals to 'X'
		
		int randchar;

		for(int i = 0; i < r; i++){
			randchar = (rand() % 26);
			randchar += 97;
			tempstring[i] = randchar;
		}				//put random characters in the string
			
		len = strlen(tempstring);
      		if (offset < len) {
          		if (offset + size > len)
            		  size = len - offset;
         	 memcpy(buf, tempstring + offset, size);
     			 } else{
         			 size = 0;
  				}
	}
			} else {

			    return -ENOENT;
			}	
	
      return size;
  }



  
  static struct fuse_operations hello_oper = {
      .getattr   = hello_getattr,
      .readdir = hello_readdir,
      .open   = hello_open,
      .read   = hello_read,
  };
  

  int main(int argc, char *argv[]){
      return fuse_main(argc, argv, &hello_oper, NULL);
  }
