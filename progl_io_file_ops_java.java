import java.io.*;

class progl_io_file_ops_java{

	static String directoryName;
	
	public static void main(String[] args){	
		create_directory();		

		//create_basic_file();
		//operation_using_writer_reader();
		operation_write_read_using_wrappers();
		operation_rename_delete_file_dir();
	}

	static void create_directory(){
		directoryName = "content_dir_prog_created";
		try{
			File file = new File(directoryName);
			file.mkdir();
		} catch(Exception e){
			//no IOException thrown
		}
	}

	static void create_basic_file(){
		try{
			boolean newFile = false;
			File file = new File(directoryName, "content_file_prog_created.txt");
			System.out.println(file.exists());
			newFile = file.createNewFile();
			System.out.println(newFile);
			System.out.println(file.exists());
		} catch (IOException e){}
	}

	static void operation_using_writer_reader(){
		char[] in = new char[50];
		int size = 0;
		try{
			File file = new File(directoryName, "content_file_prog_created.txt");
			FileWriter fw = new FileWriter(file);
			fw.write("hello world\ntext completed\n");
			fw.flush();
			fw.close();
			
			FileReader fr = new FileReader(file);
			size = fr.read(in);
			System.out.print(size + " ");
			for(char c : in) 
				System.out.print(c);
			fr.close();
		} catch (IOException e){}
	}

	static void operation_write_read_using_wrappers(){
		String readString;
		try{
			File file = new File(directoryName, "content_file_prog_created.txt");
			PrintWriter pw = new PrintWriter(file);
			pw.println("Hello World");
			pw.println("Print Writer Testing");
			pw.println("Test Completed");
			pw.flush();
			pw.close();

			FileReader fr = new FileReader(file);
			BufferedReader br = new BufferedReader(fr);
			while((readString = br.readLine()) != null){
				System.out.print(readString + ", ");
			}
		} catch(IOException e){}
	}

	static void operation_rename_delete_file_dir(){
		try{
			File file = new File(directoryName, "content_file_prog_created.txt");
			File rfile = new File(directoryName, "content_file_prog_renamed.txt");
			file.renameTo(rfile);
			System.out.println("Renamed file exists " + file.exists());
			
			File ofile = new File(directoryName, "content_file_prog_created.txt");
			System.out.println("Does old file exists after rename " + ofile.exists());
			
			File dfile = new File(directoryName);
			System.out.println("Directory deletion with existing members " + dfile.delete() + "\n");
			
			for(File f : dfile.listFiles()){
				System.out.println(f.getName() + ", " + f.getCanonicalPath() + ", " + f.delete());
				System.out.println();
			}
		
			/*String[]entries = dfile.list();
			for(String s: entries){
			    File currentFile = new File(dfile.getPath(),s);
			    currentFile.delete();
			}*/
		
			//Thread.sleep(5000);
			for(File f : dfile.listFiles()){
				System.out.println(f.getName() + ", " + f.getCanonicalPath() + ", " + f.delete());
			}
			
			System.out.println("Directory deletion of an empty directory " + dfile.delete() + ", "  + dfile.exists() + ", " + dfile.list().length);
			System.out.println("Directory deletion of a non existing directory " + dfile.delete());
		} catch(Exception e){
			//no IOException thrown
			System.out.println("Exception thrown");
		}
	}
}
