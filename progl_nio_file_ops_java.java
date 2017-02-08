import java.nio.file.*;
import java.io.IOException;
import java.util.*;
import java.nio.file.attribute.*;
import java.lang.Thread.*;

class file_visitor_sample extends SimpleFileVisitor<Path>{
	public FileVisitResult visitFile(Path path, BasicFileAttributes attrs){
	//	if(path.getFileName().endsWith("1"))
	//		System.out.println("visited: " + path.getFileName());
		System.out.println("Visit File: " + path);
		return FileVisitResult.CONTINUE; //SKIP_SUBTREE, TERMINATE, SKIP_SIBLINGS
	}

	public FileVisitResult preVisitDirectory(Path path, BasicFileAttributes atrrs) {
		System.out.println("PreVisit Dir: " + path);
		return FileVisitResult.CONTINUE;
	}

	public FileVisitResult visitFileFailed(Path path, IOException exc){
		return FileVisitResult.CONTINUE;
	}

	public FileVisitResult postVisitDirectory(Path path, IOException exc){
		System.out.println("PostVisit Dir: " + path);
		return FileVisitResult.CONTINUE;
	}
}

class progl_nio_file_ops_java{
	
	static String directoryName = "content_dir_prog_created";
	public static void main(String[] args){		
		System.out.println("Regular file operations......");
		create_directory_file();
		other_ops_directory_file();
		//retrieve_path_information();
		get_set_attributes();

		System.out.println();
		System.out.println("DirectoryStream Checks.......");
		apply_directory_stream();

		System.out.println();
		System.out.println("File Visitor Checks........");
		file_visitor_sample fvisitor = new file_visitor_sample();
		try{
			Files.walkFileTree(Paths.get(directoryName), fvisitor);
		} catch(IOException e) { System.out.println("Files.walkFileTree IOException"); 	}

		System.out.println();
		System.out.println("Path Matcher Checks......");
		path_matcher_ops();
	}
	
	static void path_matcher_ops(){
		Path path1 = Paths.get(directoryName, "content_dir_nio_1");
		Path path2 = Paths.get("content_dir_prog_created\\content_dir_nio_1");
		path_matcher_matches(path1, "glob:content*");
		path_matcher_matches(path1, "glob:content**");
		path_matcher_matches(path1, "glob:**nio*");
		path_matcher_matches(path2, "glob:content*");
		path_matcher_matches(path2, "glob:content**");
		path_matcher_matches(path2, "glob:**nio*");
	}

	static void path_matcher_matches(Path path, String glob){
		PathMatcher pathMatcher = FileSystems.getDefault().getPathMatcher(glob);
		System.out.println(path.toString() + ", " + glob + " : " + pathMatcher.matches(path));
	}

	static void create_directory_file(){
		try{
			Path dirPath = Paths.get(directoryName);
			if(!Files.exists(dirPath)) Files.createDirectory(dirPath);
			Path filePath = Paths.get(directoryName,"content_file_nio_1.txt");
			if(!Files.exists(filePath)) Files.createFile(filePath);
		} catch(IOException e){}
	}

	static void other_ops_directory_file(){
		Path sourceDir = Paths.get(directoryName, "content_dir_nio_1");
		Path targetDir = Paths.get(directoryName, "content_dir_nio_2");
		Path sourceFile = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_1.txt");
		Path targetFile = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_2.txt");
		
		try{
			Files.deleteIfExists(sourceFile);
			Files.deleteIfExists(targetFile);
			Files.deleteIfExists(sourceDir);
			Files.deleteIfExists(targetDir);
			
			Files.createDirectories(sourceDir);
			Files.createFile(sourceFile);
			
			Files.copy(sourceFile, targetFile);
			Files.copy(sourceFile, targetFile, StandardCopyOption.REPLACE_EXISTING);//Files.copy(sourceFile, targetFile); //exception expected
			Files.copy(sourceDir, targetDir); //Doesn't copy files in the directory, only directory file is created.
			Files.copy(sourceDir, targetDir, StandardCopyOption.REPLACE_EXISTING);
		} 
		catch(Exception e){
			System.out.println("Exception Message: " + e.getMessage());
		}
		finally{
	/*		try{
			Files.deleteIfExists(sourceFile);
			Files.deleteIfExists(targetFile);
			Files.deleteIfExists(sourceDir);
			Files.deleteIfExists(targetDir);
			} 
			catch(IOException e) { 
				System.out.println("IO Exception Message: " + e.getMessage());
			}*/
		}
	}

	static void retrieve_path_information(){
		Path path = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_1.txt");
		System.out.println("Path getFileName() : " + path.getFileName());
		System.out.println("Path getName(ind) : " + path.getName(1));
		System.out.println("Path getNameCount() : " + path.getNameCount());
		System.out.println("Path getParent() : " + path.getParent());
		System.out.println("Path getRoot() : " + path.getRoot());
		System.out.println("Path subPath(0,2) : " + path.subpath(0,2));
		System.out.println("Path toString() : " + path.toString());
		System.out.println("Path normalize() : " + Paths.get(directoryName, "content_dir_nio_1", "..").normalize());
		System.out.println("Path normalize() : " + Paths.get(directoryName, "..", "..").normalize());

		System.out.println();
		System.out.println();

		int spaces = 1;
		for(Path subPath : path){
			System.out.format("%" + spaces + "s%s%n", "", subPath);
			spaces += 2;
		}
	}

	static void get_set_attributes(){
		try{
			Path filePath = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_1.txt");
			System.out.println(Files.getLastModifiedTime(filePath));
			Thread.sleep(100);
			Date januaryFirst = new GregorianCalendar(2013, Calendar.JANUARY, 1).getTime();
			FileTime fileTime = FileTime.fromMillis(januaryFirst.getTime());
			Files.setLastModifiedTime(filePath, fileTime);
			System.out.println(Files.getLastModifiedTime(filePath));
			System.out.println("IsReadable: " + Files.isReadable(filePath));
			System.out.println("IsWritable: " + Files.isWritable(filePath));
			System.out.println("IsExecutable: " + Files.isExecutable(filePath));
			access_basic_file_attributes();
			access_posix_file_attributes();
		}
		catch(InterruptedException e){}
		catch(IOException e){}
	}

	static void access_basic_file_attributes(){
		try{
			Path filePath = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_1.txt");
			BasicFileAttributes basicAttrs = Files.readAttributes(filePath, BasicFileAttributes.class);
			System.out.println("create: " + basicAttrs.creationTime());
			System.out.println("access: " + basicAttrs.lastAccessTime());
			System.out.println("modify: " + basicAttrs.lastModifiedTime());
			System.out.println("directory: " + basicAttrs.isDirectory());

			FileTime now = FileTime.fromMillis(System.currentTimeMillis());
			BasicFileAttributeView basicAttrsView = Files.getFileAttributeView(filePath, BasicFileAttributeView.class);
			basicAttrsView.setTimes(basicAttrs.lastModifiedTime(), now, null); //Modified, Accessed, Created(null means dont change)
		} catch(IOException e){}
	}

	static void access_posix_file_attributes(){
		try{
			Path filePath = Paths.get(directoryName, "content_dir_nio_1", "content_file_nio_1.txt");
			PosixFileAttributes posix = Files.readAttributes(filePath, PosixFileAttributes.class);
			Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
			Files.setPosixFilePermissions(filePath, perms);
			System.out.println(posix.permissions());
			System.out.println(posix.group());
		} catch(IOException e){}
	}

	static void apply_directory_stream(){
		Path dirPath = Paths.get(directoryName);
		try(DirectoryStream<Path> stream = Files.newDirectoryStream(dirPath)){
			for(Path path: stream)
				System.out.println(path.getFileName());
		} catch(IOException e){}
	}
}
