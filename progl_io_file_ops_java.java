import java.io.*;

class progl_io_file_ops_java{

	static String directoryName;
	
	public static void main(String[] args){	
		create_directory();		

		//create_basic_file();
		//operation_using_writer_reader();
		operation_write_read_using_wrappers();
	}

	static void create_directory(){
		directoryName = "content_dir_prog_created";
		try{
			File file = new File(directoryName);
			file.mkdir();
		} catch(Exception e){}
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
}
