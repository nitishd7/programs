import java.nio.file.*;
import java.nio.file.attribute.*;
import java.util.*;
import java.io.IOException;


class progl_nio_watch_service_java{
	static String directoryName = "content_dir_prog_created";
	public static void main(String[] args){
		Path path = Paths.get(directoryName);

		run_watch_service(path);
	}

	public static void run_watch_service(Path path){
		try{
			WatchService watcher = FileSystems.getDefault().newWatchService();
			path.register(watcher, StandardWatchEventKinds.ENTRY_DELETE);

			while(true){
				WatchKey key;
				try{
					key = watcher.take();
				} catch(InterruptedException x){ return; }
	
				for(WatchEvent<?> event: key.pollEvents()){
					WatchEvent.Kind<?> kind = event.kind();
					System.out.println(kind.name());
					System.out.println(kind.type());
					System.out.println(event.context());
					String name = event.context().toString();
					if(name.equals("content_dir_nio_2")){
						System.out.println("Directory deleted, start the operations");
					}
				}
				key.reset();
			}
		} catch (IOException e){}
	}
}
