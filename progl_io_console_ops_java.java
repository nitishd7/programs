import java.io.Console;

class progl_io_console_ops_java{

	public static void main(String[] args){
		console_basic_read_write();
	}

	static void console_basic_read_write(){
		String name = "";
		Console c = System.console();
		char[] pw;
		pw = c.readPassword("%s", "pw: ");
		for(char ch : pw)
			c.format("%c ", ch);
		c.format("\n");

		while(true){
			name = c.readLine("%s", "input?: ");
			c.format("output: %s \n", "result is " + name);
		}
	}
}
