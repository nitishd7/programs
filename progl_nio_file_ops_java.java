import java.nio.file.*;
import java.io.IOException;

class progl_nio_file_ops_java{
	
	static String directoryName = "content_dir_prog_created";
	public static void main(String[] args){
		create_directory_file();
	}

	static void create_directory_file(){
		try{
			Path dirPath = Paths.get(directoryName);
			if(!Files.exists(dirPath)) Files.createDirectory(dirPath);
			Path filePath = Paths.get(directoryName,"content_file_prog_created.txt");
			if(!Files.exists(filePath)) Files.createFile(filePath);
		} catch(IOException e){}
	}
}
