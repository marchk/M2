import java.net.*;
import java.io.*;
import java.util.*;

public class serveurTCP{
 
 	static ArrayList<Socket> members;
 	static HashMap<String,ArrayList<String>> announces;
 	static String man;
 	
 	
 	private static void initMan(){
	
		BufferedReader br = null;
		FileReader fr = null;

		try {
			br = new BufferedReader(new FileReader("../Docs/man.txt"));
			String sCurrentLine;
			man = "";

			while ((sCurrentLine = br.readLine()) != null) {
				man += sCurrentLine+"@";
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null)
					br.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}	
		}
	}

 	
 	
 	synchronized static void ajoute(String ad, String m){
 		announces.get(ad).add(m);
 	}
 	
 	
 	
	synchronized static void connect(Socket ad){
		String adr = ad.getInetAddress().toString();
		if(announces.get(adr)==null){		
			System.out.println(""+adr+" is connected !");
			announces.put(adr,new ArrayList<String>());
			members.add(ad);
		}
		
	}
	
	
	synchronized static void disconnect(Socket ad){
		members.remove(ad);
		String adr = ad.getInetAddress().toString();
		System.out.println(""+adr+" has left !");
		announces.remove(adr);
	}
	
	

	public static void main(String[] args){
		try{
			initMan();
			announces= new HashMap<String,ArrayList<String>>();
			members = new ArrayList<Socket>();
			ServerSocket server;
			if(args.length >1){return;}
			else if(args.length==1){ server=new ServerSocket(Integer.parseInt(args[0]));}
			else{ server=new ServerSocket(7777); }
			while(true){
				Socket socket=server.accept();
				connect(socket);
				servThread st = new servThread(socket);
				Thread t = new Thread(st);
				t.start();
			}
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}
}
